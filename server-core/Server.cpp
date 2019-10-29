//
// Created by mabartos on 10/29/19.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../common/Errors.h"
#include "Server.h"


Server::Server(int port) : port(port) {
}

void Server::run() {

    int sockFd, newSocketFd, portNumber;
    socklen_t socketLength;
    char buffer[1024];
    struct sockaddr_in address;
    int n = 1;

    if ((sockFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        Errors::error(EXIT_FAILURE, "Creating a socket!");
    }

    //SOL,SO? n?
    if (setsockopt(sockFd, SOL_SOCKET, SO_REUSEPORT, &n, sizeof(n))) {
        Errors::error(EXIT_FAILURE, "Set Socket options!!");
    }

    address.sin_family = AF_INET;
    //TODO ANY?
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(sockFd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        Errors::error(EXIT_FAILURE, "Socket binding!!");
    }

    //TODO 5?
    if (listen(sockFd, 5) != 0) {
        Errors::error(EXIT_FAILURE, "Server listen !!");
    }

    if ((newSocketFd = accept(sockFd, (struct sockaddr *) &address, (socklen_t *) &socketLength)) < 0) {
        Errors::error(EXIT_FAILURE, "Server Accept!!");
    }

    n = read(newSocketFd, buffer, 1024);
    printf("%s\n", buffer);
    send(newSocketFd, "sdd", 4, 0);
    printf("Sent");

}
