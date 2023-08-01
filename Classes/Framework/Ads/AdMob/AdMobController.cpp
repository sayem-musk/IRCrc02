//
//  adMobController.cpp
//  MUSK
//
//  Created by Tarek Saazeb on 6/12/16.
//
//

#include "AdMobController.h"
#include "AppDelegate.h"
#include "../../../DBClasses/Resources.h"
#include "../../../CustomClass/Config.h"
#include "../../Firebase/MUSKFirebase.h"
#include "../../Firebase/MUSKFirebaseManager.h"

#pragma mark- Shared Manager

static AdMobController *sharedInstance=NULL;
AdMobController* AdMobController::sharedManager()
{
    if(sharedInstance==NULL)
    {
        sharedInstance=AdMobController::create();
    }
    return sharedInstance;
}

#pragma mark- Init Method

AdMobController::AdMobController() { }

AdMobController::~AdMobController() { }

AdMobController* AdMobController::create()
{
    AdMobController* ret = new AdMobController();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool AdMobController::init()
{
    if(Node::init())
    {
        //int savedAdCounter = UserDefault::getInstance()->getIntegerForKey(adCounterKey.c_str(),0);
        //UserDefault::getInstance()->setIntegerForKey(adCounterKey.c_str(), savedAdCounter + 1);
        
        return true;
    }
    return false;
}

void AdMobController::initAdmob()
{
    MUSKFirebase::initAdmob();
}

void AdMobController::loadAds(string strAbMobId)
{
    MUSKFirebase::loadRewardedVideoAd(strAbMobId);
}

void AdMobController::waitToRequestAnotherAd(float dt)
{
    AdMobController::loadRewardAds();
}

#pragma mark- Custom

bool AdMobController::isAdsAvailable()
{
    if(MUSKFirebaseManager::sharedManager()->isAdsAvailable()){
        return true;
    }
    return false;
}

void AdMobController::loadRewardAds()
{
    CCLOG("Loading Reward Ads");
}

void AdMobController::showRewardAds()
{
    //VideoAdsManager *videoAdsManager=VideoAdsManager::sharedManager();
    
    if(MUSKFirebaseManager::sharedManager()->isAdsAvailable()) {
        MUSKFirebaseManager::sharedManager()->showRewardedAd();
    }
    else {
        CCLOG("Admob---ads not ready");
    }
}

void AdMobController::loadInterstitialAds()
{
    CCLOG("Loading Interstitial Ads");
}

void AdMobController::showInterstitialAds()
{
}

#pragma mark- Listener

void AdMobController::onRewardedVideoLoaded(bool isPrecache)
{
    CCLOG("onRewardedVideoLoaded: isPrecache: %d",isPrecache);
    VideoAdsManager::sharedManager()->adLoadComplete();
}
void AdMobController::onRewardedVideoFailedToLoad(){
    CCLOG("onRewardedVideoFailedToLoad");
    VideoAdsManager::sharedManager()->adLoadFailed();
}
void AdMobController::onRewardedVideoShown()
{
    CCLOG("onRewardedVideoShown");
}
void AdMobController::onRewardedVideoFinished(double amount, string name)
{
    VideoAdsManager *videoAdsManager=VideoAdsManager::sharedManager();
    if(videoAdsManager!=NULL) {
        int rewardAmount = 10;
        videoAdsManager->reward(name, "currency", rewardAmount);
    }
}

void AdMobController::onRewardedVideoClosed(bool finished)
{
    CCLOG("onRewardedVideoClosed: %d",finished);
 
    //CCLOG("app listener working adViewDidDismissScreen");
    VideoAdsManager *videoAdsManager=VideoAdsManager::sharedManager();
    
    cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
        if(videoAdsManager!=NULL)
            videoAdsManager->loadRewardAdsComplete();
    });
}
void AdMobController::onRewardedVideoExpired()
{
    CCLOG("onRewardedVideoExpired");
}
