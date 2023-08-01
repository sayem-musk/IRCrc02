//
//  MUSKFirebaseManager.cpp
//  MUSK
//
//  Created by Tarek Saazeb on 6/12/16.
//
//

#include "MUSKFirebaseManager.h"
#include "../../AppDelegate.h"
#include "../../Framework/Ads/AdMob/AdMobController.h"
#include "../../Framework/Firebase/MUSKFirebase.h"
#include "../../DBClasses/Resources.h"
#include "../../CustomClass/TagManager.h"

#pragma mark- Ad3Delegate

void Ad3Delegate::onInterstitial3AdClosed(string name) { }

#pragma mark- Shared Manager

static MUSKFirebaseManager *sharedInstance=NULL;

MUSKFirebaseManager* MUSKFirebaseManager::sharedManager()
{
    if(sharedInstance==NULL)
    {
        sharedInstance=MUSKFirebaseManager::create();
    }
    return sharedInstance;
}

#pragma mark- Init Method

MUSKFirebaseManager::~MUSKFirebaseManager()
{
    
}

MUSKFirebaseManager::MUSKFirebaseManager()
{
    
}

MUSKFirebaseManager* MUSKFirebaseManager::create()
{
    MUSKFirebaseManager* ret = new MUSKFirebaseManager();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool MUSKFirebaseManager::init()
{
    firMessagingType = FIRMessagingType_Gems;
    firMessagingRewardValue = 25;
    isFIREMessagingReceived = false;
    gameLoaded = false;
    adSearchOrder=TagManager::getDefaultAdsSearchOrder();
    this->ad3Delegate=NULL;
    
    return true;
}

#pragma mark- Firebase Analytics
void MUSKFirebaseManager::sendAnalyticsEvent(string _eventName, string _eventCategory, string _eventLabel, int _eventValue)
{
    int remoteValue = TagManager::getAnalyticsService();
    if (remoteValue == 0) {
        MUSKFirebase::sendAnalyticsEvent(_eventName, _eventCategory, _eventLabel, _eventValue);
        MUSKFirebase::sendGoogleAnalyticsEvent(_eventName, _eventCategory, _eventLabel, _eventValue);
    }
    else if (remoteValue == 1) {
        MUSKFirebase::sendAnalyticsEvent(_eventName, _eventCategory, _eventLabel, _eventValue);
    }
    else if (remoteValue == 2){
        MUSKFirebase::sendGoogleAnalyticsEvent(_eventName, _eventCategory, _eventLabel, _eventValue);
    }
}

void MUSKFirebaseManager::sendVirtualCurrencyEvent(string _eventName, string _itemName, string _currencyName, int _value)
{
    int remoteValue = TagManager::getAnalyticsService();
    if (remoteValue == 0) {
        MUSKFirebase::sendVirtualCurrencyEvent(_eventName, _itemName, _currencyName, _value);
    }
    else if (remoteValue == 1) {
        MUSKFirebase::sendVirtualCurrencyEvent(_eventName, _itemName, _currencyName, _value);
    }
}

#pragma mark- Firebase Screen

void MUSKFirebaseManager::setCurrentScreen(string _screenName, string _screenClass)
{
    MUSKFirebase::setCurrentScreen(_screenName, _screenClass);
}

#pragma mark- Firebase RemoteConfig
string MUSKFirebaseManager::getRemoteConfigValue(string key)
{
    return MUSKFirebase::getRemoteConfigValue(key);
}

#pragma mark- Firebase RemoteConfig Listener
void MUSKFirebaseManager::onRemoteFetchCompleted(bool isSuccess)
{
    CCLOG("onRemoteFetchCompleted: %d",isSuccess);
    
    vector<int> *adSearchOrderRemote = TagManager::getAdSearchOrder();
    if (adSearchOrderRemote->size() > 0) {
        adSearchOrder->clear();
        adSearchOrder = adSearchOrderRemote;
    }
    
//    AppDelegate *appDelegate =AppDelegate::sharedApplication();
//    string adSearchOrderStr = MUSKFirebaseManager::sharedManager()->getRemoteConfigValue("adSearchOrder1");
//    vector<string> *adSearchOrderStrArray = appDelegate->componentSeparatedByString(adSearchOrderStr, ",");
//
//    adSearchOrder->clear();
//
//    for (string element:*adSearchOrderStrArray)
//    {
//        if(element!="")
//            adSearchOrder->push_back(stoi(element));
//    }
    
    /*string totalAdTypeStr = MUSKFirebaseManager::sharedManager()->getRemoteConfigValue("totalAdTypeStr1");
    MUSKFirebaseManager::sharedManager()->TotalAdType = stoi(totalAdTypeStr);
    
    CCLOG("debug-remoteconfig: %s %s %d",adSearchOrderStr.c_str(), totalAdTypeStr.c_str(),MUSKFirebaseManager::sharedManager()->TotalAdType);*/
}

#pragma mark- Firebase AdMob
void MUSKFirebaseManager::loadRewardedVideoAd(string adUnitId)
{
    MUSKFirebase::loadRewardedVideoAd(adUnitId);
}

void MUSKFirebaseManager::showRewardedAd()
{
    MUSKFirebase::showRewardedAd();
}

bool MUSKFirebaseManager::isAdsAvailable()
{
    return MUSKFirebase::isAdsAvailable();
}

#pragma mark- Firebase AdMob Interstitial
void MUSKFirebaseManager::loadInterstitialAd(string adUnitId)
{
    MUSKFirebase::loadInterstitialAd(adUnitId);
    MUSKFirebaseManager::sharedManager()->sendAnalyticsEvent("gaeInterstitial_Load", "0", "0", 1);
}

void MUSKFirebaseManager::showInterstitialAd()
{
    MUSKFirebase::showInterstitialAd();
    MUSKFirebaseManager::sharedManager()->sendAnalyticsEvent("gaeInterstitial_Show", "0", "0", 1);
}

bool MUSKFirebaseManager::isInterstitialAdsAvailable()
{
    return MUSKFirebase::isInterstitialAdsAvailable();
}

#pragma mark- Firebase Admob Listener

void MUSKFirebaseManager::onFireAdMobRewarded(string name, string type, double amount)
{
    CCLOG("fb - cpp - onFireAdMobRewarded");
    AdMobController::sharedManager()->onRewardedVideoFinished(amount, name);
}

void MUSKFirebaseManager::onFireAdmobRewardedVideoAdLeftApplication(string name)
{
    CCLOG("fb - cpp - onFireAdmobRewardedVideoAdLeftApplication");
}

void MUSKFirebaseManager::onFireAdmobRewardedVideoAdClosed(string name)
{
    CCLOG("fb - cpp - onFireAdmobRewardedVideoAdClosed");
    AdMobController::sharedManager()->onRewardedVideoClosed(false);
}

void MUSKFirebaseManager::onFireAdmobRewardedVideoAdFailedToLoad(string name)
{
    CCLOG("fb - cpp - onFireAdmobRewardedVideoAdFailedToLoad");
    AdMobController::sharedManager()->onRewardedVideoFailedToLoad();
}

void MUSKFirebaseManager::onFireAdmobRewardedVideoAdLoaded(string name)
{
    CCLOG("fb - cpp - onFireAdmobRewardedVideoAdLoaded");
    AdMobController::sharedManager()->onRewardedVideoLoaded(false);
}

void MUSKFirebaseManager::onFireAdmobRewardedVideoAdOpened(string name)
{
    CCLOG("fb - cpp - onFireAdmobRewardedVideoAdOpened");
    AdMobController::sharedManager()->onRewardedVideoShown();
}

void MUSKFirebaseManager::onFireAdmobRewardedVideoStarted(string name)
{
    CCLOG("fb - cpp - onFireAdmobRewardedVideoStarted");
    
}

void MUSKFirebaseManager::onFireAdmobRewardedVideoCompleted(string name)
{
    CCLOG("fb - cpp - onFireAdmobRewardedVideoCompleted");
    
}

string getValueFromKey(string key, vector<string> *allPairs, string separator){
    for (int i=0; i<allPairs->size(); i++) {
        string pair = allPairs->at(i);
        vector<string> *arrSinglePair = AppDelegate::componentSeparatedByString(pair, separator);
        
        string tempKey = arrSinglePair->at(0);
        string tempValue = arrSinglePair->at(1);
        if(tempKey == key)return tempValue;
    }
    return "";
}

#pragma mark- Firebase In App Messaging
void  MUSKFirebaseManager::onFirebaseInAppMessagingParamsReceived(string params){
    
    CCLOG("fb - cpp - onFirebaseInAppMessagingParamsReceived %s", params.c_str());
    //AppDelegate *appDelegate=AppDelegate::sharedApplication();
    
    vector<string> *allPairs=AppDelegate::componentSeparatedByString(params, "&");
    
    CCLOG("allPairs = %ld", allPairs->size());
    
    for (int i=0; i<allPairs->size(); i++) {
        string pair = allPairs->at(i);
        vector<string> *arrSinglePair = AppDelegate::componentSeparatedByString(pair, "=");
        CCLOG("arrSinglePair = %ld", arrSinglePair->size());
        string key = arrSinglePair->at(0);
        string value = arrSinglePair->at(1);
        CCLOG("[%s] = %s", key.c_str(), value.c_str());
        
        if(key == "type" && value == "rewardgems") {
            string rewardAmount = getValueFromKey("rewardamount", allPairs, "=");
            int rewardAmountInt = 0;
            if(rewardAmount != "" && !rewardAmount.empty()) {
                rewardAmountInt = stoi(rewardAmount);
                CCLOG("I have got reward : rewardAmount =  %s", rewardAmount.c_str());
            }
            
            cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
                if(rewardAmountInt > 0 && rewardAmountInt < 10000) {
                    Resources *resources=Resources::sharedManager();
                    resources->addResource(bucksIndex,ClickerCalculation::getNewVector(to_string(rewardAmountInt)));
                }
            });
            
            break;
        }
    }
    
}

