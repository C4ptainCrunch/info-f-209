#define RCV_SIZE 2

void connection(const int socket){
    std::string response = "";
    char buffer[RCV_SIZE];

    sendTo(socket, "Hello, bite!");
    response = recieveFrom(socket, buffer);
    sendTo(socket, response);
    sendTo(socket, "Bye");
    close(socket);

}

/*void connection(const int fd, const JsonObject * usersInfos){
    sendTo(fd, "Hello, bite!\n");
    bool quit=false
    while(! quit)
    {
        std::string ping = recieveFrom(fd);
        sendTo(fd, ping);
        JsonObject json(ping);
        Thread thread=Thread(fd, usersInfos);
        if (json.getKey()=="user.login")
        {
	        logIn(&json, &thread)
        }
        else if (json.getKey()=="user.signup")
        {
	        signUp(&json, &thread)
        }
        else if (json.getKey()=="user.quit")
        {
	        quit=true;
        }
        else
        {
	        // erreur à gérer
        }
        if(thread.getConnected()!="~")
        {
	        quidditch(); // boucle infinie jusqu'à ce que le user demande de quitter le jeu
	        quit=true;
        }
    }
    close(fd);

}*/

/*
class Thread //classe de l'objet mis en mémoire dans un thread
{
	Thread(int fd, const JsonObjet * json)
	{
	    userSocket=fd;
	    userInfos=json;
	    connected="~"; //valeur sentinelle quand on ne sait pas qui est sur le socket (change au log in)

	}
	~Thread()
	{

	}
	bool isKownUser(std::String userName)
	{
	    // cherche un user dans une base de donnée et renvoi un bool
	}
	std::String getConnected()
	{
	    return connected;
	}
    void setConnected(std::String userName)
    {
	    connected=userName;
    }
    int getSocket()
    {
	    return userSocket;
    }
}
*/
