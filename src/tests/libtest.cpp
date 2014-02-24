#include "libtest.h"
using namespace std;

int test(vector<func_struct> testvec){
    int fail = 0;

    cout << "\e[93mExecuting " << testvec.size() << " tests: \e[0m" << endl;

    for(int i=0; i < testvec.size(); i++){
        printf("%-25s ...", (testvec[i].name + "():").c_str());

        try {
            testvec[i].ptr();
            cout << "\b\b\b[ \e[1;32mOk\e[0m ]" << endl;
        }
        catch (AssertFail e){
            fail++;
            cout << "\b\b\b[\e[1;31mFAIL\e[0m] " << e.what() << "\e[0m" << endl;
        }
        catch (exception e){
            fail++;
            cout << "\b\b\b[\e[1;34mTHRO\e[0m] " << e.what() << "\e[0m" << endl;
        }
    }
    cout << endl;
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
        errorMessage+="in " + func + "() ";
    if(file!="")
        errorMessage+="in " + file;
    if(line>0){
        if(file=="")
            errorMessage+=" At line " + to_string(line);
        else
            errorMessage+=":" + to_string(line);
    }
    if(message!="")
        errorMessage+=": " + message;
    return errorMessage;
}
