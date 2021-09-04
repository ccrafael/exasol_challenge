//
// Created by fali on 29/07/2021.
//

#ifndef EXASOL_COMMAND_H
#define EXASOL_COMMAND_H
#include <string>
#include <map>

using namespace std;

class Command {
public:
    virtual bool apply(map<string, string> * context, string ** args, int num_args) = 0;
};


#endif //EXASOL_COMMAND_H
