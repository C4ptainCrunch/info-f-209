#ifndef SERVVIEWMANAGEMENT_H
#define SERVVIEWMANAGEMENT_H

#include <cstdlib>
#include <vector>

#include "helpers.h"
#include "../../common/lib/json/json.h"
#include "../../common/lib/json/helpers.h"
#include "../../common/lib/exception/BadRequest.h"

class UserHandler;

namespace views {
void playerlist(JsonValue * message, UserHandler * handler);
}

#include "../UserHandler.h"
#include "../../common/lib/file/file.h"
#include "../../common/models/Manager.h"

#endif
