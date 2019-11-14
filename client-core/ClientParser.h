//
// Created by mabartos on 10/17/19.
//

#ifndef ISA_CLIENTPARSER_H
#define ISA_CLIENTPARSER_H

#include <vector>
#include "../common/Parser.h"
#include "../common/HttpRequest.h"

/**
 * Parse client args from CLI
 */
class ClientParser : public Parser {
private:

    string host;

    /**
     * Create Request from System arguments
     * @param vect  Vector of arguments
     * @param request   Request, which will be returned
     * @return  Http Request
     */
    HttpRequest &createRequestFromVect(const vector<string> &vect, HttpRequest &request);

    HttpRequest &clientRequest;

public:
    /**
     * Constructor of Client Parser
     * @param argc  Count of arguments
     * @param argv  System arguments
     * @param req
     */
    ClientParser(int argc, char **argv, HttpRequest &req);

    /**
     * Create url from vector of arguments
     * @param urls vector of arguments
     * @return URL
     */
    static string createUrl(const vector<string> &urls);

    /**
     * Print help
     */
    void printHelp() override;

    ~ClientParser() = default;

    /**
     * Parse arguments
     */
    void parseArgs() override;

    /**
     * Get generated request from args
     * @return
     */
    HttpRequest &getRequest();

    /**
     * Get Hostname or IPv4
     */
    string getHost();
};
#endif //ISA_CLIENTPARSER_H
