#include <json.h>

bool logIn(char* json, const int fd)
{
	std::string log = recieveFrom(fd);
	std::string password = recieveFrom(fd);
	bool logged=false;
	Json::Value usersInfos;
	Json::Reader infosReader;
	if(parsingSuccess)
	{
	    if("NULL"!=usersInfos.get(log, "NULL"))   // vérifie si le compte existe
	    {
			if(usersInfos[log]==password)
			{
		        logged=true;
			    std::string message="Authentification réussie, bienvenue "+log;
			    sendTo(fd, message);
			}
		}
	}
	return logged;
}

bool signUp(char* json, const int fd)  // reçoit un json avec l'ensemble des infos des users
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
		    usersInfos[log]=password;                                    //enregistre le nouveau compte
		    std::string message="Inscription réussie, bienvenue "+log;
		    sendTo(fd, message);
		}
	}
	return signedUp;
}
