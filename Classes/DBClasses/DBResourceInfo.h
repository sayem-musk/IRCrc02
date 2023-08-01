//
//  DBResourceInfo.h
//  MUSK
//
//  Created by Tarek Saazeb on 6/12/16.
//
//

#ifndef DBResourceInfo_h
#define DBResourceInfo_h

#include <sqlite3.h>
#include "IncludeAndroid.h"

using namespace std;

//CREATE TABLE "resources" ( `resourceid` INTEGER NOT NULL, resource_type INTEGER,`resource_name` TEXT,screen_id INTEGER, `amount` TEXT, `amount_exp` TEXT, `capacity` TEXT, `ext1` TEXT, `ext2` TEXT, `ext3` TEXT, `ext4` TEXT, `ext5` TEXT, `ext6` TEXT, `ext7` TEXT, `ext8` TEXT, `ext9` TEXT, PRIMARY KEY(`resourceid`) )

//resourceid,resource_type,resource_name,screen_id,amount,amount_exp,capacity,bucks_value,ext1,ext2,ext3,ext4,ext5,ext6,ext7,ext8,ext9

class DBResourceInfo
{
public:
    // Attributes.
    int resourceid;
    int resource_type;
    string resource_name;
    int screen_id;
    string amount;
    string amount_exp;
    string capacity;
    string bucks_value;
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
    ~DBResourceInfo();
    DBResourceInfo();
    static DBResourceInfo* create();
    virtual bool init();
    
    static DBResourceInfo* create(int primaryKey);
    virtual bool init(int primaryKey);
    
    void show();
    
    void insertIntoDatabase();
    void updateDatabase();
    static void deleteDatabase(int primaryKey);
    static void deleteAllDatabase();
};

#endif /* DBResourceInfo_h */






