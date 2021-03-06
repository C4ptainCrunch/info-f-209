#ifndef SERV_VIEWMATCH_H
#define SERV_VIEWMATCH_H

#include <cstdlib>
#include <vector>

#include "helpers.h"
#include "../../common/lib/json/json.h"
#include "../../common/lib/json/helpers.h"
#include "../../common/lib/exception/BadRequest.h"

class UserHandler;

namespace views {
void end_turn(JsonValue * message, UserHandler * handler);
void surrender(JsonValue * message, UserHandler * handler);
}

#include "../UserHandler.h"

#endif
