//
//  HumanExit.h
//  IRC-mobile
//
//  Created by Tarek Saazeb on 4/5/20.
//

#ifndef HumanExit_h
#define HumanExit_h

#include "cocos2d.h"
#include "../CustomClass/SpineObject.h"

USING_NS_CC;

class HumanExit : public Node
{
public:
    Sprite *imgStageBackground;
    
    int selectedHuman;
#pragma mark- Init Method
    ~HumanExit();
    HumanExit();
    static HumanExit* create(int _selectedHuman);
    virtual bool init(int _selectedHuman);
    void removeFromParentAndCleanup(bool cleanup);
    
#pragma mark- Animation
    Node *nodeHuman;
    SpineObject *animHuman;
    Point nodePosition;
    
    void loadAnimation();
    void setAnimation();

    void setNodeCoinsAnimation();
};

#endif /* HumanExit_h */
