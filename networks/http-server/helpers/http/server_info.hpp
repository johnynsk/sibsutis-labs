#pragma once
#include <string>
#include "../../types.hpp"

namespace garcon {
    std::string 
    prepareServerInfo(struct connection_t * connection, struct request_t * request, struct server_t * server);
};