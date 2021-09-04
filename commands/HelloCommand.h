//
// Created by fali on 01/08/2021.
//

#ifndef EXASOL_HELLOCOMMAND_H
#define EXASOL_HELLOCOMMAND_H

#include "Command.h"
#include "../Connection.h"

class HelloCommand : public Command {
private:
    Connection * connection;
public:
    explicit HelloCommand(Connection * connection);
    bool apply(map<string, string> *context, string ** args, int num_args) override;
};


#endif //EXASOL_HELLOCOMMAND_H
