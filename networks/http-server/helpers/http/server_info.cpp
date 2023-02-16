#include "server_info.hpp"
#include <sstream>
#include <mutex>
#include "../../constants.hpp"

namespace garcon {
    std::string prepareServerInfo(struct connection_t * connection, struct request_t * request, struct server_t * server) {
        stringstream body;
        body << "Garcon version: " << SERVER_VERSION;
        body << "Compiled with " << 
            "G++ version: " << SERVER_COMPILER_VERSION << ", "
            "LibBoost: " SERVER_BOOST_VERSION << endl << endl;

        body << endl << SERVER_INFO_SEPARATOR << endl;
        body << "* Information about your request:" << endl
            << request->identity
            << "Remote address is " << connection->remote_address
            << ":" << connection->remote_port << endl
            << "Using keep-alive: " << (connection->keep_alive ? "yes" : "no") << endl
            << "Protocol = " << request->protocol << ", Method = " << request->method
            << "URI: " << request->uri << endl
            << "Parsed headers: " << endl;

        for (auto header: request->headers) {
            body << "\t" << header.first << ": " << header.second << endl;
        }
        std::string requestBody = request->body.str();

        body << "Body: length(" << requestBody.size() << ")"
            << requestBody << endl << endl;

        body << SERVER_INFO_SEPARATOR << endl
            << "Connections information:" << endl;

        size_t keepAliveCount = 0;

        const std::lock_guard<std::mutex> * serverLock;
        serverLock = new std::lock_guard(server->connections_guard);
        std::stringstream buffer; // active connections buffer

        for (auto connection: server->active_connections) {
            const std::lock_guard<std::mutex> * connectionLock;
            connectionLock = new std::lock_guard(connection->requests_guard);

            buffer << connection->identity
                << (connection->keep_alive ? "K " : "C ")
                << connection->remote_address << ":"
                << connection->remote_port << endl;

            if (connection->active_request != nullptr) {
                struct request_t * ar = connection->active_request;
                buffer 
                    << ar->identity
                    << "State: " << request_statuses[ar->status];

                if (ar->status == MODE_FILE_TRANSMITTING && ar->response != nullptr) {
                    int b = 5;
                    int percent = 100;
                    if (ar->response->body.length > 0) {
                        percent = ar->response->body.sent * 100 / ar->response->body.length;
                    }
                    
                    buffer << " sent " << ar->response->body.sent 
                        << " out of " << ar->response->body.length << " (" << percent << "): "
                        << ar->response->body.path;
                }
            } else {
                buffer << "No request" << endl;
            }
            buffer << endl;

            if (connection->keep_alive) {
                keepAliveCount++;
            }

            delete connectionLock;
        }

        delete serverLock;

        body << " * Active connections: " << server->active_connections.size()
            << " / Keep-Alive: " << keepAliveCount
            << "; Not cleaned: " << server->dead_connections.size()
            << "; Total: " << server->total_connections << endl;

        body << buffer.str();
        
        body << endl << SERVER_INFO_SEPARATOR << endl;
        body << " * See you next time!" << endl;

        return body.str();
    }
}