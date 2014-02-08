#include "Shop.h"

using namespace std;

Shop::Shop(string name,unsigned int income): Installation(1), income_(income), name_(name) {}

Shop::~Shop(){}

unsigned int Shop::getIncome(){
	return income_;
}

void Shop::setIncome(unsigned int income){
	income_ = income;
}

string Shop::getName(){
	return name_;
}
