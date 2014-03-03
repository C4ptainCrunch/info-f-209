#include "libtest.h"

using namespace std;
#include "../lib/json/json.h"

void test_empty_dict(){

    string message = "{}";

    JsonValue * value = JsonValue::fromString(message);

    ASSERT_NOT_NULL(value, "Parsing null");

    JsonDict* dict_p = JDICT(value);
    ASSERT_NOT_NULL(dict_p, "Dict null");

    ASSERT(dict_p->size() == 0, "Dict not null");
}

void test_dict_one_val(){
    string fix[] = {
        "{\"a\":\"b\"}",
        "{\"a\" :\"b\"}",
        "{\"a\": \"b\"}",
        "{\"a\" : \"b\"}",
        "{  \"a\"  :  \"b\"  }"
    };

    for(int i=0; i < 5; i++){
        string message = fix[i];

        JsonValue * value = JsonValue::fromString(message);

        ASSERT_NOT_NULL(value, "Parsing null");

        JsonDict* dict_p = JDICT(value);
        ASSERT_NOT_NULL(dict_p, "Dict null");

        ASSERT(dict_p->size() == 1, "Dict not null");
        ASSERT_EQUAL((string) *JSTRING((*dict_p)["a"]), "b", "d[a]!=b");
    }
}

void test_empty_list(){
    string message = "[]";

    JsonValue * value = JsonValue::fromString(message);
    ASSERT_NOT_NULL(value, "Parsing null");

    JsonList * list_p = JLIST(value);
    ASSERT_NOT_NULL(list_p, "List null");

    ASSERT(list_p->size() == 0, "List not empty");
}

void test_empty_string(){
    string message = "\"\"";

    JsonValue * value = JsonValue::fromString(message);
    ASSERT_NOT_NULL(value, "Parsing not null");

    JsonString* string_p = JSTRING(value);
    ASSERT_NOT_NULL(string_p, "String not null");

    ASSERT_EQUAL((string) *string_p, "", "Empty string");
}

void test_true_bool(){
    string message = "true";

    JsonValue* value = JsonValue::fromString(message);
    ASSERT_NOT_NULL(value, "Parsing not null");

    JsonBool * bool_p = JBOOL(value);
    ASSERT_NOT_NULL(bool_p, "Cast");

    ASSERT(*bool_p, "Must be true");
}

void test_false_bool(){
    string message = "false";

    JsonValue* value = JsonValue::fromString(message);
    ASSERT_NOT_NULL(value, "Parsing not null");

    JsonBool * bool_p = JBOOL(value);
    ASSERT_NOT_NULL(bool_p, "Cast");

    ASSERT_FALSE(*bool_p, "Must be false");
}

void test_null(){
    string message = "null";

    JsonValue* value = JsonValue::fromString(message);
    ASSERT_NOT_NULL(value, "Parsing not null");

    JsonNull* null_p = JNULL(value);
    ASSERT_NOT_NULL(null_p, "Cast to null");

    ASSERT_NULL(*null_p, "Is null");

}

void test_list_of_multiple_elemets(){
    string message ="[ true, false, null, \"plop\",1,2 , 3]";

    JsonValue* value = JsonValue::fromString(message);
    ASSERT_NOT_NULL(value, "Parsing not null");

    JsonList* list_p = JLIST(value);
    ASSERT_NOT_NULL(list_p, "Cast");

    ASSERT_EQUAL(list_p->size(), 7, "List contain 7 elements");
}


#define TESTVEC {T(test_empty_dict), T(test_empty_list), T(test_empty_string), T(test_true_bool), T(test_false_bool), T(test_null), T(test_dict_one_val), T(test_list_of_multiple_elemets)}
TEST();