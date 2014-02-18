#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <vector>
#include "../models/Player.h"

struct objectDataPair {
    string name;
    int level;
};

class Client;
//Classe de base d'un état.
class GameState
{
public:
    GameState(Client * client); //Contient toujours un pointeur vers le client du jeu.
    virtual ~GameState();
    virtual void handleEvents() = 0; //Gère les entrées de l'utilisateurs.
    virtual void logic() = 0; //Effectue les actions nécéssaire et demande un changement d'état en fonction de status.
    virtual void display() = 0; //Effectue tout les affichages de l'état.

    //FONCTIONS D'APPELS SERVEURS :

    virtual bool notifyServQuit(); //Notifie le serveur de l'arrêt du user.
    virtual bool checkChallenge(); //Vérifie si le joueur est défié.
    virtual std::string getChallengerName();
    virtual int getChallengerLevel();
    virtual int answerToChallenge(bool accept);

    //log in

    virtual int log(std::string username, std::string password);
    virtual int sign(std::string username, std::string password);

    //general

    virtual std::string getName();
    virtual int getMoney();
    virtual int getLevel();

    //team management

    virtual std::vector<struct objectDataPair> getInTeamPlayerList(); //liste des joueurs de la team
    virtual std::vector<struct objectDataPair> getOutOfTeamPlayerList(); //liste des autres joueurs du club

    virtual Player getDataOnPlayer(std::string name); //infos détaillées sur un joueur
    virtual bool healPlayer(std::string name);
    virtual int swapPlayer(std::string name, std::string name2); //swap un joueur de la team avec un joueur du club en dehors de la team

    //infrastructures management
    virtual std::vector<struct objectDataPair> getInfrastructureList();
    virtual bool UpdateInfrastructure(int ID);

    //auction house
    virtual std::vector<struct objectDataPair> getSellingPlayer();  //liste des joueurs vendu à l'hotel des ventes
    virtual int sell(std::string name, int prix); //place un joueur à l'hdv
    virtual int bid(std::string name); //enchéri dans un tour sur un joueur
    virtual int getRoundOnBid(std::string name); //obtient le nbre de tours déjà passé sur une enchère
    virtual int getRemainingTimeOnRound(std::string name); //le temps restant jusqu'a la fin de l'enchère
    virtual int getCurrentBid(std::string name); //enchère courrante (prix)
    virtual int getBidderCount(std::string name); //nombre d'enchérisseurs de ce tour ci
    virtual bool checkEndOfBid(std::string name); //vérifie si l'enchère est terminé
    virtual int endBid(std::string name); //résout la fin de l'enchère

    //user list
    virtual std::vector<struct objectDataPair> getConnectedList();
    virtual int challenge(std::string name);


protected:
    Client * client_;
    int status_; //Beaucoup des états dépendent de leur status pour leur affichage ou logique.
};

class IntroState : public GameState //Premier état : affichage de l'intro.
{
public:
    IntroState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
};

class UnloggedState : public GameState //Permet de s'enregistrer ou s'authentifier
{
public:
    UnloggedState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
    virtual void parse(std::vector<std::string> & inputVec);
private:
    std::string nameInput;
    std::string passInput;
};

class MenuState : public GameState //Affiche le menu principal et redirige vers le menu souhaité.
{
public:
    MenuState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
    virtual void parse(std::vector<std::string> & inputVec);
};


class ManagePlayerState : public GameState //Gestion des joueurs
{
public:
    ManagePlayerState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
    virtual void parse(std::vector<std::string> & inputVec);
};

class ManageInfrastructureState : public GameState //Gestion des infrastructures
{
public:
    ManageInfrastructureState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
    virtual void parse(std::vector<std::string> & inputVec);
};

class AuctionHouseState : public GameState //Hotel des ventes
{
public:
    AuctionHouseState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
    virtual void parse(std::vector<std::string> & inputVec);
};

class ConnectedListState : public GameState //Liste de joueurs connectés, permet de les défier aussi.
{
public:
    ConnectedListState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
    virtual void parse(std::vector<std::string> & inputVec);
};

class InGameState : public GameState //État en jeu.
{
public:
    InGameState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
};

#endif //GAME_STATE_H
