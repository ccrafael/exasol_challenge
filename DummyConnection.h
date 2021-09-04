//
// Created by fali on 01/08/2021.
// Used to test
//

#ifndef EXASOL_DUMMY_CONNECTION_H
#define EXASOL_DUMMY_CONNECTION_H

#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <cstdlib>
#include <fcntl.h>
#include <sys/shm.h>

#include "Connection.h"
using namespace std;

class DummyConnection : public Connection {
private:
    int msg_num = 0;
    string commans[11] = {"HELO",
                          "POW igVVemrGZlPSlAKvJJtwXmWcOJVtzDpxsvlPsIPPlzjdCOutuPxxsmoHlagZsPZd 9",
                         "NAME arg1",
                         "MAILNUM arg1",
                         "MAIL1 arg1",
                         "SKYPE arg1",
                         "BIRTHDATE arg1",
                         "COUNTRY arg1",
                         "ADDRNUM arg1",
                         "ADDRLINE1 arg1",
                         "END"};

public:
    DummyConnection() = default;;
    string read() override;

    void write(string data) override {};
    void open_connection() override {};
    void close_connection() override{};

};

#endif //EXASOL_DUMMY_CONNECTION_H
