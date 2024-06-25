#include "service.h"

#include <iostream>

void ProxyService::get(const web_http::http_request& request) const {
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

ProxyService::ProxyService() : listener("http://localhost:1741/ProxyService") {
    //listener.support(methods::POST, std::bind(&UserService::handle_post, this, std::placeholders::_1));
    //listener.support(methods::PUT, std::bind(&UserService::handle_put, this, std::placeholders::_1));
    //listener.support(methods::DELETE, std::bind(&UserService::handle_delete, this, std::placeholders::_1));
    listener.support(web_http::methods::GET, std::bind(&ProxyService::get, this, std::placeholders::_1));
}

ProxyService::~ProxyService() {
    std::cout << "ProxyService is being destroyed!\n";
    this->stop();
}

void ProxyService::start() {
    std::cout << "Starting ProxyService!\n";
    listener.open().wait();
}

void ProxyService::stop() {
    std::cout << "ProxyService is being stopped!\n";
    listener.close().wait();
}