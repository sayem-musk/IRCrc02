//
//  VideoAdsManager.cpp
//  MUSK
//
//  Created by Tarek Saazeb on 6/12/16.
//
//

#include "VideoAdsManager.h"
#include "AppDelegate.h"
#include "../../Framework/Ads/AdMob/AdMobController.h"
#include "../../Framework/Ads/FBAudienceNetwork/FBAN.h"
#include "../../Framework/Ads/FBAudienceNetwork/FBANManager.h"
#include "../../Framework/Firebase/MUSKFirebase.h"
#include "../../Framework/Firebase/MUSKFirebaseManager.h"
#include "../../CustomClass/ApplicationWrapper.h"
#include "../../CustomClass/Config.h"

#pragma mark- Video Ads Delegate

void VideoAdsDelegate::provideContentForViewAdd(string identifier) { }

#pragma mark- Shared Manager

static VideoAdsManager *sharedInstance=NULL;
VideoAdsManager* VideoAdsManager::sharedManager()
{
    if(sharedInstance==NULL)
    {
        sharedInstance=VideoAdsManager::create();
    }
    return sharedInstance;
}

#pragma mark- Init Method

VideoAdsManager::~VideoAdsManager() { }

VideoAdsManager::VideoAdsManager() { }

VideoAdsManager* VideoAdsManager::create()
{
    VideoAdsManager* ret = new VideoAdsManager();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool VideoAdsManager::init()
{
    if(Node::init())
    {
        this->addDelegate=NULL;
        this->isInterconnected=true;
        
        adSearchIndex=0;
        
        this->initializeAds();
        this->loadAds();
        
        return true;
    }
    return false;
}

void VideoAdsManager::initializeAds()
{
    AdMobController::sharedManager()->initAdmob();
    FBAN::initRewardedAd();
    setRunningAdType();
    //MUSKFirebase::initInterstitialAd();
    //MUSKFirebaseManager::sharedManager()->sendAnalyticsEvent("gaeInterstitial_Load", "0", "0", 1);
}

void VideoAdsManager::removeFromParentAndCleanup(bool cleanup)
{
    Node::removeFromParentAndCleanup(cleanup);
}

void VideoAdsManager::setRunningAdType()
{
    runningAdType=VideoAdsType::VA_AdMob;
    if(adSearchIndex<MUSKFirebaseManager::sharedManager()->adSearchOrder->size())
    {
        switch (MUSKFirebaseManager::sharedManager()->adSearchOrder->at(adSearchIndex))
        {
            case 101 ... 200:
                runningAdType=VideoAdsType::VA_FaceBookAds;
                break;
            case 201 ... 300:
                runningAdType=VideoAdsType::VA_AdMob;
                break;
            case 301 ... 400:
                runningAdType=VideoAdsType::VA_FaceBookAds_Interstitial;
                break;
            case 401 ... 500:
                runningAdType=VideoAdsType::VA_Admob_Interstitial;
                break;
                
            default:
                runningAdType=VideoAdsType::VA_AdMob;
                break;
        }
    }
}

string VideoAdsManager::getAdsUnitId()
{
    if(adSearchIndex<MUSKFirebaseManager::sharedManager()->adSearchOrder->size())
    {
        switch (MUSKFirebaseManager::sharedManager()->adSearchOrder->at(adSearchIndex))
        {
            case adKey_admob_25:
            {
                return Config::sharedManager()->admob_adunit_id_25;
            }
            case adKey_admob_20:
            {
                return Config::sharedManager()->admob_adunit_id_20;
            }
            case adKey_admob_15:
            {
                return Config::sharedManager()->admob_adunit_id_15;
            }
            case adKey_admob_10:
            {
                return Config::sharedManager()->admob_adunit_id_10;
            }
            case adKey_admob_05:
            {
                return Config::sharedManager()->admob_adunit_id_05;
            }
            case adKey_admob_default:
            {
                return Config::sharedManager()->admob_adunit_id_default;
            }
        }
    }
    return "0";
}

void VideoAdsManager::loadAds()
{
    if (adSearchIndex<MUSKFirebaseManager::sharedManager()->adSearchOrder->size())
    {
        setRunningAdType();
        
        if(runningAdType==VideoAdsType::VA_FaceBookAds || runningAdType==VideoAdsType::VA_FaceBookAds_Interstitial)
        {
            adSearchIndex++;
            loadAds();
            return;
        }
        
        MUSKFirebaseManager::sharedManager()->selectedAd = MUSKFirebaseManager::sharedManager()->adSearchOrder->at(adSearchIndex);
        strRunningAdsUnitId=getAdsUnitId();
        CCLOG("strRunningAdsUnitId %s %d %d %d",strRunningAdsUnitId.c_str(), adSearchIndex, (int)MUSKFirebaseManager::sharedManager()->adSearchOrder->size(), MUSKFirebaseManager::sharedManager()->adSearchOrder->at(adSearchIndex));
        if(strRunningAdsUnitId!="0")
        {
            if(runningAdType==VideoAdsType::VA_AdMob)
            {
                AdMobController::sharedManager()->loadAds(strRunningAdsUnitId);
            }
            else if(runningAdType==VideoAdsType::VA_FaceBookAds)
            {
                FBAN::loadRewardedAd(strRunningAdsUnitId);
            }
            else if(runningAdType==VideoAdsType::VA_FaceBookAds_Interstitial)
            {
                FBAN::initInterstitialAd(strRunningAdsUnitId);
            }
            else if(runningAdType==VideoAdsType::VA_Admob_Interstitial)
            {
                MUSKFirebase::initInterstitialAd();
                MUSKFirebaseManager::sharedManager()->loadInterstitialAd(strRunningAdsUnitId);
            }
        }
        else
            adLoadFailed();
    }
}

void VideoAdsManager::loadAds(int type,string strAdsId)
{
    runningAdType=type;
    strRunningAdsUnitId=strAdsId;
    if(type==VideoAdsType::VA_AdMob)
    {
        AdMobController::sharedManager()->loadAds(strAdsId);
    }
    else if(type==VideoAdsType::VA_FaceBookAds)
    {
        FBAN::loadRewardedAd(strAdsId);
    }
    else if(type==VideoAdsType::VA_FaceBookAds_Interstitial)
    {
        FBAN::initInterstitialAd(strAdsId);
    }
    else if(type==VideoAdsType::VA_Admob_Interstitial)
    {
        MUSKFirebase::initInterstitialAd();
        MUSKFirebaseManager::sharedManager()->loadInterstitialAd(strAdsId);
    }
}

void VideoAdsManager::adLoadComplete()
{
    log("VideoAdsManager------------------------------adLoadComplete");
    
    AppDelegate *appDelegate = (AppDelegate*)AppDelegate::sharedApplication();
    if(appDelegate->isTestMode())
    {
        //adLoadFailed();
    }
  
    adSearchIndex=MAX(adSearchIndex-2, 0);
    ///adSearchIndex++;
    //CCLOG("adLoadComplete adSearchIndex---> %d",adSearchIndex);
    //CCLOG("adLoadComplete adSearchIndex %d", adSearchIndex);
    
    //MUSKFirebaseManager::sharedManager()->sendAnalyticsEvent("gaeRewardVideo", "AdsReceived", "0", 0);
    
    //AdsAnimation::sharedManager()->adLoadComplete();
}

void VideoAdsManager::adLoadFailed()
{
    CCLOG("adLoadFailed--->");
    //AdViewPanel::waitToRequestAnotherAd();
    AppDelegate *appDelegate = (AppDelegate*)AppDelegate::sharedApplication();
    adSearchIndex++;
    
    //if(runningAdType==VideoAdsType::VA_Admob_Interstitial)
    {
        appDelegate->gHud->loadInterstitialAdFailed();
    }
    
    //CCLOG("adLoadFailed adSearchIndex %d", adSearchIndex);
    
    if(appDelegate->isTestMode())
    {
        //adSearchIndex=adSearchIndex+6;
    }
    
    if (adSearchIndex<MUSKFirebaseManager::sharedManager()->adSearchOrder->size())
    {
        this->loadAds();
    }
    else
    {
        MUSKFirebaseManager::sharedManager()->selectedAd = 0;
    }
}

void VideoAdsManager::restartAdLoad()
{
    if (adSearchIndex>=MUSKFirebaseManager::sharedManager()->adSearchOrder->size())
    {
        adSearchIndex=MAX((int)MUSKFirebaseManager::sharedManager()->adSearchOrder->size()-2, 0);
        this->loadAds();
    }
}

void VideoAdsManager::setRunningAdsType(VideoAdsManager::VideoAdsType adsType)
{
    runningAdType=adsType;
}

bool VideoAdsManager::isVideoAdsAvailable()
{
    if (runningAdType == VideoAdsType::VA_AdMob) {
        if (AdMobController::isAdsAvailable())
            return true;
    }
    else  if (runningAdType == VideoAdsType::VA_FaceBookAds) {
        if (FBAN::isRewardedAdLoaded())
            return true;
    }
    else if(runningAdType==VideoAdsType::VA_FaceBookAds_Interstitial)
    {
        if (FBAN::isInterstitialAdLoaded())
            return true;
    }
    else if(runningAdType==VideoAdsType::VA_Admob_Interstitial)
    {
        if(MUSKFirebaseManager::sharedManager()->isInterstitialAdsAvailable())
            return true;
    }
    return false;
}

void VideoAdsManager::showVideoAds(VideoAdsDelegate *_addDelegate)
{
    if (!this->isVideoAdsAvailable()) {
        return;
    }
    
    this->addDelegate=_addDelegate;
    
    //CCLOG("runningAdType: %d", runningAdType);
    
    if (runningAdType == VideoAdsType::VA_AdMob) {
        AdMobController::sharedManager()->showRewardAds();
    }
    else  if (runningAdType == VideoAdsType::VA_FaceBookAds) {
        FBAN::showRewardedAd();
    }
    else if(runningAdType==VideoAdsType::VA_FaceBookAds_Interstitial)
    {
        FBAN::showInterstitialAd();
    }
    else if(runningAdType==VideoAdsType::VA_Admob_Interstitial)
    {
        MUSKFirebaseManager::sharedManager()->showInterstitialAd();
    }
}

#pragma mark- Add Response

void VideoAdsManager::loadRewardAdsComplete()
{
    if(this->addDelegate!=NULL)
    {
        this->addDelegate->provideContentForViewAdd("rewarded Add");
    }
    this->addDelegate=NULL;
    
    this->videoAdsShowCompleted();
    this->loadAds();
}

void VideoAdsManager::loadInterstitialComplete()
{
    //int rewardAmount = INTERSTITIAL_AD_REWARD;
    //AdViewPanel::loadRewardShowPanel(rewardAmount);
}

void VideoAdsManager::reward(const std::string &name, const std::string &currency, double amount)
{
    
}

void VideoAdsManager::videoAdsShowCompleted()
{

}

void VideoAdsManager::setConnectedToInternet()
{
//    if(this->isVideoAdsAvailable())
//        this->isInterconnected=true;
//    else
    this->isInterconnected=ApplicationWrapper::sharedManager()->isConnectedToInternet();
}


