#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>

#include "json.h"
#include "utils.h"

using namespace std;


JsonDict::JsonDict(){}

void JsonDict::add(JsonString key, JsonValue * value){
    dict[(string) key] = value;
}


JsonList::JsonList(){}

void JsonList::add(JsonValue * value){
    content.push_back(value);
}

JsonString::JsonString(){}

JsonString::JsonString(string val){
    value = val;
}

JsonString::operator std::string() const{
    return value;
}

JsonString JsonString::operator=(const JsonString &str){
    value = str.value;
    return *this;
}


JsonValue * createNumber(string message, int &i){
    return new JsonValue();
}

JsonValue * createValue(string message, int &i){
    int bak = i;
    i = 0;
    string s;
    while(i < message.length()){
        i += skip_whitespace(message, i);
        switch(message[i]){
            case '{':
                s = cut_from(message, i + 1 );
                i = bak;
                return createDict(s, i);
                break;
            case '[':
                s = cut_from(message, i + 1 );
                i = bak;
                return createList(s, i);
                break;
            case '"':
                s = cut_from(message, i + 1 );
                i = bak;
                return createString(s, i);
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                return createNumber(cut_from(message, i), i);
                break;
            default:
                throw 1;
        }
    }
    throw 1;
}

JsonDict * createDict(string message, int &i){
    JsonString * key;
    JsonValue * value;
    bool colon = false;
    bool coma = false;

    JsonDict * r = new JsonDict();
    i = skip_whitespace(message, 0);


    while(1){
        if(message[i] == '}'){
            i++;
            return r;
        }
        i += skip_whitespace(message, i);
        key = createString(cut_from(message, i + 1 ), i);
        i++;
        i += skip_colon(message, i);
        value = createValue(cut_from(message, i), i);
        i++;
        r->add(*key, value);
        i += skip_whitespace(message, i);
        if(message[i] == ','){
            i++;
        }
    }
}

JsonList * createList(string message, int &i){
    JsonList * r = new JsonList();
    i = 0;
    while(1){
        JsonValue * value;
        i += skip_whitespace(message, i);
        value = createValue(cut_from(message, i), i);
        i++;
        r->add(value);
        i += skip_whitespace(message, i);
        switch(message[i]){
            case ',':
                i++;
                break;
            case ']':
                i++;
                return r;
                break;
            default:
                throw 1;
        }
    }
}


JsonString * createString(string message, int &i){
    int bak = i;
    i = 0;
    while(i < message.length()){
        switch(message[i]){
        case '\\':
            i++;
            break;
        case '"':
            i++;
            string s = message.substr(0, i - 1);
            i += bak;
            return new JsonString(s);
            break;
        }
    i++;
    }
    throw 1;
}
