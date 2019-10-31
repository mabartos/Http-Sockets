//
// Created by mabartos on 10/29/19.
//
#include <utility>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include "../common/Errors.h"
#include "Client.h"

#define BUFFER_SIZE 1024

using namespace std;

Client::Client(string host, int port, string request) : host(move(host)), port(port), request(move(request)) {
}

void Client::run() {
    int sock = 0, valRead;
    struct sockaddr_in address;

    string hello = "Hello from client";
    char buffer[BUFFER_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        Errors::error(EXIT_FAILURE, "Socket creation !!");
    }

    // IPv4
    address.sin_family = AF_INET;
    // Port
    address.sin_port = htons(port);

    if (host == "localhost") {
        host = "127.0.0.1";
    }

    // Convert IPv4 addresses from text to binary form
    if (inet_pton(AF_INET, host.c_str(), &address.sin_addr) <= 0) {
        Errors::error(EXIT_FAILURE, "Invalid Address !!");
    }

    if (connect(sock, (struct sockaddr *) &address, sizeof(address)) < 0) {
        Errors::error(EXIT_FAILURE, "Connection failed");
    }

    send(sock, request.c_str(), request.size(), 0);
    valRead = read(sock, buffer, BUFFER_SIZE);

    printf("%d\n", valRead);
    printf("%s\n", buffer);
    close(sock);
}

string Client::getHost() {
    return host;
}

int Client::getPort() {
    return port;
}
