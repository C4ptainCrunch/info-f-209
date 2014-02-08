//#include <json.h>  module json à coder

bool logIn(char * message, Thread * thread, JsonObject * usersInfos)  // usersInfo est un pointeur vers un json contenant l'ensemble des log et password connus
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

bool signUp(char* message, Thread * thread, JsonObject * usersInfo)  // reçoit un json avec l'ensemble des infos des users
{
	bool signedUp=false;
	char * reponseMessage;
	JsonObject json(message);     // classe JsonObject à définir dans le module
	char * userName=json.get("userName");
	if(usersInfo.get(userName)!="~")  // ~ étant une valeur sentinelle renvoyée quand l'élément cherché n'est pas dans le json, et utilisée ici pour vérifier si le userName est correct
	{
	    if(usersInfos.get(userName)==json.get(password))   // le password
	    {
			signedUp=true;
			usersInfos.addItem(log,password);  // rajoute le nouveau compte
			reponseMessage="blablabla";  //à définir plus tard
		}
		else
		{
			reponseMessage="blablabla2";  //à définir plus tard
		}
	}
	else
	{
		reponseMessage="blablabla3";  //à définir plus tard
	}
	JsonObject reponse(reponseMessage);
	thread.send_message("user.login", reponse);
	return signedUp;
}
