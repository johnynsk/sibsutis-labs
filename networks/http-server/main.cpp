#include <iostream>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <exception>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <sstream>
#include <sys/stat.h>
#include <fstream>
#include <map>
#include <arpa/inet.h>
#include <filesystem>
#include <signal.h>
#include <csignal>
#include <queue>
#include <fcntl.h>
#include <regex>
#include <netinet/tcp.h>
#include <chrono>

#include "helpers.hpp"
#include "constants.hpp"
#include "types.hpp"

// #include <boost/log/core.hpp>
// #include <boost/log/trivial.hpp>
// #include <boost/log/expressions.hpp>
// #include <boost/thread/thread.hpp> 

using namespace std;

bool needShutDown = false;
struct server_t server;

namespace garcon
{
    std::string prepareServerInfo(struct connection_t * connection, struct request_t * request, struct server_t * server) {
        stringstream body;
        body << "Garcon version: " << SERVER_VERSION << endl;
        body << "Compiled with " << 
            "G++ version: " << SERVER_COMPILER_VERSION << ", "
            "LibBoost: " SERVER_BOOST_VERSION << endl;

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
            << " * Connections information:" << endl;

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
                    << ar->method
                    << " " << ar->uri << " "
                    << "State: " << request_statuses[ar->status];

                if (ar->status == MODE_FILE_TRANSMITTING && ar->response != nullptr) {
                    int b = 5;
                    int percent = 100;
                    if (ar->response->body.length > 0) {
                        percent = ar->response->body.sent * 100 / ar->response->body.length;
                    }
                    
                    buffer << " (" << percent << "%)";
                }
                
                buffer << endl;
            } else {
                buffer << "No request" << endl;
            }

            if (connection->keep_alive) {
                keepAliveCount++;
            }

