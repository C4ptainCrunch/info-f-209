#include <iostream>
#include <sstream>

#include "Socket.h"
#include "client.h"
#include "GameState.h"

//Les définitions ci dessous sont toutes les valeurs que peut avoir l'attribut 'status' de la class de base GameState.
//Valeurs générales :
enum STATUS
{
    STATUS_DEFAULT = 0,
    STATUS_BAD_ENTRY = -1,
    STATUS_DISCONNECT = -2,
    STATUS_RETURNMENU = -3,
    STATUS_QUIT = -4
};
//Valeurs pour unlogged :
enum UNLOGGED
{
    UNLOGGED_CONNECTED = 1,
    UNLOGGED_CONNECT = 2,
    UNLOGGED_REGISTER = 3
};
//Valeurs pour menu :
enum MENU
{
    MENU_MANAGEPLAYERS = 1,
    MENU_MANAGEINFRASTRUCTURES = 2,
    MENU_AUCTIONHOUSE = 3,
    MENU_CONNECTEDLIST = 4
};

using namespace std;

GameState::GameState(Client * client)
{
    client_ = client;
    status = STATUS_DEFAULT;
}

GameState::~GameState() {}

void GameState::setNextState(int state)
{
    client_->setNextState(state);
}


IntroState::IntroState(Client * client) : GameState(client)
{
    cout<<"BienvenuS dans le systme !"<<endl;
}
void IntroState::handleEvents() {}
void IntroState::logic()
{
    setNextState(STATE_UNLOGGED);
}
void IntroState::display() {}

//Unlogged-------------------------------------------------------------------------

UnloggedState::UnloggedState(Client * client) : GameState(client)
{
    cout<<"Entrez l'option souhaité avec les paramètres requis délimités par un espace."<<endl;
    cout<<"Exemple : '1 Usr mdp'"<<endl;
    cout<<endl;
    display();
}
void UnloggedState::handleEvents()
{
    string inputString;
    getline(cin, inputString);
    vector<string> inputVec = split(inputString, ' ');
    parse(inputVec);
}

void UnloggedState::logic()
{
    switch (status) {
    case UNLOGGED_CONNECT :
        //envoyer et traiter les données du serveur.
        status = UNLOGGED_CONNECTED;
        setNextState(STATE_MENU);
        break;
    case UNLOGGED_REGISTER :
        //envoyer et traiter les données du serveur.
        break;
    case STATUS_QUIT :
        setNextState(STATE_EXIT);
        break;
    }
}
void UnloggedState::display()
{
    switch (status) {
    case STATUS_DEFAULT :
        cout<<"Se connecter : 1 - Nom d'utilisateur - Mot de passe"<<endl;
        cout<<"S'enregistrer : 2 - Nom d'utilisateur - Mot de passe"<<endl;
        cout<<"Quitter : Q"<<endl;
        cout<<endl;
        break;
    case UNLOGGED_CONNECTED :
        cout<<"Connecté."<<endl;
        cout<<endl;
        break;
    case STATUS_BAD_ENTRY :
        cout<<"Erreur : votre entrée est incorrecte."<<endl;
        cout<<endl;
        break;
    }

}

void UnloggedState::parse(vector<string> & inputVec)
{
    if (inputVec.empty() == true)
        status = STATUS_BAD_ENTRY;
    else {
        string option = inputVec[0];
        if (option.size() != 1)
            status = STATUS_BAD_ENTRY;
        else {
            switch (option.c_str()[0]) {
            case '1' :
                if (inputVec.size() == 3) {
                    nameInput = inputVec[1];
                    passInput = inputVec[2];
                    status = UNLOGGED_CONNECT; //demande de connection
                }
                else {
                    status = STATUS_BAD_ENTRY;
                }
                break;
            case '2' :
                if (inputVec.size() == 3) {
                    nameInput = inputVec[1];
                    passInput = inputVec[2];
                    status = UNLOGGED_REGISTER; //demande d'enregistrement
                }
                else {
                    status = STATUS_BAD_ENTRY;
                }
                break;
            case 'q' :
            case 'Q' :
                status = STATUS_QUIT;
                break;
            default :
                status = STATUS_BAD_ENTRY;
                break;
            }
        }
    }
}
//Menu-------------------------------------------------------------------------

