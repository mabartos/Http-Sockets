#include "stdio.h"
#include "stdlib.h"
#include "string"
#include "ctype.h"
#include "server-core/ServerParser.h"
#include <vector>
#include <stdexcept>


using namespace std;

int main(int argc, char **argv) {
    ServerParser parser(argc, argv);
    int port;
    if ((port=parser.getPort())!=0) {
        printf("%d\n", port);
    } else {
        printf("NOPE\n");
    }
    return 0;
}




