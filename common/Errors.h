//
// Created by mabartos on 10/17/19.
//

#ifndef ISA_ERRORS_H
#define ISA_ERRORS_H

#include "string"

using namespace std;

/**
 * Helper class for proper exit of system
 */
class Errors {
public:
    /**
     * Static error method, which exit program with statusCode and message
     * @param statusCode Status of exit
     * @param message   Message, which will be showed before exiting program
     */
    static void error(int statusCode, const string &message);

    /**
     * Static error method, which exit program with statusCode
     * @param statusCode Status of exit
     */
    static void error(int statusCode);

private:
    Errors() = default;

    ~Errors() = default;
};


#endif //ISA_ERRORS_H
