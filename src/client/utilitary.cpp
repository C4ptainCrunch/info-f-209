#include <iostream>

#include <sstream>
#include <algorithm>
#include "utilitary.h"

using namespace std;


//Utilitaire--------------------------------------------------------------------------
vector<string> split(const string & text, char delim) {
    stringstream ss(text);
    string item;
    vector<string> elems;

    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }

    return elems;
}

int stringToInt(const string & text) {
    return atoi(text.c_str());
}

bool isNumber(const string & text) {
    return !text.empty() && std::find_if(text.begin(), text.end(), [](char c) {return !std::isdigit(c); }) == text.end();
}
