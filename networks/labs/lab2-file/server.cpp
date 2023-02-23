#include <stdlib.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>

#include <arpa/inet.h>

#include <iostream>
#include <filesystem>
#include <fstream>
#include <boost/program_options.hpp>
using namespace boost::program_options;
using namespace std;

void logUnixError(const char *prefix, const char *action)
{
    std::stringstream message;
    message << prefix << "Unable to " << action << ". The reason is: (" << errno << ") " << strerror(errno) << std::endl;
    std::cerr << message.str().c_str();
}

variables_map parse(int argc, char *argv[])
{
    options_description desc{"Options"};
    variables_map arguments;

    desc.add_options()("help", "Print Usage")("ip", value<string>()->default_value("0.0.0.0"), "IP Address")("port,p", value<unsigned short>()->default_value(9100), "Port");

    try
    {
        store(parse_command_line(argc, argv, desc), arguments);
        notify(arguments);

        if (arguments.count("help"))
        {
            std::cout << desc << '\n';
            exit(1);
        }
    }
    catch (const boost::program_options::error &ex)
    {
        std::cerr << ex.what() << '\n';
        std::cerr << desc << endl;
        exit(1);
    }

    return arguments;
}

int getOpenedSocket(int port, string ip)
{
    struct sockaddr_in addr;
    int descriptor = socket(AF_INET, SOCK_STREAM, 0);

    if (descriptor < 0)
    {
        logUnixError(" ~ ", "open socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());

    if (bind(descriptor, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        logUnixError(" ~ ", "bind address");
        exit(1);
    }

    socklen_t namelen = sizeof(addr);
    if (getsockname(descriptor, (struct sockaddr *)&addr, &namelen) == -1)
    {
        logUnixError(" ~ ", "getsockname method");
        exit(1);
    }

    cout << "listen incoming connections on " << inet_ntoa(addr.sin_addr) << ":" << ntohs(addr.sin_port) << endl;

    if (listen(descriptor, 1) == -1)
    {
        logUnixError(" ~ ", "listen");
        exit(1);
    }

    return descriptor;
}

void noop() {};

struct header_t {
    size_t filesize;
    unsigned char filename_size;
    char filename[256];
};

struct chunk_t {
    int length;
    char data[256];
};

header_t parseHeader(int socket)
{
    header_t header;
    size_t bytes = recv(socket, (void*)&header, sizeof(header_t), 0);
    return header;
}

void handleRequest(int socket)
{
    FILE *output;
    char buf[1024], path[128];
    int bytes_read;
    int pid = getpid();

    //handshake
    header_t header;
    {
        int bytes = recv(socket, (void*)&header, sizeof(header_t), 0);
        bytes < 0 ? logUnixError(" < ", "receive header") : noop();
        cout << "header received: " << bytes << endl;
    }

    cout << header.filename << ": " << header.filesize << endl;
    {
        int bytes = send(socket, (void*)&header, sizeof(header_t), 0);
        bytes < 0 ? logUnixError(" > ", "send header") : noop();
        cout << "header sent: " << bytes << endl;
    }

    string filename = string("upload/") + header.filename;
    std::fstream file(filename, file.binary | file.out);

    bool receiveFile = true;
    while (receiveFile) {
        chunk_t chunk;
        bytes_read = recv(socket, (void*)&chunk, sizeof(chunk_t), 0);
        
        cout << bytes_read << "bytes readed, chunk size " << chunk.length << endl;

        if (bytes_read <= 0) {
            receiveFile = false;
            break;
        }

        file.write(chunk.data, chunk.length);
    }
    file.close();
    close(socket);
    exit(0);
}

/* Уничтожение процесса-зомби */
void reaper(int sig)
{
    int status;
    while (wait3(&status, WNOHANG, (struct rusage *)0) >= 0);
}

int main(int argc, char *argv[])
{
    variables_map arguments = parse(argc, argv);
    int clientSocket, listener, i;
    unsigned short port = arguments["port"].as<unsigned short>();
    string ip = arguments["ip"].as<string>();

    signal(SIGCHLD, reaper);

    listener = getOpenedSocket(port, ip);

    while (1)
    {
        clientSocket = accept(listener, NULL, NULL);

        if (clientSocket < 0) {
            logUnixError(" @ ", "accept connection");
            exit(1);
        }

        if (fork()) {
            close(clientSocket);
        } else {
            cout << " @ socket: " << clientSocket << endl;
            handleRequest(clientSocket);
        }
    }

    return 0;
}