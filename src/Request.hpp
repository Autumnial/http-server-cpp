#pragma once
#include "Enums.hpp"

#include <map>
#include <string>
class Request {
  public:
    std::string path;
    Method      method;
    std::map<std::string, std::string> headers; 
};
