#include "../test/libtest.h"

using namespace std;
#include "thread.h"

void * print_message(void*) {

    cout << "Threading" << endl;
    usleep(SECOND);
    cout << "Threading2" << endl;
    usleep(SECOND);
}

void test_thread() {
    Thread a = Thread(print_message, NULL);
    a.join();

}

#define TESTVEC {T(test_thread)}

TEST();
