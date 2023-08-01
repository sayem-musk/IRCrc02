//
//  SubscriptionUnit.h
//  MUSK
//
//  Created by game1 on 2/19/18.
//

#ifndef SubscriptionUnit_h
#define SubscriptionUnit_h

#include <stdio.h>
#include <vector>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

enum SubscriptionType
{
    weeksub1,
    //monthsub1,
    subscriptionCount
};

class SingleSubscriptionUnit;

class SubscriptionUnitManager
{
public:
    
    vector<SingleSubscriptionUnit*> *allSubscriptionUnits;
    
#pragma mark- Init Method
    static SubscriptionUnitManager* sharedManager();
    
    string getSubscriptionIdentifierWith(SubscriptionType subType);
    vector<SingleSubscriptionUnit *> *loadAllSubscription();
    SingleSubscriptionUnit* subscriptionUnitForIdentifier(string _identifier);
    
private:
    ~SubscriptionUnitManager();
    SubscriptionUnitManager();
    static SubscriptionUnitManager* create();
    virtual bool init();
    
    string getSubscriptionIdentifier(string resourceType, string price);
    
    
};

class SingleSubscriptionUnit
{
public:
    string identifier;
    string subscriptionTitle;
    string subscriptionDetails;
    string price_original;
    
#pragma mark- Init Method
    static SingleSubscriptionUnit* create();
private:
    ~SingleSubscriptionUnit();
    SingleSubscriptionUnit();
    virtual bool init();
};

#endif /* SubscriptionUnit_h */
