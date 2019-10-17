//
// Created by mabartos on 10/17/19.
//

#ifndef ISA_ERRORS_H
#define ISA_ERRORS_H

#include "string"

using namespace std;

class Errors {
public:
    static void error(int statusCode, const string &message);

    static void error(int statusCode);

private:
    Errors() = default;

    ~Errors() = default;
};


#endif //ISA_ERRORS_H