            delete connectionLock;
        }

        delete serverLock;

        body << "Active connections: " << server->active_connections.size()
            << " / Keep-Alive: " << keepAliveCount
            << "; Not cleaned: " << server->dead_connections.size()
            << "; Received Total: " << server->total_connections << endl;

        body << buffer.str();
        
        body << endl << SERVER_INFO_SEPARATOR << endl;
        body << " * See you next time!" << endl;

        return body.str();
    }

    int closeConnection(struct connection_t *connection, int code)
    {
        connection->established = false;

        {
            stringstream message;
            message << connection->identity << "Closing the connection. " << endl;
            cout << message.str().c_str();
        }

        int unixCode = 0;

        unixCode = shutdown(connection->descriptor, SHUT_RDWR);
        if (code == ERROR_SHOULD_READ_ERRNO && errno != ERROR_BAD_DESCRIPTOR)
        {
            logUnixError(connection->identity.c_str(), "shutdown connection (RDWR)");
        }

        unixCode = close(connection->descriptor);
        if (code == ERROR_SHOULD_READ_ERRNO && errno != ERROR_BAD_DESCRIPTOR)
        {
            logUnixError(connection->identity.c_str(), "close connection descriptior");
        }

        const std::lock_guard<std::mutex> * lock;
        lock = new std::lock_guard(server.connections_guard);

        server.active_connections.remove(connection);
        server.dead_connections.push_back(connection);

        delete connection->active_request;
        delete lock;
        return code;
    }

    void prepareFileToOutput(struct request_t *request)
    {
        filesystem::path cwd = filesystem::current_path() / "web-root";
        filesystem::path path(filesystem::absolute(cwd.c_str() + request->uri));
        {
            stringstream message;
            message << request->identity << "Checking for the file path " << path << "; " << cwd << endl;
            cerr << message.str().c_str();
        }

        struct response_t *response = request->response;

        if (!filesystem::exists(path))
        {
            {
                stringstream message;
                message << request->identity << "The file does not exists." << endl;
                cerr << message.str().c_str();
            }   

            response->code = HTTP_ERROR_NOT_FOUND;
            response->body.unicode << "The file does not exists.";
            response->body.type = DATA_IS_UNICODE;

            return;
        }

        if (string(path).find(cwd) != 0)
        {
            {
                stringstream message;
                message << request->identity << "Probably wrong url is using: '" << filesystem::canonical(path) << "'" << endl;
                cerr << message.str().c_str();
            }   

            response->code = HTTP_ERROR_ACCESS_DENIED;
            response->body.unicode << "Access to this resource is denied. Need to become a superhero.";
            response->body.type = DATA_IS_UNICODE;

            return;
        }

        if (access(string(path).c_str(), R_OK) < 0)
        {
            {
                stringstream message;
                message << request->identity << "Access denied" << endl;
                cerr << message.str().c_str();
            }   

            response->code = HTTP_ERROR_ACCESS_DENIED;
            response->body.unicode << "Access to this resource is denied. Need to become a superhero.";
            response->body.type = DATA_IS_UNICODE;

            return;
        }

        if (filesystem::is_directory(path))
        {
            if (filesystem::exists(path / "index.html"))
            {
                path = path / "index.html";
            }
            else
            {
                response->code = HTTP_ERROR_OK;
                response->body.unicode << listForDirectory(path);

                return;
            }
        }

        if (!filesystem::exists(path) || !filesystem::is_regular_file(path))
        {
            {
                stringstream message;
                message << request->identity << "The file does not exists." << endl;
                cerr << message.str().c_str();
            }   

            response->code = HTTP_ERROR_NOT_FOUND;
            response->body.unicode << "The file does not exists.";
            response->body.type = DATA_IS_UNICODE;

            return;
        }

        if (access(string(path).c_str(), R_OK) < 0)
        {
            {
                stringstream message;
                message << request->identity << "Access denied" << endl;
                cerr << message.str().c_str();
            }   

            response->code = HTTP_ERROR_ACCESS_DENIED;
            response->body.unicode << "Access to this resource is denied. Need to become a superhero.";
            response->body.type = DATA_IS_UNICODE;

            return;
        }

        response->headers[HEADER_CONTENT_TYPE] = getMimeType(path);
        response->body.length = filesystem::file_size(path);
        response->body.type = DATA_IS_FILE;
        response->body.path = path;

        return;
    }

    int parseHeaders(struct connection_t *connection, struct request_t *request)
    {
        {
            int mode = MODE_READ_METHOD;
            request->status = mode;
            {
                string line;
                while (mode == MODE_READ_METHOD)
                {
                    connection->access_time = std::chrono::system_clock::now();
                    char symbol;
                    {
                        char buffer[1];
                        auto count = recv(connection->descriptor, buffer, 1, 0);
                        if (count < 1)
                        {
                            logUnixError(request->identity, "parse HTTP headers: method");

                            return ERROR_CONNECTION_LOST;
                        }
                        symbol = buffer[0];
                    }

                    if (symbol == ' ')
                    {
                        mode = MODE_READ_URI;
                    }
                    else
                    {
                        line.push_back(symbol);
                    }
                }

                request->method = line;
                {
                    stringstream message;
                    message << request->identity << "The method is: " << request->method << endl;
                    cerr << message.str().c_str();
                }
            }

            request->status = mode;
            {
                string line;
                while (mode == MODE_READ_URI)
                {
                    connection->access_time = std::chrono::system_clock::now();
                    char symbol;
                    {
                        char buffer[1];
                        auto count = recv(connection->descriptor, buffer, 1, 0);
                        if (count < 1)
                        {
                            logUnixError(request->identity, "parse HTTP headers: URI");

                            return ERROR_CONNECTION_LOST;
                        }
                        symbol = buffer[0];
                    }

                    if (symbol == ' ')
                    {
                        mode = MODE_READ_PROTOCOL;
                    }
                    else
                    {
                        line.push_back(symbol);
                    }
                }

                request->uri = line;
                {
                    stringstream message;
                    message << request->identity << "The URI is: " << request->uri << endl;
                    cout << message.str().c_str();
                }
            }

            request->status = mode;
            {
                string line;
                char previousSymbol = '\0';
                while (mode == MODE_READ_PROTOCOL)
                {
                    connection->access_time = std::chrono::system_clock::now();
                    char symbol;
                    {
                        char buffer[1];
                        auto count = recv(connection->descriptor, buffer, 1, 0);
                        if (count < 1)
                        {
                            logUnixError(request->identity, "parse HTTP headers: protocol");

                            return ERROR_CONNECTION_LOST;
                        }
                        symbol = buffer[0];
                    }

                    if (previousSymbol == '\r' && symbol == '\n')
                    {
                        mode = MODE_READ_HEADERS;
                    }
                    else if (symbol != '\r' && symbol != '\n')
                    {
                        line.push_back(symbol);
                    }

                    previousSymbol = symbol;
                }

                request->protocol = line;
                {
                    stringstream message;
                    message << request->identity << "The protocol is: " << request->protocol << endl;
                    cout << message.str().c_str();
                }
            }

            // TODO ADD VERIFY THE METHOD
            request->status = mode;
            {
                string line;
                char previousSymbol = '\0';

                while (mode == MODE_READ_HEADERS)
                {
                    connection->access_time = std::chrono::system_clock::now();
                    char symbol;
                    {
                        char buffer[1];
                        auto count = recv(connection->descriptor, buffer, 1, 0);
                        if (count < 1)
                        {
                            logUnixError(request->identity, "parse HTTP headers");

                            return ERROR_CONNECTION_LOST;
                        }
                        symbol = buffer[0];
                    }

                    if (symbol != '\r' && symbol != '\n')
                    {
                        line.push_back(symbol);
                    }

                    if (previousSymbol == '\r' && symbol == '\n')
                    {
                        if (line.size() == 0)
                        {
                            {
                                stringstream message;
                                message << request->identity << "Parsing headers done." << endl;
                                cerr << message.str().c_str();
                            }
                            previousSymbol = symbol;

                            if (request->method.compare("GET") == 0 || request->method.compare("HEAD") == 0 || request->method.compare("OPTIONS") == 0)
                            {
                                mode = MODE_REQUEST_READY;
                            }
                            else
                            {
                                mode = MODE_READ_BODY;
                            }

                            break;
                        }

                        {
                            stringstream message;
                            message << request->identity << "Header line: " << line << endl;
                            cerr << message.str().c_str();
                        }

                        string key = line.substr(0, line.find(": "));
                        string value = line.substr(line.find(": ") + 2, line.size());
                        request->headers[key] = value;
                        line = string();
                    }

                    previousSymbol = symbol;
                }
            }

            request->status = mode;
            {
                string line;
                char previousSymbol = '\0';

                while (mode == MODE_READ_BODY)
                {
                    connection->access_time = std::chrono::system_clock::now();
                    char buffer[1];
                    auto count = recv(connection->descriptor, buffer, 1, 0);
                    if (count < 1)
                    {
                        mode = MODE_REQUEST_READY;
                        {
                            stringstream message;
                            message << request->identity << "message body has readed successfuly" << endl;
                            cerr << message.str().c_str();
                        }
                        
                        logUnixError(request->identity, "read additional byte in body reading section");

                        continue;
                    }

                    request->body << buffer;
                }
            }
            request->status = mode;
        }

        // Check for keep-alive connection
        {
            std::map<std::string, std::string>::iterator connectionHeader = request->headers.find(HEADER_CONNECTION);
            if (connectionHeader != request->headers.end() && connectionHeader->second == HEADER_CONNECTION_KEEP_ALIVE)
            {
                connection->keep_alive = true;
            }
        }
        return 0;
    }

    int serveRequest(struct connection_t *connection, struct request_t *request)
    {
        {
            int code = parseHeaders(connection, request);
            if (code == ERROR_CONNECTION_LOST) {
                return ERROR_CONNECTION_LOST;
            }
        }

        connection->access_time = std::chrono::system_clock::now();
        stringstream responseStream;
        vector<string> responseHeaders;
        stringstream responseBody;
        struct response_t * response = new struct response_t;
        request->response = response;

        response->headers[HEADER_CONNECTION] = connection->keep_alive ? HEADER_CONNECTION_KEEP_ALIVE : HEADER_CONNECTION_CLOSE;

        if (request->uri.compare("/info") == 0)
        {
            response->headers[HEADER_CONTENT_TYPE] = HEADER_CONTENT_TYPE_TEXT_PLAIN;
            response->body.unicode << prepareServerInfo(connection, request, &server);
        }
        else
        {
            prepareFileToOutput(request);
        }

        ifstream file;

        if (response->body.type == DATA_IS_FILE)
        {
            response->headers[HEADER_ACCEPT_RANGES] = HEADER_ACCEPT_RANGES_BYTES;

            file.open(response->body.path.c_str(), ios::binary);
            file.seekg(0, file.end);
            response->body.maxlength = file.tellg();
            {
                std::map<std::string, std::string>::iterator requestRangeHeader = request->headers.find(HEADER_RANGE);

                if (requestRangeHeader != request->headers.end())
                {
                    std::smatch matches;
                    const std::regex expressionRange("^bytes=(\\d+)-(\\d+)$");
                    const std::regex expressionStarts("^bytes=(\\d+)-$");
                    size_t from = 0;
                    size_t to = response->body.maxlength;

                    if (std::regex_match(requestRangeHeader->second, matches, expressionRange))
                    {
                        from = std::stoull(matches[1].str());
                        to = std::stoull(matches[2].str());
                    }
                    else if (std::regex_match(requestRangeHeader->second, matches, expressionStarts))
                    {
                        from = std::stoull(matches[1].str());
                        to = response->body.maxlength;
                    }
                    else
                    {
                        response->body.unicode << "Got unsupported range." << endl
                                               << "Garcon supports only the following set of Content-Ranges:" << endl
                                               << "bytes=5-100" << endl
                                               << "bytes=5-" << endl;

                        response->body.type = DATA_IS_UNICODE;
                        response->code = HTTP_ERROR_NOT_IMPLEMENTED;

                        {
                            stringstream message;
                            message << request->identity << "Got unsupported " << HEADER_RANGE << " header: " << requestRangeHeader->second;
                            cerr << message.str().c_str();
                        }
                    }

                    if (from <= response->body.maxlength && to <= response->body.maxlength && to - from >= 0)
                    {
                        response->body.from = from;
                        response->body.to = to;
                        response->body.length = to - from;
                        std::stringstream responseContentRange;
                        responseContentRange << HEADER_ACCEPT_RANGES_BYTES << " " << from << "-" << to << "/" << response->body.maxlength;
                        response->headers[HEADER_CONTENT_RANGE] = responseContentRange.str();
                        response->code = HTTP_ERROR_PARTIAL_CONTENT;
                        cerr << request->identity << "Detected boundaries: " << from << "-" << to << " with length = " << to - from << "\n";
                    }
                    else
                    {
                        response->body.type = DATA_IS_UNICODE;
                        response->code = HTTP_BAD_REQUEST;
                        response->body.unicode << "Got wrong range" << endl
                                               << "Range should:" << endl
                                               << "1) starts should not exceeds file size; " << endl
                                               << "2) end should not exceeds file size;" << endl
                                               << "3) start should be less than end;" << endl
                                               << endl
                                               << "You sent " << requestRangeHeader->second << "; File size was " << response->body.maxlength << endl;
                    }
                }
                else
                {
                    response->body.length = response->body.maxlength;
                    response->body.from = 0;
                    response->body.to = response->body.maxlength;
                }
            }
            file.seekg(0, file.beg);
        }

        if (response->body.type == DATA_IS_UNICODE)
        {
            response->headers[HEADER_ACCEPT_RANGES] = HEADER_ACCEPT_RANGES_NONE;
            response->headers[HEADER_CONTENT_TYPE] = HEADER_CONTENT_TYPE_TEXT_PLAIN;

            response->body.maxlength = response->body.unicode.str().size();
            response->body.length = response->body.maxlength;
        }

        {
            response->headers[HEADER_CONTENT_LENGTH] = to_string(response->body.length);
            responseStream << "HTTP/1.1 " << to_string(response->code) << " " << http_errors[response->code] << CRLF;
            {
                stringstream message;
                message << request->identity << "Response: " << response->code << " " << http_errors[response->code] << endl;
                message << request->identity << "Headers: " << endl;
                
                for (const auto &header : response->headers)
                {
                    responseStream << header.first << ": " << header.second << CRLF;
                    message << request->identity << "\t" << header.first << ": " << header.second << endl;
                }

                cerr << message.str().c_str();
            }

            responseStream << CRLF;
        }

        {
            ssize_t bytes;

            if (request->method.compare("HEAD") == 0)
            {
                bytes = send(connection->descriptor, responseStream.str().c_str(), responseStream.str().size(), 0);
            }
            else if (response->body.type == DATA_IS_UNICODE)
            {
                if (request->method.compare("HEAD") != 0)
                {
                    responseStream << response->body.unicode.str() << CRLF;
                };
                bytes = send(connection->descriptor, responseStream.str().c_str(), responseStream.str().size(), 0);
            }
            else if (response->body.type == DATA_IS_FILE)
            {
                {
                    size_t length = responseStream.str().size();
                    char blobs[length];
                    memcpy(&blobs[0], &responseStream.str().c_str()[0], length);

                    bytes = send(connection->descriptor, blobs, length, MSG_NOSIGNAL);
                    //;write(connection->descriptor, blobs, length); trying to avoid sigpipe
                    if (bytes == ERROR_SHOULD_READ_ERRNO)
                    {
                        logUnixError(connection->identity, "write HTTP headers for file");
                        const std::lock_guard<std::mutex> * connectionLock;
                        connectionLock = new std::lock_guard(connection->requests_guard);
                        
                        request->response = nullptr;
                        delete response;
                        delete connectionLock;
                        return ERROR_CONNECTION_LOST;
                    }
                }

                char buffer[256 * 1024];
                size_t readed = 0;

                // auto a = request->response;
                // auto b = response->body;
                request->status = MODE_FILE_TRANSMITTING;
                file.seekg(response->body.from, file.beg);
                while (!file.eof() && readed < response->body.length)
                {
                    connection->access_time = std::chrono::system_clock::now();
                    size_t blockSize = response->body.length - readed > 256 * 1024 ? 256 * 1024 : response->body.length - readed;
                    file.read(buffer, blockSize);
                    size_t chunk = file.gcount();
                    // {
                    //     stringstream message;
                    //     message << request->identity << response->body.path << ": readed bytes " << readed << "-" << readed + chunk << "; " << endl;
                    //     //cerr << message.str().c_str();
                    // }

                    bytes = send(connection->descriptor, buffer, chunk, MSG_NOSIGNAL);
                    //bytes = write(connection->descriptor, buffer, chunk); Try to avoid sigpipe
                    
                    if (bytes == ERROR_SHOULD_READ_ERRNO)
                    {
                        logUnixError(connection->identity, "write HTTP headers for file");
                        break;
                    }

                    readed += chunk;
                    response->body.sent = readed;
                }

                file.close();
            }

            if (bytes < 0)
            {
                logUnixError(request->identity, "send the response");
                request->response = nullptr;
                const std::lock_guard<std::mutex> * connectionLock;
                connectionLock = new std::lock_guard(connection->requests_guard);
                
                request->response = nullptr;
                delete response;
                delete connectionLock;
                return ERROR_CONNECTION_LOST;
            }
        }
        
        connection->access_time = std::chrono::system_clock::now();
        const std::lock_guard<std::mutex> * connectionLock;
        connectionLock = new std::lock_guard(connection->requests_guard);
        request->response = nullptr;
        delete response;
        delete connectionLock;
        return 0;
    }

    int serveConnection(struct connection_t *connection)
    {
        unsigned int requestsCounter = 0;
        connection->open = true;
        connection->established = true;
        connection->access_time = std::chrono::system_clock::now();

        while (connection->established)
        {
            ++requestsCounter;
            struct request_t *request = new struct request_t;
            {
                request->number = requestsCounter;

                stringstream logIdentity;
                logIdentity << "[#" << connection->number
                            << ":" << requestsCounter
                            << "]\t";

                request->identity = logIdentity.str().c_str();
            }

            connection->active_request = request;
            int code = serveRequest(connection, request);
            
            if (code == ERROR_CONNECTION_LOST || !connection->keep_alive) {
                connection->established = false;
            }

            const std::lock_guard<std::mutex> * connectionLock;
            connectionLock = new std::lock_guard(connection->requests_guard);
            connection->active_request = nullptr;

            // if (request != nullptr) {
            //     delete request;
            // }
            delete connectionLock;
        }

        closeConnection(connection, OBSERVER_STOP_DONE);

        return 0;
    }
}

