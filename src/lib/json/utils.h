#include "ParseError.h"
#include <vector>

int skip_whitespace(std::string message, int start);
int skip_colon(std::string message, int start);
std::string cut_from(std::string message, int from);