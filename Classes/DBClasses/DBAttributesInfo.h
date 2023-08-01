//
//  DBAttributesInfo.hpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 2/17/20.
//

#ifndef DBAttributesInfo_h
#define DBAttributesInfo_h

#include "IncludeAndroid.h"

using namespace std;

//CREATE TABLE "attributes_info" ( `attributes_id` INTEGER NOT NULL, `attributes_type` INTEGER, `attributes_level` INTEGER, `attributes_unlock_level` INTEGER, `attributes_price` TEXT, `attributes_effect` TEXT,`attributes_experience` INTEGER,`is_disable` INTEGER,  `ext1` TEXT, `ext2` TEXT, `ext3` TEXT, `ext4` TEXT, `ext5` TEXT, `ext6` TEXT, `ext7` TEXT, `ext8` TEXT, `ext9` TEXT, PRIMARY KEY(`attributes_id`) )

//attributes_id,attributes_type,attributes_level,attributes_unlock_level,attributes_price,attributes_effect,attributes_experience,is_disable,ext1,ext2,ext3,ext4,ext5,ext6,ext7,ext8,ext9

class DBAttributesInfo
{
public:
    int attributes_id;
    int attributes_type;
    int attributes_level;
    int attributes_unlock_level;
    string attributes_price;
    string attributes_effect;
    int attributes_experience;
    int is_disable;
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
    ~DBAttributesInfo();
    DBAttributesInfo();
    static DBAttributesInfo* create();
    virtual bool init();
    
    static DBAttributesInfo* create(int primaryKey);
    virtual bool init(int primaryKey);
    
    void setDefaultsValue();
    void show();
    
    static vector<DBAttributesInfo*>* getAllAttributesInfo();
    static DBAttributesInfo* getAttributesInfo(int _attributes_id);
    static vector<DBAttributesInfo*>* getAttributesInfoForType(int _attributes_type);
    static DBAttributesInfo* getAttributesInfoForTypeLevel(int _attributes_type,int level);
    static string getNameOfAttributes(int type);
};

#endif /* DBAttributesInfo_h */
