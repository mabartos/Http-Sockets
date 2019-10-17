//
// Created by mabartos on 10/17/19.
//

#include "Errors.h"

void Errors::error(int statusCode, const string &message) {
    fprintf(stderr, "Error: %s\n", message.c_str());
    error(statusCode);
}

void Errors::error(int statusCode) {
    exit(statusCode);
}

