#ifndef IDENTIFICATION_H
#define IDENTIFICATION_H

#include <cstdlib>
#include <vector>
#include "../lib/file/files.h"
#include "../lib/json/json.h"
#include "../server/UserHandler.h"
#include "constants.h"
#include "../models/Manager.h"
#include "../lib/json/utils.h"

void logIn(JsonValue * message, UserHandler * thread);
void signUp(JsonValue * message, UserHandler * thread);
int main();

#endif // IDENTIFICATION_H