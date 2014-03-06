#include <iostream>

#include "../lib/socket/Socket.h"
#include "client.h"
#include "GameState.h"
#include "utilitary.h"
#include "../lib/json/json.h"
#include "../views/constants.h"

//Les définitions ci dessous sont toutes les valeurs que peut avoir l'attribut 'status' de la class de base GameState.
//Valeurs générales :
enum STATUS {
    STATUS_DEFAULT = 0,
    STATUS_BAD_ENTRY = -1,
    STATUS_RETURNMENU = -2,
    STATUS_QUIT = -3,
    STATUS_SUCCESS = -4,
    STATUS_FAILURE = -5,
    STATUS_NO_FUNDS = -6
};

enum UNLOGGED {
    UNLOGGED_CONNECTED = 1,
    UNLOGGED_CONNECT = 2,
    UNLOGGED_REGISTER = 3,
    UNLOGGED_WRONG_LOGS = 4,
    UNLOGGED_ALREADY_USED = 5,
    UNLOGGED_REGISTERED = 6
};

enum MENU {
    MENU_MANAGEPLAYERS = 1,
    MENU_MANAGEINFRASTRUCTURES = 2,
    MENU_AUCTIONHOUSE = 3,
    MENU_CONNECTEDLIST = 4
};

enum MANAGE_PLAYERS {
    MANAGE_PLAYERS_HEAL = 1,
    MANAGE_PLAYERS_DISPLAY = 2,
    MANAGE_PLAYERS_SWAP = 3,
    MANAGE_PLAYERS_INVALID_NAME = 4,
    MANAGE_PLAYERS_HEALING_UNWOUND = 5
};

#define HEAL_PRICE 500

using namespace std;

GameState::GameState(Client * client): client_(client), status_(STATUS_DEFAULT) {}

GameState::~GameState() {}

//FONCTIONS D'APPELS SERVEURS :


//log in

int GameState::log(string username, string password) {
    string message = "logIn : ";
    int res;
    JsonInt JSres;
    JsonString JSusername(username);
    JsonString JSpass(password);
    JsonDict dict;
    dict.add("username", &JSusername);
    dict.add("password", &JSpass);
    message += dict.toString();
    client_->send(message);
    client_->recv(message);
    JSres.fromString(message);
    res = JSres.getValue();
    return res;
}
int GameState::sign(string username, string password) {
    string message = "signUp : ";
    int res;
    JsonInt JSres;
    JsonString JSusername(username);
    JsonString JSpass(password);
    JsonDict dict;
    dict.add("username", &JSusername);
    dict.add("password", &JSpass);
    message += dict.toString();
    client_->send(message);
    client_->recv(message);
    JSres.fromString(message);
    res = JSres.getValue();
    return res;
}

//general

struct objectDataPair GameState::getUserInfo() {
    struct objectDataPair user;
    user.name = "uglyfakka";
    user.level = 12;
    return user;
}

int GameState::getMoney() {
    return 69;
}

//team management

vector<int> GameState::getPlayerList() {
    vector<int> vec;
    return vec;
}

NonFieldPlayer GameState::getDataOnPlayer(int pos) {
    NonFieldPlayer nfp;
    return nfp;
}
bool GameState::healPlayer(int pos) {
    return true;
}
bool GameState::swapPlayer(int pos1, int pos2) {
    return true;
}

//infrastructures management
vector<int> GameState::getInfrastructureList() {}
bool GameState::UpdateInfrastructure(int ID) {}

//auction house
vector<struct objectDataPair> GameState::getSellingPlayer() {}
int GameState::sell(string name, int prix) {}
int GameState::bid(string name) {}
int GameState::getRoundOnBid(string name) {}
int GameState::getRemainingTimeOnRound(string name) {}
int GameState::getCurrentBid(string name) {}
int GameState::getBidderCount(string name) {}
bool GameState::checkEndOfBid(string name) {}
int GameState::endBid(string name) {}

//user list
vector<struct objectDataPair> GameState::getConnectedList() {}
int GameState::challenge(string name) {}

//Intro-------------------------------------------------------------------------------
IntroState::IntroState(Client * client): GameState(client) {}
void IntroState::handleEvents() {}
void IntroState::logic() {
    client_->setNextState(STATE_UNLOGGED);
}
void IntroState::display() {
    cout << "Bienvenue à Quidditch Manager 2014!" << endl; //Rework
}

