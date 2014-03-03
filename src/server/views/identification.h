#ifndef IDENTIFICATION_H
#define IDENTIFICATION_H

#include <cstdlib>
#include <vector>

#include "../lib/json/json.h"

class UserHandler;
void logIn(JsonValue * message, UserHandler * handler);
void logIn(JsonValue * message, UserHandler * handler);
//void signUp(JsonValue * message, UserHandler * handler);
#include "../server/UserHandler.h"
#include "../lib/file/files.h"
#include "constants.h"
#include "../models/Manager.h"

#endif // IDENTIFICATION_H