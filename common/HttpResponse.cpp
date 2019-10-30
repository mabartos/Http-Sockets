//
// Created by mabartos on 10/30/19.
//

#include "HttpResponse.h"

string HttpResponse::toStr() {
    string result;

    result.append(this->httpVersion)
            .append(" ")
            .append(to_string(this->statusCode))
            .append(" ")
            .append(status)
            .append("\r\n");

    if (getContentLength() != 0) {
        result.append("Content-Type: ").append(this->contentType).append("\r\n");
        result.append("Content-Length: ").append(to_string(getContentLength())).append("\r\n");

    }
    result.append("\r\n\r\n");

    if (getContentLength() != 0) {
        result.append(this->getContent()).append("\r\n");
        result.append("\r\n\r\n");
    }
    return result;
}

void HttpResponse::setContent(const string &cont) {
    this->content = cont;
}

string HttpResponse::getContent() {
    return this->content;
}

string HttpResponse::getContentType() {
    return this->contentType;
}

int HttpResponse::getContentLength() {
    return this->content.size();
}

int HttpResponse::getStatusCode() {
    return this->statusCode;
}

string HttpResponse::getStatus() {
    return this->status;
}

void HttpResponse::setStatus(const string &statusPhrase) {
    this->status = statusPhrase;
}

void HttpResponse::setStatusCode(int codeStatus) {
    this->statusCode = codeStatus;
}

string HttpResponse::getHttpVersion() {
    return this->httpVersion;
}

void HttpResponse::setHttpVersion(const string &version) {
    this->httpVersion = version;
}
