#include "../test/libtest.h"

#include "file.h"

using namespace std;

void test_dir() {
    // TODO: should remove old directories
    ASSERT(createDir("/tmp/plop"), "Creation failed");
    // TODO: should test if dir realy exists
}

void test_recursive_dir() {
    // TODO: should remove old directories
    ASSERT(createDir("/tmp/plip/plap/plop/"), "Creation failed");
    // TODO: should test if dir realy exists
}

#define TESTVEC {T(test_dir), T(test_recursive_dir)}

TEST();
