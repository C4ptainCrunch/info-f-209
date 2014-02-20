#include <string>
#include <iostream>

#include "json.h"

using namespace std;

// List
// -----------
int listmain(){
    int i = 0;
    JsonList* list_p = JLIST(JsonValue::fromString("[ 2    , \"elem2\"]"));
    JsonInt * int_p = JINT((*list_p)[0]);

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
    cout << "------------" << endl << endl;
    return dictmain();
}