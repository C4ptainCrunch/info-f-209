#include "../../common/lib/test/libtest.h"
#include "serverhandler.h"

using namespace std;


void test_connect() {
    ServerHandler sh = ServerHandler("localhost", 5000);
    ASSERT(sh.connect_socket(), "connection failed");
}

void test_connect_inex() {
    ServerHandler sh = ServerHandler("localhost", 1);
    ASSERT_FALSE(sh.connect_socket(), "connection should have failed");
}

void send_message() {
    ServerHandler sh = ServerHandler("localhost", 5000);
    ASSERT(sh.connect_socket(), "Connection failed");
    sh.send("plop:");
    string message;
    sh.recieve(message);
    ASSERT_EQUAL("error:{\"Bad request\" : \"Unknown topic : 'plop'\", \"code\" : 100}", message, "Bad error");
}

void send_without_connect() {
    bool catched = false;
    ServerHandler sh = ServerHandler("localhost", 5000);
    try {
        sh.send("youhou");
    }
    catch (...) {
        catched = true;
    }
    ASSERT(catched, "Exception not thrown");
}

#define TESTVEC {T(test_connect), T(test_connect_inex), T(send_message), T(send_without_connect)}

TEST();
