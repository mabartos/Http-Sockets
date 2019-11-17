CXX=g++
RM=rm -f
ISA_SERVER=isaserver
ISA_CLIENT=isaclient
.DEFAULT_GOAL := default

COMMON_SOURCES=common/Errors.cpp common/Parser.cpp common/Parser.h common/HttpRequest.cpp common/HttpMethod.h common/HttpResponse.cpp
SERVER_SOURCES=isaserver.cpp server-core/ServerParser.cpp server-core/ServerParser.h server-core/Server.cpp server-core/board/NoticeBoard.cpp server-core/board/Boards.cpp
CLIENT_SOURCES=isaclient.cpp client-core/ClientParser.cpp client-core/Client.cpp

OBJ_COMMON = $(COMMON_SOURCES:.cpp=.o)
OBJ_SERVER = $(SERVER_SOURCES:.cpp=.o)
OBJ_CLIENT = $(CLIENT_SOURCES:.cpp=.o)

$(ISA_SERVER): $(OBJ_COMMON) $(OBJ_SERVER)
	$(CXX) -o $(ISA_SERVER) $(OBJ_COMMON) $(OBJ_SERVER)

$(ISA_CLIENT): $(OBJ_COMMON) $(OBJ_CLIENT)
	$(CXX) -o $(ISA_CLIENT) $(OBJ_COMMON) $(OBJ_CLIENT)

.cpp.o:
	$(CC) -c $< -o $@

default: $(ISA_CLIENT)  $(ISA_SERVER)

all: default

clean:
	$(RM) *.o *~ *.gch $(ISA_SERVER) $(ISA_CLIENT)
	cd common/ && $(RM) *.o *~ *.gch
	cd server-core/ && $(RM) *.o *~ *.gch
	cd server-core/board && $(RM) *.o *~ *.gch
	cd client-core/ && $(RM) *.o *~ *.gch





