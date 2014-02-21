#ifndef MODELUNSERIALIZATION
#define MODELUNSERIALIZATION

#include <iostream>
#include <sstream>
#include <exception>

class ModelUnserializationError : public std::exception {
    public:
        ModelUnserializationError();
        const char * what() const throw();
};

#endif
