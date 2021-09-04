//
// Created by fali on 01/08/2021.
//

#ifndef EXASOL_UTILS_H
#define EXASOL_UTILS_H
#include <ctime>
#include <unistd.h>
#include <cstdlib>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

string to_hex(unsigned char *data, int len);
string sha1_digest(string data);

#endif //EXASOL_UTILS_H
