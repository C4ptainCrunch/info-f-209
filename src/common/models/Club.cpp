#include "Club.h"

using namespace std;

Club::Club(): money_(0), installations_() {

    for (int i = 0; i < 7; ++i) {
        players_.push_back(new NonFieldPlayer());

        team_->setPlayer(*players_.at((unsigned int)i), i);

    }
}


Club::Club(JsonValue * json) {
    JsonDict * club = JDICT(json);
    JsonDict * ins;

    if (club == NULL) {
        throw ModelUnserializationError("Club initialized from non dict");
    }

    JsonInt * money_int = JINT((*club)["money"]);
    if (money_int == NULL) {
        throw ModelUnserializationError("Missing int at key 'money' in Club");
    }

    int money = *money_int;
    Installation installations[5];

    JsonList * installations_list = JLIST((*club)["installations"]);
    if (installations_list == NULL) {
        throw ModelUnserializationError("Missing list at key 'installations' in Club");
    }
    if (installations_list->size() != 5) {
        throw ModelUnserializationError("Bad 'installations' size in Club");
    }


    for (int i = 0; i < 5; i++) {
        ins = JDICT((*installations_list)[i]);
        if (ins == NULL) {
            throw ModelUnserializationError("Null installation in Club");
        }

        installations[i] = Installation(ins);
    }

    Team * team = new Team((*club)["team"]);
    JsonList * player_list = JLIST((*club)["players"]);
    if (player_list == NULL) {
        throw ModelUnserializationError("Missing list at key 'players' in Club");
    }

    vector<NonFieldPlayer *> players;
    for (int i = 0; i < player_list->size(); i++) {
        players.push_back(new NonFieldPlayer((*player_list)[i]));
    }
    for (int i = 0; i < 7; i++) {
        if (team->getPlayer(i) != NULL) {
            players.push_back(team->getPlayer(i));
        }
    }

    new (this)Club(money, installations, team, players);
}

Club::Club(int money, Installation * installations, Team * team, vector<NonFieldPlayer *> players): money_(money), players_(players) {
    for (int i = 0; i < 5; ++i) {
        installations_[i] = installations[i];
    }
    team_ = team;
}

Club::~Club() {}

int Club::addMoney(const int deltaMoney) {
    return money_ += deltaMoney;
}

int Club::getMoney() {
    return money_;
}

int Club::getLevel() {
    int level = 0;
    for (int i = 0; i < 5; ++i) {
        level += installations_[i].getLevel();
    }
    return level;
}

Team * Club::getTeam() {
    return team_;
}

std::vector<NonFieldPlayer *> Club::getNonFieldPlayers() {
    return players_;
}

void Club::addNonFieldPlayer(NonFieldPlayer * player) {
    players_.push_back(player);
}

NonFieldPlayer * Club::removeNonFieldPlayer(unsigned int pos) {
    NonFieldPlayer * tmpPlayer = players_[pos];
    players_.erase(players_.begin() + pos);
    return tmpPlayer;
}


void Club::addInstallation(Installation & installation, int pos) {
    installations_[pos] = installation;
}

Installation * Club::getInstallations() {
    return installations_;
}


Club::operator JsonDict() const {
    JsonDict r;

    r.add("money", new JsonInt(money_));

    JsonDict * team = new JsonDict(*team_);
    r.add("team", team);

    JsonList * installations = new JsonList();
    for (int i = 0; i < 5; i++) {
        JsonDict * install = new JsonDict(installations_[i]);
        installations->add(install);
    }
    r.add("installations", installations);

    JsonList * players = new JsonList();
    for (int i = 0; i < players_.size(); i++) {
        bool present = false;
        for (int j = 0; (j < 7) && (!present); j++) {
            present = players_[i] == team_->getPlayer(j);
        }
        if (!present) {
            JsonDict * player = new JsonDict(*(players_[i]));
            players->add(player);
        }
    }
    r.add("players", players);

    return r;
}
