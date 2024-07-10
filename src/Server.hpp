#pragma once

#include "Request.hpp"
#include "Response.hpp"
#include <cstdint>
#include <map>
#include <netinet/in.h>
#include <string>
class Server{
    typedef Response (*Route)(Request);
    
    private: 
        int sock; 
        std::map<std::string, Route> routes;

    private:
        Request parse_request(std::string request_string); 

    public:
        Server(in_port_t port);
        void run();
};
