#ifndef PARSEERROR
#define PARSEERROR

#include <iostream>
#include <sstream>
#include <exception>

class ParseError : public std::exception {
    ParseError();
    const char * what() const throw();
}

#endif
