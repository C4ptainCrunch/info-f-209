#ifndef BADREQUEST
#define BADREQUEST

#include <iostream>
#include <sstream>
#include <exception>
#include <stdexcept>


class SocketError: public std::runtime_error {
public:
    SocketError(std::string message="Socket Error.");
};

#endif
