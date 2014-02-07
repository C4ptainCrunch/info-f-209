#include <map>

map<std::String, qtd::String>* loadUsersInfos()
{
    std::String fileName="UsersInfos.json";
	map<std::String, std::String>* usersInfos= new map<std::String, std::String>;
	//parser(usersInfos, fileName);
	return usersInfos;
	
}

bool logIn(map<std::String, std::String> usersInfos, const int fd)
{
	std::string log = recieveFrom(fd);
	std::string password = recieveFrom(fd);
	bool logged=false;
	if(usersInfos.find(log)!=end())
	{
	    if(usersInfos[log]==password)
		{
			logged=true;
		}
	}
	return logged;
}
	