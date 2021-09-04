//
// Created by fali on 01/08/2021.
//

#ifndef CONNECTION_H
#define CONNECTION_H
#include <string>


using namespace  std;

class Connection {
public:
    Connection()= default;
    virtual ~Connection() = default;

    virtual string read() = 0;
    virtual void write(string data) = 0;
    virtual void open_connection() = 0;
    virtual void close_connection() = 0;
};

#endif //CONNECTION_H
