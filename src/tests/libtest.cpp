#include "libtest.h"
using namespace std;

int test(vector<func_struct> testvec){
    int fail = 0;
    bool pass = true;
    bool except = true;
    string error = "";
    string reset = "";

    cout << YELLOW << "Executing " << testvec.size() << " tests:" << WHITE << endl;

    for(int i=0; i < testvec.size(); i++){
        pass = false;
        except = true;

        cout << testvec[i].name + "() ...";

        try {
            testvec[i].ptr();
            pass = true;
        }
        catch (AssertFail e){
            fail++;
            except = false;
            error = e.what();
        }
        catch (runtime_error e){
            fail++;
            error = e.what();
        }
        catch (exception e){
            fail++;
            error = e.what();
        }
        reset = "";
        int max = testvec[i].name.length() + 6;
        for(int i=0; i < max; i++)
            reset += DEL;
        cout << reset << "[";
        if(pass)
            cout << GREEN << " Ok ";
        else {
            if(except)
                cout << PURPLE << "THRO";
            else
                cout << RED << "FAIL";
        }
        cout << WHITE << "] ";
        if(!pass)
            cout << error;
        else
            cout << testvec[i].name << "()";
        cout << endl;
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
        errorMessage+=": " + string(BOLD) + message;
    return errorMessage;
}
