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
    throw ParseError();
}

int skip_colon(string message, int start){
    int ret;
    bool colon = false;

    ret = skip_whitespace(message, start);
    while(start + ret < message.length() && !colon){
        switch(message[start + ret]){
            case ':':
                colon = true;
                break;
            default:
                throw ParseError();
        }
        ret++;
    }
    ret += skip_whitespace(message, start + ret);
    return ret;
}

string cut_from(string message, int from){
    return message.substr(from, message.length());
}