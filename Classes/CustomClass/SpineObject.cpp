//
//  SpineObject.cpp
//  MUSK
//
//  Created by Tarek Saazeb on 1/26/17.
//
//

#include "SpineObject.h"
#include "../AppDelegate.h"

SpineObject::~SpineObject()
{
    
}

SpineObject::SpineObject()
{
    
}

SpineObject* SpineObject::create(string strFileName,float scaleValue)
{
    SpineObject* ret = new SpineObject();
    if(ret && ret->init(strFileName,scaleValue))
    {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
    return ret;
}

bool SpineObject::init(string strFileName,float scaleValue)
{
    if(Node::init())
    {
        AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
        
        animationObject=SkeletonAnimation::createWithJsonFile(strFileName+".json", strFileName+".atlas",scaleValue*appDelegate->deviceScaleFloat);
        this->addChild(animationObject);
        originalColor=animationObject->getColor();
        selectedColor=originalColor;
        isMoving=false;
    }
    return true;
}

void SpineObject::removeSpineObject()
{
    this->runAction(Sequence::create(DelayTime::create(0.02f),CallFunc::create(CC_CALLBACK_0(SpineObject::removeFromParentAndCleanup, this,true)),NULL));
}

void SpineObject::removeFromParentAndCleanup(bool cleanup)
{
    stopAllActions();
    unscheduleAllCallbacks();
    animationObject->stopAllActions();
    animationObject->removeFromParentAndCleanup(cleanup);
    Node::removeFromParentAndCleanup(cleanup);
}

string SpineObject::getAnimationName(int animType)
{
    string animationName="run";
    switch (animType)
    {
        case animTypeIdle:
            animationName="idle";
            break;
        case animTypeWalk:
            animationName="walk";
            break;
        case animTypeMovement:
            animationName="move";
            break;
        case animTypeEat:
            animationName="eat";
            break;
        case animTypePrepararion:
            animationName="prep";
            break;
        case animTypeAttack:
            animationName="attack";
            break;
        case animTypeDefence:
            animationName="defence";
            break;
        case animTypePower:
            animationName="power";
            break;
        case animTypeSkillAttack:
            animationName="skill";
            break;
        case animTypeOther:
            animationName="anim";
            break;
        case animTypeWork:
            animationName="work";
            break;
        case animTypeRun:
            animationName="run";
            break;
        case animTypeHit:
            animationName="hit";
            break;
        case animTypeDeath:
            animationName="death";
            break;
        case animTypeAttack2:
            animationName="attack2";
            break;
        case animTypeAnimation:
            animationName="animation";
            break;
        case animTypeStanding:
            animationName="standing";
            break;
        case animTypeWalking:
            animationName="walk";
            break;
            
        case animTypeWriting:
            animationName="writing";
            break;
            
        default:
            break;
    }
    return animationName;
}

void SpineObject::startAnimation(int animType)
{
    animationObject->setAnimation(0, this->getAnimationName(animType), true);
}

void SpineObject::startAnimation(int animType,bool loop)
{
    animationObject->setAnimation(0, this->getAnimationName(animType), loop);
}

void SpineObject::startAnimation(int trackIndex,int animType,bool loop)
{
    animationObject->setAnimation(trackIndex, this->getAnimationName(animType), loop);
}

void SpineObject::startAnimation(string strAnimType)
{
    animationObject->setAnimation(0, strAnimType, true);
}

void SpineObject::startAnimation(string strAnimType,bool loop)
{
    animationObject->setAnimation(0, strAnimType, loop);
}

void SpineObject::startAnimation(int trackIndex,string strAnimType,bool loop)
{
    animationObject->setAnimation(trackIndex, strAnimType, loop);
}

bool SpineObject::isSpineObjectTouched(Point touchLocation)
{
    Rect area=animationObject->getBoundingBox();
    Point point=this->convertToNodeSpace(touchLocation);
    
/*    LayerColor *backColor=LayerColor::create(Color4B::RED, area.size.width, area.size.height);
    backColor->setOpacity(0.5*255);
    this->addChild(backColor, -1);*/
    
    if(area.containsPoint(point))
    {
        return true;
    }
    return false;
}

bool SpineObject::isSpineObjectTouched(Rect areaTouch)
{
    Rect area=animationObject->getBoundingBox();
    Point point1=this->convertToNodeSpace(areaTouch.origin);
    Point point2=this->convertToNodeSpace(areaTouch.origin+Point(areaTouch.size.width,0));
    Point point3=this->convertToNodeSpace(areaTouch.origin+Point(0,areaTouch.size.height));
    Point point4=this->convertToNodeSpace(areaTouch.origin+Point(areaTouch.size.width,areaTouch.size.height));
    
    /*    LayerColor *backColor=LayerColor::create(Color4B::RED, area.size.width, area.size.height);
     backColor->setOpacity(0.5*255);
     this->addChild(backColor, -1);*/
    
    if(area.containsPoint(point1) || area.containsPoint(point2) || area.containsPoint(point3) || area.containsPoint(point4))
    {
        return true;
    }
    return false;
}

void SpineObject::setSpineColor(Color3B color)
{
    if(selectedColor!=color)
    {
        selectedColor=color;
        animationObject->setColor(selectedColor);
    }
}

void SpineObject::resetSpineColor()
{
    if(selectedColor!=originalColor)
    {
        selectedColor=originalColor;
        animationObject->setColor(selectedColor);
    }
}

#pragma mark- Shadow

void SpineObject::addShadow()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    Sprite *imgShadow=Sprite::create(folderImagesStore+"shadow.png");
    imgShadow->setName("imgShadow");
    imgShadow->setScale(appDelegate->deviceScaleFloat);
    imgShadow->setPosition(Point(0*appDelegate->deviceScaleFloat,0*appDelegate->deviceScaleFloat));
    this->animationObject->addChild(imgShadow,-1);
}

