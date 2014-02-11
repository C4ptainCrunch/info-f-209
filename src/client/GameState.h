#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <vector>

class Client;

class GameState
{
public:
    GameState(Client * client);
    virtual ~GameState();
    virtual void handleEvents() = 0;
    virtual void logic() = 0;
    virtual void display() = 0;

    virtual void setNextState(int state);
protected:
    int status;
private:
    Client * client_;
};

class IntroState : public GameState
{
public:
    IntroState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
};

class UnloggedState : public GameState
{
public:
    UnloggedState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
    virtual void parse(std::vector<std::string> & inputVec);
private:
    std::string nameEntry;
    std::string passEntry;
};

class MenuState : public GameState
{
public:
    MenuState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
    virtual void parse(std::vector<std::string> & inputVec);
};


class ManagePlayerState : public GameState
{
public:
    ManagePlayerState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
    virtual void parse(std::vector<std::string> & inputVec);
};

class ManageInfrastructureState : public GameState
{
public:
    ManageInfrastructureState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
    virtual void parse(std::vector<std::string> & inputVec);
};

class AuctionHouseState : public GameState
{
public:
    AuctionHouseState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
    virtual void parse(std::vector<std::string> & inputVec);
};

class FriendListState : public GameState
{
public:
    FriendListState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
    virtual void parse(std::vector<std::string> & inputVec);
};

class InGameState : public GameState
{
public:
    InGameState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
};

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

#endif //GAME_STATE_H
