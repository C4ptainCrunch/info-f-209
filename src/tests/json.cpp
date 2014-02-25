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

void test_empty_list(){
    string message = "[1]";

    JsonValue * value = JsonValue::fromString(message);
    ASSERT_NOT_NULL(value, "Parsing null");

    JsonDict* dict_p = JDICT(value);
    ASSERT_NOT_NULL(dict_p, "List null");

    ASSERT(dict_p->size() == 0, "List not empty");
}

void test_non_parse(){
    string message = "{";

    JsonValue * value = JsonValue::fromString(message);
}

#define TESTVEC {T(test_empty_dict), T(test_empty_list), T(test_non_parse)}
TEST();