//Unlogged-------------------------------------------------------------------------
UnloggedState::UnloggedState(Client * client): GameState(client) {
    cout << "Entrez l'option souhaité avec les paramètres requis délimités par un espace." << endl;
    cout << "Exemple : '1 Usr mdp'" << endl;
    cout << endl;
    display();
}
void UnloggedState::handleEvents() {
    string inputString;
    getline(cin, inputString);
    vector<string> inputVec = split(inputString, ' ');
    parse(inputVec); //Status est modifié dans parse.
}

void UnloggedState::logic() {
    int res; //réponse du serveur
    switch (status_) { //status_ est modifié dans handleEvent
        case UNLOGGED_CONNECT:
            res = log(nameInput_, passInput_); //appel serveur ici

            if (res == SUCCESS) {
                status_ = UNLOGGED_CONNECTED;
                client_->setNextState(STATE_MENU);
            }
            else
            if (res == FAIL) {
                status_ = UNLOGGED_WRONG_LOGS;
            }
            break;

        case UNLOGGED_REGISTER:
            res = sign(nameInput_, passInput_);

            if (res == SUCCESS) {
                status_ = UNLOGGED_REGISTERED;
            }
            else
            if (res == FAIL) {
                status_ = UNLOGGED_ALREADY_USED;
            }
            break;

        case STATUS_QUIT:
            client_->setNextState(STATE_EXIT);
            break;
    }
}
void UnloggedState::display() {
    switch (status_) {
        case STATUS_DEFAULT:
            cout << "Se connecter : 1 - Nom d'utilisateur - Mot de passe" << endl;
            cout << "S'enregistrer : 2 - Nom d'utilisateur - Mot de passe" << endl;
            cout << "Quitter : Q" << endl;
            cout << endl;
            break;
        case UNLOGGED_CONNECTED:
            cout << "Connecté." << endl;
            cout << endl;
            break;
        case UNLOGGED_WRONG_LOGS:
            cout << "Nom de compte ou mot de passe incorrecte." << endl;
            cout << endl;
            break;
        case UNLOGGED_REGISTERED:
            cout << "Enregistrement terminé" << endl;
            cout << endl;
            break;
        case UNLOGGED_ALREADY_USED:
            cout << "Nom de compte déjà utilisé." << endl;
            cout << endl;
            break;
        case STATUS_BAD_ENTRY:
            cout << "Erreur : votre entrée est incorrecte." << endl;
            cout << endl;
            break;
    }

}

void UnloggedState::parse(vector<string> & inputVec) {
    if (inputVec.empty() == true) { //S'il n'y a pas d'entrée utilisateur
        status_ = STATUS_BAD_ENTRY;
    }
    else {
        string option = inputVec[0];
        if (option.size() != 1) { //Si le premier token est plus long qu'un caractèred
            status_ = STATUS_BAD_ENTRY;
        }
        else {
            switch (option.c_str()[0]) { //On switch sur le premier caractère
                case '1': //Demande de connection
                    if (inputVec.size() == 3) {
                        nameInput_ = inputVec[1];
                        passInput_ = inputVec[2];
                        status_ = UNLOGGED_CONNECT;
                    }
                    else {
                        status_ = STATUS_BAD_ENTRY;
                    }
                    break;
                case '2': //Demande d'enregistrement
                    if (inputVec.size() == 3) {
                        nameInput_ = inputVec[1];
                        passInput_ = inputVec[2];
                        status_ = UNLOGGED_REGISTER;
                    }
                    else {
                        status_ = STATUS_BAD_ENTRY;
                    }
                    break;
                case 'q': //Demande de quit
                case 'Q':
                    status_ = STATUS_QUIT;
                    break;
                default: //Si n'importe quoi d'autre est entré
                    status_ = STATUS_BAD_ENTRY;
                    break;
            }
        }
    }
}
//Menu-------------------------------------------------------------------------

