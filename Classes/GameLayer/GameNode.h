//
//  GameNode.hpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 3/14/20.
//

#ifndef GameNode_h
#define GameNode_h

#include "cocos2d.h"
#include "../GameLayer/Human.h"
#include "../GameLayer/Waiter.h"

USING_NS_CC;
using namespace std;

class GameNode : public Node
{
public:
    static Scene* createScene();
    
#pragma mark- Init Method
    ~GameNode();
    GameNode();
    static GameNode* create();
    virtual bool init();
    void removeFromParentAndCleanup(bool cleanup);
    
#pragma mark- Call After Time
    void callAfterTime(float dt);
    void callAfterTimeForAds(float dt);
    
#pragma mark- Load Stage
    string strStageFolder;
    Sprite *imgStageBackground;
    Sprite *imgGate;
    Sprite *imgTruck;

    void loadStage();
    void loadOtherStageElement();
    void changeOtherElement();

#pragma mark- Load TableChair
    vector<Sprite*> *arrTableSprite;
    
    void loadTableChair();
    void removeAllTableChair();
    void loadTableSprite();
    Sprite* getTableSprite(int tableIndex);
    void addNewTableChair(int chairIndex);
    
#pragma mark- Human
    vector<Human*> *allHuman;

    void loadHuman();
    void setHumanSchedule();
    void humanSchedule(float dt);
    void removeHumanFromQueue();
    void updateObjectAtIndexHuman();
    
#pragma mark- HumanExit
    vector<int> *allChairToFinish;
    
    void setChairToFinish(int chairIndex);
    void loadHumanExit();
    void setHumanExitSchedule();
    void humanExitSchedule(float dt);
    
#pragma mark- Touch
    void setTouchEnable();
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
    void onTouchCancelled(Touch *touch, Event *event);
    
#pragma mark- Last Time Play
    void startLastTimePlay();
    void lastTimePlay(float dt);
    
#pragma mark- Music
    void playBackgroundMusic();
    void stopBackgroundMusic();
    void setMUsicSound();
    
#pragma mark- DoubleCoinsFor5Min
    int doubleCoinsFor5MinTime;
    
    Sprite *imgDoubleCoinsFor5Min;
    Label *lblDoubleCoinsFor5Min;
    
    void loadDoubleCoinsFor5Min();
    void setDoubleCoinsFor5Min();
    void doubleCoinsFor5MinSchudule(float dt);
    
#pragma mark- Waiter
    int totalWaiterCount;
    vector<Waiter*> *allWaiter;

    void setWaiter();
    void loadWaiter();
    void loadWaiter(int waiterId);
};

#endif /* GameNode_h */
