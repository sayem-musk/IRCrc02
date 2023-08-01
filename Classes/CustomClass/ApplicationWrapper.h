//
//  ApplicationWrapper.h
//
//
//  Created by  on 3/3/18.
//
//

#ifndef ApplicationWrapper_h
#define ApplicationWrapper_h

#include "platform/CCPlatformMacros.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class ApplicationWrapper
{
public:
    static ApplicationWrapper* sharedManager();
    
#pragma mark- Init Method
    ~ApplicationWrapper();
    ApplicationWrapper();
    static ApplicationWrapper* create();
    virtual bool init();

#pragma mark- ApplicationWrpper
    string getBundleId();
    string getDeviceUDID();
    string getDeviceOSVersion();
    string getDeviceName();
    
    void setUserIdentifier(string _userIdentifier);
    void setUserEmail(string _userEmail);
    void setUserName(string _userName);
    void setString(string _key, string _value);
    void showPopUpRate();
    void openUrl(string url);
    
    bool isConnectedToInternet();
};


#endif /* ApplicationWrapper_h */
