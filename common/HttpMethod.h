//
// Created by mabartos on 10/17/19.
//

#ifndef ISA_HTTPMETHOD_H
#define ISA_HTTPMETHOD_H

#include "string"

using namespace std;

enum HttpMethods {
    GET,
    POST,
    PUT,
    DELETE
};

typedef enum HttpMethods HttpMethod;

/*

class HttpMethod {
public:
    static const string GET;
    static const string POST;
    static const string PUT;
    static const string DELETE;
};

 */

#endif //ISA_HTTPMETHOD_H
