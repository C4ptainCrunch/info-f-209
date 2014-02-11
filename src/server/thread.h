class Thread //classe de l'objet mis en mémoire dans un thread
{
public:
	Thread(int fd, const JsonObjet * usersInfos);
	~Thread();
	bool isKownUser(std::String userName);
	std::String getConnected();
	void setConnected(std::String userName);
	int getSocket();

private:
	int userSocket;   // socket d'écoute du thread
	const JsonObject * usersInfos;// pointeur vers une structure contenant les log/password de tous les users
	std::String connected; // log du user connecté au socket du thread
};

// dériver Thread en ServerThread, AuctionThread, MatchThread, ManageThread, ... ?