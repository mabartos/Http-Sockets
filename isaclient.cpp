//
// Created by mabartos on 10/17/19.
//
#include "stdio.h"
#include "stdlib.h"
#include "client-core/ClientParser.h"
#include "client-core/Client.h"

/**
 * Main function of Client side
 */
int main(int argc, char **argv) {
    // Create instance of Request
    HttpRequest request;
    // Parse the client arguments
    ClientParser parser(argc, argv, request);
    // Create client instance
    Client client(parser.getHost(), parser.getPort(), parser.getRequest().toStr());
    // Run the client
    client.run();
}