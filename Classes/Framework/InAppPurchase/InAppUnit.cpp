//
//  InAppUnit.cpp
//  MUSK
//
//  Created by Tarek Saazeb on 12/14/16.
//
//

#include "InAppUnit.h"

InAppUnit::~InAppUnit()
{
    
}

InAppUnit::InAppUnit()
{
    
}

InAppUnit* InAppUnit::create()
{
    InAppUnit* ret = new InAppUnit();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool InAppUnit::init()
{
    sort_order=0;
    resourceType=0;
    identifier="0";
    amount="0";
    price="0";
    display_name="0";
    sku="0";
    inappDetails="0";
    
    return true;
}

/*
 
 1st - 100 - 1 gem
 2nd - 1,000 - 5 gems
 3rd - 10,000 - 25 gems
 4th - 100,000 - 125 gems
 5th - 1,000,000 - 600 gems
 6th - 10,000,000 - 3000 gems
 
 This is the formula to calculate gems (modified version of Dahimi's).
 
 Gems = (x - a) / ( (b - a) / (c - d) ) + d
 
 Where:
 
 x = Resources needed (gold or elixir)
 a = resource amount of plateau below resources needed.
 b = resource amount of plateau above resources needed.
 c = gem amount of plateau above resources needed.
 d = gem amount of plateau below resources needed.
 */

static int priceRange[6][2]=
{
    100,1,
    1000,5,
    10000,25,
    100000,125,
    1000000,600,
    10000000,3000,
};

int InAppUnit::priceForAmount(int amount)
{
    int priceRangeIndex=0;
    
    while (amount>priceRange[priceRangeIndex][0])
    {
        priceRangeIndex++;
    }
    int price;
    if(amount==0)
        return 0;
    else if(priceRangeIndex==0)
        price=1;
    else
    {
        int x=amount;
        int a=priceRange[priceRangeIndex-1][0];
        int b=priceRange[priceRangeIndex][0];
        int c=priceRange[priceRangeIndex][1];
        int d=priceRange[priceRangeIndex-1][1];
   
        price=(x-a)/((b-a)/(c-d))+d;
    }
    return price;
}

InAppUnit *InAppUnit::getInAppUnit(string identifier)
{
    int unitCount=(int)sizeof(productPurchaseInfo)/(sizeof(string)*5);

    for (int i=0; i<unitCount; i++)
    {
        if(productPurchaseInfo[i][0]==identifier)
        {
            InAppUnit *inAppUnit=InAppUnit::create();
            
            inAppUnit->sort_order=(i+1);
            inAppUnit->resourceType=dollarIndex;
            inAppUnit->identifier=Config::sharedManager()->bundleIdentifier+"."+productPurchaseInfo[i][0];
            inAppUnit->amount=productPurchaseInfo[i][1];
            inAppUnit->productid="0";
            inAppUnit->price=productPurchaseInfo[i][2];
            inAppUnit->display_name=productPurchaseInfo[i][3];
            inAppUnit->sku=folderImagesInAppPurchase+productPurchaseInfo[i][4];
            inAppUnit->inappDetails="No Details";
            
            return inAppUnit;
        }
    }
    return NULL;
}

InAppUnit *InAppUnit::getInAppUnitPack(string identifier)
{
    int inAppCount=(int)sizeof(packPurchaseInfo)/(sizeof(string)*6);
    
    for (int i=0; i<inAppCount; i++)
    {
        if(packPurchaseInfo[i][0]==identifier)
        {
            InAppUnit *inAppUnit=InAppUnit::create();
            inAppUnit->sort_order=(i+1);
            inAppUnit->resourceType=dollarIndex;
            inAppUnit->identifier=Config::sharedManager()->bundleIdentifier+"."+packPurchaseInfo[i][0];
            inAppUnit->amount=packPurchaseInfo[i][1];
            inAppUnit->productid=packPurchaseInfo[i][2];
            inAppUnit->price=packPurchaseInfo[i][3];
            inAppUnit->display_name=packPurchaseInfo[i][4];
            inAppUnit->sku=folderImagesInAppPurchase+packPurchaseInfo[i][5];
            inAppUnit->inappDetails="No Details";
            
            return inAppUnit;
        }
    }
    return NULL;
}

vector<InAppUnit*> *InAppUnit::getAllInAppUnit()
{
    vector<InAppUnit*> *allInapp=new vector<InAppUnit*>();
    int unitCount=(int)sizeof(productPurchaseInfo)/(sizeof(string)*5);
    
    for (int i=0; i<unitCount; i++)
    {
        InAppUnit *inAppUnit=InAppUnit::create();
        
        inAppUnit->sort_order=(i+1);
        inAppUnit->resourceType=dollarIndex;
        inAppUnit->identifier=Config::sharedManager()->bundleIdentifier+"."+productPurchaseInfo[i][0];
        inAppUnit->amount=productPurchaseInfo[i][1];
        inAppUnit->productid="0";
        inAppUnit->price=productPurchaseInfo[i][2];
        inAppUnit->display_name=productPurchaseInfo[i][3];
        inAppUnit->sku=folderImagesInAppPurchase+productPurchaseInfo[i][4];
        inAppUnit->inappDetails="No Details";
        
        allInapp->push_back(inAppUnit);
    }
    
    int inAppCount=(int)sizeof(packPurchaseInfo)/(sizeof(string)*6);
    
    for (int i=0; i<inAppCount; i++)
    {
        InAppUnit *inAppUnit=InAppUnit::create();
        inAppUnit->sort_order=(i+1);
        inAppUnit->resourceType=dollarIndex;
        inAppUnit->identifier=Config::sharedManager()->bundleIdentifier+"."+packPurchaseInfo[i][0];
        inAppUnit->amount=packPurchaseInfo[i][1];
        inAppUnit->productid=packPurchaseInfo[i][2];
        inAppUnit->price=packPurchaseInfo[i][3];
        inAppUnit->display_name=packPurchaseInfo[i][4];
        inAppUnit->sku=folderImagesInAppPurchase+packPurchaseInfo[i][5];
        inAppUnit->inappDetails="No Details";
        
        allInapp->push_back(inAppUnit);
    }
    
    return allInapp;
}

string InAppUnit::getAllInappIds()
{
    vector<InAppUnit*> *allInappInfo=InAppUnit::getAllInAppUnit();
    CCLOG("getInappIds-Enter");
    string inappIds = "";
    
    for (int i = 0; i < allInappInfo->size(); i++)
    {
        InAppUnit *sInappUnit = allInappInfo->at(i);
        inappIds += (i!=0?";":"")+sInappUnit->identifier;
    }
    CCLOG("selectedInAppUnit-size: %ld getInappIds: %s", allInappInfo->size(),inappIds.c_str());
    return inappIds;
}

InAppUnit* InAppUnit::getNoAdsInappIds()
{
    vector<InAppUnit*> *allInappInfo=InAppUnit::getAllInAppUnit();
    CCLOG("getInappIds-Enter");
    string inappIds = "";
    
    for (int i = 0; i < allInappInfo->size(); i++)
    {
        InAppUnit *sInappUnit = allInappInfo->at(i);
        if(sInappUnit->display_name=="noads")
        {
            return new InAppUnit(*sInappUnit);
        }
    }
    return InAppUnit::create();
}

