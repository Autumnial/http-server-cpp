#include "Server.hpp"
#include <cerrno>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <pthread.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>
#include "Enums.hpp"
#include "Request.hpp"
#include "ncurses.h"

void *manual_close(void *sock_v) {
    bool should_close = false;
    initscr();
    nodelay(stdscr, false);
    printw("server starting...\n");
    refresh();

    int sock = *(int *)sock_v;

    while (!should_close) {

        int ch;
        ch = getch();

        if (ch == 'q') {
            should_close = true;
        }
    }

    endwin();
    close(sock);
    exit(0);
    return NULL;
}

Server::Server(in_port_t port) {
    this->sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock <= 0) {
        std::cout << std::strerror(errno) << std::endl;
        exit(-1);
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(sock, (sockaddr *)&addr, sizeof(addr)) < 0) {
        std::cout << std::strerror(errno) << std::endl;
        exit(-2);
    }
}

Request Server::parse_request(std::string req_str) {

    Request req;

    int carriage_return = req_str.find('\r');
    int newline = req_str.find('\n');

    std::string header;

    if (carriage_return != std::string::npos) {
        header = req_str.substr(0, carriage_return);
        req_str = req_str.substr(newline + 1);
    } else {
        header = req_str.substr(0, newline);
        req_str = req_str.substr(newline + 1);
    }

    int         space = header.find(' ');
    std::string method = header.substr(0, space);
    header = header.substr(space + 1);

    space = header.find(' ');
    std::string path = header.substr(0, space);
    std::string http = header.substr(space + 1);

    req.method = method_from_string(method); 
    req.path = path; 
    // parse headers
    //

    std::cout << method << "\r\n";
    std::cout << path << "\r\n";
    std::cout << http << "\r\n";

    return req;
}

void Server::run() {

    pthread_t input_thread;
    pthread_create(&input_thread, NULL, manual_close, &sock);

    listen(sock, 10);

    while (true) {

        // handle connection
        int client;
        client = accept(sock, NULL, NULL);

        if (client == -1) {
            std::cout << "failed to bind \n";
            std::cout << strerror(errno) << std::endl;
            close(sock);
            exit(-3);
        }

        char buff[4096] = {0};
        recv(client, &buff, 4096, 0);

        std::string buf(buff);

        Request req = parse_request(buf);

        std::string messg = "HTTP/1.1 200 OK\nConnection: close\n\nhaii ^w^"; 

        send(client, messg.c_str(), messg.length(), 0);
        
        close(client);
    }
}
