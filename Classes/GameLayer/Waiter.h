//
//  Waiter.h
//  IRC-mobile
//
//  Created by Tarek Saazeb on 7/11/20.
//

#ifndef Waiter_h
#define Waiter_h

#include "cocos2d.h"
#include "../CustomClass/SpineObject.h"

USING_NS_CC;

class Waiter : public Node
{
public:
    int object_at_index;
    int selectedWaiter;
    
    Sprite *imgStageBackground;
    
#pragma mark- Init Method
    ~Waiter();
    Waiter();
    static Waiter* create(int _object_at_index,int _selectedWaiter);
    virtual bool init(int _object_at_index,int _selectedWaiter);
    void removeFromParentAndCleanup(bool cleanup);
    
#pragma mark- Animation
    Node *nodeWaiter;
    SpineObject *animWaiter;
    cocos2d::Point startPosition;
    cocos2d::Point finalPosition;
    int writingAnimCount;
    
    void setPositionValue();
    void loadAnimation();
    void setAnimation();
    void setMoveAnimation();
    void setWritingAnimation();
    void setAnimationComplete();
};

#endif /* Waiter_h */
