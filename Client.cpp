//
// Created by fali on 29/07/2021.
//
#include "Client.h"
#include <regex>
#include "commands/HelloCommand.h"
#include "commands/PowCommand.h"
#include "commands/EndCommand.h"
#include "commands/SendDataCommand.h"
#include <iostream>

Client::Client(Connection * connection) {
    this->connection = connection;

    this->commands.emplace("HELO", new HelloCommand(connection));
    this->commands.emplace("END", new EndCommand(connection));
    this->commands.emplace("POW", new PowCommand(connection, 24));
    this->commands.emplace("NAME", new SendDataCommand(connection, "Rafael Campaña"));
    this->commands.emplace("MAILNUM", new SendDataCommand(connection, "1"));
    this->commands.emplace("MAIL1", new SendDataCommand(connection, "racampce@gmail.com"));
    this->commands.emplace("SKYPE", new SendDataCommand(connection, "N/A"));
    this->commands.emplace("BIRTHDATE", new SendDataCommand(connection, "29.04.1981"));
    this->commands.emplace("COUNTRY", new SendDataCommand(connection, "Spain"));
    this->commands.emplace("ADDRNUM", new SendDataCommand(connection, "1"));
    this->commands.emplace("ADDRLINE1", new SendDataCommand(connection, "Malaga, Malaga, Joaquin Turina, 17, 7, B"));
}

void tokens(string line, string **args, int *n) {
    regex rgx("\\s+");
    sregex_token_iterator iter(line.begin(), line.end(), rgx, -1);
    sregex_token_iterator end;
    int i = 0;
    for (; iter != end; ++iter) {
        if (i >> MAX_ARGS) {
            throw "Command with too much args";
        }
        // clone the token as a new string
        args[i] = new string(*iter);
        i++;
    }
    *n = i;
}

void free_args(string ** args, int n) {
    for (int i = 0; i < n; ++i) {
        delete args[i];
    }
}

void Client::start() {
    try {
        this->connection->open_connection();
    } catch (const char *e){
        throw "Not posible to open conn.";
    }

    bool end = false;
    int error_count = 0;
    auto **args = (string **) malloc(sizeof (string**) * MAX_ARGS);

    while (!end) {
        string line = this->connection->read();
        int num_args = 0;

        // max args to MAX_ARGS
        tokens(line, args, &num_args);

        try {
            end = process_cmd(args, num_args);
            error_count = 0;
        } catch (char const* e) {
            error_count++;
            cerr << e << endl;
        }
        free_args(args, num_args);

        if (error_count > MAX_ERRORS) {
            cout << "Finish connection with server because too much errors."<< endl;
            break;
        }
    }

    delete args;
}

bool Client::process_cmd(string **args, int num_args) {
    auto it = this->commands.find(*args[0]);
    if (it != this->commands.end()) {
        cout <<"Execute command=["<< *args[0] << "]" << endl;
        return it->second->apply(&this->context, args, num_args);
    } else {
        throw "Error, command not found";
    }
}

Client::~Client() {
    this->connection->close_connection();
    delete this->connection;
}