void shutdown(int)
{
    {
        stringstream message;
        message << endl << server.identity
         << "SIGINT > Looks like Agent Smith was detected us. We should have no traces, shutdown active connections" << endl;
        cerr << message.str().c_str();
    }
    
    needShutDown = true;

    shutdown(server.descriptor, SHUT_RDWR);
};

int keepNotAlive(struct server_t * server) {
    while (!needShutDown || needShutDown && server->active_connections.size() > 0) {
        std::list<struct connection_t *> victims;

        // show for outdated keep-alive connections
        {
            std::chrono::time_point deadPoint = std::chrono::system_clock::now() - server->config.keep_alive_timeout;
            const std::lock_guard<std::mutex> * lock;
            lock = new std::lock_guard(server->connections_guard);

            for (auto it: server->active_connections) {
                struct connection_t * connection = it;

                if (connection->keep_alive && connection->access_time < deadPoint) {
                    victims.push_back(connection);
                }
            }

            delete lock;
        }

        {
            for (auto it: victims) {
                struct connection_t * connection = it;
                garcon::closeConnection(connection, OBSERVER_KILL_BY_TIMEOUT);
            }
        }


        // stop all dead connections
        {
            const std::lock_guard<std::mutex> * lock;
            lock = new std::lock_guard(server->connections_guard);
            for (auto it: server->dead_connections) {
                struct connection_t * connection = it;

                if (connection->worker->joinable()) {
                    connection->worker->join();
                }

                delete connection->active_request;
                delete connection;
            }
            
            server->dead_connections.clear();
            delete lock;
        }
        
        std::this_thread::sleep_for(2000ms);
    }

    return 0;
}

