//
// Created by mabartos on 10/29/19.
//

#ifndef ISA_CLIENT_H
#define ISA_CLIENT_H

#include "string"

using namespace std;

class Client {
private:
    string host;
    int port;
    string request;

public:
    Client(string host, int port, string request);

    ~Client() = default;

    void run();

    string getHost();

    int getPort();

    string getRequest();
};


#endif //ISA_CLIENT_H
