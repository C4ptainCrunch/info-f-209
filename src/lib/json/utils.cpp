#include "utils.h"

using namespace std;

int skip_whitespace(string message, int start){
    int ret = 0;
    while(start + ret < message.length()){
        switch(message[start + ret]){
            case '\n':
            case '\t':
            case '\r':
            case ' ':
                break;
            default:
                return ret;
        }
        ret++;
    }
    throw ParseError("while skipping whitespace", __LINE__, start + ret);
}

int skip_colon(string message, int start){
    int ret = skip_whitespace(message, 0);
    bool colon = false;
    while(start + ret < message.length() && !colon){
        switch(message[start + ret]){
            case ':':
                colon = true;
                break;
            default:
                throw ParseError("while skipping colons found " + string(1, message[start + ret]), __LINE__, start + ret);
        }
        ret++;
    }
    ret += skip_whitespace(message, start + ret);
    return ret;
}

string cut_from(string message, int from){
    return message.substr(from, message.length());
}