bool bindServerPort(struct server_t * server)
{
    server->descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (server->descriptor < 0)
    {
        logUnixError(server->identity, "open socket");

        return false;
    }

    struct sockaddr_in host;
    host.sin_family = AF_INET;
    host.sin_addr.s_addr = inet_addr(server->config.address.c_str());

    struct sigaction *sigint = new struct sigaction;
    sigint->sa_handler = shutdown;
    sigaction(SIGINT, sigint, 0);
    server->port = server->config.port > 0 ? server->config.port : 8190;

    {
        int code;
        do
        {
            {
                stringstream message;
                message << server->identity << "Try to use the following port: " << server->port << endl;
                cerr << message.str().c_str();
            }

            host.sin_port = htons(server->port);

            {
                code = bind(server->descriptor, (struct sockaddr *)&host, sizeof(host));

                if (code < 0)
                {
                    logUnixError(server->identity, (std::string("bind to port ") + std::to_string(server->port)).c_str());
                }
                else
                {
                    stringstream message;
                    message << server->identity << "Listening the following port: " << server->port << endl;
                    cerr << message.str().c_str();

                    break;
                }
            }

            if (server->config.port > 0)
            {
                break;
            }

            server->port++;
        } while (server->port <= 8200);

        if (code < 0)
        {
            stringstream message;
            message << server->identity << "All ports in a range are unavailable. Please set port manually (e.g. 'http-server 8195')" << endl;
            cerr << message.str().c_str();

            return false;
        }
    }

    {
        int code = listen(server->descriptor, 10);
        if (code == ERROR_SHOULD_READ_ERRNO)
        {
            logUnixError(server->identity, "listen socket");

            close(server->descriptor);
            return false;
        }
    }

    return true;
}

