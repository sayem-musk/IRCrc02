//
//  Waiter.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 7/11/20.
//

#include "Waiter.h"
#include "AppDelegate.h"

#pragma mark- Init Method

Waiter::~Waiter()
{
    
}

Waiter::Waiter()
{
    
}

Waiter* Waiter::create(int _object_at_index,int _selectedWaiter)
{
    Waiter* ret = new Waiter();
    if(ret && ret->init(_object_at_index,_selectedWaiter)) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool Waiter::init(int _object_at_index,int _selectedWaiter)
{
    if(Node::init())
    {
        object_at_index=_object_at_index;
        selectedWaiter=_selectedWaiter;
        
        AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
        
        imgStageBackground=appDelegate->gnode->imgStageBackground;
        
        setPositionValue();
        
        loadAnimation();
        
        return true;
    }
    return false;
}

void Waiter::removeFromParentAndCleanup(bool cleanup)
{
    Node::removeFromParentAndCleanup(cleanup);
}

#pragma mark- Animation

void Waiter::setPositionValue()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    
    startPosition=Point(appDelegate->winSize.width/2-250*imgStageBackground->getScaleX(),appDelegate->winSize.height/2-100*imgStageBackground->getScaleY());
    finalPosition=Point(appDelegate->winSize.width/2-250*imgStageBackground->getScaleX(),appDelegate->winSize.height/2-100*imgStageBackground->getScaleY());
    
    switch(object_at_index)
    {
        case 0:
        {
            startPosition=Point(appDelegate->winSize.width/2+70*imgStageBackground->getScaleX(),appDelegate->winSize.height/2+140*imgStageBackground->getScaleY());
            //finalPositiion=Point(appDelegate->winSize.width/2-60*imgStageBackground->getScaleX(),appDelegate->winSize.height/2+80*imgStageBackground->getScaleY());
            finalPosition=Point(appDelegate->winSize.width/2+20*imgStageBackground->getScaleX(),appDelegate->winSize.height/2+110*imgStageBackground->getScaleY());
        }
            break;
        case 1:
        {
            startPosition=Point(appDelegate->winSize.width/2-255*imgStageBackground->getScaleX(),appDelegate->winSize.height/2+70*imgStageBackground->getScaleY());
            finalPosition=Point(appDelegate->winSize.width/2-240*imgStageBackground->getScaleX(),appDelegate->winSize.height/2+35*imgStageBackground->getScaleY());
        }
            break;
        
        case 2:
        {
            startPosition=Point(appDelegate->winSize.width/2-280*imgStageBackground->getScaleX(),appDelegate->winSize.height/2-100*imgStageBackground->getScaleY());
            finalPosition=Point(appDelegate->winSize.width/2-220*imgStageBackground->getScaleX(),appDelegate->winSize.height/2-75*imgStageBackground->getScaleY());
        }
            break;
    }
}

void Waiter::loadAnimation()
{
    if(AppDelegate::isContainObject(this, nodeWaiter))
        nodeWaiter->removeFromParentAndCleanup(true);
    
    float scaleValue=-1;
    
    string strAnimation=folderImagesWaiter+to_string(selectedWaiter)+"a";
    
    switch(object_at_index)
    {
        case 0:
        {
            strAnimation=folderImagesWaiter+to_string(selectedWaiter)+"b";
            scaleValue=1;
        }
            break;
        case 1:
        {
            strAnimation=folderImagesWaiter+to_string(selectedWaiter)+"b";
        }
            break;
        
        case 2:
        {
            strAnimation=folderImagesWaiter+to_string(selectedWaiter)+"a";
        }
            break;
    }
    
    CCLOG("strAnimation %s",strAnimation.c_str());
 
    nodeWaiter=Node::create();
    nodeWaiter->setPosition(startPosition);
    this->addChild(nodeWaiter,1000);
    
    animWaiter=SpineObject::create(strAnimation, 0.1f);
    nodeWaiter->addChild(animWaiter,1000);
    
    animWaiter->setScaleX(scaleValue*animWaiter->getScaleX());
    
    animWaiter->animationObject->showAnimationNames();
    
    setAnimation();
}

void Waiter::setAnimation()
{
    writingAnimCount=3;
    //CCLOG("selectedHuman %d",selectedHuman);
    animWaiter->startAnimation(animTypeIdle);
    
    nodeWaiter->stopAllActions();
    
    DelayTime *delayTime=DelayTime::create(1.5f);
    Sequence *sequenceMove=Sequence::create(delayTime,CallFunc::create(CC_CALLBACK_0(Waiter::setMoveAnimation, this)),NULL);
    nodeWaiter->runAction(sequenceMove);
}

void Waiter::setMoveAnimation()
{
    animWaiter->startAnimation(animTypeWalking);
    
    double staticDistance=525.0f;
    double distance=sqrt(pow((finalPosition.y-nodeWaiter->getPosition().y), 2)+pow((finalPosition.x-nodeWaiter->getPosition().x), 2));
    double animationTime=(5.0f*distance)/staticDistance;
    
    MoveTo *moveto=MoveTo::create(animationTime, finalPosition);
    Sequence *sequenceMove=Sequence::create(moveto,CallFunc::create(CC_CALLBACK_0(Waiter::setWritingAnimation, this)),NULL);
    nodeWaiter->runAction(sequenceMove);
}

void Waiter::setWritingAnimation()
{
    animWaiter->startAnimation(animTypeWalking);
    
    animWaiter->animationObject->setCompleteListener([&] (spTrackEntry* entry) {
        writingAnimCount--;
        if(writingAnimCount==0)
        {
            setAnimationComplete();
        }
    });
}

void Waiter::setAnimationComplete()
{
    if(AppDelegate::isContainObject(this, nodeWaiter))
        nodeWaiter->removeFromParentAndCleanup(true);
    
    float scaleValue=-1;
    
    string strAnimation=folderImagesWaiter+to_string(selectedWaiter)+"a";
    
    switch(object_at_index)
    {
        case 0:
        {
            strAnimation=folderImagesWaiter+to_string(selectedWaiter)+"a";
        }
            break;
        case 1:
        {
            scaleValue=1;
            strAnimation=folderImagesWaiter+to_string(selectedWaiter)+"a";
        }
            break;
        
        case 2:
        {
            scaleValue=1;
            strAnimation=folderImagesWaiter+to_string(selectedWaiter)+"b";
        }
            break;
    }
    
    nodeWaiter=Node::create();
    nodeWaiter->setPosition(finalPosition);
    this->addChild(nodeWaiter,1000);
    
    animWaiter=SpineObject::create(strAnimation, 0.1f);
    nodeWaiter->addChild(animWaiter,1000);
    
    animWaiter->setScaleX(scaleValue*animWaiter->getScaleX());
    
    animWaiter->startAnimation(animTypeWalking);
    
    double staticDistance=525.0f;
    double distance=sqrt(pow((startPosition.y-nodeWaiter->getPosition().y), 2)+pow((startPosition.x-nodeWaiter->getPosition().x), 2));
    double animationTime=(5.0f*distance)/staticDistance;
    
    MoveTo *moveto=MoveTo::create(animationTime, startPosition);
    Sequence *sequenceMove=Sequence::create(moveto,CallFunc::create(CC_CALLBACK_0(Waiter::loadAnimation, this)),NULL);
    nodeWaiter->runAction(sequenceMove);
}
