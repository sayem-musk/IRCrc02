//
//  DBScreenInfo.h
//  IRC-mobile
//
//  Created by Tarek Saazeb on 2/15/20.
//

#ifndef DBScreenInfo_h
#define DBScreenInfo_h

#include <stdio.h>
#include "IncludeAndroid.h"

using namespace std;

//CREATE TABLE "screen_info" ( `screen_id` INTEGER NOT NULL, `screen_name` TEXT, `unlock_level` INTEGER, `unlock_price` TEXT, `unlock_price_exp` TEXT, `screen_order` INTEGER, `disable` INTEGER, `ext1` TEXT, `ext2` TEXT, `ext3` TEXT, `ext4` TEXT, `ext5` TEXT, `ext6` TEXT, `ext7` TEXT, `ext8` TEXT, `ext9` TEXT, PRIMARY KEY(`screen_id`) )

//screen_id,screen_name,unlock_level,unlock_price,unlock_price_exp,disable,ext1,ext2,ext3,ext4,ext5,ext6,ext7,ext8,ext9

class DBScreenInfo
{
public:
    int screen_id;
    string screen_name;
    int unlock_level;
    string unlock_price;
    string unlock_price_exp;
    int screen_order;
    int disable;
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
    ~DBScreenInfo();
    DBScreenInfo();
    static DBScreenInfo* create();
    virtual bool init();
    
    static DBScreenInfo* create(int primaryKey);
    virtual bool init(int primaryKey);
    
    void show();
    
    static vector<DBScreenInfo*>* getAllScreenInfo();
    static DBScreenInfo* getScreenInfo(int _screen_id);
};

#endif /* DBScreenInfo_h */
