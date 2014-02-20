#ifndef MANAGER_H
#define MANAGER_H

#include "Club.h"
#include "../lib/json/json.h"
#include <string>

class Manager{

    public:
        Manager(std::string name, std::string userName, std::string password, Club club = Club());
        Manager(JsonValue * json);
        ~Manager();
        bool checkPassword(const std::string password);
        void changePassword(const std::string password);
        Club* getClub();
        std::string getUserName();
        std::string getName();
        bool isFree();
        void setFreeState(bool state);

    private:
        std::string name_;
        std::string userName_;
        std::string hash_;
        Club club_;
        bool free;

};

#endif // MANAGER_H
