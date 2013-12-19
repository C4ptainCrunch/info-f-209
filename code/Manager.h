#ifndef Manager_h
#define Manager_h

class Club;

class Manager {

 public:

    virtual void getExperience();

    virtual void setExperience();


 private:
    Integer experience;

 public:

    Club *myClub;
};

#endif // Manager_h
