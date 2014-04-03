#include "SocketError.h"

using namespace std;

SocketError::SocketError(string message): runtime_error::runtime_error(message) {}
