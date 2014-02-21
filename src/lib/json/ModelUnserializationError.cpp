#include "ModelUnserializationError.h"

using namespace std;

ModelUnserializationError::ModelUnserializationError(){ }

const char * ModelUnserializationError::what() const throw(){
    return "Json serialization error.";
}
