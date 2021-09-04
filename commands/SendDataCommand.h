//
// Created by fali on 01/08/2021.
//

#ifndef EXASOL_SENDDATACOMMAND_H
#define EXASOL_SENDDATACOMMAND_H
#include <string>
#include <map>
#include "../Connection.h"
#include "Command.h"

class SendDataCommand : public Command {
private:
    Connection * connection;
    string data;

public:
    explicit SendDataCommand(Connection * connection, string data);
    ~SendDataCommand();
    bool apply(map<string, string> *context, string ** args, int num_args) override;
};


#endif //EXASOL_SENDDATACOMMAND_H
