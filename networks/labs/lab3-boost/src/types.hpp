#pragma once
#include <string>

struct config_t {
    std::string address;
    int port;
    std::string message;
};

struct endpoint_t {
    config_t config;  
};
