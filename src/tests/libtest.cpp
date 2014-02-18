#include "libtest.h"
using namespace std;

int test(vector<func_struct> testvec){
    cout << "Executing " << testvec.size() << "tests..." << endl;
    for(int i=0; i < testvec.size(); i++){
        cout << testvec[i].name << endl;
        testvec[i].ptr();
    }
    return 0;
}