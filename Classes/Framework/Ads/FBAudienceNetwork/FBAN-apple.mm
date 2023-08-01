
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

#import "FBAN.h"
#import <Foundation/Foundation.h>
#include "FBANManager.h"
#include "FBAudienceManager.h"

#pragma mark- FB Audience Network Interstitial Ad
void FBAN::initInterstitialAd(string placeMentID)
{
    [[FBAudienceManager sharedManager] initInterstitialAd:[NSString stringWithUTF8String:placeMentID.c_str()]];
}

void FBAN::loadInterstitialAd()
{
    [[FBAudienceManager sharedManager] loadInterstitialAd];
}

bool FBAN::isInterstitialAdLoaded()
{
    return [[FBAudienceManager sharedManager] isInterstitialAdLoaded];
    
}

void FBAN::showInterstitialAd()
{
    [[FBAudienceManager sharedManager] showInterstitialAd];
}

#pragma mark- FB Audience Network Interstitial Ad 2
void FBAN::initInterstitialAd2(string placeMentID)
{
    [[FBAudienceManager sharedManager] initInterstitialAd2:[NSString stringWithUTF8String:placeMentID.c_str()]];
}

void FBAN::loadInterstitialAd2()
{
    [[FBAudienceManager sharedManager] loadInterstitialAd2];
}

bool FBAN::isInterstitialAdLoaded2()
{
    return [[FBAudienceManager sharedManager] isInterstitialAdLoaded2];
    
}

void FBAN::showInterstitialAd2()
{
    [[FBAudienceManager sharedManager] showInterstitialAd2];
}

#pragma mark- FB Audience Network Rewarded Video
void FBAN::initRewardedAd()
{
    [[FBAudienceManager sharedManager] initRewardedAd];
}

void FBAN::loadRewardedAd(string placeMentID)
{
    [[FBAudienceManager sharedManager] loadRewardedAd:[NSString stringWithUTF8String:placeMentID.c_str()]];
}

bool FBAN::isRewardedAdLoaded()
{
    return [[FBAudienceManager sharedManager] isRewardedAdLoaded];
}

void FBAN::showRewardedAd()
{
    [[FBAudienceManager sharedManager] showRewardedAd];
}

#pragma mark- FB Audience Network Rewarded Video 2

void FBAN::initRewardedAd2()
{
    [[FBAudienceManager sharedManager] initRewardedAd2];
}

void FBAN::loadRewardedAd2(string placeMentID)
{
    [[FBAudienceManager sharedManager] loadRewardedAd2:[NSString stringWithUTF8String:placeMentID.c_str()]];
}

bool FBAN::isRewardedAdLoaded2()
{
    return [[FBAudienceManager sharedManager] isRewardedAdLoaded2];
}

void FBAN::showRewardedAd2()
{
    [[FBAudienceManager sharedManager] showRewardedAd2];
}

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

