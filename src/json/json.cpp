#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>

using namespace std;

class JsonNode {};

class JsonList : public JsonNode {
    public:
        vector<JsonNode> children;
};

class JsonNumber : public JsonNode {
    public:
        string value;
};

//JsonNode object(char * str);
JsonNode list(char * str);
//JsonNode string_f(char * str);
JsonNode number(char * str);
JsonNode root(char * str);

// JsonNode object(char * str){
//     JsonObject ret;
//     ret.content = str;
//     return ret;
// }

JsonNode list(char * str){
    JsonNode ret;
    JsonNode (*next_state)(char *);

    while(str[0] == ' ' || str[0] == '\n'){
        str++;
    }
    switch (str[0]){
        // case '{':
        //     next_state = &object;
        //     break;
        case '[':
            next_state = &list;
            break;
        // case '"':
        //     next_state = &string_f;
        //     break;
        default:
            next_state = &number;
            break;
    }
    str++;
    return next_state(str);
}

// JsonNode string_f(char * str){
//     JsonNode ret;
//     ret.type = "string";
//     ret.content = str;
//     return ret;
// }

JsonNode number(char * str){
    JsonNumber ret;
    ret = JsonNumber();
    ret.value = str[0];
    return ret;
}

JsonNode root(char * str){
    JsonNode (*next_state)(char *);
    while(str[0] == ' ' || str[0] == '\n'){
        str++;
    }
    switch (str[0]){
        // case '{':
        //     next_state = &object;
        //     break;
        case '[':
            next_state = &list;
            break;
        // case '"':
        //     next_state = &string_f;
        //     break;
        default:
            next_state = &number;
            break;
    }
    str++;
    return next_state(str);
}


int main(int argc, char *argv[]){
    char * str = "[8, 2]";
    cout << "OUTPUT" << "\n" << "==========" << "\n";
    JsonList b;
    JsonNode * a = &b;
    a = root(str);
    //cout << b << "\n";
    return 0;
}


char * findEnd(char type, char * str){
    return "";
}

class JsonToken {
    public:
        JsonToken(char * str);
        ~JsonToken();
        char type;
        std::vector<JsonToken*> children;
};

JsonToken::JsonToken(char * str) {
    for(char * i = str; i[0] != '\0'; i++) {
        switch (i[0]){
        case '{':
            type = '{';
            break;
        case '[':
            type = '[';
            break;
        case '"':
            type = '"';
            break;
        default:
            cout << "fail: " << i[0] << "\n";
            break;
        }
        children.push_back(new JsonToken(findEnd(type, i)));
    }
}

JsonToken::~JsonToken() {
    for(int i = 0; i < children.size(); i++){
        delete children.at(i);
    }
}


/*
TOKENS

/^,$/, 'comma'
/^:$/, 'end-label'
/^\{$/, 'begin-object'
/^\}$/, 'end-object'
/^\[$/, 'begin-array'
/^\]$/, 'end-array'
/^"(\\["\\/bfnrtu"]|[^"\\"])*"$/, 'string'
/^"([^"]|\\")*$/, 'maybe-string'
/^null$/, 'null'
/^(true|false)$/, 'boolean'
/^-?\d+(\.\d+)?([eE]-?\d+)?$/, 'number'
/^-?\d+\.$/, 'maybe-decimal-number'
/^-$/, 'maybe-negative-number'
/^\w+$/, 'symbol'

TESTS :

{
    "name": "Juventus Milan",
    "money": 10000,
    "players": [
        {
            "name": "ballotelli",
            "inventory":[
                {
                    "type": "balais",
                    "speed": 1000
                }
            ],
        },
                {
            "name": "chabal",
            "inventory":[
                {
                    "type": "potion",
                    "puissance": 10
                }
            ],
        }
    ]
}

*/