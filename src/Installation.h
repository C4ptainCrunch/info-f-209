#ifndef Installation_h
#define Installation_h

class Installation {

 public:
	virtual Installation();
	virtual ~Installation();
	virtual bool operator=();
    virtual void improve();
    virtual int getLevel();

 private:
    int level;
};

#endif // Installation_h
