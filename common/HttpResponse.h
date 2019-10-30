//
// Created by mabartos on 10/30/19.
//

#ifndef ISA_HTTPRESPONSE_H
#define ISA_HTTPRESPONSE_H

#include "string"

using namespace std;

class HttpResponse {
private:
    int statusCode;
    string status;
    string httpVersion = "HTTP/1.1";
    string contentType = "text/plain";
    string content = "";
    int contentLength = 0;

public:
    HttpResponse() = default;

    ~HttpResponse() = default;

    string toStr();

    void setContent(const string &content);

    string getContent();

    string getContentType();

    int getContentLength();

    int getStatusCode();

    string getStatus();

    void setStatus(const string &statusPhrase);

    void setStatusCode(int statusCode);

    string getHttpVersion();

    void setHttpVersion(const string &version);
};


#endif //ISA_HTTPRESPONSE_H
