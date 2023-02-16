#pragma once
#include <string>
#include <iostream>
// #include <boost/log/core.hpp>
// #include <boost/log/trivial.hpp>
// #include <boost/log/expressions.hpp>

class streamMessage
{

};

void noop() {

}

void logServer(const char * message) {

}

void logError(const char * message) {

}

void logInfo(const char * message) {

}

void logLine(void * variable) {
    std::cerr << &variable;
}

void logUnixError(const char * prefix, const char * action) {
    std::stringstream message;
    message << prefix << "Unable to " << action << ". The reason is: (" << errno << ") " << strerror(errno) << std::endl;
    std::cerr << message.str().c_str();
}

void logUnixError(const char * action) {
    logUnixError("", action);
}

void logUnixError(std::string prefix, const char * action) {
    logUnixError(prefix.c_str(), action);
}