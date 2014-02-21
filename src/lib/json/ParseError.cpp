#include "ParseError.h"

using namespace std;

ParseError(){ }

const char * what() const throw(){
    return "Json parse error."
}
