//
//  Chair.h
//  IRC-mobile
//
//  Created by Tarek Saazeb on 3/30/20.
//

#ifndef Chair_h
#define Chair_h

#include "cocos2d.h"
#include "../CustomClass/SpineObject.h"

USING_NS_CC;

class Chair : public Node
{
public:
    int objectAtIndex;
    bool isEmpty;
    
#pragma mark- Init Method
    ~Chair();
    Chair();
    static Chair* create(int _objectAtIndex);
    virtual bool init(int _objectAtIndex);
    void removeFromParentAndCleanup(bool cleanup);
    
#pragma mark- Load All
    Sprite *imgTable;
    
    int chairIndex;
    int tableIndex;;
    
    void loadAll(float dt);
    
#pragma mark- Load Sprite
    Sprite *imgChair;
    
    void loadChairSprite();
    
#pragma mark- Animation
    int selectedHuman;
    int animationCount;
    Node *nodeHuman;
    SpineObject *animHuman;
    cocos2d::Point nodePosition;

    void addHumanInChair(int _selectedHuman);
    void animHumanLoaded(float dt);
    void animationFinish();
    void setFinishEating();
    void finishEating(float dt);
};

#endif /* Chair_h */
