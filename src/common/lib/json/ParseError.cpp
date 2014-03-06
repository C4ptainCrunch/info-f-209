#include "ParseError.h"

using namespace std;

ParseError::ParseError(string message): runtime_error::runtime_error(message){}