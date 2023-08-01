//
//  MUSKFirebase.cpp
//  MUSK-mobile
//
//  Created by Tarek Saazeb on 5/25/18.
//

#include "MUSKFirebase.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS && CC_TARGET_PLATFORM != CC_PLATFORM_MAC && CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)

#include "GoogleAnalyticsManager.h"

#pragma mark- Firebase Analytics
void MUSKFirebase::initFireAnalytics()
{
    
}

void MUSKFirebase::sendAnalyticsEvent(string _eventName, string _eventCategory, string _eventLabel, int _eventValue)
{
    
}

void MUSKFirebase::sendVirtualCurrencyEvent(string _eventName, string _itemName, string _currencyName, int _value)
{
    
}

#pragma mark- Google Analytics
void MUSKFirebase::initGoogleAnalytics()
{
    
}

void MUSKFirebase::sendGoogleAnalyticsEvent(string _eventName, string _eventCategory, string _eventLabel, int _eventValue)
{
    
}

#pragma mark- Firebase Screen

void MUSKFirebase::setCurrentScreen(string _screenName, string _screenClass)
{
    
}

#pragma mark- Firebase RemoteConfig
void MUSKFirebase::initRemoteConfig()
{
    
}

string MUSKFirebase::getRemoteConfigValue(string key)
{
    return "0";
}

#pragma mark- Firebase AdMob
void MUSKFirebase::initAdmob()
{
    
}

void MUSKFirebase::loadRewardedVideoAd(string adUnitId)
{
    
}

void MUSKFirebase::showRewardedAd()
{
    
}

bool MUSKFirebase::isAdsAvailable()
{
    return false;
}

#pragma mark- Firebase AdMob Interstitial

void MUSKFirebase::initInterstitialAd()
{
    CCLOG("initAdmob-cpp");
}

void MUSKFirebase::loadInterstitialAd(string adUnitId)
{
    
}

void MUSKFirebase::showInterstitialAd()
{
    
}

bool MUSKFirebase::isInterstitialAdsAvailable()
{
    return false;
}

#endif // (CC_TARGET_PLATFORM != CC_PLATFORM_IOS && CC_PLATFORM != CC_PLATFORM_ANDROID)

