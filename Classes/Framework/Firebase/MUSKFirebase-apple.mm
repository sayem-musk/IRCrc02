//
//  MUSKFirebase.m
//  MUSK-mobile
//
//  Created by Tarek Saazeb on 5/25/18.
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

#import "MUSKFirebase.h"
#import <Foundation/Foundation.h>
#include "FirebaseManager.h"
#include "MUSKFirebaseManager.h"
#include "Config.h"
#include "FBAudienceManager.h"
#include "GoogleAnalyticsManager.h"

#pragma mark- Firebase Analytics
void MUSKFirebase::initFireAnalytics()
{
    [FirebaseManager initFireAnalytics];
}

void MUSKFirebase::sendAnalyticsEvent(string _eventName, string _eventCategory, string _eventLabel, int _eventValue)
{
    [FirebaseManager sendAnalyticsEvent:[NSString stringWithUTF8String:_eventName.c_str()] eventCategory:[NSString stringWithUTF8String:_eventCategory.c_str()] eventLabel:[NSString stringWithUTF8String:_eventLabel.c_str()] eventValue:_eventValue];
}

void MUSKFirebase::sendVirtualCurrencyEvent(string _eventName, string _itemName, string _currencyName, int _value)
{
    [FirebaseManager sendVirtualCurrencyEvent:[NSString stringWithUTF8String:_eventName.c_str()] itemName:[NSString stringWithUTF8String:_itemName.c_str()] currencyName:[NSString stringWithUTF8String:_currencyName.c_str()] value:_value];
}

#pragma mark- Firebase Screen

void MUSKFirebase::setCurrentScreen(string _screenName, string _screenClass)
{
    [FirebaseManager setCurrentScreen:[NSString stringWithUTF8String:_screenName.c_str()] screenClass:[NSString stringWithUTF8String:_screenClass.c_str()]];
}

#pragma mark- Google Analytics
void MUSKFirebase::initGoogleAnalytics()
{
    [[GoogleAnalyticsManager sharedManager] initGoogleAnalytics];
}

void MUSKFirebase::sendGoogleAnalyticsEvent(string _eventName, string _eventCategory, string _eventLabel, int _eventValue)
{
    [[GoogleAnalyticsManager sharedManager] sendGoogleAnalyticsEvent:[NSString stringWithUTF8String:_eventName.c_str()] eventCategory:[NSString stringWithUTF8String:_eventCategory.c_str()] eventLabel:[NSString stringWithUTF8String:_eventLabel.c_str()] eventValue:_eventValue];
}

#pragma mark- Firebase RemoteConfig
void MUSKFirebase::initRemoteConfig()
{
    [FirebaseManager initRemoteConfig];
}

string MUSKFirebase::getRemoteConfigValue(string key)
{
    NSString *configValue = [FirebaseManager getRemoteConfigValue:[NSString stringWithUTF8String:key.c_str()]];
    return std::string([configValue UTF8String]);
}

#pragma mark- Firebase AdMob
void MUSKFirebase::initAdmob()
{
    dispatch_async(dispatch_get_main_queue(), ^{
        [FirebaseManager initAdmob];
    });
}

void MUSKFirebase::loadRewardedVideoAd(string adUnitId)
{
    [FirebaseManager loadRewardedVideoAd:[NSString stringWithUTF8String:adUnitId.c_str()]];
}

void MUSKFirebase::showRewardedAd()
{
    [FirebaseManager showRewardedAd];
}

bool MUSKFirebase::isAdsAvailable()
{
    return [FirebaseManager isAdsAvailable];
}

#pragma mark- Firebase AdMob Interstitial

void MUSKFirebase::initInterstitialAd()
{
    CCLOG("initAdmob-cpp");
    [[FirebaseManager sharedManager] initInterstitialAd];
}

void MUSKFirebase::loadInterstitialAd(string adUnitId)
{
    [[FirebaseManager sharedManager] loadInterstitialAd:[NSString stringWithUTF8String:adUnitId.c_str()]];
}

void MUSKFirebase::showInterstitialAd()
{
    [[FirebaseManager sharedManager] showInterstitialAd];
}

bool MUSKFirebase::isInterstitialAdsAvailable()
{
    return [[FirebaseManager sharedManager] isInterstitialAdsAvailable];
}

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

