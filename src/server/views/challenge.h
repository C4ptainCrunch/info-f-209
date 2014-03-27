#ifndef SVIEWMATCH_H
#define SVIEWMATCH_H

#include <cstdlib>
#include <vector>

#include "helpers.h"
#include "../../common/lib/json/json.h"
#include "../../common/lib/json/helpers.h"
#include "../../common/lib/exception/BadRequest.h"

class UserHandler;

namespace views {
void challenge(JsonValue * message, UserHandler * handler);
void accept_challenge(JsonValue * message, UserHandler * handler);
}

#include "../UserHandler.h"

#endif // SVIEWMATCH_H
