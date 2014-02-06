#ifndef MANAGER_H
#define MANAGER_H


class Manager{

    public:
        Manager(String name, String userName, String password, Club club = Club());
        ~Manager();
        bool checkPassword(const String password);
        void changePassword(const String password);
        Club & getClub();
        String getUserName();
        String getName();

    private:
        String name;
        String userName;
        String hash;
        Club club;

};

#endif // MANAGER_H
