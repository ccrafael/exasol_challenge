//
// Created by fali on 01/08/2021.
//
#include "NetworkConnection.h"

NetworkConnection::NetworkConnection(string addr, int port, string cert_path, string key_path) {
    this->address = addr;
    this->port = port;
    this->cert_path = cert_path;
    this->key_path = key_path;

    this->initSSL_CTX();
}

void NetworkConnection::initSSL_CTX() {

    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    const SSL_METHOD *method = TLS_client_method();
    this->ctx = SSL_CTX_new(method);

    if (this->ctx == nullptr) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    cout << "SSL context initialized" << endl;

    if (SSL_CTX_use_certificate_file(ctx, cert_path.c_str(), SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        abort();
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, key_path.c_str(), SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        abort();
    }

    cout << "Cert & key loaded" << endl;

    // verify private key
    if (!SSL_CTX_check_private_key(ctx)) {
        fprintf(stderr, "Private key does not match the public certificate\n");
        abort();
    }
}

void ShowCerts(SSL *ssl) {
    X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl); /* get the server's certificate */
    if (cert != NULL) {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);       /* free the malloc'ed string */
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);       /* free the malloc'ed string */
        X509_free(cert);     /* free the malloc'ed certificate copy */
    } else
        printf("No certificates.\n");
}

void NetworkConnection::open_connection() {

    struct hostent *host;
    struct sockaddr_in addr;

    if ((host = gethostbyname(this->address.c_str())) == NULL) {
        perror(this->address.c_str());
        abort();
    }
    this->socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = *(long *) (host->h_addr);
    if (connect(this->socket_fd, (struct sockaddr *) &addr, sizeof(addr)) != 0) {
        close(this->socket_fd);
        perror(this->address.c_str());
        abort();
    }

    this->ssl = SSL_new(ctx);
    if (this->ssl == nullptr) {
        fprintf(stderr, "SSL_new() failed\n");
        exit(EXIT_FAILURE);
    }

    SSL_set_fd(ssl, socket_fd);
    if (SSL_connect(ssl) == FAIL) {
        ERR_print_errors_fp(stderr);
    } else {
        printf("Connected with %s encryption\n", SSL_get_cipher(ssl));
        ShowCerts(ssl);
    }
}


string NetworkConnection::read() {
    string line;
    char buff = 0;
    int received = 0;
    while (buff != '\n') {
        received = SSL_read(ssl, &buff, 1);
        switch (SSL_get_error(ssl, received)) {
            case SSL_ERROR_NONE: {
                line.push_back(buff);
                break;
            }
            case SSL_ERROR_ZERO_RETURN: {
                cout << "SSL_ERROR_ZERO_RETURN" << endl;
                break;
            }
            case SSL_ERROR_WANT_READ: {
                cout << "SSL_ERROR_WANT_READ" << endl;
                break;
            }
            case SSL_ERROR_WANT_WRITE: {
                cout << "SSL_ERROR_WANT_WRITE" << endl;
                break;
            }
            default: {
                throw "SSL problem";
            }
        }
    }
    return line;
}

void NetworkConnection::close_connection() {
    SSL_free(ssl);
    close(this->socket_fd);
    SSL_CTX_free(ctx);
}

void NetworkConnection::write(string data) {
    SSL_write(ssl, data.c_str(), data.length());
}
