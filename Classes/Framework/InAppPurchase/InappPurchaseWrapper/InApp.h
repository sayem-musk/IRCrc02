//
//  InApp.h
//  ITIW
//
//  Created by itiw on 3/3/18.
//
//

#ifndef InApp_h
#define InApp_h

#include "platform/CCPlatformMacros.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

struct LocalisedInappValues {
    string productId;
    string currency;
    double priceValue;
};

class InApp
{
public:
    static InApp* sharedManager();
   
#pragma mark- Init Method
    ~InApp();
    InApp();
    static InApp* create();
    virtual bool init();

#pragma mark- InApp initialization
    static void initInApp();
    
#pragma mark- InApp custom methods
    static void purchase(string _productId);
    static void restorePurchase(string _productId);
    static bool isInappServiceAvailable();
    static void loadInappProducts(string productIds, string seperator);
    
    static void subscribe(string _productId);
    static bool isSubscribed(string _productId);
    static bool isCancelled(string _productId);
};


#endif /* InApp_h */
