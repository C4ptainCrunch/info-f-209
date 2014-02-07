#include "Club.h"

using namespace std;

Club::Club(): money_(0), installations_()
{
    // TODO: fill team_ and players_ with players.
}

Club::Club(int money, vector<Installation> installations, Team& team, vector<NonFieldPlayer> players): money_(money), installations_(installations), players_(players)
{
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


void Club::addInstallation(Installation& installation)
{
    installations_.push_back(installation);
}

std::vector<Installation> Club::getInstallations()
{
    return installations_;
}

Installation& Club::delInstallation(unsigned int pos)
{
    Installation tmpInstallation(installations_[pos]);
    installations_.erase(installations_.begin() + pos);
    return tmpInstallation;
}


