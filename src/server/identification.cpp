//#include "json.h"  module json à coder
//#include "Thread.h"  module de l'objet appartenant au thread

bool logIn(char * message, Thread * thread)  //  l'ensemble des log et password connus est dans l'objet thread
{
	bool logged=false;
	char * reponseMessage;
	JsonObject json(message);     // classe JsonObject à définir dans le module
	char * userName=json.get("userName");
	if(usersInfo.getPassword(userName)!="~")  // ~ étant une valeur sentinelle renvoyée quand l'élément cherché n'est pas dans le json, et utilisée ici pour vérifier si le userName est correct
	{
	    if(thread.getPassword(userName)==json.get(password))   // vérifie le password
	    {
			logged=true;
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
	JsonObject reponse;
	thread.send_message("user.login", reponseMessage);
	return logged;
}

bool signUp(char* message, Thread * thread)
{
	bool signedUp=false;
	char * reponseMessage;
	JsonObject json(message);     // classe JsonObject à définir dans le module
	char * userName=json.get("userName");
	if(thread.getPassword(userName)!="~")  // ~ étant une valeur sentinelle renvoyée quand l'élément cherché n'est pas dans le json, et utilisée ici pour vérifier si le userName est correct
	{
	    if(thread.getPassword(userName)==json.get(password))
	    {
			signedUp=true;
			thread.addUserDatas(log,password);  // rajoute le nouveau compte
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