#pragma mark- Firebase Messaging
void  MUSKFirebaseManager::onFirebaseMessagingParamsReceived(string params){
    
    CCLOG("fb - cpp - onFirebaseMessagingParamsReceived %s", params.c_str());
    
    vector<string> *allPairs=AppDelegate::componentSeparatedByString(params, "&");
    
    for (int i=0; i<allPairs->size(); i++) {
        string pair = allPairs->at(i);
        vector<string> *arrSinglePair = AppDelegate::componentSeparatedByString(pair, "=");
        
        if(arrSinglePair->at(0) == "firebase" && arrSinglePair->at(1) == "reward"){
            isFIREMessagingReceived = true;
            break;
        }
    }

    int dragonId = 0;
    string dragonIdStr = getValueFromKey("dragon", allPairs, "=");
    if(dragonIdStr != "" && !dragonIdStr.empty())dragonId = stoi(dragonIdStr);
    if(dragonId > 0){
        CCLOG("ash dragon %d", dragonId);
        firMessagingType = FIRMessagingType_Product;
        firMessagingRewardValue = dragonId;
    }

    int noOfGem = 0;
    string noOfGemStr = getValueFromKey("gem", allPairs, "=");
    if(noOfGemStr != "" && !noOfGemStr.empty())noOfGem = stoi(noOfGemStr);
    if(noOfGem > 0 && noOfGem < 10000){
        CCLOG("ash gem %d", noOfGem);
        firMessagingType = FIRMessagingType_Gems;
        firMessagingRewardValue = noOfGem;
    }

    CCLOG("gameLoaded %d",gameLoaded);
    if(gameLoaded){
        cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
            MUSKFirebaseManager::sharedManager()->onFirebaseMessagingRewardCollected();
        });
    }
}

void  MUSKFirebaseManager::onFirebaseMessagingRewardCollected() {
    CCLOG("fb - cpp - onFirebaseMessagingParamsReceived %s", "onFirebaseMessagingRewardCollected");
    
    if(gameLoaded == false)gameLoaded = true;
    
    if(isFIREMessagingReceived){
        isFIREMessagingReceived = false;
        //AppDelegate *appDelegate=AppDelegate::sharedApplication();
        //InAppMessagingPopup *rewardPanel = InAppMessagingPopup::create();
        //appDelegate->gHud->addChild(rewardPanel, 10);
    }
}
