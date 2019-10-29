#include "stdio.h"
#include "stdlib.h"
#include "string"
#include "ctype.h"
#include "server-core/ServerParser.h"
#include "server-core/Server.h"
#include <vector>
#include <stdexcept>


using namespace std;

int main(int argc, char **argv) {
    ServerParser parser(argc, argv);
    Server server(parser.getPort());
    server.run();
    return 0;
}




