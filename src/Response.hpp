#pragma once
#include "Enums.hpp"
#include "Exceptions.hpp"
#include <map>
#include <string>
class Response{
    StatusCode statusCode; 
    std::map<std::string, std::string> headers; 
    std::string body; 

    public:
        std::string build_response();
        Response* set_header(std::string header, std::string value);
        // throws HeaderNotFoundException
        std::string get_header(std::string header); 
        Response* set_body(std::string body); 
        Response* append_body(std::string append_str); 
        Response* set_statusCode(StatusCode code); 
        static Response* create_response(); 
};
