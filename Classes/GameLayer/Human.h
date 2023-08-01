//
//  Human.h
//  IRC-mobile
//
//  Created by Tarek Saazeb on 4/2/20.
//

#ifndef Human_h
#define Human_h

#include "cocos2d.h"
#include "../CustomClass/SpineObject.h"

USING_NS_CC;

class Human : public Node
{
public:
    int object_at_index;
    int selectedHuman;
    
    Sprite *imgStageBackground;
    
#pragma mark- Init Method
    ~Human();
    Human();
    static Human* create(int _object_at_index);
    virtual bool init(int _object_at_index);
    void removeFromParentAndCleanup(bool cleanup);
    
    void updateObjectAtIndex(int _object_at_index);
    
#pragma mark- Animation
    Node *nodeHuman;
    SpineObject *animHuman;
    
    void loadAnimation();
    void setAnimation();
    void addHumanInStation();
};

#endif /* Human_h */
