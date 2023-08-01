//
//  InAppController.cpp
//  MUSK
//
//  Created by game1 on 2/19/18.
//

#include "InAppController.h"
#include "AppDelegate.h"
#include "../InAppPurchase/InAppUnit.h"
#include "../InAppPurchase/InappPurchaseWrapper/InAppManager.h"

#pragma mark- InAppDelegate

InAppDelegate::~InAppDelegate()
{
    
}

void InAppDelegate::provideContent(string identifier)
{
}

#pragma mark- Shared Manager

static InAppController *sharedInstance=NULL;
InAppController* InAppController::sharedManager()
{
    if(sharedInstance==NULL)
    {
        sharedInstance=InAppController::create();
    }
    return sharedInstance;
}

#pragma mark- Init Method

InAppController::~InAppController()
{
    
}

InAppController::InAppController()
{
    
}

InAppController* InAppController::create()
{
    InAppController* ret = new InAppController();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool InAppController::init()
{
    delegate=NULL;
    return true;
}

#pragma mark- In App Purchase

void InAppController::loadPurcheases()
{
    CCLOG("loadPurcheases");
    //nIAP::getProducts();
    InAppManager::sharedManager()->loadInappProducts();
}

void InAppController::startPurchase(string strIdentifier)
{
    UserDefault::getInstance()->setStringForKey("strInAppIdentifier", strIdentifier);
    UserDefault::getInstance()->flush();
    //AppDelegate *appDelegate=AppDelegate::sharedApplication();
    CCLOG("Start IAP %s", strIdentifier.c_str());
    InAppController::sharedManager()->startLoading();
    //IAP::purchase(strIdentifier);
    InAppManager::sharedManager()->purchase(strIdentifier);
}

void InAppController::restorePurchase(string strIdentifier)
{
    UserDefault::getInstance()->setStringForKey("strInAppIdentifier", strIdentifier);
    UserDefault::getInstance()->flush();
    //AppDelegate *appDelegate=AppDelegate::sharedApplication();
    CCLOG("Start IAP %s", strIdentifier.c_str());
    InAppController::sharedManager()->startLoading();
    //IAP::purchase(strIdentifier);
    InAppManager::sharedManager()->restorePurchase(strIdentifier);
}

void InAppController::onPurchaseSuccess(string productId, string purchaseToken, string purchaseSignature)
{
    string strIdentifier = UserDefault::getInstance()->getStringForKey("strInAppIdentifier", "pack2");
    
    if(this->delegate!=NULL)
        this->delegate->provideContent(strIdentifier);
    else
        this->provideContent(strIdentifier);
    
    InAppController::sharedManager()->stopLoading();
}

void InAppController::onPurchaseFailed(int errorCode, string errorMessage)
{
    InAppController::sharedManager()->stopLoading();
}

void InAppController::onProductRequestSuccess(vector<LocalisedInappValues> products)
{
    for ( LocalisedInappValues product: products)
    {
        //InAppUnit::updateAllInAppUnit(product.productId.c_str(),product.currency.c_str(),product.priceValue);
    }
}

#pragma mark- provideContent

void InAppController::provideContent(string identifier)
{
    //InAppUnit *inAppUnit=InAppUnit::getInAppUnit(identifier);
    //Resources::addResource(inAppUnit->amount);
}

#pragma mark- Loading

void InAppController::startLoading()
{
    CCLOG("startLoading()---");
    //Size winSize=Director::getInstance()->getVisibleSize();
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    loadingLayer=LoadingLayer::create();
    appDelegate->gHud->addChild(loadingLayer,20);
    printf("InAppController::startLoading\n");
}

void InAppController::stopLoading() {
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    //if (loadingLayer != nullptr && loadingLayer != NULL)
    if(AppDelegate::isContainObject(appDelegate->gHud, loadingLayer))
        loadingLayer->removeFromParentAndCleanup(true);
}










