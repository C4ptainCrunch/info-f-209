#ifndef PARSEERROR
#define PARSEERROR

#include <iostream>
#include <sstream>
#include <exception>

class ParseError : public std::exception {
    public:
        ParseError(std::string message="Unknown error", int line=-1, int position=-1);
        const char * what() const throw();

    private:
        std::string message;
        int line;
        int position;
};

#endif
