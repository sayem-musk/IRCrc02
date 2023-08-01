//
//  DBLevels.hpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 2/17/20.
//

#ifndef DBLevels_h
#define DBLevels_h

#include "IncludeAndroid.h"

//CREATE TABLE "levels" ( `levelid` INTEGER, `experience` INTEGER, `experience_per_customer` INTEGER, `rewards` TEXT, rewards_xp TEXT, `ext1` TEXT, `ext2` TEXT, `ext3` TEXT, `ext4` TEXT, `ext5` TEXT, `ext6` TEXT, `ext7` TEXT, `ext8` TEXT, `ext9` TEXT, PRIMARY KEY(`levelid`) )

//levelid,experience,experience_per_customer,rewards,rewards_xp,ext1,ext2,ext3,ext4,ext5,ext6,ext7,ext8,ext9

using namespace std;

class DBLevels
{
public:
    int levelid;
    int experience;
    int experience_per_customer;
    string rewards;
    string rewards_xp;
    string ext1;
    string ext2;
    string ext3;
    string ext4;
    string ext5;
    string ext6;
    string ext7;
    string ext8;
    string ext9;
    
#pragma mark- Init Method
    ~DBLevels();
    DBLevels();
    static DBLevels* create();
    virtual bool init();
    
    static DBLevels* create(int primaryKey);
    virtual bool init(int primaryKey);
    
    void show();
    
    static vector<DBLevels*>* getAllLevels();
    static DBLevels* getLevels(int _levelid);
};

#endif /* DBLevels_h */
