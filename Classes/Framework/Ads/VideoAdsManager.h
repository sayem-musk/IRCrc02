//
//  VideoAdsManager.h
//  MUSK
//
//  Created by Tarek Saazeb on 6/12/16.
//
//

#ifndef VideoAdsManager_h
#define VideoAdsManager_h

#include "cocos2d.h"
#include "extensions/ExtensionExport.h"

USING_NS_CC;
using namespace std;

enum
{
    adKey_admob_25=201,
    adKey_admob_20=202,
    adKey_admob_15=203,
    adKey_admob_10=204,
    adKey_admob_05=205,
    adKey_admob_default=206,
};

class CC_EX_DLL VideoAdsDelegate
{
public:
    virtual void provideContentForViewAdd(string identifier);
};

class CC_EX_DLL BannerAdsDelegate
{
public:
    virtual void loadBannerAdsComplete(string identifier);
};


class VideoAdsManager : public Node
{
public:
    typedef enum {
        VA_None = 0,
        VA_AdMob = 1,
        VA_FaceBookAds = 3,
        VA_FaceBookAds_Interstitial = 4,
        VA_Admob_Interstitial = 5,
        VA_Admob_Banner = 6,
    } VideoAdsType;
    
    int runningAdType;

    VideoAdsDelegate *addDelegate;
    
    bool isInterconnected;
    
#pragma mark- Shared Manager
    static VideoAdsManager* sharedManager();

#pragma mark- Init Method
    ~VideoAdsManager();
    VideoAdsManager();
    static VideoAdsManager* create();
    virtual bool init();
    void removeFromParentAndCleanup(bool cleanup);
    
    void initializeAds();
    
    int adSearchIndex;
    void setRunningAdType();
    string getAdsUnitId();
    
    string strRunningAdsUnitId;
    
    void loadAds();
    void loadAds(int type,string strAdId);
    //void loadAds2();
    void adLoadComplete();
    void adLoadFailed();
    void restartAdLoad();
    void setRunningAdsType(VideoAdsManager::VideoAdsType adsType);
    
    bool isVideoAdsAvailable();
    void showVideoAds(VideoAdsDelegate *_addDelegate);
    
    void videoAdsShowCompleted();
    
#pragma mark- Add Response
    void loadRewardAdsComplete();
    void loadInterstitialComplete();
    void reward(const std::string &name, const std::string &currency, double amount);
    
    void setConnectedToInternet();
};

#endif /* VideoAdsManager_h */
