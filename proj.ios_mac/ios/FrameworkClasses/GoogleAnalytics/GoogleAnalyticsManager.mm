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

#import "GoogleAnalyticsManager.h"
#import "cocos2d.h"
#include "Config.h"
#import "GAIDictionaryBuilder.h"
#import "GAIFields.h"

static GoogleAnalyticsManager *sharedInstance = nil;

@implementation GoogleAnalyticsManager

#pragma mark Singleton Methods
+ (GoogleAnalyticsManager*)sharedManager {
    if (sharedInstance == nil)
        sharedInstance = [[self alloc] init];

    return sharedInstance;
}

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
        gAnalytics = [GAI sharedInstance];
        gTracker = [GAI sharedInstance].defaultTracker;
    }
    return self;
}

#pragma mark- Firebase Analytics
-(void)initGoogleAnalytics
{
    //GAI *gai = [GAI sharedInstance];
    [gAnalytics trackerWithTrackingId:[NSString stringWithUTF8String:Config::sharedManager()->google_analytics_key.c_str()]];
    
    // Optional: automatically report uncaught exceptions.
    gAnalytics.trackUncaughtExceptions = YES;
    
    // Optional: set Logger to VERBOSE for debug information.
    // Remove before app release.
    gAnalytics.logger.logLevel = kGAILogLevelVerbose;
}

-(void)sendGoogleAnalyticsEvent:(NSString*)_eventName eventCategory:(NSString*)_eventCategory eventLabel:(NSString*)_eventLabel eventValue:(NSInteger)_eventValue
{
    
    [gTracker send:[[GAIDictionaryBuilder createEventWithCategory:_eventCategory
                                                          action:_eventName
                                                           label:_eventLabel
                                                           value:[NSNumber numberWithInteger:_eventValue]] build]];
}

@end
