//
// Created by mabartos on 10/29/19.
//

#ifndef ISA_SERVER_H
#define ISA_SERVER_H

#include "vector"
#include "string"
#include "board/Boards.h"
#include "../common/HttpRequest.h"
#include "../common/HttpResponse.h"

using namespace std;

/**
 * Main class for Server side of app
 */
class Server {

private:
    int port;
    Boards boards;

    vector<string> getUrl(const string &endpoint);

public:
    /**
     * Constructor for server-side
     * @param port Port, where server listen
     */
    explicit Server(int port);

    ~Server() = default;

    /**
     * Start the server
     */
    void run();

    /**
     * Execute request and return Response
     * @param request
     * @param response
     * @return Generated Response from received request
     */
    HttpResponse &manageRequest(HttpRequest &request, HttpResponse &response);
};

#endif //ISA_SERVER_H
