#pragma once
#include "Enums.hpp"

#include <map>
#include <string>
class Request {
  private:
    std::string                        path;
    Method                             method;
    std::string                        body;
    std::map<std::string, std::string> headers;
    std::map<std::string, std::string> parameters;
    float                              http_version;

  public:
    std::string getPath() const;
    void        setPath(const std::string &newPath);

    // Getter and Setter for method
    Method getMethod() const;
    void   setMethod(const Method &newMethod);

    // Getter and Setter for body
    std::string getBody() const;
    void        setBody(const std::string &newBody);

    // Getter and Setter for individual header
    std::string getHeader(const std::string &key) const;
    void        setHeader(const std::string &key, const std::string &value);

    // Getter and Setter for individual parameter
    std::string getParameter(const std::string &key) const;
    void        setParameter(const std::string &key, const std::string &value);

    int getHttpVersion();
    void setHttpVersion(float vers);
};
