#include "BadRequest.h"

using namespace std;

BadRequest::BadRequest(string message): runtime_error::runtime_error(message){}
