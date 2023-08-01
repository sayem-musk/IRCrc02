//
//  DBMyScreen.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 2/15/20.
//

#include "DBMyScreen.h"
#include "AppDelegate.h"

#pragma mark- Init Method

DBMyScreen::~DBMyScreen()
{
    
}

DBMyScreen::DBMyScreen()
{
    
}

DBMyScreen* DBMyScreen::create()
{
    DBMyScreen* ret = new DBMyScreen();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool DBMyScreen::init()
{
   return true;
}

DBMyScreen* DBMyScreen::create(int primaryKey,bool isMyScreen)
{
    DBMyScreen* ret = new DBMyScreen();
    if(ret && ret->init(primaryKey,isMyScreen)) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool DBMyScreen::init(int primaryKey,bool isMyScreen)
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    sqlite3 *database=appDelegate->database;
    
    const char *sql;
    
    if(isMyScreen==true)
        sql="SELECT * FROM my_screen WHERE my_screen_id=?";
    else
        sql="SELECT * FROM my_screen WHERE screen_id=?";
    
    sqlite3_stmt *init_statement=NULL;
    
    if (sqlite3_prepare_v2(database, sql, -1, &init_statement, NULL) != SQLITE_OK) {
        CCLOG("Error: failed to prepare statement with message '%s'.", sqlite3_errmsg(database));
    }
    
    sqlite3_bind_int(init_statement, 1, primaryKey);
    if (sqlite3_step(init_statement) == SQLITE_ROW)
    {
        int index=0;
        
        my_screen_id=sqlite3_column_int(init_statement,index++);
        screen_id=sqlite3_column_int(init_statement,index++);
        is_unlocked=sqlite3_column_int(init_statement,index++);
        screen_level=sqlite3_column_int(init_statement,index++);
        screen_experience=sqlite3_column_int(init_statement,index++);
        collect_coins_per_sec=sqlite3_column_int(init_statement,index++);
        customer_frequency_level=sqlite3_column_int(init_statement,index++);
        station_capacity_level=sqlite3_column_int(init_statement,index++);
        queue_capacity_level=sqlite3_column_int(init_statement,index++);
        ticket_price_level=sqlite3_column_int(init_statement,index++);
        speed_level=sqlite3_column_int(init_statement,index++);
        cars_level=sqlite3_column_int(init_statement,index++);
        balloons_level=sqlite3_column_int(init_statement,index++);
        icecream_level=sqlite3_column_int(init_statement,index++);
        fastfood_level=sqlite3_column_int(init_statement,index++);
        airship_level=sqlite3_column_int(init_statement,index++);
        ext1=AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        ext2=AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        ext3=AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        ext4=AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        ext5=AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        ext6=AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        ext7=AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        ext8=AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        ext9=AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
    }
    else
    {
        my_screen_id=0;
        screen_id=0;
        is_unlocked=0;
        screen_level=0;
        screen_experience=0;
        collect_coins_per_sec=0;
        customer_frequency_level=0;
        station_capacity_level=0;
        queue_capacity_level=0;
        ticket_price_level=0;
        speed_level=0;
        cars_level=0;
        balloons_level=0;
        icecream_level=0;
        fastfood_level=0;
        airship_level=0;
        ext1="0";
        ext2="0";
        ext3="0";
        ext4="0";
        ext5="0";
        ext6="0";
        ext7="0";
        ext8="0";
        ext9="0";
    }
    // Reset the statement for future reuse.
    sqlite3_reset(init_statement);
    sqlite3_finalize(init_statement);
    
    return true;
}

void DBMyScreen::show()
{
    CCLOG("-------------------------------------------");
    CCLOG("my_screen_id %d",my_screen_id);
    CCLOG("screen_id %d",screen_id);
    CCLOG("is_unlocked %d",is_unlocked);
    CCLOG("screen_level %d",screen_level);
    CCLOG("screen_experience %d",screen_experience);
    CCLOG("collect_coins_per_sec %d",collect_coins_per_sec);
    CCLOG("customer_frequency_level %d",customer_frequency_level);
    CCLOG("station_capacity_level %d",station_capacity_level);
    CCLOG("queue_capacity_level %d",queue_capacity_level);
    CCLOG("ticket_price_level %d",ticket_price_level);
    CCLOG("speed_level %d",speed_level);
    CCLOG("cars_level %d",cars_level);
    CCLOG("balloons_level %d",balloons_level);
    CCLOG("icecream_level %d",icecream_level);
    CCLOG("fastfood_level %d",fastfood_level);
    CCLOG("airship_level %d",airship_level);
    CCLOG("ext1 %s",ext1.c_str());
    CCLOG("ext2 %s",ext2.c_str());
    CCLOG("ext3 %s",ext3.c_str());
    CCLOG("ext4 %s",ext4.c_str());
    CCLOG("ext5 %s",ext5.c_str());
    CCLOG("ext6 %s",ext6.c_str());
    CCLOG("ext7 %s",ext7.c_str());
    CCLOG("ext8 %s",ext8.c_str());
    CCLOG("ext9 %s",ext9.c_str());
}

void DBMyScreen::insertIntoDatabase()
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    sqlite3 *database=appDelegate->database;
    sqlite3_stmt *insert_statement=NULL;
    
    const char *sql="INSERT INTO my_screen (screen_id,is_unlocked,screen_level,screen_experience,collect_coins_per_sec,customer_frequency_level,station_capacity_level,queue_capacity_level,ticket_price_level,speed_level,cars_level,balloons_level,icecream_level,fastfood_level,airship_level,ext1,ext2,ext3,ext4,ext5,ext6,ext7,ext8,ext9) VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
    if (sqlite3_prepare_v2(database, sql, -1, &insert_statement, NULL) != SQLITE_OK) {
        CCLOG("Error: failed to prepare statement with message '%s'.", sqlite3_errmsg(database));
    }
    int index=1;

    sqlite3_bind_int(insert_statement, index++, screen_id);
    sqlite3_bind_int(insert_statement, index++, is_unlocked);
    sqlite3_bind_int(insert_statement, index++, screen_level);
    sqlite3_bind_int(insert_statement, index++, screen_experience);
    sqlite3_bind_int(insert_statement, index++, collect_coins_per_sec);
    sqlite3_bind_int(insert_statement, index++, customer_frequency_level);
    sqlite3_bind_int(insert_statement, index++, station_capacity_level);
    sqlite3_bind_int(insert_statement, index++, queue_capacity_level);
    sqlite3_bind_int(insert_statement, index++, ticket_price_level);
    sqlite3_bind_int(insert_statement, index++, speed_level);
    sqlite3_bind_int(insert_statement, index++, cars_level);
    sqlite3_bind_int(insert_statement, index++, balloons_level);
    sqlite3_bind_int(insert_statement, index++, icecream_level);
    sqlite3_bind_int(insert_statement, index++, fastfood_level);
    sqlite3_bind_int(insert_statement, index++, airship_level);
    sqlite3_bind_text(insert_statement, index++, ext1.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(insert_statement, index++, ext2.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(insert_statement, index++, ext3.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(insert_statement, index++, ext4.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(insert_statement, index++, ext5.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(insert_statement, index++, ext6.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(insert_statement, index++, ext7.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(insert_statement, index++, ext8.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(insert_statement, index++, ext9.c_str(), -1, SQLITE_TRANSIENT);
    
    int success=sqlite3_step(insert_statement);
    
    if (success == SQLITE_ERROR) {
        CCLOG("Error: failed to insert into the database with message '%s'.", sqlite3_errmsg(database));
        my_screen_id=0;
    } else {
        my_screen_id=(int)sqlite3_last_insert_rowid(database);
    }
    
    sqlite3_reset(insert_statement);
    sqlite3_finalize(insert_statement);
}

void DBMyScreen::updateDatabase()
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    sqlite3 *database=appDelegate->database;
    sqlite3_stmt *update_statement=NULL;
    
    const char *sqlu="UPDATE my_screen SET screen_id=?, is_unlocked=?, screen_level=?, screen_experience=?,collect_coins_per_sec=?, customer_frequency_level=?, station_capacity_level=?, queue_capacity_level=?, ticket_price_level=?, speed_level=?, cars_level=?, balloons_level=?, icecream_level=?, fastfood_level=?, airship_level=?, ext1=?, ext2=?, ext3=?, ext4=?, ext5=?, ext6=?, ext7=?, ext8=?, ext9=? WHERE my_screen_id=?";
    if (sqlite3_prepare_v2(database, sqlu, -1, &update_statement, NULL) != SQLITE_OK) {
        CCLOG("Error: failed to prepare statement with message '%s'.", sqlite3_errmsg(database));
    }
    
    int index=1;
    
    sqlite3_bind_int(update_statement, index++, screen_id);
    sqlite3_bind_int(update_statement, index++, is_unlocked);
    sqlite3_bind_int(update_statement, index++, screen_level);
    sqlite3_bind_int(update_statement, index++, screen_experience);
    sqlite3_bind_int(update_statement, index++, collect_coins_per_sec);
    sqlite3_bind_int(update_statement, index++, customer_frequency_level);
    sqlite3_bind_int(update_statement, index++, station_capacity_level);
    sqlite3_bind_int(update_statement, index++, queue_capacity_level);
    sqlite3_bind_int(update_statement, index++, ticket_price_level);
    sqlite3_bind_int(update_statement, index++, speed_level);
    sqlite3_bind_int(update_statement, index++, cars_level);
    sqlite3_bind_int(update_statement, index++, balloons_level);
    sqlite3_bind_int(update_statement, index++, icecream_level);
    sqlite3_bind_int(update_statement, index++, fastfood_level);
    sqlite3_bind_int(update_statement, index++, airship_level);
    sqlite3_bind_text(update_statement, index++, ext1.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext2.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext3.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext4.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext5.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext6.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext7.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext8.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext9.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(update_statement, index++, my_screen_id);
    
    int success=sqlite3_step(update_statement);
    if(success==SQLITE_ERROR) {
        CCLOG("Error: failed to insert into the database with message '%s'.", sqlite3_errmsg(database));
    }
    
    sqlite3_reset(update_statement);
    sqlite3_finalize(update_statement);
}

void DBMyScreen::deleteDatabase(int primaryKey)
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    sqlite3 *database=appDelegate->database;
    sqlite3_stmt *delete_statement=NULL;
    
    // Compile the query for retrieving score data.
    const char *sqlu="DELETE FROM my_screen WHERE my_screen_id=?";
    if (sqlite3_prepare_v2(database, sqlu, -1, &delete_statement, NULL) != SQLITE_OK) {
        CCLOG("Error: failed to prepare statement with message '%s'.", sqlite3_errmsg(database));
    }
    
    sqlite3_bind_int(delete_statement, 1, primaryKey);
    int success=sqlite3_step(delete_statement);
    if(success==SQLITE_ERROR) {
        CCLOG("Error: failed to insert into the database with message '%s'.", sqlite3_errmsg(database));
    }
    sqlite3_reset(delete_statement);
    sqlite3_finalize(delete_statement);
}

void DBMyScreen::deleteAllDatabase()
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    sqlite3 *database=appDelegate->database;
    sqlite3_stmt *delete_statement=NULL;
    
    // Compile the query for retrieving score data.
    const char *sqlu="DELETE FROM my_screen";
    if (sqlite3_prepare_v2(database, sqlu, -1, &delete_statement, NULL) != SQLITE_OK) {
        CCLOG("Error: failed to prepare statement with message '%s'.", sqlite3_errmsg(database));
    }
    
    int success=sqlite3_step(delete_statement);
    if(success==SQLITE_ERROR) {
        CCLOG("Error: failed to insert into the database with message '%s'.", sqlite3_errmsg(database));
    }
    sqlite3_reset(delete_statement);
    sqlite3_finalize(delete_statement);
}





