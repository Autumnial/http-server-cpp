#include "Response.hpp"
#include "Enums.hpp"
#include <chrono>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <string>
#include <strstream>

std::string Response::build_response() {

    this->set_header("content-length", std::to_string(body.size()));
    this->set_header("content-type", "text/plain");
    this->set_header("server", "Cel's CPP server :D");

    auto now = std::chrono::system_clock::now();

    auto now_t = std::chrono::system_clock::to_time_t(now);

    std::tm *gmtime = std::gmtime(&now_t);

    std::ostrstream timestr;
    timestr << std::put_time(gmtime, "%a, %e %b %Y %H:%M:%S GMT");

    this->set_header("date", timestr.str());

    std::string resp_string = "HTTP/1.1 ";
    resp_string.append(status_to_string(statusCode));
    resp_string.append("\n");

    for (auto header : headers) {
        resp_string.append(header.first);
        resp_string.append(": ");
        resp_string.append(header.second);
        resp_string.append("\n");
    }

    resp_string.append("\n");
    resp_string.append(body);

    return resp_string;
}

std::string Response::get_header(std::string header){
    if(!this->headers.contains(header)){
        throw HeaderNotFoundException(); 
    }

    return this->headers.find(header)->second;
    
}

Response *Response::set_header(std::string header, std::string value) {
    if (headers.contains(header)) {
        headers.at(header) = value;
    } else {
        headers.insert({header, value});
    }

    return this;
}

Response *Response::set_body(std::string body) {
    this->body = body;
    return this;
}

Response *Response::append_body(std::string body) {
    this->body.append(body);
    return this;
}

Response *Response::set_statusCode(StatusCode code) {
    this->statusCode = code;
    return this;
}

Response *Response::create_response() {
    Response *response = new Response(); 
    return response;
}
