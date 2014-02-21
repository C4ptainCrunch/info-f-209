#include <string>
#include <iostream>

#include "json.h"

using namespace std;

// List
// -----------
int listmain(){
    JsonList* list_p = JLIST(JsonValue::fromString("[ 1    ,\n \"elem2\"]"));
    JsonString * str_p = JSTRING((*list_p)[1]);

    cout << (string) *str_p << endl;
    return 0;
}


// Null
// -----------
int nullmain(){
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
    JsonList* list_p = JLIST(JsonValue::fromString("[ 1 , 200000000 , 3 , \"elem2\"]"));
    JsonInt * int_p = JINT((*list_p)[1]);

    cout << (int) *int_p << endl;
    return 0;
}

// Bool
int boolmain(){
    JsonList* list_p = JLIST(JsonValue::fromString("[ true , false , 3 , \"elem2\"]"));
    JsonBool* bool_p = JBOOL((*list_p)[0]);
    JsonBool* bool_p1 = JBOOL((*list_p)[1]);

    if(*bool_p == true){
        cout << "T" << endl;
    }
    if(*bool_p1 == false){
        cout << "F" << endl;
    }
    return 0;
}


// Dict
// -----------
int dictmain(){
    string message = "{\"cle1\" :   \"val1\"   , \"cle2\" : \"val2\" ,  \"cle3\":\"val3\",\"cle3\":\"val\\\\3bis\"}";

    JsonDict* dict_p = JDICT(JsonValue::fromString(message));
    cout << "Len=" << dict_p->size() << endl;
    JsonString * str_p = JSTRING((*dict_p)["cle3"]);
    cout << (string) *str_p << endl;
    return 0;
}

int inmain(){
    listmain();
    cout << "------------" << endl;
    intmain();
    cout << "------------" << endl;
    boolmain();
    cout << "------------" << endl;
    nullmain();
    cout << "------------" << endl;
    dictmain();
    return 0;
}


int outmain(){
    JsonDict * r = new JsonDict();
    r->add("coucou", new JsonBool(true));
    r->add("caca", new JsonInt(1));
    cout << r->toString() << endl;

    JsonList * l = new JsonList();
    l->add(new JsonString("coucou"));
    l->add(new JsonInt(10));
    cout << l->toString() << endl;

    cout << JsonBool(true).toString() << endl;

    cout << JsonNull().toString() << endl;

    cout << JsonInt(10).toString() << endl;

    cout << JsonString("coucou").toString() << endl;
    return 0;
}

int main(){
    return inmain();
}