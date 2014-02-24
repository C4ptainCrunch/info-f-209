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

void assert(bool value, string message, int line, string file, string func){
    if(!value){
        throw AssertFail(message, line, file, func);
    }
}

void assertFalse(bool value, string message, int line, string file, string func){
    assert(!value, message, line, file, func);
}

AssertFail::AssertFail(string message, int line, string file, string func) : message(message), line(line), file(file), func(func) {}

string AssertFail::what() {
    string errorMessage;
    if(func!="")
        errorMessage+="In function: " + func + " ";
    if(file!="")
        errorMessage+="In file: " + file + " ";
    if(line>0)
        errorMessage+="At line " + to_string(line) + " ";
    if(message!="")
        errorMessage+=": " + message;
    return errorMessage;
}
