//
// Created by fali on 01/08/2021.
//
#include "HelloCommand.h"

HelloCommand::HelloCommand(Connection *connection) {
    this->connection = connection;
}

bool HelloCommand::apply(map<string, string> * context, string **args, int num_args) {
    this->connection->write("EHLO\n");
    return false;
}
