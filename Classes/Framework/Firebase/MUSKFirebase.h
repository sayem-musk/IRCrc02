//
//  MUSKFirebase.h
//  MUSK-mobile
//
//  Created by Tarek Saazeb on 5/25/18.
//

#ifndef MUSKFirebase_h
#define MUSKFirebase_h

#include "platform/CCPlatformMacros.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class MUSKFirebase
{
public:

#pragma mark- Firebase Analytics
    static void initFireAnalytics();
    static void sendAnalyticsEvent(string _eventName, string _eventCategory, string _eventLabel, int _eventValue);
    static void sendVirtualCurrencyEvent(string _eventName, string _itemName, string _currencyName, int _value);
    
#pragma mark- Google Analytics
    static void initGoogleAnalytics();
    static void sendGoogleAnalyticsEvent(string _eventName, string _eventCategory, string _eventLabel, int _eventValue);
    
#pragma mark- Firebase Screen
    static void setCurrentScreen(string _screenName, string _screenClass);
    
#pragma mark- Firebase RemoteConfig
    static void initRemoteConfig();
    static string getRemoteConfigValue(string key);
    
#pragma mark- Firebase AdMob
    static void initAdmob();
    static void loadRewardedVideoAd(string adUnitId);
    static void showRewardedAd();
    static bool isAdsAvailable();
    
#pragma mark- Firebase AdMob Interstitial
    static void initInterstitialAd();
    static void loadInterstitialAd(string adUnitId);
    static void showInterstitialAd();
    static bool isInterstitialAdsAvailable();
};


#endif /* MUSKFirebase_h */
