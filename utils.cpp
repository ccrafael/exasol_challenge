//
// Created by fali on 01/08/2021.
//

#include "utils.h"

string to_hex(unsigned char *data, int len) {
    stringstream ss;
    ss << std::hex;

    for (int i = 0; i < len; ++i) {
        ss << std::setw(2) << std::setfill('0') << (int) data[i];
    }

    return ss.str();
}

string sha1_digest(string data) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1((const unsigned char *) data.c_str(), data.length(), hash);
    return to_hex(hash, SHA_DIGEST_LENGTH);
}
