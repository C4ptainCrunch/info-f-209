#ifndef SVIEWUSER_H
#define SVIEWUSER_H

#include <cstdlib>
#include <vector>

#include "helpers.h"
#include "../../common/lib/json/json.h"
#include "../../common/lib/json/helpers.h"
#include "../../common/lib/exception/BadRequest.h"

class UserHandler;

namespace views {
void login(JsonValue * message, UserHandler * handler);
void signup(JsonValue * message, UserHandler * handler);
void userlist(JsonValue * message, UserHandler * handler);
}

#include "../UserHandler.h"
#include "../../common/lib/file/file.h"
#include "../../common/models/Manager.h"

#endif // SVIEWUSER_H
