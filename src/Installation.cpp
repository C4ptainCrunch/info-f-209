#include "Installation.h"

Installation::Installation(int level = 1) : level_(level){}

Installation::~Installation(){}

void Installation::improve(){
	level_ += 1;
}

int Installation::getLevel(){
	return level_;
}