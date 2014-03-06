#ifndef BADREQUEST
#define BADREQUEST

#include <iostream>
#include <sstream>
#include <exception>
#include <stdexcept>


class BadRequest : public std::runtime_error {
    public:
        BadRequest(std::string message="Bad Request.");
};

#endif
