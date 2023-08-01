//
//  SpineObject.h
//  MUSK
//
//  Created by Tarek Saazeb on 1/26/17.
//
//

#ifndef SpineObject_h
#define SpineObject_h

#include "cocos2d.h"
#include <spine/spine-cocos2dx.h>

using namespace std;
using namespace spine;
using namespace cocos2d;

enum
{
    animTypeIdle=1,
    animTypeWalk=2,
    animTypeMovement=3,
    animTypeEat=4,
    animTypePrepararion=5,
    animTypeAttack=6,
    animTypeDefence=7,
    animTypePower=8,
    animTypeSkillAttack=9,
    animTypeOther=10,
    animTypeWork=11,
    
    animTypeRun=12,
    animTypeHit=13,
    animTypeDeath=14,
    animTypeAttack2=15,
    animTypeAnimation=16,
    animTypeStanding=17,
    
    animTypeWalking=18,
    animTypeWriting=19,
};

enum
{
    ageBaby,
    ageAdult,
    ageOld,
};

class SpineObject : public Node
{
public:
    SkeletonAnimation *animationObject;
    
    ~SpineObject();
    SpineObject();
    static SpineObject* create(string strFileName,float scaleValue);
    
    bool init(string strFileName,float scaleValue);
    void removeSpineObject();
    void removeFromParentAndCleanup(bool cleanup) override;
    
    string getAnimationName(int animType);
    void startAnimation(int animType);
    void startAnimation(int animType,bool loop);
    void startAnimation(int trackIndex,int animType,bool loop);
    
    void startAnimation(string strAnimType);
    void startAnimation(string strAnimType,bool loop);
    void startAnimation(int trackIndex,string strAnimType,bool loop);
    
    bool isSpineObjectTouched(cocos2d::Point touchLocation);
    bool isSpineObjectTouched(cocos2d::Rect areaTouch);
    
#pragma mark- Color
    Color3B selectedColor;
    Color3B originalColor;
    void setSpineColor(Color3B color);
    void resetSpineColor();
    
#pragma mark- Shadow
    void addShadow();
    
#pragma mark- Move
    bool isMoving;
    cocos2d::Rect movingArea;
    cocos2d::Point postionOffset;
    cocos2d::Point runningDirectionOffSet;
    
    void setSpineObjectMove(cocos2d::Rect _movingArea,string _strMoveOffset);
    void movingSpineObject();
};

#endif /* SpineObject_h */
