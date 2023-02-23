#include <stdlib.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <netdb.h>
#include <memory.h>
#include <string.h>
#include <arpa/inet.h>

#include <iostream>
#include <filesystem>
#include <fstream>
#include <boost/program_options.hpp>
using namespace std;
using namespace boost::program_options;

void logUnixError(const char * prefix, const char * action) {
    std::stringstream message;
    message << prefix << "Unable to " << action << ". The reason is: (" << errno << ") " << strerror(errno) << std::endl;
    std::cerr << message.str().c_str();
}

struct hostent * resolveAddress(string host)
{
    unsigned int i = 0;
    struct hostent *hp = gethostbyname(host.c_str());
    
	if (hp == nullptr) {
        logUnixError(" ~ ", (string("resolve ip by hostname") + host).c_str());
        exit(1);
    } else 	{
		while (hp->h_addr_list[i] != nullptr) {
            cerr << " ~ Resolved IP: " << inet_ntoa(*(struct in_addr *)(hp->h_addr_list[i])) << endl;
            i++;
        }
    }
    
	return hp;
}

int establishConnection(string host, unsigned short port)
{
    int sock;
    struct sockaddr_in addr;
   
	sock = socket(AF_INET, SOCK_STREAM, 0);   
	if(sock < 0) {
        logUnixError(" ~ ", "open socket");
        exit(1);
    }
   
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);   
	struct hostent *hp = resolveAddress(host);
    
    memcpy(&addr.sin_addr, hp->h_addr_list[0], hp->h_length);
    
	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        logUnixError(" ~ ", "connect");
        exit(1);
    }
    
	return sock;
}

variables_map parse(int argc, char *argv[])
{
    using namespace boost::program_options;
    options_description desc{"Options"};
    variables_map arguments;

    auto setFilename = [](string filename)
    { if (!filesystem::exists(filename)) throw std::runtime_error(string("File does not exists: ") + filename);};

    desc.add_options()("help", "Print usage")
        ("host,h", value<string>()->default_value("localhost"), "IP Address")
        ("port,p", value<unsigned short>()->required(), "Port")
        ("filename,f", value<string>()->notifier(setFilename)->required(), "File Name");

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

struct header_t {
    size_t filesize;
    unsigned char filename_size;
    char filename[256];
};

struct chunk_t {
    int length;
    char data[256];
};

int main(int argc, char *argv[])
{
    variables_map arguments = parse(argc, argv);
    FILE *input;
    int length, size;
    char buf[512];
    
    string filename = arguments["filename"].as<string>();
    std::fstream file(filename, file.binary | file.in);
    if (!file.is_open()) {
        cerr << "Could not open file with filename " << filename << endl;
        exit(1);
    }

    file.seekg(0, file.end);
    size_t filesize = file.tellg();
    file.seekg(0, file.beg);

	int socket = establishConnection(arguments["host"].as<string>(), arguments["port"].as<unsigned short>());
   
    char headerSend[1024], headerReceived[1024];
    header_t header;
    {
        header.filesize = filesize;
        header.filename_size = filename.size();    

        for (int i = 0; i < filename.size(); i++) {
            header.filename[i] = filename[i];
        }
        
        header.filename[filename.size()] = '\0';
    }

    size_t sent_bytes = send(socket, (void*)&header, sizeof(header_t), 0);
	size_t received_bytes = recv(socket, (void*)&header, sizeof(header_t), 0);

    cout << " ~ handshake finished, file size: " << header.filesize << endl;

    while (!file.eof()) {
        chunk_t chunk;
        file.read(&chunk.data[0], 256);
        chunk.length = file.gcount();

        send(socket, (void*)&chunk, sizeof(chunk_t), 0);
        cout << " ~ readed " << chunk.length << ", " << sizeof(chunk) << " bytes send" << endl;
        sleep(1);
    }

	close(socket);
    return 0;
}