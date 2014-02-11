#ifndef Installation_h
#define Installation_h

class Installation{

 public:
    Installation(int level);
    ~Installation();
    virtual void improve();
    virtual int getLevel();

 protected:
    int level;
};

#endif // Installation_h
