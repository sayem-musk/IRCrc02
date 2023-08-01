//
//  ApplicationWrapper.cpp
//
//
//  Created by  on 3/3/18.
//
//

#include "ApplicationWrapper.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS && CC_TARGET_PLATFORM != CC_PLATFORM_MAC && CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)

#pragma mark- Shared Manager

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
    CCLOG("ApplicationWrapper-windows");
    return "windows";
}

strin ApplicationWrapper::getDeviceUDID()
{
    CCLOG("ApplicationWrapper-windows-getDeviceUDID");
    return "windows";
}

string ApplicationWrapper::getDeviceOSVersion()
{
    CCLOG("ApplicationWrapper-windows-getDeviceOSVersion");
    return "windows";
}

string ApplicationWrapper::getDeviceName()
{
    CCLOG("ApplicationWrapper-windows-getDeviceName");
    return "windows";
}

void ApplicationWrapper::setUserIdentifier(string _userIdentifier)
{
    CCLOG("ApplicationWrapper-windows-setUserIdentifier");
}

void ApplicationWrapper::setUserEmail(string _userEmail)
{
    CCLOG("ApplicationWrapper-windows-setUserEmail");
}

void ApplicationWrapper::setUserName(string _userName)
{
    CCLOG("ApplicationWrapper-windows-setUserName");
}

void ApplicationWrapper::setString(string _key, string _value)
{
    CCLOG("ApplicationWrapper-windows-setString");
}

bool ApplicationWrapper::isConnectedToInternet()
{
    return true;
}


#pragma mark- Rating

void ApplicationWrapper::showPopUpRate()
{
    
}

void ApplicationWrapper::openUrl(string url)
{

}

#endif // (CC_TARGET_PLATFORM != CC_PLATFORM_IOS && CC_PLATFORM != CC_PLATFORM_ANDROID)

