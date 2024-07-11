#pragma once
#include "Enums.hpp"
#include <map>
class Response{
    StatusCode statusCode; 
    std::map<std::string, std::string> headers; 
    std::string body; 

    public:
        std::string build_response();
        void set_header(std::string header, std::string value);
        void set_body(std::string body); 
        void append_body(std::string append_str); 
        void set_statusCode(StatusCode code); 
};
