#include "Enums.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Server.hpp"
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>

Response *greet(Request _r) {

    auto response = Response::create_response()
                        ->set_statusCode(StatusCode::OK)
                        ->set_body("Greetings, from the cpp server!");

    return response;
}

Response *sleepy(Request _r) {
    auto response = Response::create_response();
    sleep(5);
    response->set_statusCode(StatusCode::OK);
    response->set_body("zzzzz im a sleepy little route");

    return response;
}

Response *personal_greeting(Request _r) {
    return Response::create_response()
        ->set_statusCode(StatusCode::OK)
        ->set_body("");
}

int main(int argc, char *argv[]) {

    Server server(6969);
    server.add_route("/", greet);
    server.add_route("/sleepy", sleepy);
    server.add_route("/greet_name", personal_greeting);
    server.run();

    return 0;
}
