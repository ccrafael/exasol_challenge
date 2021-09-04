//
// Created by fali on 01/08/2021.
//

#ifndef EXASOL_ENDCOMMAND_H
#define EXASOL_ENDCOMMAND_H
#include <string>
#include <map>
#include "../Connection.h"
#include "Command.h"

class EndCommand : public Command {
private:
    Connection * connection;

public:
    explicit EndCommand(Connection * connection);
    ~EndCommand();
    bool apply(map<string, string> *context, string ** args, int num_args) override;
};


#endif //EXASOL_ENDCOMMAND_H
