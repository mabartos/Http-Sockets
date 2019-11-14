//
// Created by mabartos on 10/17/19.
//

#ifndef ISA_HTTPREQUEST_H
#define ISA_HTTPREQUEST_H

#include "string"
#include <regex>
#include <sstream>
#include <iostream>
#include "HttpMethod.h"

using namespace std;

/**
 * Helper class for creating Http Request
 */
class HttpRequest {
private:
    string host = "";
    unsigned int port = 0;
    string endpoint = "";
    string content = "";
    HttpMethod method = HttpMethod::NONE;
    string httpVersion = "HTTP/1.1";
    string contentType = "text/plain";
    int contentLength = 0;

public:
    HttpRequest() = default;

    explicit HttpRequest(const char *requestString);

    ~HttpRequest() = default;

    void setHost(string host);

    void setPort(unsigned int port);

    void setEndpoint(string end);

    void setHttpMethod(HttpMethod method);

    void setHttpMethod(const string &reqMethod);

    string getHost();

    unsigned int getPort();

    string getEndpoint();

    string getContent();

    void setContent(const string &con);

    int getContentLength();

    void setContentLength(int length);

    void setContentLength(const string &length);

    HttpMethod getMethod();

    string toStr();
};


#endif //ISA_HTTPREQUEST_H
