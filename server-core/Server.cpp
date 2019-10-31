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
#include "../common/HttpResponse.h"
#include "../common/Parser.h"

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
        HttpResponse response;
        response = manageRequest(request, response);

        send(newSocketFd, response.toStr().data(), response.toStr().size(), 0);
        close(newSocketFd);
    }
}

//TODO verify find functions
HttpResponse &Server::manageRequest(HttpRequest &request, HttpResponse &response) {
    vector<string> endpoints = getUrl(request.getEndpoint());
    int endCount = endpoints.size();

    switch (request.getMethod()) {
        case GET:
            if (endCount > 0 && endpoints.at(0) == "boards") {
                string namesBoards = boards.getNamesAllBoards();
                if (!namesBoards.empty()) {
                    response.setStatusCode(200);
                    response.setStatus("OK");
                    response.setContent(namesBoards);
                    break;
                }
            } else if (endCount > 1 && endpoints.at(0) == "board") {
                string name = endpoints.at(1);
                if (!name.empty() && boards.existsBoard(name)) {
                    response.setStatusCode(200);
                    response.setStatus("OK");
                    response.setContent(boards.getBoard(name).getAllContent());
                    break;
                }
            }
            response.setStatusCode(404);
            response.setStatus("Not Found");
            break;
        case POST:
            if (endCount > 1) {
                if (endpoints.at(0) == "boards") {
                    string name = endpoints.at(1);
                    if (boards.existsBoard(name)) {
                        response.setStatusCode(409);
                        response.setStatus("Conflict");
                        break;
                    } else if (boards.createBoard(name)) {
                        response.setStatusCode(201);
                        response.setStatus("Created");
                        break;
                    }
                } else if (endpoints.at(0) == "board") {
                    string name = endpoints.at(1);
                    if (boards.existsBoard(name)) {
                        if (request.getContentLength() == 0) {
                            response.setStatusCode(400);
                            response.setStatus("Bad Request");
                            break;
                        }
                        boards.getBoard(name).addItem(request.getContent());
                        response.setStatusCode(201);
                        response.setStatus("Created");
                        break;
                    }
                }
            }
            response.setStatusCode(404);
            response.setStatus("Not Found");
            break;
        case PUT:
            if (endCount > 2 && endpoints.at(0) == "board") {
                string name = endpoints.at(1);
                string idString = endpoints.at(2);

                if (boards.existsBoard(name) && Parser::isNumber(idString)) {
                    if (request.getContentLength() == 0) {
                        response.setStatusCode(400);
                        response.setStatus("Bad Request");
                        break;
                    }
                    int id = strtol(idString.c_str(), nullptr, 10);
                    if (boards.getBoard(name).changeItemContent(id, request.getContent()))
                        break;
                }
            }
            response.setStatusCode(404);
            response.setStatus("Not Found");
            break;
        case DELETE:
            if (endCount > 1) {
                if (endpoints.at(0) == "boards") {
                    string name = endpoints.at(1);
                    if (boards.existsBoard(name) && boards.deleteBoard(name)) {
                        response.setStatusCode(200);
                        response.setStatus("OK");
                        break;
                    }
                } else if (endCount > 2 && endpoints.at(0) == "board") {
                    string name = endpoints.at(1);
                    string idString = endpoints.at(2);

                    if (boards.existsBoard(name) && Parser::isNumber(idString)) {
                        int id = strtol(idString.c_str(), nullptr, 10);
                        if (boards.getBoard(name).removeItem(id))
                            break;
                    }
                }
            }
            response.setStatusCode(404);
            response.setStatus("Not Found");
            break;
        case NONE:
            response.setStatusCode(404);
            response.setStatus("Not Found");
            break;
    }
    return response;
}

vector<string> Server::getUrl(const string &endpoint) {
    vector<string> result;
    string end = endpoint;
    if (!end.empty()) {
        size_t pos = 0;

        while ((pos = end.find('/')) != std::string::npos) {
            string token = end.substr(0, pos);
            result.push_back(token);
            end.erase(0, pos + 1);
        }
        result.push_back(end);
    }
    return result;
}
