#include "ParseError.h"

using namespace std;

ParseError::ParseError(string message, int line, int position): message(message), line(line), position(position) {}

const char * ParseError::what() const throw(){
    string ret = message;
    if(line >= 0)
        ret += " on line " + to_string(line);
    if(position >= 0)
        ret += " on position " + to_string(position);
    return ret.c_str();
}
