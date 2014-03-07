#ifndef JSON_HELPERS_H
#define JSON_HELPERS_H

#include "json.h"
#include "../exception/BadRequest.h"

std::string getString(JsonDict * dict, std::string key);

#endif
