#include <string>
#include <iostream>

#include "json.h"

using namespace std;

// List
// -----------
int listmain(){
    int i = 0;
    JsonValue * val = createValue("[\"elem 1 \"    ,\n \"elem2\"]", i);
    JsonList* listptr = dynamic_cast<JsonList*>(val);
    JsonValue * one = listptr->content.at(1);
    JsonString * strptr = dynamic_cast<JsonString*>(one);
    cout << strptr->value << endl;
    return 0;
}

// Dict
// -----------
int dictmain(){
    int i = 0;
    JsonValue * val = createValue("{\"cle1\" :   \"val1\"   , \"cle2\" : \"val2\" ,  \"cle3\":\"val3\",\"cle3\":\"val3bis\"}", i);
    JsonDict* strptr = dynamic_cast<JsonDict*>(val);
    cout << "Len=" << strptr->dict.size() << endl;
    JsonValue * c = strptr->dict["cle3"];
    JsonString * cstr = dynamic_cast<JsonString*>(c);
    cout << cstr->value << endl;
    return 0;
}

int main(){
    listmain();
    cout << "------------" << endl;
    return dictmain();
}