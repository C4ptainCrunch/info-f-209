#include "../test/libtest.h"
#include "thread.h"

using namespace std;


void * print_message(void*) {

    cout << "Threading" << endl;
    sleep(1);
    cout << "Threading2" << endl;
    sleep(1);
    return 0;
}

void test_thread() {
    Thread a = Thread(print_message, NULL);
    a.join();

}

#define TESTVEC {T(test_thread)}

TEST();
