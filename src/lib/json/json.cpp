#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <map>

#include "json.h"
#include "utils.h"

using namespace std;

// Value

JsonValue * JsonValue::fromString(std::string message){
    int i = 0;
    return JsonValue::fromString(message, i);
}

JsonValue * JsonValue::fromString(std::string message, int &i){
    int bak = i;
    i = 0;
    string s;
    while(i < message.length()){
        i += skip_whitespace(message, i);
        switch(message[i]){
            case '{':
                s = cut_from(message, i + 1 );
                i = bak;
                return JsonDict::fromString(s, i);
                break;
            case '[':
                s = cut_from(message, i + 1 );
                i = bak;
                return JsonList::fromString(s, i);
                break;
            case '"':
                s = cut_from(message, i + 1 );
                i = bak;
                return JsonString::fromString(s, i);
                break;
            // case 'b':
            // case 'f':
            //     s = cut_from(message, i);
            //     i = bak;
            //     return JsonBool::fromString(s, i);
            case 'n':
                s = cut_from(message, i);
                i = bak;
                return JsonNull::fromString(s, i);
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
                s = cut_from(message, i);
                i = bak;
                return JsonInt::fromString(s, i);
                break;
            default:
                throw 1;
        }
    }
    throw 1;
}

/*std::string JsonValue::toString(JsonValue * json){
    return json->toString();
}*/

// String

string replaces(string str, string find, string replace){
    if (str.length() < find.length())
        return str;
    size_t pos = str.find(find);
    if(pos == string::npos)
        return str;
    return str.replace(pos,find.length(),replace);
}

string replaces(string str, string find, char replace){
    return replaces(str, find, string(1, replace));
}

JsonString::JsonString(string val){
    val = replaces(val, "\\\\", '\\');
    val = replaces(val, "\\\"", '"');
    val = replaces(val, "\\t", '\t');
    val = replaces(val, "\\n", '\n');
    val = replaces(val, "\\r", '\r');
    val = replaces(val, "\\b", '\b');
    val = replaces(val, "\\f", '\f');
    // TODO : replace \u four-hex-digits
    value = val;
}

JsonString::operator std::string() const{
    return value;
}

JsonString JsonString::operator=(const JsonString &str){
    value = str.value;
    return *this;
}

JsonString * JsonString::fromString(std::string message){
    int i = 0;
    return JsonString::fromString(message, i);
}

JsonString * JsonString::fromString(std::string message, int &i){
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

std::string JsonString::toString(){
    std::string infos = "\"" + this->value + "\"";
    return infos;
}

// Dict

JsonDict * JsonDict::fromString(std::string message){
    int i = 0;
    return JsonDict::fromString(message, i);
}

JsonDict * JsonDict::fromString(std::string message, int &i){
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
        key = JsonString::fromString(cut_from(message, i + 1 ), i);
        i++;
        i += skip_colon(message, i);
        value = JsonValue::fromString(cut_from(message, i), i);
        i++;
        r->add(*key, value);
        i += skip_whitespace(message, i);
        if(message[i] == ','){
            i++;
        }
    }
}

std::string JsonDict::toString(){
    std::string infos = "{";
    for (std::map<std::string, JsonValue *>::iterator index = this->dict.begin() ; index != this->dict.end() ; index++ ){
        infos += ((std::string) index->first) + " : ";
        infos += index->second->toString();
        infos += ", ";
    }
    infos = infos.substr(0, infos.size()-2) + "}";
    return infos;
}

void JsonDict::add(JsonString key, JsonValue * value){
    dict[(string) key] = value;
}

size_t JsonDict::size(){
    return dict.size();
}

JsonValue * JsonDict::operator[](const std::string &str){
    return this->dict[str];
}



// List

JsonList * JsonList::fromString(std::string message){
    int i = 0;
    return JsonList::fromString(message, i);
}

JsonList * JsonList::fromString(std::string message, int &i){
    JsonList * r = new JsonList();
    i = 0;
    while(1){
        JsonValue * value;
        i += skip_whitespace(message, i);
        value = JsonValue::fromString(cut_from(message, i), i);
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

std::string JsonList::toString(){
    std::string infos = "[";
    int index=0;
    while (index < this->content.size()){
        infos += this->content[index]->toString();
        index++;
        if (index+1 != this->content.size()){
            infos+=", ";
        }
    }
    infos+="]";
    return infos;
}

void JsonList::add(JsonValue * value){
    content.push_back(value);
}

size_t JsonList::size(){
    return content.size();
}

JsonValue * JsonList::operator[](const int &i){
    return this->content.at(i);
}


// Int

JsonInt * JsonInt::fromString(std::string message){
    int i = 0;
    return JsonInt::fromString(message, i);
}

JsonInt * JsonInt::fromString(std::string message, int &i){
    int bak = i;
    JsonInt * r = new JsonInt();
    bool end;
    i = 0;
    while(!end){
        switch(message[i]){
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
                i++;
                break;
            default:
                end = true;
                break;
        }
    }
    r->setValue(message.substr(0, i));
    i += bak - 1;
    return r;
}

string JsonInt::toString(){
    return (string) *this;
}


int JsonInt::getValue(){
    return value;
}

void JsonInt::setValue(int val){
    value = val;
}

void JsonInt::setValue(string val){
    value = stoi(val);
}

JsonInt::operator std::string() const{
    return std::to_string(value);
}

JsonInt::operator int() const{
    return value;
}

// Null

JsonNull * JsonNull::fromString(std::string message){
    int i = 0;
    return JsonNull::fromString(message, i);
}

string JsonNull::toString(){
    return "null";
}

JsonNull * JsonNull::fromString(std::string message, int &i){
    i += 4;
    if(message.substr(0,4) != "null"){
        throw 1;
    }
    return new JsonNull;
}

bool JsonNull::operator ==(const int * i){
    return i == 0;
}
