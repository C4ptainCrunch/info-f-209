#ifndef PARSEERROR
#define PARSEERROR

#include <iostream>
#include <sstream>
#include <exception>
#include <stdexcept>

#define PARSE_ERROR(message, position) ParseError(std::string(message) + " in " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " at position " + std::to_string(position))

class ParseError: public std::runtime_error {
public:
    ParseError(std::string message="Json parse error.");
};

#endif
