//
//  AdsAnimation.h
//  IRC-mobile
//
//  Created by Tarek Saazeb on 7/4/20.
//

#ifndef AdsAnimation_h
#define AdsAnimation_h

#include "../StoreLayer/StorePanel.h"
#include "../Framework/Ads/VideoAdsManager.h"

USING_NS_CC;

enum
{
    adsTypeCoinsDouble=1,
    adsTypeCoins=2,
    adsTypeGems=3,
};

static int TimeGap=2*60;

static string strCoinsDoubleFor5Min="CoinsDoubleFor5Min";
static int CoinsDoubleFor5Min=5*60;

static string strCoinsRewardTime="CoinsRewardTime";
static int CoinsRewardTime=5;

class AdsAnimation : public StorePanel,public VideoAdsDelegate,public AlertViewDelegate
{
public:
    static AdsAnimation* sharedManager();
    
    int currentAdsType;
    
#pragma mark- Init Method
    ~AdsAnimation();
    AdsAnimation();
    static AdsAnimation* create();
    virtual bool init();
    void removeFromParentAndCleanup(bool cleanup);
    
#pragma mark- Ads Animation
    void loadAds(float dt);
    void loadAdsAnimation();
    void removeAdsAnimation();
    
#pragma mark- Coins Double Animation
    Node *nodeCoinsDoubleFor5Min;
    
    void loadCoinsDoubleFor5Min();
    void coinsDoubleFor5MinCallback(cocos2d::Ref *pSender);
    void giveCoinsDoubleFor5MinReward();
    
#pragma mark- Coins Animation
    vector<string> *arrCoinsReward;
    Node *nodeCoinsAnimation;
    
    void loadCoinsNode();
    void coinsCallback(cocos2d::Ref *pSender);
    void coinsCallbackFinal();
    void loadCoinsNodeAnimation();
    void giveCoinsReward();
    vector<string> *getCoinsValue();
    void setCoinsValue();
    
#pragma mark- Provide Content
    virtual void provideContentForViewAdd(string identifier);
    
#pragma mark- AlertView
    void alertViewCallBack(int tag,int buttonIndex);
};

#endif /* AdsAnimation_h */
