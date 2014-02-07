#include <Json.h>

bool logIn(char* userName, char * password, const int fd)
{
	std::string log = recieveFrom(fd);
	std::string password = recieveFrom(fd);
	bool logged=false;
	if(userName==log and password)
	{
	    if(usersInfos[log]==password)
		{
			logged=true;
			std::string message="Authentification réussie, bienvenue "+log;
			sendTo(fd, message);
		}
	}
	return logged;
}

bool signUp(char* json, const int fd)
{
	bool signedUp=false;
	std::string log = recieveFrom(fd);
	std::string password = recieveFrom(fd);
	Json::Value usersInfos;
	Json::Reader infosReader;
	bool parsingSuccess=infoReader.parse(json, usersInfos);
	if(parsingSuccess)
	{
	    if("NULL"==usersInfos.get(log, "NULL"))
	    {
		    signedUp=true;
		    usersInfos[log]=password;
		    std::string message="Inscription réussie, bienvenue "+log;
		    sendTo(fd, message);
		}
	}
	return signedUp;
}
