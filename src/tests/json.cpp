#include "libtest.h"

using namespace std;
//#include "../lib/json/json.h"

void test_empty_dict(){
    ASSERT(false, "plop");

    assertFalse(false);

    int *top = NULL;
    assertNull(top);

    double a = 5;
    double *val = &a;
    assertNotNull(val);

    assertEqual(8, 8.0);
    // string message = "{}";
    // int i = 0;

    // JsonValue * value = JsonValue::fromString(message, i)
    // ASSERT_NOT_NULL(value);

    // JsonDict* dict_p = JDICT(value);
    // ASSERT_NOT_NULL(dict_p);

    // ASSERT_EQUAL(dict_p->size(), 0);
}

void test_empty_list(){
    // string message = "{}";
    // int i = 0;

    // JsonValue * value = JsonValue::fromString(message, i)
    // ASSERT_NOT_NULL(value);

    // JsonDict* dict_p = JDICT(value);
    // ASSERT_NOT_NULL(dict_p);

    // ASSERT_EQUAL(dict_p->size(), 0);
}

#define TESTVEC {T(test_empty_dict), T(test_empty_list)}
TEST();
