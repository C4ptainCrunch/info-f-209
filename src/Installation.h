#ifndef INSTALLATION_h
#define INSTALLATION_h

class Installation{

 public:
    Installation(int level = 1);
    ~Installation();
    virtual void improve();
    virtual int getLevel();

 protected:
    int level_;
};

#endif // INSTALLATION_h
