#include "helpers.h"

using namespace std;

string getString(JsonDict * dict, string key) {
    JsonString * str_ptr = JSTRING((*dict)[key]);
    if (str_ptr == NULL) {
        throw BadRequest("Malformatted Json : missing key : " + key);
    }

    return (string) * str_ptr;
}

bool getBool(JsonDict * dict, string key) {
    JsonBool * bool_ptr = JBOOL((*dict)[key]);
    if (bool_ptr == NULL) {
        throw BadRequest("Malformatted Json : missing key : " + key);
    }

    return (bool) * bool_ptr;
}
