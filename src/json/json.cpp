#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <exception>

#include "json.h"

using namespace std;

JsonDict::JsonDict(){}

void JsonDict::add(JsonString key, JsonValue * value){
    dict[(string) key] = value;
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

JsonValue * createList(string message, int &i){
    return new JsonValue();
}

JsonValue * createNumber(string message, int &i){
    return new JsonValue();
}

JsonValue * createValue(string message, int &i){
    i = 0;
    while(i < message.length()){
        switch(message[i]){
            case '{':
                return createDict(message.substr(i + 1, message.length()), i);
                break;
            case '[':
                return createList(message.substr(i + 1, message.length()), i);
                break;
            case '"':
                return createString(message.substr(i + 1, message.length()), i);
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
                return createNumber(message.substr(i, message.length()), i);
                break;
            case '\n':
            case ' ':
                i++;
                break;
            default:
                throw 1;
        }
    }
    throw 1;
}

JsonDict * createDict(string message, int &i){
    JsonDict * r = new JsonDict();
    i = 0;
    while(1){
        JsonString * key;
        JsonValue * value;
        bool colon = false;
        bool coma = false;
        bool gotkey = false;
        while(i < message.length()){
            switch(message[i]){
                case '"':
                    key = createString(message.substr(i + 1, message.length()), i);
                    gotkey = true;
                    break;
                case '\n':
                case ' ':
                    break;
                case '}':
                    i++;
                    return r;
                    break;
                default:
                    throw 1;
            }
            if(gotkey){
                break;
            }
            i++;
        }
        i++;
        while(i < message.length() && !colon){
                switch(message[i]){
                case ':':
                    colon = true;
                    break;
                case '\n':
                case ' ':
                    break;
                default:
                    throw 1;
            }
            i++;
        }
        int bak = i;

        value = createValue(message.substr(i, message.length()), i);
        i += bak + 1;
        r->add(*key, value);
        while(i < message.length() && !coma){
                switch(message[i]){
                case ',':
                    coma = true;
                    break;
                case '\n':
                case ' ':
                    break;
                case '}':
                    i++;
                    return r;
                    break;
                default:
                    throw 1;
            }
            i++;
        }
    }
}

JsonString * createString(string message, int &i){
    int j = i;
    i = 0;
    while(i < message.length()){
        switch(message[i]){
        case '\\':
            i++;
            break;
        case '"':
            i++;
            string s = message.substr(0, i - 1);
            i += j;
            return new JsonString(s);
            break;
        }
    i++;
    }
    throw 1;
}

int main(){
    int i = 0;
    JsonValue * val = createValue("{\"cle1\":\"val1\",\"cle2\":\"val2\",\"cle3\":\"val3\",\"cle3\":\"val3bis\"}", i);
    JsonDict* strptr = dynamic_cast<JsonDict*>(val);
    cout << "Len=" << strptr->dict.size() << endl;
    JsonValue * c = strptr->dict["cle3"];
    JsonString * cstr = dynamic_cast<JsonString*>(c);
    cout << cstr->value << endl;
    return 0;
}
