//
// Created by fali on 29/07/2021.
//

#ifndef EXASOL_CLIENT_H
#define EXASOL_CLIENT_H
#include <string>
#include <map>
#include "Connection.h"
#include "commands/Command.h"

using namespace std;

#define MAX_ARGS 16
#define MAX_ERRORS 10

class Client {
private:
    Connection * connection;
    std::map<string, Command*> commands;
    std::map<string, string> context;

    bool process_cmd(string **args, int num_args);

public:
    Client(Connection * connection);
    ~Client();

    void start();

};


#endif //EXASOL_CLIENT_H
