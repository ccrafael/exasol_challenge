//
// Created by fali on 01/08/2021.
//

#include "DummyConnection.h"

string DummyConnection::read() {
    return this->commans[this->msg_num++ % 11];
}

