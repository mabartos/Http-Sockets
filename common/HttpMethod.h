//
// Created by mabartos on 10/17/19.
//

#ifndef ISA_HTTPMETHOD_H
#define ISA_HTTPMETHOD_H

#include "string"

using namespace std;

/**
 * Http Methods
 */
enum HttpMethods {
    GET,
    POST,
    PUT,
    DELETE,
    NONE
};

typedef enum HttpMethods HttpMethod;

#endif //ISA_HTTPMETHOD_H
