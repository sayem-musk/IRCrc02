//
//  InAppManager.cpp
//  MUSK
//
//  Created by Tarek Saazeb on 4/12/18.
//

#include "InAppManager.h"
#include "AppDelegate.h"
#include "../../InAppPurchase/InAppController.h"
#include "../../InAppPurchase/InAppUnit.h"
#include "../../../CustomClass/ApplicationWrapper.h"
#include "../../InAppPurchase/SubscriptionUnitManager.h"

#pragma mark- Shared Manager

static InAppManager *sharedInstance=NULL;

InAppManager* InAppManager::sharedManager()
{
    if(sharedInstance==NULL)
    {
        sharedInstance=InAppManager::create();
    }
    return sharedInstance;
}

#pragma mark- Init Method

InAppManager::~InAppManager()
{
    
}

InAppManager::InAppManager()
{
    
}

InAppManager* InAppManager::create()
{
    InAppManager* ret = new InAppManager();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool InAppManager::init()
{
    totalInappUnit = 0;
    inappInfoLoadCount = 0;
    countTobeCalled = 0;
    return true;
}

#pragma mark- Inapp Purchase Methods
void InAppManager::purchase(string _productId)
{
    InApp::purchase(_productId);
}

void InAppManager::restorePurchase(string _productId)
{
    InApp::restorePurchase(_productId);
}

void InAppManager::loadInappProducts()
{
    string inappIds = InAppUnit::getAllInappIds();
    CCLOG("inappIds %s",inappIds.c_str());
    InApp::loadInappProducts(inappIds,";");
}

#pragma mark- Inapp Listener Method

void InAppManager::onProductPurchasedInapp(string productId, string purchaseToken, string purchaseSignature)
{
    CCLOG("onProductPurchasedInapp-cpp");
    CCLOG("Purchase-debug code: %s token: %s signature: %s",productId.c_str(),purchaseToken.c_str(),purchaseSignature.c_str());
    InAppController::sharedManager()->onPurchaseSuccess(productId, purchaseToken, purchaseSignature);
}

void InAppManager::onPurchaseHistoryRestoredInapp()
{
    CCLOG("onPurchaseHistoryRestoredInapp-cpp");
}

void InAppManager::onBillingErrorInapp(int errorCode, string errorMessage)
{
    CCLOG("onBillingErrorInapp-cpp");
    CCLOG("Error-debug code: %d message: %s",errorCode,errorMessage.c_str());
    InAppController::sharedManager()->onPurchaseFailed(errorCode, errorMessage);
}

void InAppManager::onBillingInitializedInapp()
{
    CCLOG("onBillingInitializedInapp-cpp");
    InAppController::sharedManager()->loadPurcheases();
}

void InAppManager::onGetInappProducts(vector<LocalisedInappValues> results)
{
    CCLOG("InAppManager-size: %ld",results.size());
    
    if (results.size() <= 0 && !ApplicationWrapper::sharedManager()->isConnectedToInternet())
    {
        return;
    }
    if (results.size()<=0)
    {
        countTobeCalled++;
        if (countTobeCalled>3)
        {
            return;
        }
    }
    inappInfoLoadCount += results.size();
    InAppController::sharedManager()->onProductRequestSuccess(results);
    
    int totalInapp = InAppManager::sharedManager()->totalInappUnit;
    int loadCount = InAppManager::sharedManager()->inappInfoLoadCount;
    if (totalInapp>loadCount)
    {
        string inappIds = InAppUnit::getAllInappIds();
        InApp::loadInappProducts(inappIds,";");
    }
}

void InAppManager::onProductSubscription(string productId, string purchaseToken, string purchaseSignature)
{
    CCLOG("subscription-response-cpp: %s %s %s", productId.c_str(),purchaseToken.c_str(),purchaseSignature.c_str());
    
    //UserDefault::getInstance()->setBoolForKey("isinapppurchased", true);
    //UserDefault::getInstance()->flush();
    
    InAppController::sharedManager()->stopLoading();
    InAppManager::sharedManager()->proccessInappData(productId);
}

void InAppManager::proccessInappData(string identifier)
{
    
}
