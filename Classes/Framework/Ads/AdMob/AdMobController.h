//
//  adMobController.h
//  MUSK
//
//  Created by Tarek Saazeb on 6/12/16.
//
//

#ifndef adMobController_h
#define adMobController_h

#include <stdio.h>
#include "cocos2d.h"
#include "../../../Framework/Ads/VideoAdsManager.h"

USING_NS_CC;
using namespace std;

class AdMobController : public Node
{
public:
    
    static AdMobController* sharedManager();
    
#pragma mark- Init Method
    AdMobController();
    ~AdMobController();
    static AdMobController* create();
    virtual bool init();
    
    void initAdmob();
    
    void waitToRequestAnotherAd(float dt);
    
#pragma mark- Custom
    static bool isAdsAvailable();
    static void loadRewardAds();
    void showRewardAds();
    
    static void loadInterstitialAds();
    static void showInterstitialAds();
    void loadAds(string strAbMobId);
    
#pragma mark- Listener
    void onRewardedVideoLoaded(bool isPrecache);
    void onRewardedVideoFailedToLoad();
    void onRewardedVideoShown();
    void onRewardedVideoFinished(double amount, string name);
    void onRewardedVideoClosed(bool finished);
    void onRewardedVideoExpired();
};

#endif /* adMobController_h */
