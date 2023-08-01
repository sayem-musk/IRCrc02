//
//  GameHud.hpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 3/14/20.
//

#ifndef GameHud_h
#define GameHud_h

#include "cocos2d.h"
#include "../Framework/Ads/VideoAdsManager.h"

USING_NS_CC;

class GameHud : public Node, public VideoAdsDelegate
{
public:
#pragma mark- Init Method
    ~GameHud();
    GameHud();
    static GameHud* create();
    virtual bool init();
    void removeFromParentAndCleanup(bool cleanup);
    
    void loadStorePanel(int panelId);
    
#pragma mark- Lower Buttons
    Menu *menuLowerButton;
    ProgressTimer *chairBarNode;
    
    void loadLowerButtons();
    void setButtonInfo(MenuItemSprite *btnLowerButton);
    void setButtonInfoByTag(int tag);
    void lowerButtonCallBack(cocos2d::Ref *pSender);
    
#pragma mark- Gate Buttons
    void loadGateButtons();
    void gateCallBack(cocos2d::Ref *pSender);
    
#pragma mark- Theme Buttons
    void loadThemeButtons();
    void themeCallBack(cocos2d::Ref *pSender);
    
#pragma mark- Ornaments Buttons
    void loadOrnamentsButtons();
    void ornamentsCallBack(cocos2d::Ref *pSender);

#pragma mark- Offline Earning
    void loadOfflineEarning();
    
#pragma mark- Show Add
    bool isInterstitialAdLoadCalled;
    
    void setInterstitialAd();
    void loadInterstitialAdFailed();
    void showInterstitialAd();
    void provideContentForViewAdd(string identifier);
};

#endif /* GameHud_h */
