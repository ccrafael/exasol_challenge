//
// Created by fali on 01/08/2021.
//

#include "EndCommand.h"

EndCommand::EndCommand(Connection *connection) {
    this->connection = connection;
}

EndCommand::~EndCommand() {}

bool EndCommand::apply(map<string, string> *context, string **args, int num_args) {
    this->connection->write("OK\n");

    return true;
}
