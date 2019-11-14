//
// Created by mabartos on 10/29/19.
//
#include <utility>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <sstream>
#include <iostream>
#include <regex>
#include <netdb.h>
#include "../common/Errors.h"
#include "Client.h"

#define BUFFER_SIZE 1024

using namespace std;

Client::Client(string host, int port, string request) : host(move(host)), port(port), request(move(request)) {
}

void Client::run() {
    int sock = 0, valRead;
    struct sockaddr_in address{};
    struct addrinfo hintsHost{};
    struct addrinfo *hostResults = nullptr;

    char buffer[BUFFER_SIZE] = {0};

    // Create TCP Socket IPv4
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        Errors::error(EXIT_FAILURE, "Socket creation !!");
    }

    memset(&address, 0, sizeof(address));
    // IPv4
    address.sin_family = AF_INET;
    // Port
    address.sin_port = htons(port);

    memset(&hintsHost, 0, sizeof(hintsHost));
    // TCP
    hintsHost.ai_socktype = SOCK_STREAM;
    // IPv4
    hintsHost.ai_family = AF_INET;
    // specifies protocol for the returned socket address
    hintsHost.ai_protocol = 0;

    //TODO define
    hintsHost.ai_flags |= AI_CANONNAME;

    if (getaddrinfo((this->host).c_str(), nullptr, &hintsHost, &hostResults) != 0) {
        close(sock);
        Errors::error(EXIT_FAILURE, "Invalid Host!!");
    }

    // Get IPv4 address from hostname
    if (hostResults != nullptr) {
        struct sockaddr_in *saddr = (struct sockaddr_in *) hostResults->ai_addr;
        address.sin_addr = saddr->sin_addr;
        host = inet_ntoa(saddr->sin_addr);
        // Free all available hosts from memory
        freeaddrinfo(hostResults);
    } else {
        close(sock);
        Errors::error(EXIT_FAILURE, "Cannot find host IP!!");
    }

    // Connect to socket
    if (connect(sock, (struct sockaddr *) &address, sizeof(address)) < 0) {
        close(sock);
        Errors::error(EXIT_FAILURE, "Connection failed");
    }

    // Content cannot be bigger than BUFFER_SIZE
    if (request.size() >= BUFFER_SIZE) {
        close(sock);
        Errors::error(EXIT_FAILURE, "Request is too long!!");
    }

    // Send request to socket (server)
    send(sock, request.c_str(), request.size(), 0);

    // Read response from socket (server)
    valRead = read(sock, buffer, BUFFER_SIZE);

    if (valRead < 0) {
        close(sock);
        Errors::error(EXIT_FAILURE, "Cannot read from socket!!");
    }

    // Print response to standard outputs
    printResponse(buffer);

    // Close socket
    close(sock);
}

string Client::getHost() {
    return host;
}

string Client::getRequest() {
    return this->request;
}

int Client::getPort() {
    return port;
}

void Client::printResponse(char *buffer) {
    istringstream stream(buffer);
    string line;
    int i = 0;
    bool containsContent = false;
    string stdOut;
    string result;

    while (getline(stream, line)) {
        size_t pos = 0;

        if (i == 0) {
            result.append(line).append("\n");
            i++;
            continue;
        }

        //Get all header props key:value
        regex rgxParams("(.+): (.+)");
        smatch matches;
        if (regex_search(line, matches, rgxParams)) {
            if (matches.size() > 2) {
                string key = matches[1].str();
                string value = matches[2].str();

                // Parse Headers props
                if (key == "Content-Length") {
                    containsContent = true;
                }
                result.append(key).append(": ").append(value).append("\n");
                continue;
            }
        }

        // Get content from Response
        if (containsContent && line == "\r") {
            int j = 0;
            bool nowContent = false;
            while (getline(stream, line)) {
                // Here is decided, if the content will be parsed
                if (j == 0) {
                    if (line == "\r")
                        nowContent = true;
                    j++;
                    continue;
                }
                // Determine, whether the content is not empty
                if (nowContent && line != "\r") {
                    while ((pos = line.find('\\')) != std::string::npos) {
                        if (line.at(pos + 1) == 'n') {
                            string ss = line.substr(0, pos);
                            stdOut.append(ss).append("\n");
                            line.erase(0, pos + 2);
                        }
                    }
                    stdOut.append(line).append("\n");
                }
            }
        }
    }

    fprintf(stderr, "%s", result.c_str());
    if (containsContent)
        fprintf(stdout, "%s", stdOut.c_str());
}
