

#include "FBANManager.h"
#include "AppDelegate.h"
#include "../../Ads/AdMob/AdMobController.h"
#include "FBAN.h"


#pragma mark- FBAN Delegate

void FBANDelegate::provideContentForFBAN(string identifier) { }

void FBANDelegate::adsLoadingResponseForFBAN(bool isLoaded, int errorCode) { }

#pragma mark- Shared Manager

static FBANManager *sharedInstance=NULL;

FBANManager* FBANManager::sharedManager()
{
    if(sharedInstance==NULL)
    {
        sharedInstance=FBANManager::create();
    }
    return sharedInstance;
}

#pragma mark- Init Method

FBANManager::~FBANManager() { }

FBANManager::FBANManager() { }

FBANManager* FBANManager::create()
{
    FBANManager* ret = new FBANManager();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool FBANManager::init()
{
    this->adsLoadingDelegate=NULL;
    this->addDelegate=NULL;
    this->adsystem = 0;
    this->adsystem2_adtype = 1;
    return true;
}

#pragma mark- FB Audience Network Callbacks
void FBANManager::onInterstitialDisplayed(){
    CCLOG("FBANManager --> onInterstitialDisplayed");
}
void FBANManager::onInterstitialDismissed(){
    CCLOG("FBANManager --> onInterstitialDismissed");
    cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
        if(this->addDelegate!=NULL)
        {
            this->addDelegate->provideContentForFBAN("Interstitial");
        }
        this->addDelegate=NULL;
    });
}

void FBANManager::onError(){
    CCLOG("FBANManager --> onError");
    //FBAN::loadInterstitialAd();
//    this->runAction(Sequence::create(DelayTime::create(30.0),  CallFunc::create([&, this]() {
//        FBAN::loadInterstitialAd();
//    }),NULL));
}

void FBANManager::onAdLoaded(){
    CCLOG("FBANManager --> onAdLoaded");
}

void FBANManager::onAdClicked(){
    CCLOG("FBANManager --> onAdClicked");
}

void FBANManager::onLoggingImpression(){
    CCLOG("FBANManager --> onLoggingImpression");
}


void FBANManager::onInterstitialLoad(bool isLoaded, int errorCode)
{
    cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
        if(this->adsLoadingDelegate!=NULL)
        {
            this->adsLoadingDelegate->adsLoadingResponseForFBAN(isLoaded, errorCode);
        }
        this->adsLoadingDelegate=NULL;
    });
}

#pragma mark- FB Audience Network Rewarded Video Listener
void FBANManager::onRewardedError(string name, string msg)
{
    AdMobController::sharedManager()->onRewardedVideoFailedToLoad();
}

void FBANManager::onRewardedAdLoaded(string name)
{
    AdMobController::sharedManager()->onRewardedVideoLoaded(true);
}

void FBANManager::onRewardedAdClicked(string name)
{
    
}

void FBANManager::onRewardedLoggingImpression(string name)
{
    
}

void FBANManager::onRewardedVideoCompleted(double amount, string name)
{
    AdMobController::sharedManager()->onRewardedVideoFinished(amount, name);
}

void FBANManager::onRewardedVideoClosed(string name)
{
    AdMobController::sharedManager()->onRewardedVideoClosed(true);
}

