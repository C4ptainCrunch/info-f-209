#include "libtest.h"
using namespace std;

int test(vector<func_struct> testvec){
    int fail = 0;

    cout << "Executing " << testvec.size() << " tests..." << endl;
    cout << "=====================" << endl;
    for(int i=0; i < testvec.size(); i++){
        cout << endl << "Testing : " << testvec[i].name << "()"<< endl;
        cout << "--------------------------" << endl;
        try {
            testvec[i].ptr();
            cout << "Ok" << endl;
        }
        catch (AssertFail e){
            fail++;
            cout << "Assert error: " << e.what() << endl;
        }
        catch (exception e){
            fail++;
            cout << "what" << endl;
        }
    }
    cout << "=================" << endl;
    if(fail == 0){
        cout << "Executed " << testvec.size() << " tests. OK." << endl;
        return 0;
    }
    else {
        cout << "Fail " << fail << "/" << testvec.size() << endl;
        return 1;
    }

}

void assert(bool value, string message){
    if(!value){
        throw AssertFail(message);
    }
}

AssertFail::AssertFail(std::string message) : message(message) {}
std::string AssertFail::what() {
    return message;
}
