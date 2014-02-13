#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <exception>

#include "json.h"

using namespace std;

int skip_whitespace(string message, int start){
    int ret = 0;
    while(start + ret  < message.length()){
        switch(message[start + ret]){
            case '\n':
            case ' ':
                break;
            default:
                return ret;
        }
        ret++;
    }
    throw "a";
}

string cut_from(string message, int from){
    return message.substr(from, message.length());
}


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
    JsonDict * r = new JsonDict();
    i = 0;
    while(1){
        JsonString * key;
        JsonValue * value;
        bool colon = false;
        bool coma = false;
        bool gotkey = false;
        while(i < message.length()){
            i += skip_whitespace(message, i);
            switch(message[i]){
                case '"':
                    key = createString(cut_from(message, i + 1 ), i);
                    gotkey = true;
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
            i += skip_whitespace(message, i);
            switch(message[i]){
                case ':':
                    colon = true;
                    break;
                default:
                    throw 1;
            }
            i++;
        }

        i += skip_whitespace(message, i);

        value = createValue(cut_from(message, i), i);
        i++;
        r->add(*key, value);
        while(i < message.length() && !coma){
            i += skip_whitespace(message, i);
            switch(message[i]){
                case ',':
                    coma = true;
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

int main(){
    int i = 0;
    JsonValue * val = createValue("{\"cle1\" :   \"val1\" , \"cle2\" : \"val2\" ,  \"cle3\":\"val3\",\"cle3\":\"val3bis\"}", i);
    JsonDict* strptr = dynamic_cast<JsonDict*>(val);
    cout << "Len=" << strptr->dict.size() << endl;
    JsonValue * c = strptr->dict["cle3"];
    JsonString * cstr = dynamic_cast<JsonString*>(c);
    cout << cstr->value << endl;
    return 0;
}
