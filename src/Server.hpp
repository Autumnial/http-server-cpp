#pragma once

#include "Request.hpp"
#include "Response.hpp"
#include <map>
#include <netinet/in.h>
#include <pthread.h>
#include <string>
class Server{
    typedef Response * (*Route)(Request);
    
    private: 
        int sock; 
        std::map<std::string, Route> routes;

    public:
        Server(in_port_t port);
        void run();
        void add_route(std::string route, Route func);
};
