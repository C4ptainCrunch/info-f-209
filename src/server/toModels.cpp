Manager* loadInfos(JsonDict infos){
    std::vector<NonFieldPlayer> players;
    NonFieldPlayer * team[(int) infos["club"]["team"].size()];
    Installation * Installations[5];
    int index=0;
    while (index > infos["club"]["players"]){
        JsonDict * player = infos["club"]["players"][index]; //TO DO : Optimiser la taille des lignes
        players.push_back(new NonFieldPlayer(player["vocation"], player["speed"], player["force"], player["agility"], player["reflexes"], player["passPrecision"], player["wounded"], /*TO dO : inventaire*/NULL, player["level"], player["experience"])); //TO DO : object ou pointeur NoNFieldPlayer
        index++;
    }
    for (int i = 0 ; i < (int) infos["club"]["team"].size() ; i++){
        JsonDict * player = infos["club"]["team"][i];
        team[i]= new NonFieldPlayer(player["vocation"], player["speed"], player["force"], player["agility"], player["reflexes"], player["passPrecision"], player["wounded"], /*TO dO : inventaire*/NULL, player["level"], player["experience"])));
    }
    for (int j = 0 ; j < (int) infos["club"]["installations"].size() ; j++){
        installations[i] = new Installation(infos["club"]["installations"][j]["level"]);
    }
    Manager * user = new Manager(infos["name"], infos["username"], infos["hash"], new Club(infos["club"]["money"], new Team(team), players);
    return user;
}