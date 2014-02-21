#ifndef PARSEERROR
#define PARSEERROR

#include <iostream>
#include <sstream>
#include <exception>

class ParseError : public std::exception {
    public:
        ParseError();
        const char * what() const throw();
};

#endif
