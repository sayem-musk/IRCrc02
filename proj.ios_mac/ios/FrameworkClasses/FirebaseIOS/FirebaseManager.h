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

#import <UIKit/UIKit.h>
#import "Firebase.h"

@interface FirebaseManager : UIViewController <GADRewardBasedVideoAdDelegate, GADInterstitialDelegate>
{
    GADInterstitial *interstitial;
}
+(FirebaseManager*)sharedManager;

#pragma mark- Firebase Analytics
+(void)initFireAnalytics;
+(void)sendAnalyticsEvent:(NSString*)_eventName eventCategory:(NSString*)_eventCategory eventLabel:(NSString*)_eventLabel eventValue:(NSInteger)_eventValue;
+(void)sendVirtualCurrencyEvent:(NSString*)_eventName itemName:(NSString*)_itemName currencyName:(NSString*)_currencyName value:(NSInteger)_value;

#pragma mark- Firebase Screen
+(void)setCurrentScreen:(NSString*)_screenName screenClass:(NSString*)_screenClass;

#pragma mark- Firebase RemoteConfig
+(void)initRemoteConfig;
+(NSString*)getRemoteConfigValue:(NSString*)key;

#pragma mark- Firebase AdMob
+(void)initAdmob;
+(void)loadRewardedVideoAd:(NSString*)adUnitId;
+(void)showRewardedAd;
+(bool)isAdsAvailable;

#pragma mark- Firebase AdMob Interstitial
-(void)initInterstitialAd;
-(void)loadInterstitialAd:(NSString*)adUnitId;
-(void)showInterstitialAd;
-(bool)isInterstitialAdsAvailable;

@end

