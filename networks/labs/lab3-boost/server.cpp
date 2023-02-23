#include "src/types.hpp"
#include "src/helpers/arguments.hpp"


#include <chrono>
#include <list>
#include <memory>
#include <sstream>
#include <thread>

using std::cerr;
using std::cout;
using std::endl;
using std::list;
using std::shared_ptr;
using std::string;
using std::stringstream;
using std::thread;

#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;


struct connection_t {
    tcp::socket * socket;
    std::thread * thread;
    string remote_address;
    unsigned short remote_port;
};

string readMessage(tcp::socket * socket)
{
    streambuf buf;
    read_until(*socket, buf, "\n");
    string data = boost::asio::buffer_cast<const char *>(buf.data());

    return data;
}

void writeMessage(tcp::socket * socket, string message)
{
    const string msg = message + "\n";
    write(*socket, boost::asio::buffer(message));
}

int socketProcessor(shared_ptr<connection_t> connection)
{
    connection->remote_address = connection->socket->remote_endpoint().address().to_string();
    connection->remote_port = connection->socket->remote_endpoint().port();
    string identity;
    {
        stringstream message;
        message << "[" << connection->remote_address << ":" << connection->remote_port << "]"; 
        identity = message.str();
    }

    try {
        using namespace std::chrono_literals;
        using namespace std::chrono;

        string message = readMessage(connection->socket);
        unsigned short time;
        {
            stringstream logline;
            logline << " < " << identity << ": " << message;
            cout << logline.str();
        }

        try {
            time = std::stoi(message);
        } catch (std::exception &ex) {
            writeMessage(connection->socket, string(ex.what()) + " error happened\n");
            throw ex;
        }

        {
            stringstream logline;
            logline << " ~ " << identity << ": sleep for " << time << " seconds" << endl;
            cout << logline.str();
        }

        std::this_thread::sleep_for(seconds(time));
        
        writeMessage(connection->socket, std::to_string(time) + "\n");

        {
            stringstream logline;
            logline << " > " << identity << ": " << time << endl;
            cout << logline.str();
        }
    } catch (const std::exception &ex) {
        cout << " ! " << identity << ": " << ex.what() << endl;
    }
    connection->socket->close();

    return 0;
}

bool serverRunning = true;
shared_ptr<tcp::acceptor> acceptor_;

void shutdown(int)
{
    cerr << " ~ : got SIGINT signal, shutdown server" << endl;
    serverRunning = false; 
    acceptor_->close();
}

int main(int argc, const char *argv[])
{
    int code;
    shared_ptr<endpoint_t> server = std::make_shared<endpoint_t>();
    code = helpers::arguments::parse(argc, argv, server);
    if (code != 0) return code;

    struct sigaction *sigint = new struct sigaction;
    sigint->sa_handler = shutdown;
    sigaction(SIGINT, sigint, 0);

    io_service io_service;
    // listen for new connection
    for (unsigned char offset = 0; offset <= 10; ++offset) 
    {
        try
        {
            acceptor_.reset(new tcp::acceptor(io_service, tcp::endpoint(ip::address::from_string(server->config.address), server->config.port + offset)));
            break;
        } catch (std::exception &ex) {
            if (offset == 10) {
                throw ex;
            }
        }
    }

    string local_address = acceptor_->local_endpoint().address().to_string();
    unsigned short int local_port = acceptor_->local_endpoint().port();
    cout << " ~ listen port: [" << local_address << ":" << local_port << "]" << endl; 

    std::list<shared_ptr<connection_t>> threads;
    int connections = 0;

    while (serverRunning) {
        ++connections;
        // socket creation
        shared_ptr<connection_t> connection(new connection_t());
        tcp::socket * socket_ = new tcp::socket(io_service);
        connection->socket = socket_;
        // waiting for connection
        acceptor_->accept(*connection->socket);

        threads.push_back(connection);
        connection->thread = new std::thread(socketProcessor, connection);
        if (threads.size() > 10) {
            for (auto connection: threads) {
                if (connection->socket->is_open() == false && connection->thread->joinable())
                {
                    connection->thread->join();
                }
            }
        }
    }

    return 0;
}