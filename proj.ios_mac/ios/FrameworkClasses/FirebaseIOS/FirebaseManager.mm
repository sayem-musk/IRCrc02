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

#import "FirebaseManager.h"
#import "cocos2d.h"
#import <sys/utsname.h>
#import "MUSKFirebaseManager.h"
#include "Config.h"
#include "VideoAdsManager.h"

static FirebaseManager *sharedInstance = nil;

@implementation FirebaseManager

#define AD_NAME "Rewarded"

#pragma mark Singleton Methods
+ (FirebaseManager*)sharedManager {
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

#pragma mark- Firebase Analytics
+(void)initFireAnalytics
{
    [FIRApp configure];
}

+(void)sendAnalyticsEvent:(NSString*)_eventName eventCategory:(NSString*)_eventCategory eventLabel:(NSString*)_eventLabel eventValue:(NSInteger)_eventValue
{
    NSDictionary *params = @{
                             @"event_category":_eventCategory,
                             @"event_label":_eventLabel,
                             @"event_value":[NSNumber numberWithInteger:_eventValue]
                             };
    [FIRAnalytics logEventWithName:_eventName parameters:params];
}

+(void)sendVirtualCurrencyEvent:(NSString*)_eventName itemName:(NSString*)_itemName currencyName:(NSString*)_currencyName value:(NSInteger)_value
{
    [FIRAnalytics logEventWithName:kFIREventSpendVirtualCurrency
                        parameters:@{
                                     kFIRParameterItemName: _itemName,
                                     kFIRParameterValue: [NSNumber numberWithInteger:_value],
                                     kFIRParameterVirtualCurrencyName: _currencyName
                                     }];
}

#pragma mark- Firebase Screen

+(void)setCurrentScreen:(NSString*)_screenName screenClass:(NSString*)_screenClass
{
    [FIRAnalytics setScreenName:_screenName screenClass:_screenClass];
}

#pragma mark- Firebase RemoteConfig
static FIRRemoteConfig *remoteConfig=NULL;

+(void)initRemoteConfig
{
    remoteConfig = [FIRRemoteConfig remoteConfig];
    //FIRRemoteConfigSettings *remoteConfigSettings = [[FIRRemoteConfigSettings alloc] initWithDeveloperModeEnabled:YES];
    FIRRemoteConfigSettings *remoteConfigSettings = [[FIRRemoteConfigSettings alloc] init];
    remoteConfigSettings.minimumFetchInterval = 0;
    remoteConfig.configSettings = remoteConfigSettings;
    [remoteConfig setDefaultsFromPlistFileName:@"RemoteConfigDefaults"];
    
    long expirationDuration = 3600;
    // If your app is using developer mode, expirationDuration is set to 0, so each fetch will
    // retrieve values from the Remote Config service.
    
    // [START fetch_config_with_callback]
    // TimeInterval is set to expirationDuration here, indicating the next fetch request will use
    // data fetched from the Remote Config service, rather than cached parameter values, if cached
    // parameter values are more than expirationDuration seconds old. See Best Practices in the
    // README for more information.
    [remoteConfig fetchWithExpirationDuration:expirationDuration completionHandler:^(FIRRemoteConfigFetchStatus status, NSError *error) {
        if (status == FIRRemoteConfigFetchStatusSuccess) {
            CCLOG("Config fetched!");
            [remoteConfig activateWithCompletionHandler:^(NSError *error){
                if (error) {
                    CCLOG("error occured to activate remote config error: %s", [error.localizedDescription UTF8String]);
                    MUSKFirebaseManager::sharedManager()->onRemoteFetchCompleted(false);
                }
                else {
                    MUSKFirebaseManager::sharedManager()->onRemoteFetchCompleted(true);
                }
            }];
        } else {
            CCLOG("Config not fetched");
            CCLOG("Error %s", [error.localizedDescription UTF8String]);
            MUSKFirebaseManager::sharedManager()->onRemoteFetchCompleted(false);
        }
    }];
    // [END fetch_config_with_callback]
}

+(NSString*)getRemoteConfigValue:(NSString*)key
{
    if (remoteConfig!=NULL)
    {
        return remoteConfig[key].stringValue;
    }
    return @"0";
}

#pragma mark- Firebase AdMob
+(void)initAdmob
{
    CCLOG("initAdmob-ios");
    [[GADMobileAds sharedInstance] startWithCompletionHandler:nil];
    [GADRewardBasedVideoAd sharedInstance].delegate = [FirebaseManager sharedManager];
}

+(void)loadRewardedVideoAd:(NSString*)adUnitId
{
    [[GADRewardBasedVideoAd sharedInstance] loadRequest:[GADRequest request] withAdUnitID:adUnitId];
}

+(void)showRewardedAd
{
    if ([[GADRewardBasedVideoAd sharedInstance] isReady]) {
        [[GADRewardBasedVideoAd sharedInstance] presentFromRootViewController:[UIApplication sharedApplication].keyWindow.rootViewController];
    }
}

+(bool)isAdsAvailable
{
    return [[GADRewardBasedVideoAd sharedInstance] isReady];
    //return false;
}

#pragma mark- Firebase AdMob Interstitial
-(void)initInterstitialAd
{
    //interstitial = [[GADInterstitial alloc] initWithAdUnitID:@"ca-app-pub-3940256099942544/4411468910"];
}

-(void)loadInterstitialAd:(NSString*)adUnitId
{
    if (interstitial != NULL) {
        interstitial = NULL;
    }
    interstitial = [[GADInterstitial alloc] initWithAdUnitID:adUnitId];
    interstitial.delegate = [FirebaseManager sharedManager];
    [interstitial loadRequest:[GADRequest request]];
}

-(void)showInterstitialAd
{
    if ([self isInterstitialAdsAvailable]) {
        [interstitial presentFromRootViewController:[UIApplication sharedApplication].keyWindow.rootViewController];
    } else {
        CCLOG("Ad wasn't ready");
    }
}

-(bool)isInterstitialAdsAvailable
{
    return interstitial != NULL && interstitial.isReady;
}

#pragma mark - GADRewardBasedVideoAdDelegate

- (void)rewardBasedVideoAd:(GADRewardBasedVideoAd *)rewardBasedVideoAd
   didRewardUserWithReward:(GADAdReward *)reward {
    NSString *rewardMessage = [NSString stringWithFormat:@"Reward received with currency %@ , amount %lf",reward.type,
                               [reward.amount doubleValue]];
    CCLOG("rewardMessage %s",[rewardMessage UTF8String]);
    MUSKFirebaseManager::sharedManager()->onFireAdMobRewarded(AD_NAME, std::string([reward.type UTF8String]), [reward.amount doubleValue]);
}

- (void)rewardBasedVideoAdDidReceiveAd:(GADRewardBasedVideoAd *)rewardBasedVideoAd {
    CCLOG("Reward based video ad is received.");
    MUSKFirebaseManager::sharedManager()->onFireAdmobRewardedVideoAdLoaded(AD_NAME);
}

- (void)rewardBasedVideoAdDidOpen:(GADRewardBasedVideoAd *)rewardBasedVideoAd {
    CCLOG("Opened reward based video ad.");
    MUSKFirebaseManager::sharedManager()->onFireAdmobRewardedVideoAdOpened(AD_NAME);
}

- (void)rewardBasedVideoAdDidStartPlaying:(GADRewardBasedVideoAd *)rewardBasedVideoAd {
    CCLOG("Reward based video ad started playing.");
    MUSKFirebaseManager::sharedManager()->onFireAdmobRewardedVideoStarted(AD_NAME);
}

- (void)rewardBasedVideoAdDidCompletePlaying:(GADRewardBasedVideoAd *)rewardBasedVideoAd {
    CCLOG("Reward based video ad has completed.");
    MUSKFirebaseManager::sharedManager()->onFireAdmobRewardedVideoCompleted(AD_NAME);
}

- (void)rewardBasedVideoAdDidClose:(GADRewardBasedVideoAd *)rewardBasedVideoAd {
    CCLOG("Reward based video ad is closed.");
    MUSKFirebaseManager::sharedManager()->onFireAdmobRewardedVideoAdClosed(AD_NAME);
    //MUSKFirebaseManager::sharedManager()->loadRewardedVideoAd(Config::sharedManager()->admob_adunit_id_low);
    
}

- (void)rewardBasedVideoAdWillLeaveApplication:(GADRewardBasedVideoAd *)rewardBasedVideoAd {
    CCLOG("Reward based video ad will leave application.");
    MUSKFirebaseManager::sharedManager()->onFireAdmobRewardedVideoAdLeftApplication(AD_NAME);
}

- (void)rewardBasedVideoAd:(GADRewardBasedVideoAd *)rewardBasedVideoAd
    didFailToLoadWithError:(NSError *)error {
    CCLOG("Reward based video ad failed to load.");
    MUSKFirebaseManager::sharedManager()->onFireAdmobRewardedVideoAdFailedToLoad(AD_NAME);
}

#pragma mark - GADInterstitialDelegate

/// Tells the delegate an ad request succeeded.
- (void)interstitialDidReceiveAd:(GADInterstitial *)ad {
    CCLOG("interstitialDidReceiveAd");
    MUSKFirebaseManager::sharedManager()->onFireAdmobRewardedVideoAdLoaded(AD_NAME);
}

/// Tells the delegate an ad request failed.
- (void)interstitial:(GADInterstitial *)ad didFailToReceiveAdWithError:(GADRequestError *)error {
    MUSKFirebaseManager::sharedManager()->onFireAdmobRewardedVideoAdFailedToLoad(AD_NAME);
}

/// Tells the delegate that an interstitial will be presented.
- (void)interstitialWillPresentScreen:(GADInterstitial *)ad {
    CCLOG("interstitialWillPresentScreen");
    double amount = 10;
    MUSKFirebaseManager::sharedManager()->onFireAdMobRewarded(AD_NAME, [@"gmes" UTF8String], amount);
}

/// Tells the delegate the interstitial is to be animated off the screen.
- (void)interstitialWillDismissScreen:(GADInterstitial *)ad {
    CCLOG("interstitialWillDismissScreen");
}

/// Tells the delegate the interstitial had been animated off the screen.
- (void)interstitialDidDismissScreen:(GADInterstitial *)ad {
    CCLOG("interstitialDidDismissScreen");
    MUSKFirebaseManager::sharedManager()->onFireAdmobRewardedVideoAdClosed(AD_NAME);
}

/// Tells the delegate that a user click will open another app
/// (such as the App Store), backgrounding the current app.
- (void)interstitialWillLeaveApplication:(GADInterstitial *)ad {
    CCLOG("interstitialWillLeaveApplication");
    MUSKFirebaseManager::sharedManager()->onFireAdmobRewardedVideoAdLeftApplication(AD_NAME);
}

@end
