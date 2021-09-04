//
// Created by fali on 01/08/2021.
//

#ifndef EXASOL_NETWORK_CONNECTION_H
#define EXASOL_NETWORK_CONNECTION_H

#include <iostream>
#include <string>
#include <unistd.h>
#include <string.h>
#include <resolv.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <resolv.h>
#include <unistd.h>
#include  <netdb.h>

#include "Connection.h"
using namespace std;


#define FAIL    -1

class NetworkConnection : public Connection {
private:
    string address;
    int port;
    string cert_path;
    string key_path;
    int socket_fd;
    SSL *ssl;
    SSL_CTX *ctx;

    void initSSL_CTX();
public:
    NetworkConnection(string addr, int port, string cert_path, string key_path);
    string read() override;
    void write(string data) override;
    void open_connection() override;
    void close_connection() override;

};


#endif //EXASOL_NETWORK_CONNECTION_H
