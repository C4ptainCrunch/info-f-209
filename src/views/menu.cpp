#include "constants.h"

//*********************
// Divers
//*********************

void getConnectedList(JsonValue * json, UserHandler * thread){
    JsonList * reponse = new JsonList();
    std::vector<UserHandler*> * users = thread->getHandlers_listPtr();
    for (int i = 0 ; i < users->size() ; i++){
        reponse->add(new JsonDict());
        reponse[i]->add(JsonString(USERNAME), users[i]->getManager()->getUserName());
        reponse[i]->add(JsonString(LEVEL), (std::string) users[i]->getManager()->getClub()->getLevel())
    }
    thread->writeToClient(reponse->toString());
    delete reponse;
}

void challenge(JsonValue * json, UserHandler * thread){
    JsonDict * challengerInfos = new JsonDict();
    JsonInt * code = new JsonInt();
    code->setValue(FAIL);
    Manager * challenger = thread->getManager();
    std::vector<UserHandler*> * users = thread->getHandlers_listPtr();
    bool find = false;
    int index = 0;
    Manager * user;
    while (index < users->size() and (not find)){
        user = users[index]->getManager();
        find = (user->getUserName() == json[USERNAME]);
        index++;
    }
    if (find){
        if (user->isFree()){
            thread->setFreeState(false);
            challengerInfos->add(JsonString(USERNAME), challenger->getUserName());
            challengerInfos->add(JsonString(LEVEL), (std::string) challenger->getClub()->getLevel());
            JsonString reponse = JsonString("answerToChallenge : " + challengerInfos->toString())
            user->writeToClient(reponse.toString());
            code->setValue(CODE_SUCCESS);
        }
        
    }
    thread->writeToClient(code->toString());
    delete challengerInfos;
    delete code;
} // code

void answerToChallenge(JsonValue * json, UserHandler * thread){
    char * reponse;
} //code

//*********************
// Menu
//*********************

void getInfo(JsonValue * json, UserHandler * thread){
    JsonDict * reponse = new JsonDict();
    Manager * user = thread->getManager();
    reponse->add(JsonString(USERNAME), user->getUserName());
    reponse->add(JsonString(LEVEL), (std::string) user->getClub()->getLevel());
    writeToClient(reponse->toString());
    delete reponse;
}

void getMoney(JsonValue * json, UserHandler * thread){
    JsonDict * reponse = new JsonDict();
    Manager * user = thread->getManager();
    reponse->add(JsonString(MONEY), (std::string) user->getClub()->getMoney());
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
    JsonDict * reponse = new JsonDict();
    Manager * user = thread->getManager();
    reponse->add(JsonString(MONEY), (std::string) user->getClub()->getMoney());
    writeToClient(reponse->toString());
    delete reponse;
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
