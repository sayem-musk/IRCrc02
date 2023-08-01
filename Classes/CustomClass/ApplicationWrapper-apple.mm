//
//  ApplicationWrapper-apple
//
//
//  Created by  on 3/3/18.
//
//

#import "ApplicationWrapper.h"
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <StoreKit/StoreKit.h>
#import "Reachability.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

static ApplicationWrapper *sharedInstance=NULL;

ApplicationWrapper* ApplicationWrapper::sharedManager()
{
    if(sharedInstance==NULL)
    {
        sharedInstance=ApplicationWrapper::create();
    }
    return sharedInstance;
}

#pragma mark- Init Method

ApplicationWrapper::~ApplicationWrapper()
{
    
}

ApplicationWrapper::ApplicationWrapper()
{
    
}

ApplicationWrapper* ApplicationWrapper::create()
{
    ApplicationWrapper* ret = new ApplicationWrapper();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool ApplicationWrapper::init()
{
    return true;
}

#pragma mark- ApplicationWrpper
string ApplicationWrapper::getBundleId()
{
    //CCLOG("ApplicationWrapper-ios");
    return [[[NSBundle mainBundle] bundleIdentifier] UTF8String];
}

string ApplicationWrapper::getDeviceUDID()
{
    //CCLOG("ApplicationWrapper-ios-getDeviceUDID");
    return "0";
}

string ApplicationWrapper::getDeviceOSVersion()
{
    //CCLOG("ApplicationWrapper-ios-getDeviceOSVersion");
    
    NSString *foo = [[UIDevice currentDevice] systemVersion];
    std::string deviceOS = std::string([foo UTF8String]);
    
    return deviceOS;
}

string ApplicationWrapper::getDeviceName()
{
    //CCLOG("ApplicationWrapper-ios-getDeviceName");
    return "0";
}

void ApplicationWrapper::setUserIdentifier(string _userIdentifier)
{
    //CCLOG("ApplicationWrapper-ios-setUserIdentifier");
    //return JniHelper::callStaticStringMethod(helperClassName, "setUserIdentifier", _userIdentifier);
}

void ApplicationWrapper::setUserEmail(string _userEmail)
{
    //CCLOG("ApplicationWrapper-ios-setUserEmail");
    //return JniHelper::callStaticStringMethod(helperClassName, "setUserEmail", _userEmail);
}

void ApplicationWrapper::setUserName(string _userName)
{
    //CCLOG("ApplicationWrapper-ios-setUserName");
    //return JniHelper::callStaticStringMethod(helperClassName, "setUserName", _userName);
}

void ApplicationWrapper::setString(string _key, string _value)
{
    //CCLOG("ApplicationWrapper-ios-setString");
    //return JniHelper::callStaticStringMethod(helperClassName, "setString", _key, _value);
}

bool ApplicationWrapper::isConnectedToInternet()
{
    //return true;
    Reachability *reachability = [Reachability reachabilityForInternetConnection];
    NetworkStatus netStatus = [reachability currentReachabilityStatus];
    return !(netStatus == NotReachable);
}

#pragma mark- Rating

void ApplicationWrapper::showPopUpRate()
{
    [SKStoreReviewController requestReview];
}

void ApplicationWrapper::openUrl(string url)
{
    //[[UIApplication sharedApplication] openURL:url];
}


#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

