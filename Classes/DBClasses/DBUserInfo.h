//
//  DBUserInfo.h
//  MUSK
//
//  Created by Mainul Islam on 1/1/01.
//
//

#ifndef __MUSK__DBUserInfo__
#define __MUSK__DBUserInfo__

#include <stdio.h>
#include "IncludeAndroid.h"
//#include "../DBClasses/DBLevel.h"

using namespace std;

//CREATE TABLE "users" ( `uid` INTEGER, `screen_id` INTEGER, `experience` INTEGER, `levelid` INTEGER, `visitat` INTEGER, `ext1` TEXT, `ext2` TEXT, `ext3` TEXT, `ext4` TEXT, `ext5` TEXT, `ext6` TEXT, `ext7` TEXT, `ext8` TEXT, `ext9` TEXT, PRIMARY KEY(`uid`) )

//uid,screen_id,experience,levelid,visitat,ext1,ext2,ext3,ext4,ext5,ext6,ext7,ext8,ext9

class DBUserInfo
{
public:
    int uid;
    int screen_id;
    int experience;
    int levelid;
    int visitat;
    string ext1;
    string ext2;
    string ext3;
    string ext4;
    string ext5;
    string ext6;
    string ext7;
    string ext8;
    string ext9;
    
//    DBLevel *currentLevel;
//    DBLevel *nextLevel;
    
    static DBUserInfo* create();
    static DBUserInfo* create(int _userId);
    
    ~DBUserInfo();
    DBUserInfo();
    DBUserInfo(int _userId);
    static DBUserInfo* sharedManager();
    static DBUserInfo* initUserInfo();
    
    void insertIntoDatabase();
    void updateDatabase();
};

#endif /* defined(__MUSK__DBUserInfo__) */
