#ifndef IDENTIFICATION_H
#define IDENTIFICATION_H

#include <cstdlib>
#include <vector>

#include "../../common/lib/json/json.h"

class UserHandler;
void logIn(JsonValue * message, UserHandler * handler);
void logIn(JsonValue * message, UserHandler * handler);
//void signUp(JsonValue * message, UserHandler * handler);
#include "../UserHandler.h"
#include "../../common/lib/file/files.h"
#include "constants.h"
#include "../../common/models/Manager.h"

#endif // IDENTIFICATION_H