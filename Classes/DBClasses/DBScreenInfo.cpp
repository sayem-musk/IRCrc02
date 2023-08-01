//
//  DBScreenInfo.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 2/15/20.
//

#include "DBScreenInfo.h"
#include "AppDelegate.h"

#pragma mark- Init Method

static vector<DBScreenInfo*> *allScreenInfo=new vector<DBScreenInfo*>();

DBScreenInfo::~DBScreenInfo()
{
    
}

DBScreenInfo::DBScreenInfo()
{
    
}

DBScreenInfo* DBScreenInfo::create()
{
    DBScreenInfo* ret = new DBScreenInfo();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool DBScreenInfo::init()
{
    return true;
}

DBScreenInfo* DBScreenInfo::create(int primaryKey)
{
    DBScreenInfo* ret = new DBScreenInfo();
    if(ret && ret->init(primaryKey)) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool DBScreenInfo::init(int primaryKey)
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    sqlite3_stmt *init_statement=NULL;
    
    sqlite3 *database=appDelegate->databaseBinary;
    
    // Compile the query for retrieving score data.
    const char *sqlf="SELECT * FROM screen_info WHERE screen_id=?";
    if (sqlite3_prepare_v2(database, sqlf, -1, &init_statement, NULL) != SQLITE_OK) {
        CCLOG("Error: failed to prepare statement with message '%s'.", sqlite3_errmsg(database));
    }
    sqlf=NULL;
    
    sqlite3_bind_int(init_statement, 1, primaryKey);
    if (sqlite3_step(init_statement) == SQLITE_ROW) {
        int index=1;
        screen_id=primaryKey;
        screen_name=AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        unlock_level=sqlite3_column_int(init_statement,index++);
        unlock_price=AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        unlock_price_exp=AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        screen_order=sqlite3_column_int(init_statement,index++);
        disable=sqlite3_column_int(init_statement,index++);
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
        screen_id=0;
        screen_name="0";
        unlock_level=0;
        unlock_price="0";
        unlock_price_exp="0";
        screen_order=0;
        disable=0;
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

void DBScreenInfo::show()
{
    CCLOG("-------------------------------------------");
    CCLOG("screen_id %d",screen_id);
    CCLOG("screen_name %s",screen_name.c_str());
    CCLOG("unlock_level %d",unlock_level);
    CCLOG("unlock_price %s",unlock_price.c_str());
    CCLOG("unlock_price_exp %s",unlock_price_exp.c_str());    
    CCLOG("screen_order %d",screen_order);
    CCLOG("disable %d",disable);
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

#pragma mark- DBScreenInfo

vector<DBScreenInfo*>* DBScreenInfo::getAllScreenInfo()
{
    if(allScreenInfo->size()==0)
    {
        AppDelegate *appDelegate=AppDelegate::sharedApplication();
        
        sqlite3_stmt *iScreenInfo_statement=NULL;
        
        string sqlfStr="select screen_id from screen_info ORDER BY screen_order ASC";
        
        if (sqlite3_prepare_v2(appDelegate->databaseBinary, sqlfStr.c_str(), -1, &iScreenInfo_statement, NULL) == SQLITE_OK)
        {
            while (sqlite3_step(iScreenInfo_statement) == SQLITE_ROW)
            {
                int screenId=sqlite3_column_int(iScreenInfo_statement,0);
                allScreenInfo->push_back(DBScreenInfo::create(screenId));
            }
        }
        else
        {
            CCLOG("%s", sqlite3_errmsg(appDelegate->databaseBinary));
        }
        
        // Reset the statement for future reuse.
        sqlite3_reset(iScreenInfo_statement);
        sqlite3_finalize(iScreenInfo_statement);
    }
    
    return allScreenInfo;
}

DBScreenInfo* DBScreenInfo::getScreenInfo(int _screen_id)
{
    allScreenInfo=DBScreenInfo::getAllScreenInfo();
    for (int i=0; i<allScreenInfo->size(); i++)
    {
        DBScreenInfo *screenInfo=allScreenInfo->at(i);
        if(screenInfo->screen_id == _screen_id)
        {
            return new DBScreenInfo(*screenInfo);
        }
    }
    return DBScreenInfo::create();
}










