//
// Created by mabartos on 10/17/19.
//
#include "stdio.h"
#include "stdlib.h"
#include "client-core/ClientParser.h"
#include "client-core/Client.h"

int main(int argc, char **argv) {
    HttpRequest request;
    ClientParser parser(argc, argv, request);
    request = parser.getRequest();
    Client client;
    client.run();

}

