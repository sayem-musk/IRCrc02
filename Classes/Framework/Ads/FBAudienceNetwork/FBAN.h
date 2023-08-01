

#ifndef FBAN_h
#define FBAN_h

#include "platform/CCPlatformMacros.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class FBAN
{
public:
#pragma mark- FB Audience Network Interstitial Ad
    static void initInterstitialAd(string placeMentID);
    static void loadInterstitialAd();
    static bool isInterstitialAdLoaded();
    static void showInterstitialAd();
    
#pragma mark- FB Audience Network Interstitial Ad
    static void initInterstitialAd2(string placeMentID);
    static void loadInterstitialAd2();
    static bool isInterstitialAdLoaded2();
    static void showInterstitialAd2();
    
#pragma mark- FB Audience Network Rewarded Video
    static void initRewardedAd();
    static void loadRewardedAd(string placeMentID);
    static bool isRewardedAdLoaded();
    static void showRewardedAd();
    
#pragma mark- FB Audience Network Rewarded Video 2
    static void initRewardedAd2();
    static void loadRewardedAd2(string placeMentID);
    static bool isRewardedAdLoaded2();
    static void showRewardedAd2();
    
};


#endif /* FBAN_h */
