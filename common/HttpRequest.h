//
// Created by mabartos on 10/17/19.
//

#ifndef ISA_HTTPREQUEST_H
#define ISA_HTTPREQUEST_H

#include "string"
#include "HttpMethod.h"

using namespace std;

class HttpRequest {
private:
    string host = "";
    unsigned int port = 0;
    string endpoint = "";
    string content = "";
    HttpMethod method;
    string httpVersion = "HTTP/1.1";
    string contentType = "text/plain";

public:
    HttpRequest();

    ~HttpRequest() = default;

    void setHost(string host);

    void setPort(unsigned int port);

    void setEndpoint(string end);

    void setHttpMethod(HttpMethod method);

    string getHost();

    unsigned int getPort();

    string getEndpoint();

    string getContent();

    void setContent(const string &con);

    HttpMethod getMethod();

    string toStr();


};


#endif //ISA_HTTPREQUEST_H
