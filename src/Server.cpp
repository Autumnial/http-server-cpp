#include "Server.hpp"
#include <algorithm>
#include <array>
#include <cerrno>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <pthread.h>
#include <queue>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>
#include "Enums.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "ncurses.h"
typedef Response *(*Route)(Request);

const int NUM_THREADS = 10;
const int REQ_BUF = 8096;

std::queue<int> connection_queue;
pthread_mutex_t connection_queue_mutex;
pthread_cond_t  connection_queue_not_empty;

std::map<std::string, Route> *routes_p;

void handle_connection(int client);

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

void *await_connection(void *_) {

    while (true) {

        pthread_mutex_lock(&connection_queue_mutex);
        while (connection_queue.size() == 0) {
            pthread_cond_wait(&connection_queue_not_empty,
                              &connection_queue_mutex);
        }

        int client = connection_queue.front();
        connection_queue.pop();

        pthread_mutex_unlock(&connection_queue_mutex);

        handle_connection(client);
    }

    return NULL;
}

Response *not_found() {
    auto r = Response::create_response()->set_statusCode(StatusCode::NOT_FOUND);
    return r;
}

void Server::add_route(std::string route, Route func) {
    routes.insert({route, func});
};

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

Request parse_request(std::string req_str) {

    std::cout << req_str << "\r\n\r\n";

    Request req;

    int newline = req_str.find('\n');

    std::string request_line;

    request_line = req_str.substr(0, newline);
    req_str = req_str.substr(newline + 1);

    int         space = request_line.find(' ');
    std::string method = request_line.substr(0, space);
    request_line = request_line.substr(space + 1);

    space = request_line.find(' ');
    std::string path = request_line.substr(0, space);
    std::string http = request_line.substr(space + 1);

    int slash = http.find('/');
    http = http.substr(slash + 1);

    std::cout << http << "\r\n";

    float http_vers = std::stof(http);

    std::cout << http_vers << "\r\n\r\n";

    req.setMethod(method_from_string(method));
    req.setPath(path);

    int next_line = req_str.find('\n');

    while (next_line != std::string::npos) {

        std::string header = req_str.substr(0, next_line);
        req_str = req_str.substr(next_line + 1);
        // Parse header
        int         colon = header.find(':');
        std::string header_title = header.substr(0, colon);
        std::string header_value = header.substr(colon + 2);

        if (header_value.length() >= 1) {

            header_value.pop_back();
        }

        req.setHeader(header_title, header_value);

        // New line
        next_line = req_str.find('\n');
    }

    if (req_str.length() > 0) {
        req.setBody(req_str);
    }

    return req;
}

void Server::run() {
    routes_p = &this->routes;
    pthread_t input_thread;
    pthread_create(&input_thread, NULL, manual_close, &sock);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_t connection_thread;
        pthread_create(&connection_thread, NULL, await_connection, NULL);
    }

    listen(sock, 10);

    while (true) {

        // Handle connection
        int client;
        client = accept(sock, NULL, NULL);

        if (client == -1) {
            std::cout << "failed to bind \n";
            std::cout << strerror(errno) << std::endl;
            close(sock);
            exit(-3);
        }

        // TODO: put in queue;

        pthread_mutex_lock(&connection_queue_mutex);
        connection_queue.push(client);
        pthread_mutex_unlock(&connection_queue_mutex);
        pthread_cond_signal(&connection_queue_not_empty);
    }
}

void handle_connection(int client) {

    // loop while connected

    std::array<char, REQ_BUF> buff;
    bool                      close_connection = false;

    while (!close_connection) {
        buff.fill(0);
        // handle request
        recv(client, &buff, REQ_BUF, 0);

        std::string buf(buff.data());

        Request req = parse_request(buf);

        Response *resp;

        auto r = routes_p->find(req.getPath());

        // map.find returns end() if not found
        if (r != routes_p->end()) {
            resp = (r->second)(req);
        } else {
            resp = not_found();
        }

        try {
            auto connection = req.getHeader("Connection");
            if (connection == "close") {
                // Shut down connection
                resp->set_header("Connection", "close");
                close_connection = true;
            } else {
                resp->set_header("Connection", "keep-alive");
            }
        } catch (HeaderNotFoundException e) {

            if (req.getHttpVersion() == 1.0f) {
                // Shut down connection
                resp->set_header("Connection", "close");
                close_connection = true;
            } else {
                resp->set_header("Connection", "keep-alive");
            }
        }

        std::string messg = resp->build_response();
        delete resp;

        send(client, messg.c_str(), messg.length(), 0);
    }

    std::cout << "Shutting down connection" << std::endl;

    close(client);
}
