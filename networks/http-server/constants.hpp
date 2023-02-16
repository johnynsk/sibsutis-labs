#pragma once
#include <string>
#include <map>
#include "boost/assign.hpp"
#define SERVER_MAJOR_VERSION "1"
#define SERVER_MINOR_VERSION "1"
#define SERVER_VERSION SERVER_MAJOR_VERSION "." SERVER_MINOR_VERSION
#define SERVER_COMPILER_VERSION __VERSION__
#define SERVER_BOOST_VERSION BOOST_LIB_VERSION
#define SERVER_INFO_SEPARATOR "--------------------------------------------------------------------------------"

#define MODE_READ_METHOD 0
#define MODE_READ_URI 1
#define MODE_READ_PROTOCOL 2
#define MODE_READ_PROTOCOL_VERSION 3
#define MODE_READ_HEADERS 4
#define MODE_READ_BODY 5
#define MODE_REQUEST_READY 6
#define MODE_FILE_TRANSMITTING 7
#define ERROR_SHOULD_READ_ERRNO -1
#define ERROR_BAD_DESCRIPTOR 9
#define ERROR_ADDRESS_ALREADY_IN_USE 98
#define ERROR_CONNECTION_LOST -100
#define ERROR_CONNECTION_RESET_BY_PEER 104
#define CONNECTION_ERROR_ABNORMAL -99
#define HEADER_CONTENT_TYPE "Content-Type"
#define HEADER_CONTENT_LENGTH "Content-Length"
#define HEADER_CONTENT_RANGE "Content-Range"
#define HEADER_ACCEPT_RANGES "Accept-Ranges"
#define HEADER_RANGE "Range"
#define HEADER_CONNECTION "Connection"
#define HEADER_CONNECTION_CLOSE "close"
#define HEADER_CONNECTION_KEEP_ALIVE "keep-alive"
#define HEADER_CONTENT_TYPE_TEXT_PLAIN "text/plain"
#define HEADER_CONTENT_TYPE_UNKNOWN "application/octet-stream"
#define HEADER_ACCEPT_RANGES_BYTES "bytes"
#define HEADER_ACCEPT_RANGES_NONE "none"

#define OBSERVER_STOP_DONE 0
#define OBSERVER_KILL_BY_ERROR 0
#define OBSERVER_KILL_BY_TIMEOUT 2

#define HTTP_ERROR_OK 200
#define HTTP_ERROR_PARTIAL_CONTENT 206
#define HTTP_BAD_REQUEST 400
#define HTTP_ERROR_ACCESS_DENIED 403
#define HTTP_ERROR_NOT_FOUND 404
#define HTTP_ERROR_NOT_IMPLEMENTED 501

std::map<int, std::string> http_errors = boost::assign::map_list_of (HTTP_ERROR_OK, "OK") (HTTP_ERROR_PARTIAL_CONTENT, "Partial Content") (HTTP_BAD_REQUEST, "Bad Request") (HTTP_ERROR_ACCESS_DENIED, "Access Denied") (HTTP_ERROR_NOT_FOUND, "Not Found") (HTTP_ERROR_NOT_IMPLEMENTED, "Not Implemented");
std::map<int, std::string> request_statuses = boost::assign::map_list_of (MODE_READ_METHOD, "Parsing HTTP method") (MODE_READ_URI, "Parsing URI") (MODE_READ_PROTOCOL, "Parsing protocol name") (MODE_READ_PROTOCOL_VERSION, "Parsing protocol version") (MODE_READ_HEADERS, "Parsing headers") (MODE_READ_BODY, "Reading request body") (MODE_REQUEST_READY, "Request parsing done") (MODE_FILE_TRANSMITTING, "Transmitting");

#define DATA_IS_UNICODE 0
#define DATA_IS_BINARY 1
#define DATA_IS_FILE 2

#define CRLF "\r\n"