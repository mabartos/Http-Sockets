//
// Created by mabartos on 10/17/19.
//

#ifndef ISA_CLIENTPARSER_H
#define ISA_CLIENTPARSER_H

#include <vector>
#include "../common/Parser.h"
#include "../common/HttpRequest.h"

class ClientParser : public Parser {
private:

    string host;

    HttpRequest &createRequestFromVect(const vector<string> &vect, HttpRequest &request);

    HttpRequest &clientRequest;

    //string createUrl(const string urls[]);


public:
    ClientParser(int argc, char **argv, HttpRequest &req);

    static string createUrl(const vector<string> &urls);

    void printHelp() override;

    ~ClientParser() = default;

    void parseArgs() override;

    HttpRequest &getRequest();


    string getHost();

};


#endif //ISA_CLIENTPARSER_H
