#include "Enums.hpp"

Method method_from_string(std::string method_string) {
    if (method_string == "GET") {
        return Method::GET;
    } else if (method_string == "POST") {
        return Method::POST;
    } else if (method_string == "PUT") {
        return Method::PUT;
    } else if (method_string == "DELETE") {
        return Method::DELETE;
    } else if (method_string == "HEAD") {
        return Method::HEAD;
    } else if (method_string == "OPTIONS") {
        return Method::OPTIONS;
    } else if (method_string == "PATCH") {
        return Method::PATCH;
    } else if (method_string == "CONNECT") {
        return Method::CONNECT;
    } else if (method_string == "TRACE") {
        return Method::TRACE;
    } else {
        return Method::UNDEFINED;
    }
}
