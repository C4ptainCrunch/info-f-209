#include <iostream>

#include <sstream>
#include "utilitary.h"

using namespace std;


//Utilitaire--------------------------------------------------------------------------
vector<string> split(const string &text, char delim)
{
    stringstream ss(text);
    string item;
    vector<string> elems;

    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }

    return elems;
}
