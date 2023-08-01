//
//  DBAttributesInfo.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 2/17/20.
//

#include "DBAttributesInfo.h"
#include "AppDelegate.h"

#pragma mark- Init Method

static vector<DBAttributesInfo*> *allAttributesInfo=new vector<DBAttributesInfo*>();

DBAttributesInfo::~DBAttributesInfo()
{
    
}

DBAttributesInfo::DBAttributesInfo()
{
    
}

DBAttributesInfo* DBAttributesInfo::create()
{
    DBAttributesInfo* ret = new DBAttributesInfo();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool DBAttributesInfo::init()
{
    setDefaultsValue();
    return true;
}

DBAttributesInfo* DBAttributesInfo::create(int primaryKey)
{
    DBAttributesInfo* ret = new DBAttributesInfo();
    if(ret && ret->init(primaryKey)) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool DBAttributesInfo::init(int primaryKey)
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    sqlite3_stmt *init_statement=NULL;
    
    sqlite3 *database=appDelegate->databaseBinary;
    
    // Compile the query for retrieving score data.
    const char *sqlf="SELECT * FROM attributes_info WHERE attributes_id=?";
    if (sqlite3_prepare_v2(database, sqlf, -1, &init_statement, NULL) != SQLITE_OK) {
        CCLOG("Error: failed to prepare statement with message '%s'.", sqlite3_errmsg(database));
    }
    sqlf=NULL;
    
    sqlite3_bind_int(init_statement, 1, primaryKey);
    if (sqlite3_step(init_statement) == SQLITE_ROW) {
        int index=1;
        
        attributes_id=primaryKey;
        attributes_type=sqlite3_column_int(init_statement,index++);
        attributes_level=sqlite3_column_int(init_statement,index++);
        attributes_unlock_level=sqlite3_column_int(init_statement,index++);
        attributes_price=AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        attributes_effect=AppDelegate::convertCharToString(sqlite3_column_text(init_statement, index++));
        attributes_experience=sqlite3_column_int(init_statement,index++);
        is_disable=sqlite3_column_int(init_statement,index++);
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
        setDefaultsValue();
    }
    
    // Reset the statement for future reuse.
    sqlite3_reset(init_statement);
    sqlite3_finalize(init_statement);
    
    return true;
}

void DBAttributesInfo::setDefaultsValue()
{
    attributes_id=0;
    attributes_type=0;
    attributes_level=0;
    attributes_unlock_level=0;
    attributes_price="0";
    attributes_effect="0";
    attributes_experience=0;
    is_disable=0;
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

void DBAttributesInfo::show()
{
    CCLOG("-------------------------------------------");
    CCLOG("attributes_id %d",attributes_id);
    CCLOG("attributes_type %d",attributes_type);
    CCLOG("attributes_level %d",attributes_level);
    CCLOG("attributes_unlock_level %d",attributes_unlock_level);
    CCLOG("attributes_price %s",attributes_price.c_str());
    CCLOG("attributes_effect %s",attributes_effect.c_str());
    CCLOG("attributes_experience %d",attributes_experience);
    CCLOG("is_disable %d",is_disable);
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

#pragma mark- DBAttributesInfo

vector<DBAttributesInfo*>* DBAttributesInfo::getAllAttributesInfo()
{
    if(allAttributesInfo->size()==0)
    {
        AppDelegate *appDelegate=AppDelegate::sharedApplication();
        
        sqlite3_stmt *iAttributesInfo_statement=NULL;
        
        string sqlfStr="select attributes_id from attributes_info where is_disable=0 ORDER BY attributes_level ASC";
        
        if (sqlite3_prepare_v2(appDelegate->databaseBinary, sqlfStr.c_str(), -1, &iAttributesInfo_statement, NULL) == SQLITE_OK)
        {
            while (sqlite3_step(iAttributesInfo_statement) == SQLITE_ROW)
            {
                int attributesId=sqlite3_column_int(iAttributesInfo_statement,0);
                allAttributesInfo->push_back(DBAttributesInfo::create(attributesId));
            }
        }
        else
        {
            CCLOG("%s", sqlite3_errmsg(appDelegate->databaseBinary));
        }
        
        // Reset the statement for future reuse.
        sqlite3_reset(iAttributesInfo_statement);
        sqlite3_finalize(iAttributesInfo_statement);
    }
    
    return allAttributesInfo;
}

DBAttributesInfo* DBAttributesInfo::getAttributesInfo(int _attributes_id)
{
    allAttributesInfo=DBAttributesInfo::getAllAttributesInfo();
    for (int i=0; i<allAttributesInfo->size(); i++)
    {
        DBAttributesInfo *attributesInfo=allAttributesInfo->at(i);
        if(attributesInfo->attributes_id == _attributes_id)
        {
            return new DBAttributesInfo(*attributesInfo);
        }
    }
    return DBAttributesInfo::create();
}

vector<DBAttributesInfo*>* DBAttributesInfo::getAttributesInfoForType(int _attributes_type)
{
    vector<DBAttributesInfo*> *arrAttributesInfo=new vector<DBAttributesInfo*>();
    
    allAttributesInfo=DBAttributesInfo::getAllAttributesInfo();
    for (int i=0; i<allAttributesInfo->size(); i++)
    {
        DBAttributesInfo *attributesInfo=allAttributesInfo->at(i);
        if(attributesInfo->attributes_type == _attributes_type)
        {
            arrAttributesInfo->push_back(attributesInfo);
        }
    }
    return arrAttributesInfo;
}

DBAttributesInfo* DBAttributesInfo::getAttributesInfoForTypeLevel(int _attributes_type,int level)
{
    allAttributesInfo=DBAttributesInfo::getAllAttributesInfo();
    
    for (int i=0; i<allAttributesInfo->size(); i++)
    {
        DBAttributesInfo *attributesInfo=allAttributesInfo->at(i);
        
        if(attributesInfo->attributes_type == _attributes_type && attributesInfo->attributes_level==level)
        {
            return attributesInfo;
        }
    }
    return DBAttributesInfo::create();
}

string DBAttributesInfo::getNameOfAttributes(int type)
{
    switch (type) {
        case TypeCustomerFrequency:
            return "Customer Frequency";
        case TypeStationCapacity:
            return "Station Capacity";
        case TypeQueueCapacity:
            return "Queue Capacity";
        case TypeTicketPrice:
            return "Ticket";
        case TypeSpeed:
            return "Speed";
        case TypeCars:
            return "Cars";
        case TypeBalloons:
            return "Balloons";
        case TypeIceCream:
            return "Ice Cream";
        case TypeFastFood:
            return "Fast Food";
        case TypeAirShip:
            return "Air Ship";
        default:
            break;
    }
    return "Name";
}










