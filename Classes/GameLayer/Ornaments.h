//
//  Ornaments.h
//  IRC-mobile
//
//  Created by Tarek Saazeb on 7/10/20.
//

#ifndef Ornaments_h
#define Ornaments_h

#include "cocos2d.h"
#include "../CustomClass/SpineObject.h"

USING_NS_CC;

class Ornaments : public Node
{
public:
    static Ornaments* sharedManager();
#pragma mark- Init Method
    ~Ornaments();
    Ornaments();
    static Ornaments* create();
    virtual bool init();
    void removeFromParentAndCleanup(bool cleanup);

#pragma Ballons
    SpineObject *animBallons;
    
    void loadBallons();
    
#pragma IceCream
    SpineObject *animIceCream;

    void loadIceCream();
};

#endif /* Ornaments_h */
