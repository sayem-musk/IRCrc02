//
//  InAppManager.h
//  MUSK
//
//  Created by Tarek Saazeb on 4/12/18.
//

#ifndef InAppManager_h
#define InAppManager_h

#include "cocos2d.h"
#include "../../InAppPurchase/InappPurchaseWrapper/InApp.h"
#include "IncludeAndroid.h"

USING_NS_CC;

using namespace std;
using namespace cocos2d;
using namespace StringUtils;

class InAppManager
{
public:
    int totalInappUnit;
    int inappInfoLoadCount;
    int countTobeCalled;
#pragma mark- Init Method
    ~InAppManager();
    InAppManager();
    static InAppManager* create();
    virtual bool init();
    static InAppManager* sharedManager();
    
#pragma mark- Inapp Purchase Methods
    void purchase(string _productId);
    void restorePurchase(string _productId);
    void loadInappProducts();
    
#pragma mark- Inapp Listener Method
    void onProductPurchasedInapp(string productId, string purchaseToken, string purchaseSignature);
    void onPurchaseHistoryRestoredInapp();
    void onBillingErrorInapp(int errorCode, string errorMessage);
    void onBillingInitializedInapp();
    void onGetInappProducts(vector<LocalisedInappValues> results);
    
    void onProductSubscription(string productId, string purchaseToken, string purchaseSignature);
    void proccessInappData(string identifier);
    
};

#endif /* InAppManager_h */
