//
//  InAppController.h
//  MUSK
//
//  Created by game1 on 2/19/18.
//

#ifndef InAppController_h
#define InAppController_h

#include "cocos2d.h"
#include "extensions/ExtensionExport.h"
#include "../InAppPurchase/InappPurchaseWrapper/InApp.h"
#include "../../CustomClass/LoadingLayer.h"

USING_NS_CC;
using namespace std;

class CC_EX_DLL InAppDelegate
{
public:
    virtual ~InAppDelegate();
    virtual void provideContent(string identifier);
};
class InAppController
{
public:
    static InAppController* sharedManager();
    InAppDelegate *delegate;
#pragma mark- Init Method
    ~InAppController();
    InAppController();
    static InAppController* create();
    virtual bool init();
    
#pragma mark- In App Purchase
    void startPurchase(string strIdentifier);
    void restorePurchase(string strIdentifier);
    void loadPurcheases();
    void onPurchaseSuccess(string productId, string purchaseToken, string purchaseSignature);
    void onPurchaseFailed(int errorCode, string errorMessage);
    void onProductRequestSuccess(vector<LocalisedInappValues> products);
    
    void provideContent(string identifier);
    
#pragma mark- Loading
    LoadingLayer *loadingLayer;
    void startLoading();
    void stopLoading();
    
};

#endif /* InAppController_h */
