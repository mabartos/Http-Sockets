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
#include "../common/Errors.h"
#include "Client.h"

#define BUFFER_SIZE 1024

using namespace std;

Client::Client(string host, int port, string request) : host(move(host)), port(port), request(move(request)) {
}

void Client::run() {
    int sock = 0, valRead;
    struct sockaddr_in address;

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

    if (valRead < 0) {
        close(sock);
        Errors::error(EXIT_FAILURE, "Cannot read from socket!!");
    }
    printResponse(buffer);
    close(sock);
}

string Client::getHost() {
    return host;
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

        regex rgxParams("(.*): (.*)");
        smatch matches;
        if (regex_search(line, matches, rgxParams)) {
            if (matches.size() > 2) {
                string key = matches[1].str();
                string value = matches[2].str();

                if (key == "Content-Length") {
                    containsContent = true;
                }
                result.append(key).append(": ").append(value).append("\n");
                continue;
            }
        }

        if (containsContent && line == "\r") {
            int j = 0;
            bool nowContent = false;
            while (getline(stream, line)) {
                if (j == 0) {
                    if (line == "\r")
                        nowContent = true;
                    j++;
                    continue;
                }
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