#pragma mark- Move

enum
{
    directionRightUp=1,
    directionRightDown=2,
    directionLeftDown=3,
    directionLeftUp=4,
};

void SpineObject::setSpineObjectMove(Rect _movingArea,string _strMoveOffset)
{
    isMoving=true;
    movingArea=_movingArea;
    runningDirectionOffSet=Point(0,0);
    
    postionOffset=Point(10,5);
    
    vector<string> *arrMoveOffset=AppDelegate::componentSeparatedByString(_strMoveOffset, ",");
    if(arrMoveOffset->size()==2)
    {
        postionOffset=Point(stoi(arrMoveOffset->at(0)),stoi(arrMoveOffset->at(1)));
    }
    else if(arrMoveOffset->size()==1)
    {
        switch (stoi(arrMoveOffset->at(0)))
        {
            case 1:                             //Fast
                postionOffset=Point(15,10);
                break;
            case 2:                             //Water
                postionOffset=Point(10,5);
                break;
            case 3:                             //Slow
                postionOffset=Point(5,2.5);
                break;
            case 4:                             //Heavy
                postionOffset=Point(5,2.5);
                break;
                
            default:
                break;
        }
    }

  /*  LayerColor *layerColor=LayerColor::create(Color4B::BLACK, movingArea.size.width, movingArea.size.height);
    layerColor->setOpacity(0.5*255);
    this->addChild(layerColor,-1);*/
    
    animationObject->setPosition(Point(arc4random()%(int)movingArea.size.width,arc4random()%(int)movingArea.size.height));
    
    this->startAnimation(animTypeWalk);
    movingSpineObject();
}

void SpineObject::movingSpineObject()
{
    Point checkPosition=animationObject->getPosition()+Point(runningDirectionOffSet.x*postionOffset.x,runningDirectionOffSet.y*postionOffset.y);
    
    if(runningDirectionOffSet!=Point(0,0) && (checkPosition.x>=movingArea.origin.x && checkPosition.x<(movingArea.origin.x+movingArea.size.width) && checkPosition.y>=movingArea.origin.y && checkPosition.y<(movingArea.origin.x+movingArea.size.height)))
    {
        
    }
    else
    {
        vector<Point> *posiblePosition=new vector<Point>();
        
        for (int i=1; i<=4; i++)
        {
            Point directionOffSet=Point(+1,+1);
            if(i==directionRightUp)
                directionOffSet=Point(+1,+1);
            else if(i==directionRightDown)
                directionOffSet=Point(+1,-1);
            else if(i==directionLeftDown)
                directionOffSet=Point(-1,-1);
            else if(i==directionLeftUp)
                directionOffSet=Point(-1,+1);
            
            Point newPosition=animationObject->getPosition()+Point(directionOffSet.x*postionOffset.x,directionOffSet.y*postionOffset.y);
            if(newPosition.x>=movingArea.origin.x && newPosition.x<(movingArea.origin.x+movingArea.size.width) &&
               newPosition.y>=movingArea.origin.y && newPosition.y<(movingArea.origin.x+movingArea.size.height))
            {
                posiblePosition->push_back(directionOffSet);
            }
        }
        
        if(posiblePosition->size()==0)
        {
            Point centerPoint=Point(movingArea.origin.x+movingArea.size.width/2,movingArea.origin.y+movingArea.size.height/2);
            Point disFromCenter=centerPoint-animationObject->getPosition();
            Point directionOffSet=Point(+1,+1);
            if(disFromCenter.x<0)
                directionOffSet.x=-1;
            else
                directionOffSet.x=1;
            
            if(disFromCenter.y<0)
                directionOffSet.y=-1;
            else
                directionOffSet.y=1;
            
            posiblePosition->push_back(directionOffSet);
        }
        runningDirectionOffSet=posiblePosition->at(arc4random()%posiblePosition->size());
        if(runningDirectionOffSet.x>0)
            animationObject->setScaleX(-1);
        else
            animationObject->setScaleX(1);
    }
    
    Point nextPosition=animationObject->getPosition()+Point(runningDirectionOffSet.x*postionOffset.x,runningDirectionOffSet.y*postionOffset.y);
    animationObject->runAction(MoveTo::create(0.1, nextPosition));
    
    if(isMoving)
    {
        animationObject->setCompleteListener([&] (spTrackEntry* entry) {
            movingSpineObject();
        });
    }
}







