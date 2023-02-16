#pragma once
#include <string>
#include <map>
#include <list>
#include <mutex>
#include <thread>
#include "constants.hpp"
using namespace std;

struct request_t
{
    string method;
    string uri;
    string protocol;
    int descriptor;
    map<string, string> headers;
    string identity;
    stringstream body;
    thread *worker;
    int status;
    unsigned int number;
    struct response_t * response;
};

struct connection_t
{
    int descriptor;
    string remote_address;
    unsigned short int remote_port;
    thread *worker;
    unsigned int number;
    string identity;
    bool keep_alive = false;
    bool established = false;
    bool open = false;
    struct request_t * active_request = nullptr;
    std::mutex requests_guard;
    std::chrono::system_clock::time_point access_time;
};

struct server_config_t {
    std::chrono::seconds keep_alive_timeout = 10s;
    bool tcp_nodelay = true;
    bool ignore_broken_pipe = true;
    std::string address = "0.0.0.0";
    int port = 0;
};

struct server_t
{
    int descriptor;
    std::list<connection_t *> active_connections;
    std::deque<connection_t *> dead_connections;
    size_t total_connections;
    std::mutex connections_guard;
    int port = 8190;
    const string identity = "[%]\t";
    bool customPort = false;
    server_config_t config;
};

struct data_t
{
    stringstream unicode;
    char *binary;
    size_t length = 0;
    size_t maxlength = 0;
    int type = DATA_IS_UNICODE;
    string path;
    ifstream file;
    size_t from = 0;
    size_t to = SIZE_MAX;
    size_t sent = 0;
};

struct response_t
{
    int code = 200;
    string type = HEADER_CONTENT_TYPE_UNKNOWN;
    map<string, string> headers;
    struct data_t body;
};
