//*********************
// Divers
//*********************

void notifyServQuit(JsonValue * json, UserHandler * thread){
    char * reponse;
}

void checkChallenge(JsonValue * json, UserHandler * thread){
    char * reponse;
} //bool

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
    std::string values = "{";
    Manager * user = thread->getManager();
    values += "name : " + (std::string) user->getUserName() + ", ";
    values += "level : " + (std::string) user->getClub()->getLevel();
    values += "}";
    writeToClient(values);
} //string name int level

void getMoney(JsonValue * json, UserHandler * thread){
    std::string value = "{money : ";
    value += thread->getManager()->getClub()->getMoney();
    writeToClient(value);
} //int

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
} // bool

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

//*********************
// ConnectedList
//*********************

void getConnectedList(JsonValue * json, UserHandler * thread){
    char * reponse;
}

void challenge(JsonValue * json, UserHandler * thread){
    char * reponse;
} // code