//#include "json.h"  module json à coder
//#include "Thread.h"  module de l'objet appartenant au thread

void logIn(char * message, Thread * thread)  //  l'ensemble des log et password connus est dans l'objet thread
{
	char * reponseMessage;
	JsonObject json(message);     // classe JsonObject à définir dans le module
	char * userName=json.get("username");
	if(thread.isknownUser(userName))
	{
	    if(thread.getPassword(userName)==json.get("password"))   // vérifie le password
	    {
			reponseMessage="blablabla";  //à définir plus tard
			thread.setConnected(userName); // si connected change => authentification réussie, échec sinon (connected reste à "NULL" par exemple)
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
}

void signUp(char* message, Thread * thread)
{
	char * reponseMessage;
	JsonObject json(message);     // classe JsonObject à définir dans le module
	char * userName=json.get("userName");
	if(! thread.isKnownUser(userName))
	{
	    if(thread.getPassword(userName)==json.get("password"))
	    {
			thread.addUserDatas(userName, json.get("password"));  // rajoute le nouveau compte
			thread.setConnected(userName);
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
}
