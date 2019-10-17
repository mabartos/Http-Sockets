//
// Created by mabartos on 10/17/19.
//
#include "stdio.h"
#include "stdlib.h"
#include "client-core/ClientParser.h"

int main(int argc, char **argv) {
    HttpRequest request;
    ClientParser parser(argc, argv, request);
    request = parser.getRequest();
    printf("-------------------\n");
    printf("%s\n", request.toStr().c_str());
    printf("-------------------\n");
    
}

