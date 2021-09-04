#include <iostream>
#include "Client.h"
#include "NetworkConnection.h"
#include "DummyConnection.h"


int main() {

    char tmp[256];
    getcwd(tmp, 256);
    cout << "Current working directory: " << tmp << endl;

    // init global_seed
    srand((unsigned) time(NULL));

    // To test
    DummyConnection connection;

    /*NetworkConnection connection("18.202.148.130", 3336,
                                 "../crt.pem",
                                 "../key.pem");
    */
    Client client(&connection);

    cout << "Start" << endl;
    client.start();

    cout << "End" << endl;
    return 0;
}