MenuState::MenuState(Client * client) : GameState(client)
{
    display();
}
void MenuState::handleEvents()
{
    string inputString;
    getline(cin, inputString);
    vector<string> inputVec = split(inputString, ' ');
    parse(inputVec);
}
void MenuState::logic()
{
    switch (status) {
    case MENU_MANAGEPLAYERS :
        setNextState(STATE_MANAGE_PLAYERS);
        break;
    case MENU_MANAGEINFRASTRUCTURES :
        setNextState(STATE_MANAGE_INFRASTRUCTURES);
        break;
    case MENU_AUCTIONHOUSE :
        setNextState(STATE_AUCTION_HOUSE);
        break;
    case MENU_CONNECTEDLIST :
        setNextState(STATE_CONNECTEDLIST);
        break;
    case STATUS_DISCONNECT : //!! effectuer tout ce qui est nécéssaire pour la déconnection ici
        setNextState(STATE_INTRO);
        break;
    case STATUS_QUIT :
        setNextState(STATE_EXIT);
        break;
    }
}
void MenuState::display()
{
    switch (status) {
    case STATUS_DEFAULT :
        cout<<"Gérer votre équipe : 1"<<endl;
        cout<<"Gérer vos infrastructures : 2"<<endl;
        cout<<"Accéder à l'hotel de vente : 3"<<endl;
        cout<<"Voir la liste de connectés. : 4"<<endl;
        cout<<"Se déconnecter : 5"<<endl;
        cout<<"Quitter : Q"<<endl;
        cout<<endl;
        break;
    case STATUS_BAD_ENTRY :
        cout<<"Erreur : votre entrée est incorrecte."<<endl;
        cout<<endl;
        break;
    }
}

void MenuState::parse(vector<string> & inputVec)
{
    if (inputVec.empty() == true)
        status = STATUS_BAD_ENTRY;
    else {
        string option = inputVec[0];
        if (option.size() != 1 or inputVec.size() != 1)
            status = STATUS_BAD_ENTRY;
        else
        {
            switch (option.c_str()[0]) {
            case '1' :
                status = MENU_MANAGEPLAYERS;
                break;
            case '2' :
                status = MENU_MANAGEINFRASTRUCTURES;
                break;
            case '3' :
                status = MENU_AUCTIONHOUSE;
                break;
            case '4' :
                status = MENU_CONNECTEDLIST;
                break;
            case '5' :
                status = STATUS_DISCONNECT;
                break;
            case 'q' :
            case 'Q' :
                status = STATUS_QUIT;
                break;
            default :
                status = STATUS_BAD_ENTRY;
                break;
            }
        }
    }
}


//ManagePlayer-------------------------------------------------------------------------

ManagePlayerState::ManagePlayerState(Client * client) : GameState(client)
{
    display();
}
void ManagePlayerState::handleEvents()
{
    string inputString;
    getline(cin, inputString);
    vector<string> inputVec = split(inputString, ' ');
    parse(inputVec);
}
void ManagePlayerState::logic()
{
    switch (status) {
    case STATUS_RETURNMENU :
        setNextState(STATE_MENU);
        break;
    }
}
void ManagePlayerState::display()
{
    switch (status) {
    case STATUS_DEFAULT :
        cout<<"Retourner au menu : 1"<<endl;
        cout<<endl;
        break;
    case STATUS_BAD_ENTRY :
        cout<<"Erreur : votre entrée est incorrecte."<<endl;
        cout<<endl;
        break;
    }
}

void ManagePlayerState::parse(vector<string> & inputVec)
{
    if (inputVec.empty() == true)
        status = STATUS_BAD_ENTRY;
    else {
        string option = inputVec[0];
        if (option.size() != 1 or inputVec.size() != 1)
            status = STATUS_BAD_ENTRY;
        else {
            switch (option.c_str()[0]) {
            case '1' :
                status = STATUS_RETURNMENU;
                break;
            default :
                status = STATUS_BAD_ENTRY;
                break;
            }
        }
    }
}


//ManageInfrastructure-------------------------------------------------------------------------

ManageInfrastructureState::ManageInfrastructureState(Client * client) : GameState(client)
{
    display();
}
void ManageInfrastructureState::handleEvents()
{
    string inputString;
    getline(cin, inputString);
    vector<string> inputVec = split(inputString, ' ');
    parse(inputVec);
}

