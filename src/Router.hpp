#pragma once

#include "Request.hpp"
#include "Response.hpp"
#include <map>
#include <string>
#include <vector>
typedef Response *(*Route)(Request);

struct Router {
  private:
    std::vector<Router *>        subrouters;
    std::map<std::string, Route> routes;
    std::string                  root;
    std::string                  full_root;
    Route                        root_path = nullptr;

  public:
    Router(std::string root);
    void  add_subrouter(Router *r2);
    Route match_route(std::string route);
    void  add_route(std::string path, Route route);
};
