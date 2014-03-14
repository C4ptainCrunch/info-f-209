#include "ModelUnserializationError.h"

using namespace std;


ModelUnserializationError::ModelUnserializationError(string message): runtime_error::runtime_error("Unserialization:" + message) {}
