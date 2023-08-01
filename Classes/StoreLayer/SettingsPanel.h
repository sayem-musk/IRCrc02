//
//  SettingsPanel.h
//  IRC-mobile
//
//  Created by Tarek Saazeb on 6/3/20.
//

#ifndef SettingsPanel_h
#define SettingsPanel_h

#include "../StoreLayer/StorePanel.h"
#include "../Framework/InAppPurchase/InAppUnit.h"
#include "../Framework/InAppPurchase/InAppController.h"

USING_NS_CC;

class SettingsPanel : public StorePanel,InAppDelegate
{
public:
#pragma mark- Init Method
    ~SettingsPanel();
    SettingsPanel();
    static SettingsPanel* create();
    virtual bool init();
    void removeFromParentAndCleanup(bool cleanup);
    
#pragma mark- Buttons
    MenuItemSprite *btnMusic;
    
    void loadMusicButtons();
    void setMusicButtonsSprite();
    void musicCallBack(cocos2d::Ref *pSender);
    
#pragma mark- Vibration
    MenuItemSprite *btnVibration;
    
    void loadVibrationButtons();
    void setVibrationButtonsSprite();
    void vibrationCallBack(cocos2d::Ref *pSender);
    
#pragma mark- InApp
    InAppUnit *inAppUnit;
    Menu *menuInApp;
    Menu *menuRestore;
    
    void loadInAppButton();
    void loadForInApp();
    void loadInAppUnitData();
    void inAppCallBack(cocos2d::Ref *pSender);
    void restoreCallBack(cocos2d::Ref *pSender);
    
#pragma mark- Provide Content
    void provideContent(string identifier);
};

#endif /* SettingsPanel_h */
