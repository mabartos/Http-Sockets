//
// Created by mabartos on 10/17/19.
//

#include "ClientParser.h"
#include <vector>
#include "string"
#include "regex"
#include "../common/Errors.h"
#include <bits/unique_ptr.h>


using namespace std;

void ClientParser::printHelp() {
    printf("HELP CLIENT\n");
}

ClientParser::ClientParser(int argc, char **argv, HttpRequest &req) : Parser(argc, argv), clientRequest(req) {
    parseArgs();
}

void ClientParser::parseArgs() {
    if (this->argc == 1)
        Errors::error(-1, "Wrong count of parameters!!");

    vector<string> vect;
    HttpRequest tmpRequest;


    for (int i = 1; i < this->argc; i++) {
        string item(this->argv[i]);
        vect.push_back(item);
    }

    if (vect.size() == 1 && vect.at(0) == "-h") {
        printHelp();
    } else if (vect.size() > 1 && vect.size() < 5) {
        Errors::error(-1, "Invalid Parameters");
    }

    this->clientRequest = createRequestFromVect(vect, tmpRequest);

}

HttpRequest &ClientParser::createRequestFromVect(const vector<string> &vect, HttpRequest &request) {
    if (vect.at(0) == "-H") {
        this->host = vect.at(1);
        request.setHost(vect.at(1));
        if (vect.at(2) == "-p") {
            this->serverPort = getValidPort(vect.at(3));
            request.setPort(this->serverPort);
            if (vect.at(4) == "boards") {
                printf("boards get\n");
                request.setHttpMethod(HttpMethod::GET);
                request.setEndpoint(createUrl({"boards"}));
                //TODO BOARDS GET
                return request;
            } else if (vect.size() > 6) {
                if (vect.at(4) == "board") {
                    if (vect.at(5) == "add") {
                        printf("boards add\n");
                        request.setHttpMethod(HttpMethod::POST);
                        request.setEndpoint(createUrl({"boards", vect.at(6)}));
                        return request;

                    } else if (vect.at(5) == "delete") {
                        printf("boards del\n");
                        request.setHttpMethod(HttpMethod::DELETE);
                        request.setEndpoint(createUrl({"boards", vect.at(6)}));
                        return request;

                    } else if (vect.at(5) == "list") {
                        printf("boards list\n");
                        request.setHttpMethod(HttpMethod::GET);
                        request.setEndpoint(createUrl({"board", vect.at(6)}));
                        return request;

                    }
                } else if (vect.at(4) == "item" && vect.size() > 7) {
                    if (vect.at(5) == "add") {
                        printf("item add\n");
                        request.setHttpMethod(HttpMethod::POST);
                        request.setEndpoint(createUrl({"board", vect.at(6)}));
                        request.setContent(vect.at(7));
                        return request;

                    } else if (vect.at(5) == "delete" && isValidNumber(vect.at(7), 0, INT32_MAX)) {
                        printf("item del\n");
                        request.setHttpMethod(HttpMethod::DELETE);
                        request.setEndpoint(createUrl({"board", vect.at(6), vect.at(7)}));

                        return request;

                    } else if (vect.at(5) == "update" && vect.size() > 8 && isValidNumber(vect.at(7), 0, INT32_MAX)) {
                        printf("item update\n");
                        request.setHttpMethod(HttpMethod::PUT);
                        request.setEndpoint(createUrl({"board", vect.at(6), vect.at(7)}));
                        request.setContent(vect.at(8));
                        return request;
                    }
                }
            }
        }
    }
    Errors::error(-1, "WRONG ARGUMENTS!!");
}

string ClientParser::getHost() {
    return this->host;
}

string ClientParser::createUrl(const vector<string> &urls) {
    string result = "/";
    if (urls.empty())
        return result;
    for (int i = 0; i < urls.size() - 1; i++) {
        result += urls.at(i) + "/";
    }
    result += urls.at(urls.size() - 1);
    return result;
}

HttpRequest &ClientParser::getRequest() {
    return this->clientRequest;
}


