#include "Enums.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Server.hpp"
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>


Response greet(Request _r){
    Response response; 
    response.set_statusCode(StatusCode::OK);
    response.set_body("Greetings, from the cpp server!");

    return response;
}

Response sleepy(Request _r){
    Response response; 
    sleep(5);
    response.set_statusCode(StatusCode::OK);
    response.set_body("zzzzz im a sleepy little route");

    return response;
}

int main(int argc, char *argv[]) {

    Server server(6969);
    server.add_route("/", greet);
    server.add_route("/sleepy", sleepy);
    server.run();

    return 0;
}



