#include "service.h"

#include <iostream>

void FirstService::get(const web_http::http_request& request) const {
    std::string param = utility::conversions::to_utf8string(request.absolute_uri().query());
    std::cout << "query parameter is : " << param << '\n';

    auto http_get_vars = web::uri::split_query(request.request_uri().query());
    std::string resp{"dummy"};
    if (const auto iterator = http_get_vars.find(U("name")); http_get_vars.end() != iterator) {
        resp = iterator->second;
    }

    web_json::value response;
    response[U("name")] = web_json::value::string(U(resp));
    response[U("email")] = web_json::value::string(U("simgealkin@gmail.com"));

    // Send the response
    request.reply(web_http::status_codes::OK, response);
}

FirstService::FirstService() : listener("http://localhost:1717/firstService") {
    //listener.support(methods::POST, std::bind(&UserService::handle_post, this, std::placeholders::_1));
    //listener.support(methods::PUT, std::bind(&UserService::handle_put, this, std::placeholders::_1));
    //listener.support(methods::DELETE, std::bind(&UserService::handle_delete, this, std::placeholders::_1));
    listener.support(web_http::methods::GET, std::bind(&FirstService::get, this, std::placeholders::_1));
}

FirstService::~FirstService() {
    this->stop();
}

void FirstService::start() {
    std::cout << "Starting FirstService!\n";
    listener.open().wait();
}

void FirstService::stop() {
    std::cout << "FirstService is being stopped!\n";
    listener.close().wait();
}