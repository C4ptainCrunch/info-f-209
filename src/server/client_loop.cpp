#include "client_loop.h"

using namespace std;


void * client_loop(void * arg) {
    UserHandler * handler = (UserHandler *) arg;
    try {
        handler->loop();
    }
    catch (exception & e) {
        try {
            JsonDict answer;

            answer.add("Error", new JsonString("Unknown error"));
            answer.add("code", new JsonInt(500));
            handler->writeToClient("error", &answer);
        }
        catch (exception & e) {
            cout << "Uncought exception while handling uncought exception, very BAD !" << endl;
            cout << e.what() << endl;
        }
        catch (...) {
            cout << "Uncought UNKNOWN exception while handling uncought exception, very VERY BAD !" << endl;
        }
        cout << "Uncought exception, this is bad !" << endl;
        cout << e.what() << endl;
    }
    catch (...) {
        cout << "Uncought UNKNOWN exception, very BAD !" << endl;
    }
    delete handler;
    cout << "Client disconnected." << endl;

    return 0;
}
