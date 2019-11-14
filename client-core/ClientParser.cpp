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
    printf("\n******************************************\n");
    printf("Http Client - Martin Bartos - FIT VUT 3BIT \n");
    printf("****************************************** \n\n");
    printf("Run client : \n ./isaserver -H {HOST} -p {PORT} {COMMAND}\n\n");
    printf("{HOST} domain name, or IP address.\n");
    printf("{PORT} is port, where the server listen.\n");
    printf("{COMMAND} might be:\n");
    printf("-----------------------------------------------------------\n");
    printf("boards\t\t\t\t\t\t\t\tGET /boards\n"
           "board add <name>\t\t\t\t\tPOST /boards/<name>\n"
           "board delete <name>\t\t\t\t\tDELETE /boards/<name>\n"
           "board list <name>\t\t\t\t\tGET /board/<name>\n"
           "item add <name> <content>\t\t\tPOST /board/<name>\n"
           "item delete <name> <id>\t\t\t\tDELETE /board/<name>/<id>\n"
           "item update <name> <id> <content>\tPUT /board/<name>/<id>\n");
    printf("-----------------------------------------------------------\n\n");
    printf("Response Headers will be printed to 'STDERR'\n");
    printf("Response Body will be printed to 'STDOUT'\n\n");
    printf("See the server side :\n ./isaserver -h\n");
    printf("****************************************** \n");
}

ClientParser::ClientParser(int argc, char **argv, HttpRequest &req) : Parser(argc, argv), clientRequest(req) {
    parseArgs();
}

void ClientParser::parseArgs() {
    if (this->argc == 1)
        Errors::error(EXIT_FAILURE, "Wrong count of parameters!!");

    vector<string> vect;
    HttpRequest tmpRequest;


    for (int i = 1; i < this->argc; i++) {
        string item(this->argv[i]);
        vect.push_back(item);
    }

    if (vect.size() == 1 && vect.at(0) == "-h") {
        printHelp();
        exit(EXIT_SUCCESS);
    } else if (vect.size() > 1 && vect.size() < 5) {
        Errors::error(EXIT_FAILURE, "Invalid Parameters");
    }

    this->clientRequest = createRequestFromVect(vect, tmpRequest);

}

HttpRequest &ClientParser::createRequestFromVect(const vector<string> &vect, HttpRequest &request) {
    if (vect.at(0) == "-H" && vect.size() > 1) {
        this->host = vect.at(1);
        request.setHost(vect.at(1));
        if (vect.at(2) == "-p") {
            this->serverPort = getValidPort(vect.at(3));
            request.setPort(this->serverPort);
            if (vect.at(4) == "boards") {
                request.setHttpMethod(HttpMethod::GET);
                request.setEndpoint(createUrl({"boards"}));
                return request;
            } else if (vect.size() > 6) {
                if (vect.at(4) == "board") {
                    if (vect.at(5) == "add") {
                        request.setHttpMethod(HttpMethod::POST);
                        request.setEndpoint(createUrl({"boards", vect.at(6)}));
                        return request;

                    } else if (vect.at(5) == "delete") {
                        request.setHttpMethod(HttpMethod::DELETE);
                        request.setEndpoint(createUrl({"boards", vect.at(6)}));
                        return request;

                    } else if (vect.at(5) == "list") {
                        request.setHttpMethod(HttpMethod::GET);
                        request.setEndpoint(createUrl({"board", vect.at(6)}));
                        return request;

                    }
                } else if (vect.at(4) == "item" && vect.size() > 7) {
                    if (vect.at(5) == "add") {
                        request.setHttpMethod(HttpMethod::POST);
                        request.setEndpoint(createUrl({"board", vect.at(6)}));
                        request.setContent(vect.at(7));
                        return request;

                    } else if (vect.at(5) == "delete" && isValidNumber(vect.at(7), 0, INT32_MAX)) {
                        request.setHttpMethod(HttpMethod::DELETE);
                        request.setEndpoint(createUrl({"board", vect.at(6), vect.at(7)}));

                        return request;

                    } else if (vect.at(5) == "update" && vect.size() > 8 && isValidNumber(vect.at(7), 0, INT32_MAX)) {
                        request.setHttpMethod(HttpMethod::PUT);
                        request.setEndpoint(createUrl({"board", vect.at(6), vect.at(7)}));
                        request.setContent(vect.at(8));
                        return request;
                    }
                }
            }
        }
    }
    Errors::error(EXIT_FAILURE, "WRONG ARGUMENTS!!");
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


