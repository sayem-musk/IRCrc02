

#ifndef FBANManager_h
#define FBANManager_h

#include <stdio.h>
#include <string>
#include <vector>

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "extensions/ExtensionExport.h"

USING_NS_CC;

using namespace std;
using namespace cocos2d;
using namespace StringUtils;

enum
{
    facebook_adsystem2type_interstitial = 1,
    facebook_adsystem2type_rewarded = 2
};

class CC_EX_DLL FBANDelegate
{
public:
    virtual void provideContentForFBAN(string identifier);
    virtual void adsLoadingResponseForFBAN(bool isLoaded, int errorCode);
};

class FBANManager: public Node
{
    public:
    
    FBANDelegate *addDelegate;
    FBANDelegate *adsLoadingDelegate;
    
    int adsystem;
    int adsystem2_adtype;
    
#pragma mark- Init Method
    ~FBANManager();
    FBANManager();
    static FBANManager* create();
    virtual bool init();

    static FBANManager* sharedManager();
    
#pragma mark- FB Audience Network Listener
    void onInterstitialDisplayed();
    void onInterstitialDismissed();
    void onError();
    void onAdLoaded();
    void onAdClicked();
    void onLoggingImpression();
    void onInterstitialLoad(bool isLoaded, int errorCode);
    
#pragma mark- FB Audience Network Rewarded Video Listener
    void onRewardedError(string name, string msg);
    void onRewardedAdLoaded(string name);
    void onRewardedAdClicked(string name);
    void onRewardedLoggingImpression(string name);
    void onRewardedVideoCompleted(double amount, string name);
    void onRewardedVideoClosed(string name);
};

#endif /* FBANManager_h */
