#include "libtest.h"

using namespace std;

void test_assert_raise(){
    ASSERT_RAISE(throw 1, ..., "test");
}

#define TESTVEC {T(test_assert_raise)}

TEST();
