//
//  DBResourceInfo.cpp
//  MUSK
//
//  Created by Tarek Saazeb on 6/12/16.
//
//

#include "DBResourceInfo.h"
#include "AppDelegate.h"
#include "../CustomClass/MUSKScoreBar.h"

#pragma mark- Init Method

DBResourceInfo::~DBResourceInfo()
{
    
}

DBResourceInfo::DBResourceInfo()
{
    
}

DBResourceInfo* DBResourceInfo::create()
{
    DBResourceInfo* ret = new DBResourceInfo();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool DBResourceInfo::init()
{
    return true;
}

DBResourceInfo* DBResourceInfo::create(int primaryKey)
{
    DBResourceInfo* ret = new DBResourceInfo();
    if(ret && ret->init(primaryKey)) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }

}

bool DBResourceInfo::init(int primaryKey)
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    sqlite3 *database=appDelegate->database;
    
    const char *sql="SELECT * FROM resources WHERE resourceid=?";
    
    sqlite3_stmt *init_statement=NULL;
    
    if (sqlite3_prepare_v2(database, sql, -1, &init_statement, NULL) != SQLITE_OK) {
        CCLOG("Error: failed to prepare statement with message '%s'.", sqlite3_errmsg(database));
    }
    
    sqlite3_bind_int(init_statement, 1, primaryKey);
    if (sqlite3_step(init_statement) == SQLITE_ROW)
    {
        int index=0;
        
        resourceid=sqlite3_column_int(init_statement,index++);
        resource_type=sqlite3_column_int(init_statement,index++);
        resource_name=AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        screen_id=sqlite3_column_int(init_statement,index++);
        amount=AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        amount_exp=AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        capacity=AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        bucks_value=AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
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
        resourceid=0;
        resource_type=0;
        resource_name="0";
        screen_id=0;
        amount="0";
        amount_exp="0";
        capacity="0";
        bucks_value="0";
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

void DBResourceInfo::show()
{
    CCLOG("-------------------------------------------");
    CCLOG("resourceid %d",resourceid);
    CCLOG("resource_type %d",resource_type);
    CCLOG("resource_name %s",resource_name.c_str());
    CCLOG("screen_id %d",screen_id);
    CCLOG("amount %s",amount.c_str());
    CCLOG("amount_exp %s",amount_exp.c_str());
    CCLOG("capacity %s",capacity.c_str());
    CCLOG("bucks_value %s",bucks_value.c_str());
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

void DBResourceInfo::insertIntoDatabase()
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    sqlite3 *database=appDelegate->database;
    sqlite3_stmt *insert_statement=NULL;
    
    const char *sql="INSERT INTO resources (resource_type, resource_name , screen_id ,  amount , amount_exp , capacity , bucks_value , ext1 , ext2 , ext3 , ext4 , ext5 , ext6 , ext7 , ext8 , ext9) VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
    
    if (sqlite3_prepare_v2(database, sql, -1, &insert_statement, NULL) != SQLITE_OK) {
        CCLOG("Error: failed to prepare statement with message '%s'.", sqlite3_errmsg(database));
    }
    int index=1;
    
    sqlite3_bind_int(insert_statement,  index++, resource_type);
    sqlite3_bind_text(insert_statement, index++, resource_name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(insert_statement,  index++, screen_id);
    sqlite3_bind_text(insert_statement, index++, amount.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(insert_statement, index++, amount_exp.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(insert_statement, index++, capacity.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(insert_statement, index++, bucks_value.c_str(), -1, SQLITE_TRANSIENT);
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
        resourceid=0;
    } else {
        resourceid=(int)sqlite3_last_insert_rowid(database);
    }
    
    sqlite3_reset(insert_statement);
    sqlite3_finalize(insert_statement);
}

void DBResourceInfo::updateDatabase()
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    sqlite3 *database=appDelegate->database;
    sqlite3_stmt *update_statement=NULL;
    
    const char *sqlu="UPDATE resources SET resource_type=?, resource_name=?, screen_id=?, amount=?, amount_exp=?, capacity=?, bucks_value=?, ext1=?, ext2=?, ext3=?, ext4=?, ext5=?, ext6=?, ext7=?, ext8=?, ext9=? WHERE resourceid=?";
    if (sqlite3_prepare_v2(database, sqlu, -1, &update_statement, NULL) != SQLITE_OK) {
        CCLOG("Error: failed to prepare statement with message '%s'.", sqlite3_errmsg(database));
    }
    
    int index=1;
    
    sqlite3_bind_int(update_statement,  index++, resource_type);
    sqlite3_bind_text(update_statement, index++, resource_name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(update_statement,  index++, screen_id);
    sqlite3_bind_text(update_statement, index++, amount.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, amount_exp.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, capacity.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, bucks_value.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext1.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext2.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext3.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext4.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext5.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext6.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext7.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext8.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext9.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(update_statement, index++, resourceid);
    
    int success=sqlite3_step(update_statement);
    if(success==SQLITE_ERROR) {
        CCLOG("Error: failed to insert into the database with message '%s'.", sqlite3_errmsg(database));
    }
    
    sqlite3_reset(update_statement);
    sqlite3_finalize(update_statement);
    
     MUSKScoreBar::sharedManager()->updateScoreBar();
}

void DBResourceInfo::deleteDatabase(int primaryKey)
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    sqlite3 *database=appDelegate->database;
    sqlite3_stmt *delete_statement=NULL;
    
    // Compile the query for retrieving score data.
    const char *sqlu="DELETE FROM resources WHERE resourceid=?";
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

void DBResourceInfo::deleteAllDatabase()
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    sqlite3 *database=appDelegate->database;
    sqlite3_stmt *delete_statement=NULL;
    
    // Compile the query for retrieving score data.
    const char *sqlu="DELETE FROM resources";
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

