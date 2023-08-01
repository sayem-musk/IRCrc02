//
//  DBMyScreen.hpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 2/15/20.
//

#ifndef DBMyScreen_h
#define DBMyScreen_h

#include <stdio.h>
#include "IncludeAndroid.h"

//CREATE TABLE "my_screen" ( `my_screen_id` INTEGER NOT NULL, `screen_id` INTEGER, `is_unlocked` INTEGER, `screen_level` INTEGER, `screen_experience` INTEGER, `collect_coins_per_sec` INTEGER, `customer_frequency_level` INTEGER, `station_capacity_level` INTEGER, `queue_capacity_level` INTEGER, `ticket_price_level` INTEGER, `speed_level` INTEGER, `cars_level` INTEGER, `balloons_level` INTEGER, `icecream_level` INTEGER, `fastfood_level` INTEGER, `airship_level` INTEGER, `ext1` TEXT, `ext2` TEXT, `ext3` TEXT, `ext4` TEXT, `ext5` TEXT, `ext6` TEXT, `ext7` TEXT, `ext8` TEXT, `ext9` TEXT, PRIMARY KEY(`my_screen_id`) )

//my_screen_id,screen_id,is_unlocked,screen_level,screen_experience,collect_coins_per_sec,customer_frequency_level,station_capacity_level,queue_capacity_level,ticket_price_level,speed_level,cars_level,balloons_level,icecream_level,fastfood_level,airship_level,ext1,ext2,ext3,ext4,ext5,ext6,ext7,ext8,ext9

using namespace std;

class DBMyScreen
{
public:
    int my_screen_id;
    int screen_id;
    int is_unlocked;
    int screen_level;
    int screen_experience;
    int collect_coins_per_sec;
    int customer_frequency_level;
    int station_capacity_level;
    int queue_capacity_level;
    int ticket_price_level;
    int speed_level;
    int cars_level;
    int balloons_level;
    int icecream_level;
    int fastfood_level;
    int airship_level;
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
    ~DBMyScreen();
    DBMyScreen();
    static DBMyScreen* create();
    virtual bool init();
    
    static DBMyScreen* create(int primaryKey,bool isMyScreen=true);
    virtual bool init(int primaryKey,bool isMyScreen=true);
    
    void show();
    
    void insertIntoDatabase();
    void updateDatabase();
    static void deleteDatabase(int primaryKey);
    static void deleteAllDatabase();
    
};

#endif /* DBMyScreen_h */
