#include "helpers.h"

using namespace std;

string getString(JsonDict * dict, string key) {
    JsonString * str_ptr = JSTRING((*dict)[key]);
    if (str_ptr == NULL) {
        throw BadRequest("Malformatted Json : missing key : " + key);
    }

    return (string) * str_ptr;
}

std::string getString(JsonList * list, int i) {
    JsonString * str_ptr = JSTRING((*list)[i]);
    if (str_ptr == NULL) {
        throw BadRequest("Malformatted Json : out of range : " + to_string(i));
    }

    return (string) * str_ptr;
}

bool getBool(JsonDict * dict, string key) {
    JsonBool * bool_ptr = JBOOL((*dict)[key]);
    if (bool_ptr == NULL) {
        throw BadRequest("Malformatted Json : missing key : " + key);
    }

    return (bool) *bool_ptr;
}

JsonList * getList(JsonDict * dict, string key) {
    JsonList * list_ptr = JLIST((*dict)[key]);
    if (list_ptr == NULL) {
        throw BadRequest("Malformatted Json : missing key : " + key);
    }

    return list_ptr;
}

int getInt(JsonDict * dict, std::string key) {
    JsonInt * int_ptr = JINT((*dict)[key]);
    if (int_ptr == NULL) {
        throw BadRequest("Malformatted Json : missing key : " + key);
    }

    return (int) *int_ptr;
}

JsonDict * castDict(JsonValue * val) {
    JsonDict * dictMessage = JDICT(val);

    if (dictMessage == NULL) {
        throw BadRequest("Malformatted request. Need a JSON dict");
    }
    return dictMessage;
}
