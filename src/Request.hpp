#pragma once
#include "Enums.hpp"

#include <string>
class Request {
  public:
    std::string path;
    Method      method;
};
