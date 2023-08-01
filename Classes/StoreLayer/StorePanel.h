//
//  StorePanel.h
//  MUSK
//
//  Created by Tarek Saazeb on 7/28/16.
//
//

#ifndef StorePanel_h
#define StorePanel_h

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "AppDelegate.h"
#include "../CustomClass/SpineObject.h"
#include "../CustomClass/ScrollableButton.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d::extension;

class StorePanel : public Node
{
public:
    Size clickerMarketSize;
    AppDelegate *appDelegate;
    
    virtual bool init();
    bool initWithSmallWindow();
    bool initWithCustomContentSize();
    
#pragma mark- BackGroundColor
    LayerColor *colorBackground;
    void loadBackGroundColor();
    
#pragma mark- Touch
    void setTouchEnable();
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
    void onTouchCancelled(Touch *touch, Event *event);
    bool onTouchBeganSmallWindow(Touch *touch, Event *event);
    void onTouchMovedSmallWindow(Touch *touch, Event *event);
    void onTouchEndedSmallWindow(Touch *touch, Event *event);
    void onTouchCancelledSmallWindow(Touch *touch, Event *event);
    
#pragma mark- Load Background
    Sprite *imgBackground;
    Sprite *imgTopBar;
    Sprite *imgBottomBar;
    
    void loadBackGround();
    void loadBackGround(string strImageName);
    void loadSmallBackground();
    void loadSmallBackground(string strImageName);
    void loadTopBar();
    void loadTopBar(string strImageName);
    void loadBottomBar();
    void loadBottomBar(string strImageName);
    
#pragma mark- Cross Button
    MenuItemSprite *btnCross;
    ScrollableButton *btnScrollCross;
    void loadCrossButton();
    void loadScrollCrossButton();
    void crossCallBack(cocos2d::Ref* pSender);
    
#pragma mark- Back Button
    MenuItemSprite *btnBack;
    void loadBackButton();
    void backCallBack(cocos2d::Ref* pSender);
    
#pragma mark- Title
    Label *titleLabel;
    void loadTitle(string _panel_title);
    
#pragma mark- Create Element
    static MenuItemSprite* createButton(string imageName);
    static MenuItemSprite* createButton(string imageNameNormal,string imageNameSelected);
    static MenuItemSprite* createButtonWithLabel(string imageName,string strButtonTitle,float fontSize);
    static Label* createLabel(string strLabel,float fontSize);
    static Label* createLabelWithBold(string strLabel,float fontSize);
    static Label* createBattleLabel(string strLabel,float fontSize);
    static Label* createLabelForGoal(string strLabel,float fontSize);
    static Label* createBattleLabelWithoutBold(string strLabel,float fontSize);
    static Label* setFontSize(Label *lblLabel,float fontSize);
    
    static ScrollableButton* createScrollableButton(string imageName);
    static ScrollableButton* createScrollableButton(string imageNameNormal,string imageNameSelected);
    
#pragma mark- TouchDetection
    static bool detect_alpha(Sprite *mainSprite, Touch *touch, string imagename);
    static bool checkSpriteTouch(Sprite *mainSprite,cocos2d::Point touchLocation);
    
#pragma mark- Score Bar
    
    static Node *loadResourceNodeForScore(int _resourceType,string _resourceAmount);
    static Node *loadResourceNodeForScore(int _resourceType,vector<string> *_resourceAmount);
    
#pragma mark- Time Calculation
    
    static int getStringTimeInSecond(string strTimeValue);
    static string convertTimeToString(int timeValue);
    static string convertTimeToClockString(int timeValue);
    static string convertTimeToClockStringSmall(int timeValue);

};


#endif /* StorePanel_h */






