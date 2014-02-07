#include "identification.h"
	
}

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
			std::String message="Authentification réussie, bienvenue "+log;
			sendTo(fd, message);
		}
	}
	return logged;
}
	
