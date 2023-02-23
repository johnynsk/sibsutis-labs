#include <boost/asio.hpp>

#include <iostream>
#include <memory>
#include <sstream>

#include "src/helpers/arguments.hpp"

using namespace boost::asio;
using ip::tcp;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::shared_ptr;

int main(const int argc, const char *argv[])
{
    shared_ptr<endpoint_t> endpoint(new endpoint_t());
    int code;
    code = helpers::arguments::parse(argc, argv, endpoint);
    if (code != 0) {
        return code;
    }
    boost::asio::io_service io_service;
    tcp::socket socket(io_service);
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(endpoint->config.address), endpoint->config.port));

    string local_address = socket.local_endpoint().address().to_string();
    unsigned short int local_port = socket.local_endpoint().port();
    string remote = "[" + socket.remote_endpoint().address().to_string() + ":" + std::to_string(socket.remote_endpoint().port()) + "] ";
    cout << "[" << local_address << ":" << local_port << "] -> " << remote << endl; 


    // request/message from client
    string message;

    if (endpoint->config.message.size() > 0) {
        message = endpoint->config.message;
    } else {
        cout << "Please enter message for server: ";
        cin >> message;
    }

    boost::system::error_code error;
    boost::asio::write(socket, boost::asio::buffer(message + "\n"), error);
    if (!error)
    {
        cout << " > " << remote << message << endl;
    }
    else
    {
        cout << "send failed: " << error.message() << endl;
    }
    // getting response from server
    std::chrono::time_point start = std::chrono::system_clock::now();

    boost::asio::streambuf receive_buffer;
    boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
    if (error && error != boost::asio::error::eof)
    {
        cout << "receive failed: " << error.message() << endl;
    }
    else
    {
        using namespace std::chrono_literals;
        std::chrono::time_point end = std::chrono::system_clock::now();
        const char *data = boost::asio::buffer_cast<const char *>(receive_buffer.data());
        cout << " < " << remote << data << endl;
        std::cerr << " ⏲ " << remote << ": " << (end - start) / 1ms << " ms" << endl;
    }

    return 0;
}