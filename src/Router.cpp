#include "Router.hpp"
#include "Exceptions.hpp"
#include <iostream>
#include <string>
Router::Router(std::string root) {

    if (root.back() != '/') {
        root.push_back('/');
    }

    this->root = root;
    full_root = root;
}

Route Router::match_route(std::string route) {

    std::string local_path = route;

    // make sure we dont accidentally erase too much, route might not /exactly/
    // match what our root path is! clients tend to not end on a slash, but
    // for... reasons? we expect this slash!
    local_path.erase(0, full_root.length() - 1);

    // otherwise itll fuck up on matching routes on sub-routers
    if (local_path.front() != '/') {
        local_path = "/" + local_path;
    }

    // INFO:: length 0 probably not needed anymore...
    if (local_path == "/" || local_path.length() == 0) {
        return root_path;
    }

    for (auto r : routes) {
        if (r.first == local_path) {
            return r.second;
        }
    }

    // remove leading /, otherwise itll just find that one instead!
    local_path.erase(0, 1);
    int slash = local_path.find('/');
    if (slash != local_path.npos) {
        local_path = local_path.substr(0, slash);
    }
    
    // wrap it back up! once more to ensure its formated exactly as we expect. 
    local_path = "/" + local_path + "/";

    for (auto r : subrouters) {
        if (r->root == local_path) {
            return r->match_route(route);
        }
    }
    
    // no valid route found in own or subrouters routes.
    throw InvalidRoute();
}

// WARN: adding a route that has the same path as a subrouter is currently
// undefined behaviour.

void Router::add_subrouter(Router *r2) {
    r2->full_root = this->root + r2->root;

    subrouters.push_back(r2);
}

void Router::add_route(std::string path, Route route) {
    if (path == "/") {
        root_path = route;
        return;
    }
    routes[path] = route;
}
