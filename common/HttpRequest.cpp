#include <utility>

//
// Created by mabartos on 10/17/19.
//

#include "HttpRequest.h"
#include "Errors.h"
#include "Parser.h"

using namespace std;

HttpRequest::HttpRequest(const char *requestString) {
    string req(requestString);

    istringstream text(requestString);
    string line;
    bool init = true;

    while (getline(text, line)) {
        if (init) {
            // Regex for getting endpoint
            regex rgxHeader("(GET|POST|PUT|DELETE) /(.+) HTTP/1.1");
            smatch matches;
            if (regex_search(line, matches, rgxHeader)) {
                setHttpMethod(matches[1].str());
                setEndpoint(matches[2].str());
            } else {
                Errors::error(EXIT_FAILURE, "Bad request!!");
            }
            init = false;
            continue;
        }

        // Regex for getting properties of Http header
        regex rgxParams("(.*): (.*)");
        smatch matches;
        if (regex_search(line, matches, rgxParams)) {
            if (matches.size() > 2) {
                string key = matches[1].str();
                string value = matches[2].str();

                // Manage the props
                if (key == "Host") {
                    setHost(value);
                } else if (key == "Content-Type") {
                    this->contentType = value;
                } else if (key == "Content-Length") {
                    setContentLength(value);
                }
                continue;
            } else {
                Errors::error(EXIT_FAILURE, "Bad request!!");
            }
        }

        if (getContentLength() == 0)
            break;

        //If content is present
        regex rgxContent("(.+)");
        smatch contentMatches;
        if (regex_search(line, contentMatches, rgxContent)) {
            setContent(contentMatches[0].str());
        }
    }
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

void HttpRequest::setHttpMethod(const string &item) {
    if (item == "GET")
        this->method = HttpMethod::GET;
    else if (item == "POST")
        this->method = HttpMethod::POST;
    else if (item == "PUT")
        this->method = HttpMethod::PUT;
    else if (item == "DELETE")
        this->method = HttpMethod::DELETE;
    else
        Errors::error(EXIT_FAILURE, "Method not allowed");
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
    if (this->getMethod() == HttpMethod::POST || this->getMethod() == HttpMethod::PUT) {
        result.append("Content-Type: ").append(this->contentType).append("\r\n");
        result.append("Content-Length: ").append(to_string(this->content.size())).append("\r\n");
    }
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

int HttpRequest::getContentLength() {
    return this->contentLength;
}

void HttpRequest::setContentLength(int length) {
    if (length >= 0 && length <= INT32_MAX)
        this->contentLength = length;
}

void HttpRequest::setContentLength(const string &length) {
    if (Parser::isNumber(length)) {
        int number = strtol(length.c_str(), nullptr, 10);
        setContentLength(number);
    }
}
