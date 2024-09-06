#pragma once

#include "Request.hpp"
#include "Response.hpp"
#include "Router.hpp"
#include <map>
#include <netinet/in.h>
#include <pthread.h>
#include <string>
#include <vector>

class Server{
    typedef Response * (*Route)(Request);
    
    private: 
        int sock; 
        Router root;

    public:
        Server(in_port_t port);
        void run();
        void add_route(std::string route, Route func);
        void add_router(Router * r);
};
