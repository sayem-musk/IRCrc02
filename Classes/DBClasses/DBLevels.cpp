//
//  DBLevels.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 2/17/20.
//

#include "DBLevels.h"
#include "AppDelegate.h"

#pragma mark- Init Method

static vector<DBLevels*> *allLevels=new vector<DBLevels*>();

DBLevels::~DBLevels()
{
    
}

DBLevels::DBLevels()
{
    
}

DBLevels* DBLevels::create()
{
    DBLevels* ret = new DBLevels();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool DBLevels::init()
{
    return true;
}

DBLevels* DBLevels::create(int primaryKey)
{
    DBLevels* ret = new DBLevels();
    if(ret && ret->init(primaryKey)) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool DBLevels::init(int primaryKey)
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    sqlite3_stmt *init_statement=NULL;
    
    sqlite3 *database=appDelegate->databaseBinary;
    
    // Compile the query for retrieving score data.
    const char *sqlf="SELECT * FROM levels WHERE levelid=?";
    if (sqlite3_prepare_v2(database, sqlf, -1, &init_statement, NULL) != SQLITE_OK) {
        CCLOG("Error: failed to prepare statement with message '%s'.", sqlite3_errmsg(database));
    }
    sqlf=NULL;
    
    sqlite3_bind_int(init_statement, 1, primaryKey);
    if (sqlite3_step(init_statement) == SQLITE_ROW) {
        int index=1;
        levelid=primaryKey;
        experience=sqlite3_column_int(init_statement,index++);
        experience_per_customer=sqlite3_column_int(init_statement,index++);
        rewards=AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        rewards_xp=AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
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
        levelid=0;
        experience=0;
        experience_per_customer=0;
        rewards="0";
        rewards_xp="0";
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

void DBLevels::show()
{
    CCLOG("-------------------------------------------");
    CCLOG("levelid %d",levelid);
    CCLOG("experience %d",experience);
    CCLOG("experience_per_customer %d",experience_per_customer);
    CCLOG("rewards %s",rewards.c_str());
    CCLOG("rewards_xp %s",rewards_xp.c_str());
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

#pragma mark- DBLevels

vector<DBLevels*>* DBLevels::getAllLevels()
{
    if(allLevels->size()==0)
    {
        AppDelegate *appDelegate=AppDelegate::sharedApplication();
        
        sqlite3_stmt *iLevels_statement=NULL;
        
        string sqlfStr="select levelid from levels ORDER BY levelid ASC";
        
        if (sqlite3_prepare_v2(appDelegate->databaseBinary, sqlfStr.c_str(), -1, &iLevels_statement, NULL) == SQLITE_OK)
        {
            while (sqlite3_step(iLevels_statement) == SQLITE_ROW)
            {
                int levelId=sqlite3_column_int(iLevels_statement,0);
                allLevels->push_back(DBLevels::create(levelId));
            }
        }
        else
        {
            CCLOG("%s", sqlite3_errmsg(appDelegate->databaseBinary));
        }
        
        // Reset the statement for future reuse.
        sqlite3_reset(iLevels_statement);
        sqlite3_finalize(iLevels_statement);
    }
    
    return allLevels;
}

DBLevels* DBLevels::getLevels(int _levelid)
{
    allLevels=DBLevels::getAllLevels();
    for (int i=0; i<allLevels->size(); i++)
    {
        DBLevels *levels=allLevels->at(i);
        if(levels->levelid == _levelid)
        {
            return new DBLevels(*levels);
        }
    }
    return DBLevels::create();
}



