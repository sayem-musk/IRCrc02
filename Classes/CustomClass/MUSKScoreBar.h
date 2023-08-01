//
//  MUSKScoreBar.h
//  IRC-mobile
//
//  Created by Tarek Saazeb on 3/14/20.
//

#ifndef MUSKScoreBar_h
#define MUSKScoreBar_h

#include "cocos2d.h"

USING_NS_CC;

class MUSKScoreBar : public Node
{
public:
    static MUSKScoreBar* sharedManager();
    
#pragma mark- Init Method
    ~MUSKScoreBar();
    MUSKScoreBar();
    static MUSKScoreBar* create();
    virtual bool init();
    void removeFromParentAndCleanup(bool cleanup);
    
#pragma mark- ScoreBar
    Sprite *imgTopBar;
    Label *lblCoins;
    Label *lblLevel;
    
    void loadScoreBar();
    void updateScoreBar();
    void coinsCallBack(cocos2d::Ref *pSender);
    void settingsCallBack(cocos2d::Ref *pSender);
    
#pragma mark- Level
    Menu *menuLevel;
    ProgressTimer *progressBarLevel;
    
    void loadLevelButton(float dt);
    void levelUpCallBack(cocos2d::Ref *pSender);
    void levelUp();
    void setLevelUpShow(bool isShow);
    void setExperiencePrograssBar();
};

#endif /* MUSKScoreBar_h */
