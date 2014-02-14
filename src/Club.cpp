#include "Club.h"

using namespace std;

Club::Club(): money_(0), installations_()
{

    for (int i = 0; i<7; ++i){

        players_[i] = NonFieldPlayer();
        team_->changePlayer(i, players_[i]);
    }
    // TODO: fill team_ and players_ with players.
}

Club::Club(int money, Installation* installations, Team& team, vector<NonFieldPlayer> players): money_(money), players_(players)
{
    for (int i = 0; i < 5; ++i){
        installations_[i] = installations[i];
    }
    team_ = &team;
}

Club::~Club(){ }

int Club::addMoney(const int deltaMoney)
{
    return money_+=deltaMoney;
}

int Club::getMoney()
{
    return money_;
}

int Club::getLevel()
{
    // TODO
    return 0;
}

Team* Club::getTeam()
{
    return team_;
}

std::vector<NonFieldPlayer> Club::getNonFieldPlayers()
{
    return players_;
}

void Club::addNonFieldPlayer(NonFieldPlayer player)
{
    players_.push_back(player);
}

NonFieldPlayer& Club::removeNonFieldPlayer(unsigned int pos)
{
    NonFieldPlayer tmpPlayer(players_[pos]);
    players_.erase(players_.begin() + pos);
    return tmpPlayer;
}


void Club::addInstallation(Installation& installation, int pos)
{
    installations_[pos] = installation;
}

Installation* Club::getInstallations()
{
    return installations_;
}   

Installation& Club::delInstallation(unsigned int pos)
{
    Installation tmpInstallation(installations_[pos]);
    installations_[pos] = 0;
    return tmpInstallation;
}


