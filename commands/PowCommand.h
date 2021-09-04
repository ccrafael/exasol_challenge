//
// Created by fali on 01/08/2021.
//

#ifndef EXASOL_POWCOMMAND_H
#define EXASOL_POWCOMMAND_H
#include <string>
#include <map>
#include "../Connection.h"
#include "Command.h"
#include <random>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <openssl/sha.h>
#include <thread>
#include <set>

#define DELTA 30.0
class PowCommand : public Command {
private:
    Connection * connection;
    bool found;
    string suffix;
    int num_threads;
    unsigned int global_seed;
    string charset;
    void find_prefix (int threadid, string authdata, int leading_zeros);

public:
    explicit PowCommand(Connection * connection, int num_threads);
    ~PowCommand();
    bool apply(map<string, string> *context, string ** args, int num_args) override;

};

#endif //EXASOL_POWCOMMAND_H
