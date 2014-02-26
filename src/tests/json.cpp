#include "libtest.h"

using namespace std;
#include "../lib/json/json.h"

void test_empty_dict(){

    string message = "{}";

    JsonValue * value = JsonValue::fromString(message);

    ASSERT_NOT_NULL(value, "Parsing not null");

    JsonDict* dict_p = JDICT(value);
    ASSERT_NOT_NULL(dict_p, "Dict not null");

    ASSERT(dict_p->size() == 0, "Empty dict");
}

void test_empty_list(){
    string message = "[]";

    JsonValue * value = JsonValue::fromString(message);
    ASSERT_NOT_NULL(value, "Parsing not null");

    JsonDict* dict_p = JDICT(value);
    ASSERT_NOT_NULL(dict_p, "List not null");

    ASSERT(dict_p->size() == 0, "Empty list");
}

void test_empty_string(){
    string message = "\"\"";

    JsonValue * value = JsonValue::fromString(message);
    ASSERT_NOT_NULL(value, "Parsing not null");

    JsonString* string_p = JSTRING(value);
    ASSERT_NOT_NULL(string_p, "String not null");

    ASSERT_EQUAL((string) *string_p, "", "Empty string");

}

#define TESTVEC {T(test_empty_dict), T(test_empty_list), T(test_empty_string)}
TEST();
