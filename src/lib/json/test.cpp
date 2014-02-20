#include <string>
#include <iostream>

#include "json.h"

using namespace std;

// List
// -----------
int listmain(){
    int i = 0;
    JsonList* list_p = JLIST(JsonValue::fromString("[ 1    ,\n \"elem2\"]"));
    JsonString * str_p = JSTRING((*list_p)[1]);

    cout << (string) *str_p << endl;
    return 0;
}


// Null
// -----------
int nullmain(){
    int i = 0;
    JsonList* list_p = JLIST(JsonValue::fromString("[ null    ,\n \"elem2\"]"));
    JsonNull * null_p = JNULL((*list_p)[0]);
    if(*null_p == NULL){
        cout << "N" << endl;
    }
    //cout << (string) *str_p << endl;
    return 0;
}

// INT
int intmain(){
    int i = 0;
    JsonList* list_p = JLIST(JsonValue::fromString("[ 1 , 200000000 , 3 , \"elem2\"]"));
    JsonInt * int_p = JINT((*list_p)[1]);

    cout << (int) *int_p << endl;
    return 0;
}


// Dict
// -----------
int dictmain(){
    int i = 0;
    string message = "{\"cle1\" :   \"val1\"   , \"cle2\" : \"val2\" ,  \"cle3\":\"val3\",\"cle3\":\"val\\\\3bis\"}";

    JsonDict* dict_p = JDICT(JsonValue::fromString(message, i));
    cout << "Len=" << dict_p->size() << endl;
    JsonString * str_p = JSTRING((*dict_p)["cle3"]);
    cout << (string) *str_p << endl;
    return 0;
}

int main(){
    listmain();
    cout << "------------" << endl;
    intmain();
    cout << "------------" << endl;
    nullmain();
    cout << "------------" << endl;
    return dictmain();
}