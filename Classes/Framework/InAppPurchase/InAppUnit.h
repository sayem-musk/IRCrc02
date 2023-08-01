//
//  InAppUnit.h
//  MUSK
//
//  Created by Tarek Saazeb on 12/14/16.
//
//

#ifndef InAppUnit_h
#define InAppUnit_h

#include <stdio.h>
#include "AppDelegate.h"

using namespace std;

static string productPurchaseInfo[][5]=
{
    "noads","0,0",to_string(dollarIndex)+",2.99","noads",""
};
/*{
    "com.insparofaith.doa.99gems",to_string(buckIndex)+",99",to_string(dollarIndex)+",0.99","Pocket Of Gems","inapp_gems_cell_bg_1",
    "com.insparofaith.doa.599gems",to_string(buckIndex)+",600",to_string(dollarIndex)+",4.99","Pile Of Gems","inapp_gems_cell_bg_2",
    "com.insparofaith.doa.1500gems",to_string(buckIndex)+",1500",to_string(dollarIndex)+",9.99","Bag Of Gems","inapp_gems_cell_bg_3",
    "com.insparofaith.doa.3500gems",to_string(buckIndex)+",3500",to_string(dollarIndex)+",19.99","Sack Of Gems","inapp_gems_cell_bg_4",
    
    "com.insparofaith.doa.99gems",to_string(coinIndex)+",1000",to_string(dollarIndex)+",0.99","Pocket Of Coins","inapp_coin_cell_bg_1",
    "com.insparofaith.doa.599gems",to_string(coinIndex)+",2000",to_string(dollarIndex)+",4.99","Pile Of Coins","inapp_coin_cell_bg_2",
    "com.insparofaith.doa.1500gems",to_string(coinIndex)+",3000",to_string(dollarIndex)+",9.99","Bag Of Coins","inapp_coin_cell_bg_3",
    "com.insparofaith.doa.3500gems",to_string(coinIndex)+",4000",to_string(dollarIndex)+",19.99","Sack Of Coins","inapp_coin_cell_bg_4",
    
    "com.insparofaith.doa.99gems",to_string(foodIndex)+",100",to_string(dollarIndex)+",0.99","Pocket Of Foods","inapp_food_cell_bg_1",
    "com.insparofaith.doa.599gems",to_string(foodIndex)+",200",to_string(dollarIndex)+",4.99","Pile Of Foods","inapp_food_cell_bg_2",
    "com.insparofaith.doa.1500gems",to_string(foodIndex)+",300",to_string(dollarIndex)+",9.99","Bag Of Foods","inapp_food_cell_bg_3",
    "com.insparofaith.doa.3500gems",to_string(foodIndex)+",400",to_string(dollarIndex)+",19.99","Sack Of Foods","inapp_food_cell_bg_4"
};*/

/*{
    "com.insparofaith.dragonfantacy.gems.1.99",to_string(buckIndex)+",50",to_string(dollarIndex)+",1.99","Pile of Gems","inapp_gems_cell_bg_1",
    "com.insparofaith.dragonfantacy.gems.4.99",to_string(buckIndex)+",150",to_string(dollarIndex)+",4.99","Bag of Gems","inapp_gems_cell_bg_2",
    "com.insparofaith.dragonfantacy.gems.9.99",to_string(buckIndex)+",350",to_string(dollarIndex)+",9.99","Bucket of Gems","inapp_gems_cell_bg_3",
    "com.insparofaith.dragonfantacy.gem.29.99",to_string(buckIndex)+",1200",to_string(dollarIndex)+",29.99","Chest of Gems","inapp_gems_cell_bg_4",
    
    "com.insparofaith.dragonfantacy.coins.1.99",to_string(coinIndex)+",10000",to_string(dollarIndex)+",1.99","Pile of Coins","inapp_coin_cell_bg_1",
    "com.insparofaith.dragonfantacy.coins.4.99",to_string(coinIndex)+",30000",to_string(dollarIndex)+",4.99","Bag of Coins","inapp_coin_cell_bg_2",
    "com.insparofaith.dragonfantacy.coins.9.99",to_string(coinIndex)+",70000",to_string(dollarIndex)+",9.99","Bucket of Coins","inapp_coin_cell_bg_3",
    "com.insparofaith.dragonfantacy.coins.29.99",to_string(coinIndex)+",250000",to_string(dollarIndex)+",29.99","Chest of Coins","inapp_coin_cell_bg_4",
    
    "com.insparofaith.dragonfantacy.food.1.99",to_string(foodIndex)+",1000",to_string(dollarIndex)+",1.99","Pile of Foods","inapp_food_cell_bg_1",
    "com.insparofaith.dragonfantacy.food.4.99",to_string(foodIndex)+",3000",to_string(dollarIndex)+",4.99","Bag of Foods","inapp_food_cell_bg_2",
    "com.insparofaith.dragonfantacy.food.9.99",to_string(foodIndex)+",7000",to_string(dollarIndex)+",9.99","Bucket of Foods","inapp_food_cell_bg_3",
    "com.insparofaith.dragonfantacy.food.29.99",to_string(foodIndex)+",21000",to_string(dollarIndex)+",29.99","Chest of Foods","inapp_food_cell_bg_4"
};*/

