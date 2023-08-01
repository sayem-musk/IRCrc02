//
//  SubscriptionUnit.cpp
//  MUSK
//
//  Created by game1 on 2/19/18.
//

#include "SubscriptionUnitManager.h"
#include "AppDelegate.h"

#include <iomanip> // setprecision
#include <sstream> // stringstream

#include "../InAppPurchase/InappPurchaseWrapper/InAppManager.h"

static string subscriptionData[][4] = {
    {"weeksub","Double Reward!","Get Double Reward weekly subscription.","4.99"}
    //{"monthsub","Double Reward!","Get Double Reward weekly subscription.","14.99"}
};
#pragma mark- Init Method

static SubscriptionUnitManager *sharedInstance=NULL;

SubscriptionUnitManager* SubscriptionUnitManager::sharedManager()
{
    if(sharedInstance==NULL)
    {
        sharedInstance=SubscriptionUnitManager::create();
    }
    return sharedInstance;
}

SubscriptionUnitManager::~SubscriptionUnitManager()
{
    
}

SubscriptionUnitManager::SubscriptionUnitManager()
{
    
}

SubscriptionUnitManager* SubscriptionUnitManager::create()
{
    SubscriptionUnitManager* ret = new SubscriptionUnitManager();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool SubscriptionUnitManager::init()
{
    allSubscriptionUnits = new vector<SingleSubscriptionUnit*>();
    loadAllSubscription();
    
    return true;
}

#pragma mark- Subscription Unit

vector<SingleSubscriptionUnit *> *SubscriptionUnitManager::loadAllSubscription()
{
    for ( int i = 0; i < SubscriptionType::subscriptionCount ; i++)
    {
        SingleSubscriptionUnit *singleSubUnit = SingleSubscriptionUnit::create();
        singleSubUnit->identifier = getSubscriptionIdentifier(subscriptionData[i][0], subscriptionData[i][3]);
        singleSubUnit->subscriptionTitle = subscriptionData[i][1];
        singleSubUnit->subscriptionDetails = subscriptionData[i][2];
        singleSubUnit->price_original = subscriptionData[i][3];
        
        allSubscriptionUnits->push_back(singleSubUnit);
    }
    
    return allSubscriptionUnits;
}

string SubscriptionUnitManager::getSubscriptionIdentifierWith(SubscriptionType subType)
{
    if (subType < SubscriptionType::subscriptionCount) {
        SingleSubscriptionUnit *sSubUnit = allSubscriptionUnits->at(subType);
        return sSubUnit->identifier;
    }
    return "";
}

string SubscriptionUnitManager::getSubscriptionIdentifier(string resourceType, string price)
{
    //AppDelegate *appDelegate=AppDelegate::sharedApplication();
    Config *config=Config::sharedManager();
    return config->bundleIdentifier + "." + resourceType + price;
}

#pragma MARK- SingleSubscriptionUnit

SingleSubscriptionUnit::~SingleSubscriptionUnit()
{
    
}

SingleSubscriptionUnit::SingleSubscriptionUnit()
{
    
}

SingleSubscriptionUnit* SingleSubscriptionUnit::create()
{
    SingleSubscriptionUnit* ret = new SingleSubscriptionUnit();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool SingleSubscriptionUnit::init()
{
    return true;
}

SingleSubscriptionUnit* SubscriptionUnitManager::subscriptionUnitForIdentifier(string _identifier)
{
    for (SingleSubscriptionUnit *sUnit:*allSubscriptionUnits)
    {
        if (sUnit->identifier == _identifier) {
            return sUnit;
        }
    }
    return NULL;
}

