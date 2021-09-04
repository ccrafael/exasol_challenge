//
// Created by fali on 01/08/2021.
//
#include <iostream>
#include "SendDataCommand.h"
#include "../utils.h"

SendDataCommand::SendDataCommand(Connection *connction, string data) {
    this->connection = connction;
    this->data = data;
}

SendDataCommand::~SendDataCommand() {

}

bool SendDataCommand::apply(map<string, string> *context, string **args, int num_args) {
    if (num_args < 2) {
        throw "Wrong number of args";
    }

    auto it =  context->find("authdata");
    if (it != context->end()) {
        string authdata = it -> second;
        string arg1 = *args[1];

        cout << "arg1=" <<arg1 << endl;
        this->connection->write(sha1_digest(authdata + arg1) + " " + data + "\n");
    } else {
        throw "ERROR authdata not found in context.";
    }

    return false;
}
