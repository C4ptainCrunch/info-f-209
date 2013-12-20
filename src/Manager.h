#ifndef MANAGER_H
#define MANAGER_H


class Manager{

    public:
        Manager();
        ~Manager();
        Manager operator=();
        int getExperience();
        void setExperience();

    private:
        int experience;

};

#endif // MANAGER_H
