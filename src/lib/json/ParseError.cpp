#include "ParseError.h"

using namespace std;

ParseError::ParseError(){ }

const char * ParseError::what() const throw(){
    return "Json parse error.";
}
