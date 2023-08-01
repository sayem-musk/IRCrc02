//
//  OfflineEarning.h
//  IRC-mobile
//
//  Created by Tarek Saazeb on 5/9/20.
//

#ifndef OfflineEarning_h
#define OfflineEarning_h

#include "../StoreLayer/StorePanel.h"
#include "../Framework/Ads/VideoAdsManager.h"

USING_NS_CC;

class OfflineEarning : public StorePanel, public VideoAdsDelegate
{
public:
    static OfflineEarning* sharedManager();
    
#pragma mark- Init Method
    ~OfflineEarning();
    OfflineEarning();
    static OfflineEarning* create();
    virtual bool init();
    void removeFromParentAndCleanup(bool cleanup);
    
#pragma mark- Total Earning
    vector<string> *totalEarning;
    Label *lblCoins;
    
    void getTotalOfflineEarning();
    void loadTotalCoin();
    void acceptCallBack(cocos2d::Ref *pSender);
    void acceptReward();
    
    virtual void provideContentForViewAdd(string identifier);
    
};

#endif /* OfflineEarning_h */
