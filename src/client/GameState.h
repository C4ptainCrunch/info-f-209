#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <vector>

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

//Utilitaire :

std::vector<std::string> split(const std::string &text, char delim);

#endif //GAME_STATE_H
