#include <utility>

//
// Created by mabartos on 10/17/19.
//

#include "HttpRequest.h"

using namespace std;


HttpRequest::HttpRequest() {
}

HttpMethod HttpRequest::getMethod() {
    return this->method;
}

string HttpRequest::getHost() {
    return this->host;
}

unsigned int HttpRequest::getPort() {
    return this->port;
}

string HttpRequest::getEndpoint() {
    return this->endpoint;
}

void HttpRequest::setPort(unsigned int reqPort) {
    this->port = reqPort;
}

void HttpRequest::setEndpoint(string reqEnd) {
    this->endpoint = move(reqEnd);
}

void HttpRequest::setHttpMethod(HttpMethod reqMethod) {
    this->method = reqMethod;
}

void HttpRequest::setHost(string reqHost) {
    this->host = move(reqHost);
}

string HttpRequest::toStr() {
    string result;
    switch (this->getMethod()) {
        case GET:
            result = "GET ";
            break;
        case POST:
            result = "POST ";
            break;
        case PUT:
            result = "PUT ";
            break;
        case DELETE:
            result = "DELETE ";
            break;
    }
    result.append(this->getEndpoint()).append(" ").append(this->httpVersion).append("\r\n");
    result.append("Host: ").append(this->getHost()).append("\r\n");
    result.append("Content-Type: ").append(this->contentType).append("\r\n");
    result.append("\r\n\r\n");

    if (!content.empty()) {
        result.append(this->getContent()).append("\r\n");
        result.append("\r\n\r\n");
    }

    return result;
}

string HttpRequest::getContent() {
    return this->content;
}

void HttpRequest::setContent(const string &con) {
    this->content = con;
}
