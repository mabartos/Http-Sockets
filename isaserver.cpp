#include "stdio.h"
#include "stdlib.h"
#include "string"
#include "ctype.h"
#include "server-core/ServerParser.h"
#include "server-core/Server.h"
#include <vector>
#include <stdexcept>

using namespace std;

/**
 * Main function of Server side
 */
int main(int argc, char **argv) {
    // Create instance of Server Parser
    ServerParser parser(argc, argv);
    // Parse the server arguments
    Server server(parser.getPort());
    // Start the server
    server.run();
    return 0;
}




