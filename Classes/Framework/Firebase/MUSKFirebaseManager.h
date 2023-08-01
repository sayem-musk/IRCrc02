//
//  MUSKFirebaseManager.h
//  MUSK-mobile
//
//  Created by Tarek Saazeb on 5/25/18.
//

#ifndef MUSKFirebaseManager_h
#define MUSKFirebaseManager_h

#include <stdio.h>
#include <string>
#include <vector>

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "extensions/ExtensionExport.h"

USING_NS_CC;

using namespace std;
using namespace cocos2d;
using namespace StringUtils;

enum
{
    FIRMessagingType_Gems = 1,
    FIRMessagingType_Product = 2,
};

class CC_EX_DLL Ad3Delegate
{
public:
    virtual void onInterstitial3AdClosed(string name);
};

class MUSKFirebaseManager
{
    public:
    Ad3Delegate *ad3Delegate;
#pragma mark- Init Method
    ~MUSKFirebaseManager();
    MUSKFirebaseManager();
    static MUSKFirebaseManager* create();
    virtual bool init();
    
    static MUSKFirebaseManager* sharedManager();
    
    vector<int> *adSearchOrder;
    int selectedAd = 0;
    
#pragma mark- Firebase Analytics
    void sendAnalyticsEvent(string _eventName, string _eventCategory, string _eventLabel, int _eventValue);
    void sendVirtualCurrencyEvent(string _eventName, string _itemName, string _currencyName, int _value);

#pragma mark- Firebase Screen
    void setCurrentScreen(string _screenName, string _screenClass);
    
#pragma mark- Firebase RemoteConfig
    string getRemoteConfigValue(string key);
    
#pragma mark- Firebase RemoteConfig Listener
    void onRemoteFetchCompleted(bool isSuccess);
    
#pragma mark- Firebase AdMob
    void loadRewardedVideoAd(string adUnitId);
    void showRewardedAd();
    bool isAdsAvailable();
    
#pragma mark- Firebase AdMob Interstitial
    void loadInterstitialAd(string adUnitId);
    void showInterstitialAd();
    bool isInterstitialAdsAvailable();
    
#pragma mark- Firebase Admob Listener
    void onFireAdMobRewarded(string name, string type, double amount);
    void onFireAdmobRewardedVideoAdLeftApplication(string name);
    void onFireAdmobRewardedVideoAdClosed(string name);
    void onFireAdmobRewardedVideoAdFailedToLoad(string name);
    void onFireAdmobRewardedVideoAdLoaded(string name);
    void onFireAdmobRewardedVideoAdOpened(string name);
    void onFireAdmobRewardedVideoStarted(string name);
    void onFireAdmobRewardedVideoCompleted(string name);

#pragma mark- Firebase In App Messaging
    void onFirebaseInAppMessagingParamsReceived(string params);
    
#pragma mark- Firebase Messaging
    int firMessagingRewardValue;
    int firMessagingType;
    bool isFIREMessagingReceived;
    bool gameLoaded;
    void onFirebaseMessagingParamsReceived(string params);
    void onFirebaseMessagingRewardCollected();
};

#endif /* MUSKFirebaseManager_h */
