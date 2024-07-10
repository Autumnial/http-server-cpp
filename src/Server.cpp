#include "Server.hpp"
#include <cstddef>
#include <cstring>
#include <iostream>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "ncurses.h"

bool should_close = false;

void *manual_close(void *sock_v) {
    initscr();
    nodelay(stdscr, false);
    printw("server starting...\n");
    refresh();

    int sock = *(int *)sock_v;

    int ch;
    ch = getch();

    printw("test");

    if (ch == 'q') {
        should_close = true;
        endwin();
        close(sock);
        exit(0);
    }
    return NULL;
}

Server::Server(in_port_t port) {
    this->sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock <= 0) {
        std::cout << "failure" << std::endl;
        exit(-1);
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(sock, (sockaddr *)&addr, sizeof(addr)) < 0) {
        std::cout << "binding failed" << std::endl;
        exit(-2);
    }
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
        std::cout << buff << std::endl;

        std::string buf(buff);

        if (buf.compare("close") == 0 || buf.compare("close\n") == 0) {
            shutdown(sock, SHUT_RDWR);
            close(sock);
            exit(0);
        }

        std::string messg = "OK";

        send(client, messg.c_str(), messg.length(), 0);

        close(client);
    }
}