MenuState::MenuState(Client * client): GameState(client) {
    struct objectDataPair usr;
    usr = getUserInfo();
    name_ = usr.name;
    level_ = usr.level;
    display();
}
void MenuState::handleEvents() {
    string inputString;
    getline(cin, inputString);
    vector<string> inputVec = split(inputString, ' ');
    parse(inputVec);
}
void MenuState::logic() {
    switch (status_) {
        case MENU_MANAGEPLAYERS:
            client_->setNextState(STATE_MANAGE_PLAYERS);
            break;
        case MENU_MANAGEINFRASTRUCTURES:
            client_->setNextState(STATE_MANAGE_INFRASTRUCTURES);
            break;
        case MENU_AUCTIONHOUSE:
            client_->setNextState(STATE_AUCTION_HOUSE);
            break;
        case MENU_CONNECTEDLIST:
            client_->setNextState(STATE_CONNECTEDLIST);
            break;
        case STATUS_QUIT:
            client_->setNextState(STATE_EXIT);
            break;
    }
}
void MenuState::display() {
    int money = getMoney(); //mettre à jour le niveau.

    switch (status_) {
        case STATUS_DEFAULT:
            cout << name_ << ". Niveau " << level_ << ". Argent : " << money << " crédits." << endl << endl;
            cout << "Gérer votre équipe : 1" << endl;
            cout << "Gérer vos infrastructures : 2" << endl;
            cout << "Accéder à l'hotel de vente : 3" << endl;
            cout << "Voir la liste des managers connectés : 4" << endl;
            cout << "Quitter : Q" << endl;
            cout << endl;
            break;
        case STATUS_BAD_ENTRY:
            cout << "Erreur : votre entrée est incorrecte." << endl;
            cout << endl;
            break;
    }
}

void MenuState::parse(vector<string> & inputVec) {
    if (inputVec.empty() == true) {
        status_ = STATUS_BAD_ENTRY;
    }
    else {
        string option = inputVec[0];
        if (option.size() != 1 or inputVec.size() != 1) {
            status_ = STATUS_BAD_ENTRY;
        }
        else {
            switch (option.c_str()[0]) {
                case '1': //Gestion d'équipe
                    status_ = MENU_MANAGEPLAYERS;
                    break;
                case '2': //Gestion des infrastructures
                    status_ = MENU_MANAGEINFRASTRUCTURES;
                    break;
                case '3': //Hotel des ventes
                    status_ = MENU_AUCTIONHOUSE;
                    break;
                case '4': //Liste de connectés
                    status_ = MENU_CONNECTEDLIST;
                    break;
                case 'q':
                case 'Q': //Demande de quit
                    status_ = STATUS_QUIT;
                    break;
                default:
                    status_ = STATUS_BAD_ENTRY;
                    break;
            }
        }
    }
}


//ManagePlayer-------------------------------------------------------------------------

ManagePlayerState::ManagePlayerState(Client * client): GameState(client) {
    display();
}
void ManagePlayerState::handleEvents() {
    string inputString;
    getline(cin, inputString);
    vector<string> inputVec = split(inputString, ' ');
    parse(inputVec);
}
void ManagePlayerState::logic() {
    switch (status_) {
        case MANAGE_PLAYERS_DISPLAY:
            if (isPlayerValid(playerBuff1_)) {
                displayPlayer(getDataOnPlayer(playerBuff1_));
            }
            else {
                status_ = MANAGE_PLAYERS_INVALID_NAME;
            }
            break;
        case MANAGE_PLAYERS_HEAL:
            if (isPlayerValid(playerBuff1_)) {
                if (getDataOnPlayer(playerBuff1_).isWounded() == true) {
                    if (getMoney() >= HEAL_PRICE) {
                        if (healPlayer(playerBuff1_)) {
                            status_ = STATUS_SUCCESS;
                        }
                        else {
                            status_ = STATUS_FAILURE;
                        }
                    }
                    else {
                        status_ = STATUS_NO_FUNDS;
                    }
                }
                else {
                    status_ = MANAGE_PLAYERS_HEALING_UNWOUND;
                }
            }
            else {
                status_ = MANAGE_PLAYERS_INVALID_NAME;
            }
            break;
        case MANAGE_PLAYERS_SWAP:
            if (isPlayerValid(playerBuff1_) and isPlayerValid(playerBuff2_)) {
                if (swapPlayer(playerBuff1_, playerBuff2_)) {
                    status_ = STATUS_SUCCESS;
                }
                else {
                    status_ = STATUS_FAILURE;
                }
            }
            else {
                status_ = MANAGE_PLAYERS_INVALID_NAME;
            }
            break;
        case STATUS_RETURNMENU:
            client_->setNextState(STATE_MENU);
            break;
    }
}
void ManagePlayerState::display() {
    int money = getMoney(); //mettre à jour le niveau.
    vector<int> vec;

    switch (status_) {
        case STATUS_DEFAULT:
            cout << "Liste des joueurs :" << endl;
            displayPlayerList(vec);
            cout << endl;
            cout << "Argent : " << money << " crédits." << endl << endl;
            cout << "Voir les informations sur un joueur : 1 - numero du joueur" << endl;
            cout << "Soigner un joueur blessé (prix : " << HEAL_PRICE << ") : 2 - numero du joueur" << endl;
            cout << "Déplacer des joueurs : 3 - numero du joueur 1 - numero du joueur 2" << endl;
            cout << "Retourner au menu : 4" << endl;
            cout << endl;
            break;
        case MANAGE_PLAYERS_HEALING_UNWOUND:
            cout << "Erreur : le joueur selectionné n'est pas blessé." << endl;
            cout << endl;
            break;
        case STATUS_NO_FUNDS:
            cout << "Vous ne disposez pas assez d'argent." << endl;
            cout << endl;
        case STATUS_SUCCESS:
            cout << "Operation terminée." << endl;
            cout << endl;
            break;
        case STATUS_FAILURE:
            cout << "Echec de l'opération." << endl;
            cout << endl;
            break;
        case MANAGE_PLAYERS_INVALID_NAME:
            cout << "Erreur : nom du joueur selectionné incorrect." << endl;
            cout << endl;
            break;
        case STATUS_BAD_ENTRY:
            cout << "Erreur : votre entrée est incorrecte." << endl;
            cout << endl;
            break;
    }
}

