#ifndef VIEWS_HELPERS_H
#define VIEWS_HELPERS_H

#include <cstdlib>
#include <vector>

#include "../../common/lib/json/json.h"

class UserHandler;

void sendFail(UserHandler * handler, int errorcode, std::string topic, std::string message);

#include "../UserHandler.h"

#endif // VIEWS_HELPERS_H