bool listenConnections(struct server_t * server)
{
    needShutDown = false;
    
    unsigned int connectionCounter = 0;
    unsigned int loops = 0;

    while (!needShutDown)
    {
        ++loops;

        // establishing a connection
        {
            struct connection_t * connection;
            struct sockaddr_in remote_address;
            socklen_t remote_address_length = sizeof(struct sockaddr);
            
            int descriptor = accept(server->descriptor, (struct sockaddr *)&remote_address, &(remote_address_length));

            if (descriptor < 0)
            {
                needShutDown = true;
                logUnixError(server->identity, "accept the connection");

                continue;
            }

            ++connectionCounter;
            connection = new struct connection_t;
            connection->remote_address = string(inet_ntoa(remote_address.sin_addr));
            connection->remote_port = ntohs(remote_address.sin_port);
            connection->number = connectionCounter;
            {                                                                                                                                                                                   
                stringstream logIdentity;

                logIdentity << "[~" << connection->number << "]\t";                                                                                         
                connection->identity = logIdentity.str().c_str();                                                                                                                        
                connection->descriptor = descriptor;
            }

            {
                stringstream message;
                message << connection->identity
                    << "A new connection from "
                    << connection->remote_address
                    << ":"
                    << connection->remote_port
                    << endl;

                cout << message.str().c_str();
            }

            int tcp_nodelay = server->config.tcp_nodelay ? 1 : 0;
            {
                int code = setsockopt(connection->descriptor, IPPROTO_TCP, TCP_NODELAY, (const void *) &tcp_nodelay, sizeof(int));
                code == ERROR_SHOULD_READ_ERRNO ? logUnixError(connection->identity, "set TCP_NODELAY to true") : noop();
            }

            {
                const std::lock_guard<std::mutex> * lock;
                lock = new std::lock_guard(server->connections_guard);
                server->active_connections.push_back(connection);
                server->total_connections = connectionCounter;
                delete lock;
            }
            connection->worker = new thread(garcon::serveConnection, connection);
        }

        if (loops % 10 == 0) {
            const std::lock_guard<std::mutex> * lock;
            lock = new std::lock_guard(server->connections_guard);
            //sanitize
            for (auto it: server->dead_connections) {
                struct connection_t * connection = it;

                if (connection->worker->joinable()) {
                    connection->worker->join();
                }

                delete connection;
            }

            
            server->dead_connections.clear();
            delete lock;
        }
    }

    return 0;
}

int main(int argc, const char *argv[])
{
    needShutDown = false;
    cerr << server.identity << "Wake up, Neo. I am trying to open appropriate port for you." << endl;
    BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
    BOOST_LOG_TRIVIAL(info) << "An informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
    BOOST_LOG_TRIVIAL(error) << "An error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

    if (argc > 1)
    {
        cerr << server.identity << "You specified your custom port " << argv[1] << ". Nice choice!" << endl;
        server.config.port = atoi(argv[1]);
    }
    std::thread * killerWorker;
    killerWorker = new thread(keepNotAlive, &server);

    if (bindServerPort(&server)) {
        listenConnections(&server);
    }
    

    if (killerWorker != nullptr && killerWorker->joinable()) {
        killerWorker->join();
    }

    shutdown(server.descriptor, SHUT_RDWR) == ERROR_SHOULD_READ_ERRNO ? logUnixError(server.identity, "shutdown on server description") : noop();
    close(server.descriptor) == ERROR_SHOULD_READ_ERRNO ? logUnixError(server.identity, "close server connection") : noop();
    
    cout << server.identity << "All connections was closed. See you next time!" << endl;
    return 0;
}
