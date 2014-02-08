//#include <json.h>  module json à coder

bool logIn(char * message, pthread_t * thread, JsonObject * usersInfos)  // usersInfo est un pointeur vers un json contenant l'ensemble des log et password connus
{
	bool logged=false;
	char * reponseMessage;
	JsonObject json(message);     // classe JsonObject à définir dans le module
	JsonObject reponse;
	char * userName=json.get("userName");
	if(usersInfo.get(userName)!="~")  // ~ étant une valeur sentinelle renvoyée quand l'élément cherché n'est pas dans le json, et utilisée ici pour vérifier si le userName est correct
	{
	    if(usersInfos.get(userName)==json.get(password))   // le password
	    {
			logged=true;
			reponseMessage="blablabla";  //à définir plus tard
			thread.send_message("user.login", reponseMessage);
		}
		else
		{
			reponseMessage="blablabla2";  //à définir plus tard
			thread.send_message("user.login", reponseMessage);
		}
	}
	else
	{
		reponseMessage="blablabla3";  //à définir plus tard
		thread.send_message("user.login", reponseMessage);
	}
	return logged;
}

bool signUp(char* message, pthread_t * thread, JsonObject * usersInfo)  // reçoit un json avec l'ensemble des infos des users
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