/*{
    "gems.1.99",to_string(buckIndex)+",50",to_string(dollarIndex)+",1.99","Pile of Gems","inapp_gems_cell_bg_1",
    "gems.4.99",to_string(buckIndex)+",150",to_string(dollarIndex)+",4.99","Bag of Gems","inapp_gems_cell_bg_2",
    "gems.9.99",to_string(buckIndex)+",350",to_string(dollarIndex)+",9.99","Bucket of Gems","inapp_gems_cell_bg_3",
    "gem.29.99",to_string(buckIndex)+",1200",to_string(dollarIndex)+",29.99","Chest of Gems","inapp_gems_cell_bg_4",
    
    "coins.1.99",to_string(coinIndex)+",10000",to_string(dollarIndex)+",1.99","Pile of Coins","inapp_coin_cell_bg_1",
    "coins.4.99",to_string(coinIndex)+",30000",to_string(dollarIndex)+",4.99","Bag of Coins","inapp_coin_cell_bg_2",
    "coins.9.99",to_string(coinIndex)+",70000",to_string(dollarIndex)+",9.99","Bucket of Coins","inapp_coin_cell_bg_3",
    "coins.29.99",to_string(coinIndex)+",250000",to_string(dollarIndex)+",29.99","Chest of Coins","inapp_coin_cell_bg_4",
    
    "food.1.99",to_string(foodIndex)+",1000",to_string(dollarIndex)+",1.99","Pile of Foods","inapp_food_cell_bg_1",
    "food.4.99",to_string(foodIndex)+",3000",to_string(dollarIndex)+",4.99","Bag of Foods","inapp_food_cell_bg_2",
    "food.9.99",to_string(foodIndex)+",7000",to_string(dollarIndex)+",9.99","Bucket of Foods","inapp_food_cell_bg_3",
    "food.29.99",to_string(foodIndex)+",21000",to_string(dollarIndex)+",29.99","Chest of Foods","inapp_food_cell_bg_4"
};*/

static string packPurchaseInfo[][6]=
/*{
    "com.insparofaith.dragonfantacy.pack.4.99",to_string(buckIndex)+",100;"+to_string(coinIndex)+",25000;"+to_string(foodIndex)+",2500",to_string(0),to_string(dollarIndex)+",4.99","Pile of Gems","inapp_pack_cell_bg_1",
    "com.insparofaith.dragonfantacy.pack.14.99",to_string(buckIndex)+",250;"+to_string(coinIndex)+",50000;"+to_string(foodIndex)+",5000",to_string(0),to_string(dollarIndex)+",14.99","Pile of Gems","inapp_pack_cell_bg_2",
    "com.insparofaith.dragonfantacy.pack.29.99",to_string(buckIndex)+",750;"+to_string(coinIndex)+",225000;"+to_string(foodIndex)+",22500",to_string(0),to_string(dollarIndex)+",29.99","Pile of Gems","inapp_pack_cell_bg_3",
};*/
{
    /*"pack.4.99",to_string(buckIndex)+",100;"+to_string(coinIndex)+",25000;"+to_string(foodIndex)+",2500",to_string(0),to_string(dollarIndex)+",4.99","Pile of Gems","inapp_pack_cell_bg_1",
    "pack.14.99",to_string(buckIndex)+",250;"+to_string(coinIndex)+",50000;"+to_string(foodIndex)+",5000",to_string(0),to_string(dollarIndex)+",14.99","Pile of Gems","inapp_pack_cell_bg_2",
    "pack.29.99",to_string(buckIndex)+",750;"+to_string(coinIndex)+",225000;"+to_string(foodIndex)+",22500",to_string(0),to_string(dollarIndex)+",29.99","Pile of Gems","inapp_pack_cell_bg_3",*/
};

class InAppUnit
{
public:
    int sort_order;
    int resourceType;
    string identifier;
    string amount;
    string price;
    string display_name;
    string sku;
    string inappDetails;
    string productid;
    
    ~InAppUnit();
    InAppUnit();
    static InAppUnit* create();
    virtual bool init();
    
    static int priceForAmount(int amount);
    
    static InAppUnit* getInAppUnit(string identifier);
    static InAppUnit* getInAppUnitPack(string identifier);
    
    static vector<InAppUnit*> *getAllInAppUnit();
    static string getAllInappIds();
    static InAppUnit* getNoAdsInappIds();

};

#endif /* InAppUnit_hpp */
