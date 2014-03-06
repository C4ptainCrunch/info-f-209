#include "helpers.h"

using namespace std;

string getString(JsonDict * dict, string key){
    JsonString * str_ptr = JSTRING((*dict)[key]);
    if(str_ptr == NULL) {
        throw BadRequest("Malformatted Json : missing key : " + key);
    }

    return (string) *str_ptr;
}