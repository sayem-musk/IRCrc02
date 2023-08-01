//
//  LevelUpPanel.hpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 6/2/20.
//

#ifndef LevelUpPanel_h
#define LevelUpPanel_h

#include "../StoreLayer/StorePanel.h"
#include "../Framework/Ads/VideoAdsManager.h"

USING_NS_CC;

class LevelUpPanel : public StorePanel, public VideoAdsDelegate
{
public:
#pragma mark- Init Method
    ~LevelUpPanel();
    LevelUpPanel();
    static LevelUpPanel* create();
    virtual bool init();
    void removeFromParentAndCleanup(bool cleanup);
    
    
#pragma mark- Total Earning
    vector<string> *totalEarning;
    Label *lblCoins;
    
    void loadTotalCoin();
    void acceptCallBack(cocos2d::Ref *pSender);
    void acceptReward();
    virtual void provideContentForViewAdd(string identifier);
};

#endif /* LevelUpPanel_h */

