#include "Server.hpp"
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    Server server(6970);
    server.run();

    return 0;
}
