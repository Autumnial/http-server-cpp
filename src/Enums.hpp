#pragma once

#include <string>
enum Method {
    GET,
    POST,
    PUT,
    DELETE,
    HEAD,
    OPTIONS,
    PATCH,
    CONNECT,
    TRACE,
    UNDEFINED
};

Method method_from_string(std::string);
