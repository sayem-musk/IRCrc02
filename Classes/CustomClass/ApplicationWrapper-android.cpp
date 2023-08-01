//
//  ApplicationWrapper-android
//
//
//  Created by  on 3/3/18.
//
//

#include "ApplicationWrapper.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"

static const string helperClassName = "org/cocos2dx/cpp/ApplicationManager";

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
    CCLOG("ApplicationWrapper-android-getBundleId");
    return JniHelper::callStaticStringMethod(helperClassName, "getApplicationPackageName");
}

string ApplicationWrapper::getDeviceUDID()
{
    CCLOG("ApplicationWrapper-android-getDeviceUDID");
    return JniHelper::callStaticStringMethod(helperClassName, "getDeviceUDID");
}

string ApplicationWrapper::getDeviceOSVersion()
{
    CCLOG("ApplicationWrapper-android-getDeviceOSVersion");
    return JniHelper::callStaticStringMethod(helperClassName, "getDeviceOSVersion");
}

string ApplicationWrapper::getDeviceName()
{
    CCLOG("ApplicationWrapper-android-getDeviceName");
    return JniHelper::callStaticStringMethod(helperClassName, "getDeviceName");
}

void ApplicationWrapper::setUserIdentifier(string _userIdentifier)
{
    CCLOG("ApplicationWrapper-android-setUserIdentifier");
    JniHelper::callStaticVoidMethod(helperClassName, "setUserIdentifier",_userIdentifier);
}
void ApplicationWrapper::setUserEmail(string _userEmail)
{
    CCLOG("ApplicationWrapper-android-setUserEmail");
    JniHelper::callStaticVoidMethod(helperClassName, "setUserEmail",_userEmail);
}

void ApplicationWrapper::setUserName(string _userName)
{
    CCLOG("ApplicationWrapper-android-setUserName");
    JniHelper::callStaticVoidMethod(helperClassName, "setUserName",_userName);
}
void ApplicationWrapper::setString(string _key, string _value)
{
    CCLOG("ApplicationWrapper-android-setString");
    JniHelper::callStaticVoidMethod(helperClassName, "setString",_key,_value);
}

bool ApplicationWrapper::isConnectedToInternet()
{
    return JniHelper::callStaticBooleanMethod(helperClassName, "isConnectedToInternet");
}

#pragma mark- Rating

void ApplicationWrapper::showPopUpRate()
{
    
}

void ApplicationWrapper::openUrl(string url)
{
    
}

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