void ManageInfrastructureState::logic()
{
    switch (status) {
    case STATUS_RETURNMENU :
        setNextState(STATE_MENU);
        break;
    }
}

void ManageInfrastructureState::display()
{
    switch (status) {
    case STATUS_DEFAULT :
        cout<<"Infrastructures : "<<endl;
        cout<<"Créer une infirmerie. : 1"<<endl; //pour plus tard, spécialiser les messages (créer -> améliorer)
        cout<<"Créer un shop : 2"<<endl;
        cout<<"Revenir au menu : 3"<<endl;
        cout<<endl;
        break;
    case STATUS_BAD_ENTRY :
        cout<<"Erreur : votre entrée est incorrecte."<<endl;
        cout<<endl;
        break;
    }
}

void ManageInfrastructureState::parse(vector<string> & inputVec)
{
    if (inputVec.empty() == true)
        status = STATUS_BAD_ENTRY;
    else {
        string option = inputVec[0];
        if (option.size() != 1 or inputVec.size() != 1)
            status = STATUS_BAD_ENTRY;
        else {
            switch (option.c_str()[0]) {
            case '3' :
                status = STATUS_RETURNMENU;
                break;
            default :
                status = STATUS_BAD_ENTRY;
                break;
            }
        }
    }
}


//AuctionHouse-------------------------------------------------------------------------

AuctionHouseState::AuctionHouseState(Client * client) : GameState(client)
{
    display();
}
void AuctionHouseState::handleEvents()
{
    string inputString;
    getline(cin, inputString);
    vector<string> inputVec = split(inputString, ' ');
    parse(inputVec);
}

void AuctionHouseState::logic()
{
    switch (status) {
    case STATUS_RETURNMENU :
        setNextState(STATE_MENU);
        break;
    }
}

void AuctionHouseState::display()
{
    switch (status) {
    case STATUS_DEFAULT :
        cout<<"Hotel des ventes : "<<endl;
        cout<<"Revenir au menu : 1"<<endl;
        cout<<endl;
        break;
    case STATUS_BAD_ENTRY :
        cout<<"Erreur : votre entrée est incorrecte."<<endl;
        cout<<endl;
        break;
    }
}

void AuctionHouseState::parse(vector<string> & inputVec)
{
    if (inputVec.empty() == true)
        status = STATUS_BAD_ENTRY;
    else {
        string option = inputVec[0];
        if (option.size() != 1 or inputVec.size() != 1)
            status = STATUS_BAD_ENTRY;
        else {
            switch (option.c_str()[0]) {
            case '1' :
                status = STATUS_RETURNMENU;
                break;
            default :
                status = STATUS_BAD_ENTRY;
                break;
            }
        }
    }
}


//ConnectedList--------------------------------------------------------------------------

ConnectedListState::ConnectedListState(Client * client) : GameState(client)
{
    display();
}
void ConnectedListState::handleEvents()
{
    string inputString;
    getline(cin, inputString);
    vector<string> inputVec = split(inputString, ' ');
    parse(inputVec);
}
void ConnectedListState::logic()
{
    switch (status) {
    case STATUS_RETURNMENU :
        setNextState(STATE_MENU);
        break;
    }
}
void ConnectedListState::display()
{
    switch (status) {
    case STATUS_DEFAULT :
        cout<<"Joueurs connectés : "<<endl;
        cout<<"Revenir au menu : 1"<<endl;
        cout<<endl;
        break;
    case STATUS_BAD_ENTRY :
        cout<<"Erreur : votre entrée est incorrecte."<<endl;
        cout<<endl;
        break;
    }
}

void ConnectedListState::parse(vector<string> & inputVec)
{
    if (inputVec.empty() == true)
        status = STATUS_BAD_ENTRY;
    else {
        string option = inputVec[0];
        if (option.size() != 1 or inputVec.size() != 1)
            status = STATUS_BAD_ENTRY;
        else {
            switch (option.c_str()[0]) {
            case '1' :
                status = STATUS_RETURNMENU;
                break;
            default :
                status = STATUS_BAD_ENTRY;
                break;
            }
        }
    }
}


//InGame-------------------------------------------------------------------------

InGameState::InGameState(Client * client) : GameState(client) {}
void InGameState::handleEvents() {}
void InGameState::logic() {}
void InGameState::display() {}


vector<string> &split(const string &s, char delim, vector<string> &elems)
{
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string &s, char delim)
{
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}
