#include "libtest.h"
using namespace std;

int test(vector<func_struct> testvec){
    int fail = 0;

    cout << "\e[93mExecuting " << testvec.size() << " tests..." << endl;
    cout << "=====================\e[0m" << endl;
    for(int i=0; i < testvec.size(); i++){
        cout << endl << "Testing : " << testvec[i].name << "()"<< endl;
        cout << "--------------------------" << endl;
        try {
            testvec[i].ptr();
            cout << "\e[1;32mOk\e[0m" << endl;
        }
        catch (AssertFail e){
            fail++;
            cout << "\e[1;31mAssert error: " << e.what() << "\e[0m" << endl;
        }
        catch (exception e){
            fail++;
            cout << "\e[1;31mwhat" << "\e[0m" << endl;
        }
    }
    cout << "\e[93m=================\e[0m" << endl;
    if(fail == 0){
        cout << "Executed " << testvec.size() << " tests. \e[1;32mOK.\e[0m" << endl;
        return 0;
    }
    else {
        cout << "\e[1;31mFail " << fail << "/" << testvec.size() << "\e[0m" << endl;
        return 1;
    }

}

void assert(bool value, string message){
    if(!value){
        throw AssertFail(message);
    }
}

void assertFalse(bool value, string message){
    if(value){
        throw AssertFail(message);
    }
}

AssertFail::AssertFail(std::string message) : message(message) {}
std::string AssertFail::what() {
    return message;
}