void ManagePlayerState::displayPlayer(NonFieldPlayer player) {
    bool wounded = player.isWounded();
    if (wounded) {
        cout << "État : blessé" << endl;
    }
    else {
        cout << "État : en forme" << endl;
    }
    cout << "Niveau : " << player.getLevel() << endl;
    cout << "Vitesse : " << player.getSpeed() << endl;
    cout << "Force : " << player.getForce() << endl;
    cout << "Agilité : " << player.getAgility() << endl;
    cout << "Réflèxes : " << player.getReflexes() << endl;
    cout << "Précision de passe : " << player.getPassPrecision() << endl;
    cout << endl;
}

bool ManagePlayerState::isPlayerValid(int pos) {
    return true;
}

void ManagePlayerState::displayPlayerList(vector<int> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        cout << i << " : Niveau " << vec[i] << endl;
        if (i == 6) {
            cout << "-----------------------" << endl;
        }
    }
}

void ManagePlayerState::parse(vector<string> & inputVec) {
    if (inputVec.empty() == true) {
        status_ = STATUS_BAD_ENTRY;
    }
    else {
        string option = inputVec[0];
        if (option.size() != 1) {
            status_ = STATUS_BAD_ENTRY;
        }
        else {
            switch (option.c_str()[0]) {
                case '1': //Infos détaillés
                    if (inputVec.size() == 2 and isNumber(inputVec[1])) {
                        status_ = MANAGE_PLAYERS_DISPLAY;
                        playerBuff1_ = stringToInt(inputVec[1]); //on place l'entry du joueur dans le buffer de la classe pour qu'il soit analysé à logic
                    }
                    else {
                        status_ = STATUS_BAD_ENTRY;
                    }
                    break;
                case '2': //Soigner un joueur
                    if (inputVec.size() == 2  and isNumber(inputVec[1])) {
                        status_ = MANAGE_PLAYERS_HEAL;
                        playerBuff1_ = stringToInt(inputVec[1]);
                    }
                    else {
                        status_ = STATUS_BAD_ENTRY;
                    }
                    break;
                case '3': //Swap des joueurs
                    if (inputVec.size() == 3  and(isNumber(inputVec[1]) and isNumber(inputVec[2]))) {
                        status_ = MANAGE_PLAYERS_SWAP;
                        playerBuff1_ = stringToInt(inputVec[1]);
                        playerBuff2_ = stringToInt(inputVec[2]);
                    }
                    else {
                        status_ = STATUS_BAD_ENTRY;
                    }
                    break;
                case '4': //Retour au menu
                    if (inputVec.size() == 1) {
                        status_ = STATUS_RETURNMENU;
                    }
                    else {
                        status_ = STATUS_BAD_ENTRY;
                    }
                    break;
                default:
                    status_ = STATUS_BAD_ENTRY;
                    break;
            }
        }
    }
}


//ManageInfrastructure-------------------------------------------------------------------------

ManageInfrastructureState::ManageInfrastructureState(Client * client): GameState(client) {
    display();
}
void ManageInfrastructureState::handleEvents() {
    string inputString;
    getline(cin, inputString);
    vector<string> inputVec = split(inputString, ' ');
    parse(inputVec);
}

