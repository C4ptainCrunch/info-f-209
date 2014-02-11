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