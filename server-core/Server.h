//
// Created by mabartos on 10/29/19.
//

#ifndef ISA_SERVER_H
#define ISA_SERVER_H

#include "vector"
#include "string"
#include "board/Boards.h"

using namespace std;

class Server {

private:
    int port;
    Boards boards;

public:
    Server(int port);

    ~Server() = default;

    void run();
};


#endif //ISA_SERVER_H
