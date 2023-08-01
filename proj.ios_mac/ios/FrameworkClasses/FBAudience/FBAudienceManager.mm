/****************************************************************************
 Copyright (c) 2010-2013 cocos2d-x.org
 Copyright (c) 2013-2017 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "FBAudienceManager.h"
#import "cocos2d.h"
#include "Config.h"
#include "FBANManager.h"

static FBAudienceManager *sharedInstance = nil;

@implementation FBAudienceManager

#define AD_NAME "Rewarded"

#pragma mark Singleton Methods
+ (FBAudienceManager*)sharedManager {
    if (sharedInstance == nil)
        sharedInstance = [[self alloc] init];
    
    return sharedInstance;
}

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
    }
    return self;
}

#pragma mark- Facebook Audience Network Interstitial

-(void)initInterstitialAd:(NSString*)placementID
{
    interstitialAd = [[FBInterstitialAd alloc] initWithPlacementID:placementID];
    interstitialAd.delegate = self;
    [self loadInterstitialAd];
}

-(void)loadInterstitialAd
{
    if (interstitialAd)
    {
        NSLog(@"loadFBAudienceAd if");
        [interstitialAd loadAd];
    }
    else
    {
        NSLog(@"loadFBAudienceAd else");
    }
}

-(void)showInterstitialAd
{
    if ([self isInterstitialAdLoaded])
    {
        [interstitialAd showAdFromRootViewController:[UIApplication sharedApplication].keyWindow.rootViewController];
    } else {
        NSLog(@"isFBAudienceAdAvailable not available");
    }
}

-(BOOL) isInterstitialAdLoaded
{
    return interstitialAd && interstitialAd.isAdValid;
}

#pragma mark- FBInterstitialAdDelegate

- (void)interstitialAdDidClick:(FBInterstitialAd *)interstitialAd
{
    NSLog(@"interstitialAdDidClick");
    FBANManager::sharedManager()->onAdClicked();
}

- (void)interstitialAdDidClose:(FBInterstitialAd *)interstitialAd
{
    NSLog(@"interstitialAdDidClose %@ %@", [interstitialAd placementID], [NSString stringWithUTF8String:Config::sharedManager()->fb_2_interstitial_id_01.c_str()]);
    if ([[interstitialAd placementID] isEqualToString:[NSString stringWithUTF8String:Config::sharedManager()->fb_2_interstitial_id_01.c_str()]]) {
        FBANManager::sharedManager()->onInterstitialDismissed();
        [self initInterstitialAd2:[NSString stringWithUTF8String:Config::sharedManager()->fb_2_interstitial_id_01.c_str()]];
    }
    else {
        FBANManager::sharedManager()->onRewardedVideoClosed(AD_NAME);
        [self initInterstitialAd:[NSString stringWithUTF8String:Config::sharedManager()->fb_placement_id.c_str()]];
    }
}

- (void)interstitialAdWillClose:(FBInterstitialAd *)interstitialAd
{
    NSLog(@"interstitialAdWillClose");
}

- (void)interstitialAdDidLoad:(FBInterstitialAd *)interstitialAd
{
    NSLog(@"interstitialAdDidLoad");
    if ([[interstitialAd placementID] isEqualToString:[NSString stringWithUTF8String:Config::sharedManager()->fb_2_interstitial_id_01.c_str()]]) {
        FBANManager::sharedManager()->onAdLoaded();
        FBANManager::sharedManager()->onInterstitialLoad(true, 0);
    }
    else {
        FBANManager::sharedManager()->onRewardedAdLoaded(AD_NAME);
    }
}

- (void)interstitialAd:(FBInterstitialAd *)interstitialAd didFailWithError:(NSError *)error
{
    NSLog(@"interstitialAd error: %ld msg: %@",(long)error.code,error);
    if ([[interstitialAd placementID] isEqualToString:[NSString stringWithUTF8String:Config::sharedManager()->fb_2_interstitial_id_01.c_str()]]) {
        FBANManager::sharedManager()->onError();
        FBANManager::sharedManager()->onInterstitialLoad(false, (int)error.code);
    }
    else {
        FBANManager::sharedManager()->onRewardedError(AD_NAME, "error occured");
    }
}

- (void)interstitialAdWillLogImpression:(FBInterstitialAd *)interstitialAd
{
    NSLog(@"interstitialAdWillLogImpression");
    if ([[interstitialAd placementID] isEqualToString:[NSString stringWithUTF8String:Config::sharedManager()->fb_2_interstitial_id_01.c_str()]]) {
        FBANManager::sharedManager()->onLoggingImpression();
    }
    else {
        
    }
}

#pragma mark- FB Audience Network Rewarded Video
-(void)initRewardedAd
{
    
}

-(void)loadRewardedAd:(NSString*)placementID
{
    NSLog(@"loadRewardedAd: %@",placementID);
    if (rewardedVideoAd)
    {
        rewardedVideoAd = NULL;
    }
    rewardedVideoAd = [[FBRewardedVideoAd alloc] initWithPlacementID:placementID];
    rewardedVideoAd.delegate = self;
    [rewardedVideoAd loadAd];
}

-(BOOL)isRewardedAdLoaded
{
    return rewardedVideoAd && rewardedVideoAd.isAdValid;
}

-(void)showRewardedAd
{
    if ([self isRewardedAdLoaded]) {
        [rewardedVideoAd showAdFromRootViewController:[UIApplication sharedApplication].keyWindow.rootViewController];
    }
}

#pragma mark- FB Audience Network Rewarded Video 2
-(void)initRewardedAd2
{
    
}

-(void)loadRewardedAd2:(NSString*)placementID
{
    NSLog(@"loadRewardedAd2: %@",placementID);
    if (rewardedVideoAd2)
    {
        rewardedVideoAd2 = NULL;
    }
    rewardedVideoAd2 = [[FBRewardedVideoAd alloc] initWithPlacementID:placementID];
    rewardedVideoAd2.delegate = self;
    [rewardedVideoAd2 loadAd];
}

-(BOOL)isRewardedAdLoaded2
{
    return rewardedVideoAd2 && rewardedVideoAd2.isAdValid;
}

-(void)showRewardedAd2
{
    if ([self isRewardedAdLoaded2]) {
        [rewardedVideoAd2 showAdFromRootViewController:[UIApplication sharedApplication].keyWindow.rootViewController];
    }
}

#pragma mark- FB Audience Network Rewarded Video Listener
- (void)rewardedVideoAd:(FBRewardedVideoAd *)rewardedVideoAd didFailWithError:(NSError *)error
{
    NSLog(@"Rewarded video ad failed to load: %@", error);
    if ([[rewardedVideoAd placementID] isEqualToString:[NSString stringWithUTF8String:Config::sharedManager()->fb_2_placement_id_01.c_str()]]) {
        
    }
    else {
        FBANManager::sharedManager()->onRewardedError(AD_NAME, "error occured");
    }
}

- (void)rewardedVideoAdDidLoad:(FBRewardedVideoAd *)rewardedVideoAd
{
    NSLog(@"Rewarded video ad is loaded and ready to be displayed");
    FBANManager::sharedManager()->onRewardedAdLoaded(AD_NAME);
}

- (void)rewardedVideoAdDidClick:(FBRewardedVideoAd *)rewardedVideoAd
{
    NSLog(@"Video ad clicked");
    FBANManager::sharedManager()->onRewardedAdClicked(AD_NAME);
}

- (void)rewardedVideoAdVideoComplete:(FBRewardedVideoAd *)rewardedVideoAd;
{
    NSLog(@"Rewarded Video ad video complete - this is called after a full video view, before the ad end card is shown. You can use this event to initialize your reward");
    FBANManager::sharedManager()->onRewardedVideoCompleted(10,AD_NAME);
}

- (void)rewardedVideoAdDidClose:(FBRewardedVideoAd *)rewardedVideoAd
{
    NSLog(@"Rewarded Video ad closed - this can be triggered by closing the application, or closing the video end card");
    FBANManager::sharedManager()->onRewardedVideoClosed(AD_NAME);
}

@end
