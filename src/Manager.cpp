#include "Manager.h"
using namespace std;

Manager::Manager(string name, string userName, string password, Club club): name_(name), userName_(userName), club_(club){
	//TODO : Hash du password
}

Manager::~Manager(){}

bool Manager::checkPassword(const string password){
	//TODO
	return true;
}

void Manager::changePassword(const string password){
	//TODO
}

Club* Manager::getClub(){
	return &club_;
}

string Manager::getUserName(){
	return userName_;
}

string Manager::getName(){
	return name_;
}