void ManageInfrastructureState::logic() {
    switch (status_) {
        case STATUS_RETURNMENU:
            client_->setNextState(STATE_MENU);
            break;
    }
}

void ManageInfrastructureState::display() {
    switch (status_) {
        case STATUS_DEFAULT:
            cout << "Infrastructures : " << endl;
            cout << "Créer une infirmerie. : 1" << endl; //pour plus tard, spécialiser les messages (créer -> améliorer)
            cout << "Créer un shop : 2" << endl;
            cout << "Revenir au menu : 3" << endl;
            cout << endl;
            break;
        case STATUS_BAD_ENTRY:
            cout << "Erreur : votre entrée est incorrecte." << endl;
            cout << endl;
            break;
    }
}

void ManageInfrastructureState::parse(vector<string> & inputVec) {
    if (inputVec.empty() == true) {
        status_ = STATUS_BAD_ENTRY;
    }
    else {
        string option = inputVec[0];
        if (option.size() != 1 or inputVec.size() != 1) {
            status_ = STATUS_BAD_ENTRY;
        }
        else {
            switch (option.c_str()[0]) {
                case '3': //Retour au menu
                    status_ = STATUS_RETURNMENU;
                    break;
                default:
                    status_ = STATUS_BAD_ENTRY;
                    break;
            }
        }
    }
}


//AuctionHouse-------------------------------------------------------------------------

AuctionHouseState::AuctionHouseState(Client * client): GameState(client) {
    display();
}
void AuctionHouseState::handleEvents() {
    string inputString;
    getline(cin, inputString);
    vector<string> inputVec = split(inputString, ' ');
    parse(inputVec);
}

void AuctionHouseState::logic() {
    switch (status_) {
        case STATUS_RETURNMENU:
            client_->setNextState(STATE_MENU);
            break;
    }
}

void AuctionHouseState::display() {
    switch (status_) {
        case STATUS_DEFAULT:
            cout << "Hotel des ventes : " << endl;
            cout << "Revenir au menu : 1" << endl;
            cout << endl;
            break;
        case STATUS_BAD_ENTRY:
            cout << "Erreur : votre entrée est incorrecte." << endl;
            cout << endl;
            break;
    }
}

void AuctionHouseState::parse(vector<string> & inputVec) {
    if (inputVec.empty() == true) {
        status_ = STATUS_BAD_ENTRY;
    }
    else {
        string option = inputVec[0];
        if (option.size() != 1 or inputVec.size() != 1) {
            status_ = STATUS_BAD_ENTRY;
        }
        else {
            switch (option.c_str()[0]) {
                case '1': //Retour au menu
                    status_ = STATUS_RETURNMENU;
                    break;
                default:
                    status_ = STATUS_BAD_ENTRY;
                    break;
            }
        }
    }
}


//ConnectedList--------------------------------------------------------------------------

ConnectedListState::ConnectedListState(Client * client): GameState(client) {
    display();
}
void ConnectedListState::handleEvents() {
    string inputString;
    getline(cin, inputString);
    vector<string> inputVec = split(inputString, ' ');
    parse(inputVec);
}
void ConnectedListState::logic() {
    switch (status_) {
        case STATUS_RETURNMENU:
            client_->setNextState(STATE_MENU);
            break;
    }
}
void ConnectedListState::display() {
    switch (status_) {
        case STATUS_DEFAULT:
            cout << "Joueurs connectés : " << endl;
            cout << "Revenir au menu : 1" << endl;
            cout << endl;
            break;
        case STATUS_BAD_ENTRY:
            cout << "Erreur : votre entrée est incorrecte." << endl;
            cout << endl;
            break;
    }
}

void ConnectedListState::parse(vector<string> & inputVec) {
    if (inputVec.empty() == true) {
        status_ = STATUS_BAD_ENTRY;
    }
    else {
        string option = inputVec[0];
        if (option.size() != 1 or inputVec.size() != 1) {
            status_ = STATUS_BAD_ENTRY;
        }
        else {
            switch (option.c_str()[0]) {
                case '1': //Retour au menu
                    status_ = STATUS_RETURNMENU;
                    break;
                default:
                    status_ = STATUS_BAD_ENTRY;
                    break;
            }
        }
    }
}


//InGame-------------------------------------------------------------------------

InGameState::InGameState(Client * client): GameState(client) {}
void InGameState::handleEvents() {}
void InGameState::logic() {}
void InGameState::display() {}
