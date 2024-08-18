#include "Request.hpp"
#include "Exceptions.hpp"
std::string Request::getPath() const { return path; }

void Request::setPath(const std::string &newPath) { path = newPath; }

// Getter and Setter for method
Method Request::getMethod() const { return method; }

void Request::setMethod(const Method &newMethod) { method = newMethod; }

// Getter and Setter for body
std::string Request::getBody() const { return body; }

void Request::setBody(const std::string &newBody) { body = newBody; }

// Getter and Setter for individual header
std::string Request::getHeader(const std::string &key) const {
    auto it = headers.find(key);
    if (it != headers.end()) {
        return it->second;
    }
    throw HeaderNotFoundException();
}

void Request::setHeader(const std::string &key, const std::string &value) {
    headers[key] = value;
}

// Getter and Setter for individual parameter
std::string Request::getParameter(const std::string &key) const {
    auto it = parameters.find(key);
    if (it != parameters.end()) {
        return it->second;
    }
    throw ParameterNotFoundException();
}

void Request::setParameter(const std::string &key, const std::string &value) {
    parameters[key] = value;
}

int Request::getHttpVersion(){
    return http_version; 
}

void Request::setHttpVersion(float version){
    http_version = version; 
}
