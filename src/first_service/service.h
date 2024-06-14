#ifndef MICROSERVICE_SRC_FIRST_SERVICE_SERVICE_H
#define MICROSERVICE_SRC_FIRST_SERVICE_SERVICE_H

#include <cpprest/http_listener.h>
#include <cpprest/json.h>

/*
    *using namespace web;
    *using namespace http;
    *using namespace http::experimental::listener;
 */

//namespace aliases
namespace web_http = web::http;
namespace web_json = web::json;
namespace listener = web_http::experimental::listener;

struct ProxyService {
    ProxyService();
    ~ProxyService();
    void start();
    void stop();
    void get(const web_http::http_request&) const;
    listener::http_listener listener;
};


#endif
