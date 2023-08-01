//
//  DBUserInfo.cpp
//  MUSK
//
//  Created by Mainul Islam on 1/1/01.
//
//

#include "DBUserInfo.h"
#include "AppDelegate.h"
//#include "../CustomClass/MUSKScoreBar.h"

static DBUserInfo *sharedInstance=NULL;

DBUserInfo* DBUserInfo::sharedManager()
{
    if(sharedInstance==NULL)
    {
        sharedInstance=DBUserInfo::initUserInfo();
        if(sharedInstance==NULL)
        {
            AppDelegate *appDelegate=AppDelegate::sharedApplication();
            appDelegate->addNewUser();
            
            sharedInstance=DBUserInfo::initUserInfo();
        }
    }
    return sharedInstance;
}

DBUserInfo* DBUserInfo::initUserInfo()
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    sqlite3 *database=appDelegate->database;
    DBUserInfo *userInfo;
    
    string str_userInfo="select uid from users";
    const char *sql_userInfo=str_userInfo.c_str();
    
    sqlite3_stmt *statment_userInfo=NULL;
    
    if(sqlite3_prepare_v2(database, sql_userInfo, -1, &statment_userInfo, NULL) == SQLITE_OK)
    {
        if (sqlite3_step(statment_userInfo) == SQLITE_ROW)
        {
            int primaryKey=sqlite3_column_int(statment_userInfo, 0);
            userInfo=DBUserInfo::create(primaryKey);
        }
        else
        {
            userInfo=NULL;
        }
        sqlite3_reset(statment_userInfo);
        sqlite3_finalize(statment_userInfo);
        statment_userInfo=NULL;
    }
    return userInfo;
}

DBUserInfo* DBUserInfo::create()
{
    return new DBUserInfo();
}

DBUserInfo* DBUserInfo::create(int _userId)
{
    return new DBUserInfo(_userId);
}

DBUserInfo::~DBUserInfo()
{
    
}

DBUserInfo::DBUserInfo()
{
    
}

DBUserInfo::DBUserInfo(int _userId)
{
    int pk=_userId;
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    sqlite3 *database=appDelegate->database;
    sqlite3_stmt *init_statement=NULL;
    
    const char *sql = "SELECT * FROM users WHERE uid=?";
    if (sqlite3_prepare_v2(database, sql, -1, &init_statement, NULL) != SQLITE_OK) {
        printf("Error: failed to prepare statement with message '%s'.\n", sqlite3_errmsg(database));
    }

    sqlite3_bind_int(init_statement, 1, pk);
    if (sqlite3_step(init_statement) == SQLITE_ROW)
    {
        int index=0;
        
        uid         =sqlite3_column_int(init_statement,index++);
        screen_id     =sqlite3_column_int(init_statement,index++);
        experience  =sqlite3_column_int(init_statement,index++);
        levelid     =sqlite3_column_int(init_statement,index++);
        visitat     =sqlite3_column_int(init_statement,index++);
        ext1       = AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        ext2       = AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        ext3       = AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        ext4       = AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        ext5       = AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        ext6       = AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        ext7       = AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        ext8       = AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        ext9       = AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
    }
    else {
        uid         = 0;
        screen_id   = 0;
        experience  = 0;
        levelid     = 0;
        visitat     = 0;
        ext1       = "0";
        ext2       = "0";
        ext3       = "0";
        ext4       = "0";
        ext5       = "0";
        ext6       = "0";
        ext7       = "0";
        ext8       = "0";
        ext9       = "0";
    }
    
    //this->currentLevel=DBLevel::create(this->levelid);
    //this->nextLevel=DBLevel::create(this->levelid+1);
    
    sqlite3_reset(init_statement);
    sqlite3_finalize(init_statement);
    init_statement=NULL;
}

void DBUserInfo::insertIntoDatabase()
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    sqlite3 *database=appDelegate->database;
    sqlite3_stmt *insert_statement=NULL;
    
    const char *sql = "INSERT INTO users (screen_id,experience,levelid,visitat,ext1,ext2,ext3,ext4,ext5,ext6,ext7,ext8,ext9) VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?);";
    if (sqlite3_prepare_v2(database, sql, -1, &insert_statement, NULL) != SQLITE_OK) {
        printf("Error: failed to prepare statement with message '%s'.\n", sqlite3_errmsg(database));
    }
    
    int index=1;
    
    sqlite3_bind_int(insert_statement,  index++, screen_id);
    sqlite3_bind_int(insert_statement,	index++, experience);
    sqlite3_bind_int(insert_statement,	index++, levelid);
    sqlite3_bind_int(insert_statement,	index++, visitat);
    sqlite3_bind_text(insert_statement, index++, ext1.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(insert_statement, index++, ext2.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(insert_statement, index++, ext3.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(insert_statement, index++, ext4.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(insert_statement, index++, ext5.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(insert_statement, index++, ext6.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(insert_statement, index++, ext7.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(insert_statement, index++, ext8.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(insert_statement, index++, ext9.c_str(), -1, SQLITE_TRANSIENT);
    
    int success = sqlite3_step(insert_statement);
    
    if (success == SQLITE_ERROR) {
        printf("Error: failed to insert into the database with message '%s'.\n", sqlite3_errmsg(database));
        uid = 0;
    }
    else {
        uid=(int)sqlite3_last_insert_rowid(database);
    }
    
    sqlite3_reset(insert_statement);
    sqlite3_finalize(insert_statement);
    insert_statement=NULL;
}

void DBUserInfo::updateDatabase()
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    sqlite3 *database=appDelegate->database;
    sqlite3_stmt *update_statement=NULL;
    
    const char *sqlu = "UPDATE users SET screen_id=?, experience=?, levelid=?, visitat=?, ext1=?, ext2=?, ext3=?, ext4=?, ext5=?, ext6=?, ext7=?, ext8=?, ext9=? WHERE uid=?";
    if (sqlite3_prepare_v2(database, sqlu, -1, &update_statement, NULL) != SQLITE_OK) {
        printf("Error: failed to prepare statement with message '%s'.\n", sqlite3_errmsg(database));
    }
    int index=1;
    
    sqlite3_bind_int(update_statement,  index++, screen_id);
    sqlite3_bind_int(update_statement,	index++, experience);
   	sqlite3_bind_int(update_statement,	index++, levelid);
    sqlite3_bind_int(update_statement,	index++, visitat);
    sqlite3_bind_text(update_statement, index++, ext1.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext2.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext3.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext4.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext5.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext6.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext7.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext8.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(update_statement, index++, ext9.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(update_statement,	index++, uid);
    
    int success = sqlite3_step(update_statement);
    if(success==SQLITE_ERROR) {
        printf("Error: failed to insert into the database with message '%s'.\n", sqlite3_errmsg(database));
    } else {
        //NSLog(@"Updated user_infp Successfully...");
    }
    
    sqlite3_reset(update_statement);
    sqlite3_finalize(update_statement);
    update_statement=NULL;
    
    //CCLOG("this->experience %d this->nextLevel->experience %d",this->experience,this->nextLevel->experience);
    /*if(this->experience>=this->nextLevel->experience)
    {
        this->levelid=DBLevel::levelIdForExperience(this->experience);
        this->updateLevel(this->uid);
        sharedInstance=DBUserInfo::initUserInfo();
        appDelegate->gHud->loadStorePanel(panelLevelUpdatePanel);
    }
    if(appDelegate->gameLayerType==typeGameNode)
        MUSKScoreBar::sharedManager()->updateExperience();*/
}

