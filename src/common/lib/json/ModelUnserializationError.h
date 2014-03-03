#ifndef MODELUNSERIALIZATION
#define MODELUNSERIALIZATION

#include <iostream>
#include <sstream>
#include <exception>
#include <stdexcept>

class ModelUnserializationError : public std::runtime_error {
    public:
        ModelUnserializationError(std::string message="Json serialization error.");
};

#endif
