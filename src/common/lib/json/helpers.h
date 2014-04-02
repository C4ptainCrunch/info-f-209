#ifndef JSON_HELPERS_H
#define JSON_HELPERS_H

#include "json.h"
#include "../exception/BadRequest.h"

std::string getString(JsonDict * dict, std::string key);
std::string getString(JsonList * list, int i);

bool getBool(JsonDict * dict, std::string key);
JsonList * getList(JsonDict * dict, std::string key);
int getInt(JsonDict * dict, std::string key);
JsonDict * castDict(JsonValue * val);


#endif
