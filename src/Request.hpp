#pragma once
#include "Enums.hpp"

#include <map>
#include <string>
class Request {
  public:
    std::string path;
    Method      method;
    std::string body; 
    std::map<std::string, std::string> headers; 
    std::map<std::string, std::string> parameters;
};
