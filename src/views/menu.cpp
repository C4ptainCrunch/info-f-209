//*********************
// Divers
//*********************

/*void notifyServQuit(JsonValue * json, UserHandler * thread){
    char * reponse;
}*/

void getConnectedList(JsonValue * json, UserHandler * thread){
    JsonList * reponse = new JsonList();
    std::vector<UserHandler*> * users = thread->getHandlers_listPtr();
    for (int i = 0 ; i < users->size() ; i++){
        reponse->add(new JsonDict());
        reponse[i]->add(JsonString("name"), users[i]->getManager()->getUserName());
        reponse[i]->add(JsonString("level"), (std::string) users[i]->getManager()->getClub()->getLevel())
    }
    thread->writeToClient(reponse->toString());
    delete reponse;
}


void challenge(JsonValue * json, UserHandler * thread){
    JsonDict * challenger = new JsonDict();
    Manager * user = thread->getManager();
    std::vector<UserHandler*> * users = thread->getHandlers_listPtr();
    bool find = false;
    int index = 0;
    Manager * user;
    while (index < users->size() and (not find)){
        user = users[index];
        find = (user->getManager()->getUserName() == json["name"]);
        index++;
    }
    if (find){
        challenger->add(JsonString("name"), user->getUserName());
        challenger->add(JsonString("level"), (std::string) user->getClub()->getLevel());
        JsonString reponse = JsonString("answerToChallenge : " + challenger->toString())
        user->writeToClient(reponse.toString());
    } // bloque jusqu'à réponse?
    delete reponse;
} // code

/*void checkChallenge(JsonValue * json, UserHandler * thread){
    char * reponse;
} //bool*/

void getChallengerInfo(JsonValue * json, UserHandler * thread){
    char * reponse;
} //string name

void answerToChallenge(JsonValue * json, UserHandler * thread){
    char * reponse;
} //code

//*********************
// Menu
//*********************

void getInfo(JsonValue * json, UserHandler * thread){
    JsonDict * reponse = new JsonDict();
    Manager * user = thread->getManager();
    reponse->add(JsonString("name"), user->getUserName());
    reponse->add(JsonString("level"), (std::string) user->getClub()->getLevel());
    writeToClient(reponse->toString());
    delete reponse;
}

void getMoney(JsonValue * json, UserHandler * thread){
    JsonDict * reponse = new JsonDict();
    Manager * user = thread->getManager();
    reponse->add(JsonString("money"), (std::string) user->getClub()->getMoney());
    writeToClient(reponse->toString());
    delete reponse;
}

//*********************
// ManagerPlayers
//*********************

void getInTeamPlayerList(JsonValue * json, UserHandler * thread){
    char * reponse;
} // struct

void getOutOfTeamPlayerList(JsonValue * json, UserHandler * thread){
    char * reponse;
} // struct

void getDataOnPlayer(JsonValue * json, UserHandler * thread){
    char * reponse;
} // player

void healPlayer(JsonValue * json, UserHandler * thread){
    char * reponse;
} // bool -> code

void swapPlayer(JsonValue * json, UserHandler * thread){
    char * reponse;
} // code

//*********************
// ManageInfrastructure
//*********************

void getInfrastructureList(JsonValue * json, UserHandler * thread){
    char * reponse;
}

void updateInfrastructure(JsonValue * json, UserHandler * thread){
    char * reponse;
} //bool

//*********************
// AuctionHouse
//*********************

void getSellingPlayers()(JsonValue * json, UserHandler * thread){
    char * reponse;
}// struct

void sell(JsonValue * json, UserHandler * thread){
    char * reponse;
}// code

void bid(JsonValue * json, UserHandler * thread){
    char * reponse;
}// code

void getRoundOnBid(JsonValue * json, UserHandler * thread){
    char * reponse;
}// int

void getRemainingTimeOnRound(JsonValue * json, UserHandler * thread){
    char * reponse;
}// int

void getCurrentBid(JsonValue * json, UserHandler * thread){
    char * reponse;
}// int

void getBidderCount(JsonValue * json, UserHandler * thread){
    char * reponse;
}// int

void checkEndOfBid(JsonValue * json, UserHandler * thread){
    char * reponse;
}// bool


void endBid(JsonValue * json, UserHandler * thread){
    char * reponse;
}// code
