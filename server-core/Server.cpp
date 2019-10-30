//
// Created by mabartos on 10/29/19.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "../common/Errors.h"
#include "Server.h"
#include "../common/HttpRequest.h"

#define BUFFER_SIZE 1024

Server::Server(int port) : port(port) {
}

void Server::run() {

    int sockFd, newSocketFd;
    socklen_t socketLength;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in address;
    int n = 1;

    if ((sockFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        Errors::error(EXIT_FAILURE, "Creating a socket!");
    }

    // SOL - SocketLevel
    // SO_REUSEPORT and SO_REUSEADDR allows defining same port(but not same address) on the both side of sockets.
    // n - optval is used to access option values for setsockopt
    if (setsockopt(sockFd, SOL_SOCKET, SO_REUSEPORT | SO_REUSEADDR, &n, sizeof(n))) {
        Errors::error(EXIT_FAILURE, "Set Socket options!!");
    }

    // IPv4
    address.sin_family = AF_INET;
    // Bind to all interfaces
    address.sin_addr.s_addr = INADDR_ANY;
    // Port
    address.sin_port = htons(port);

    if (bind(sockFd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        Errors::error(EXIT_FAILURE, "Socket binding!!");
    }

    // SOMAXCONN - the maximum length that the queue of pending connections may grow to
    // the underlying service provider responsible for socket 'sockFd' sets the backlog to a maximum "reasonable" value.
    if (listen(sockFd, SOMAXCONN) != 0) {
        Errors::error(EXIT_FAILURE, "Server listen !!");
    }


    while (true) {
        if ((newSocketFd = accept(sockFd, (struct sockaddr *) &address, (socklen_t *) &socketLength)) < 0) {
            Errors::error(EXIT_FAILURE, "Server Accept!!");
        }

        bzero(buffer, BUFFER_SIZE);
        n = read(newSocketFd, buffer, BUFFER_SIZE);
        if (n < 0) {
            close(newSocketFd);
            close(sockFd);
            Errors::error(EXIT_FAILURE, "Cannot read from socket!!");
        }
        HttpRequest request(buffer);

        printf("%s\n", request.getContent().c_str());
        string message("sdd\n");
        send(newSocketFd, message.c_str(), sizeof(message.c_str()), 0);
        close(newSocketFd);

    }


}
