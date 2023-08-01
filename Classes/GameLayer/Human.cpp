//
//  Human.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 4/2/20.
//

#include "Human.h"
#include "AppDelegate.h"
#include "../GameLayer/Station.h"

#pragma mark- Init Method

Human::~Human()
{
    
}

Human::Human()
{
    
}

Human* Human::create(int _object_at_index)
{
    Human* ret = new Human();
    if(ret && ret->init(_object_at_index)) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool Human::init(int _object_at_index)
{
    if(Node::init())
    {
        object_at_index=_object_at_index;
        AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
        
        imgStageBackground=appDelegate->gnode->imgStageBackground;
        
        loadAnimation();
        
        return true;
    }
    return false;
}

void Human::removeFromParentAndCleanup(bool cleanup)
{
    if(AppDelegate::isContainObject(this, nodeHuman))
        nodeHuman->removeFromParentAndCleanup(true);
    Node::removeFromParentAndCleanup(cleanup);
}

void Human::updateObjectAtIndex(int _object_at_index)
{
    //CCLOG("object_at_index %d _object_at_index %d",object_at_index,_object_at_index);
    object_at_index=_object_at_index;
    
    setAnimation();
}

#pragma mark- Animation

void Human::loadAnimation()
{
    selectedHuman=1001+arc4random()%16;
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    
    if(AppDelegate::isContainObject(this, nodeHuman))
        nodeHuman->removeFromParentAndCleanup(true);
    
    string strAnimation=folderImagesHuman+to_string(selectedHuman)+"a";
    Point nodePosition=Point(-50*imgStageBackground->getScaleX(),appDelegate->winSize.height/2-440*imgStageBackground->getScaleY());
    float scaleValue=-1;
 
    nodeHuman=Node::create();
    nodeHuman->setPosition(nodePosition);
    this->addChild(nodeHuman,1000);
    
    animHuman=SpineObject::create(strAnimation, 0.1f);
    nodeHuman->addChild(animHuman,1000);
    
    animHuman->setScaleX(scaleValue*animHuman->getScaleX());
    
    setAnimation();
}

void Human::setAnimation()
{
    //CCLOG("selectedHuman %d",selectedHuman);
    animHuman->startAnimation(animTypeWalk);
    nodeHuman->stopAllActions();
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
                                                                                                                                      
    Point finalPosition=Point(405*imgStageBackground->getScaleX()-object_at_index*30*imgStageBackground->getScaleX(),appDelegate->winSize.height/2 - 180*imgStageBackground->getScaleY() - object_at_index*17*imgStageBackground->getScaleY());
    
    double staticDistance=525.0f;
    double distance=sqrt(pow((finalPosition.y-nodeHuman->getPosition().y), 2)+pow((finalPosition.x-nodeHuman->getPosition().x), 2));
    double animationTime=(9.0f*distance)/staticDistance;
    
    MoveTo *moveto=MoveTo::create(animationTime, finalPosition);
    Sequence *sequenceMove=Sequence::create(moveto,CallFunc::create(CC_CALLBACK_0(Human::addHumanInStation, this)),NULL);
    nodeHuman->runAction(sequenceMove);
}

void Human::addHumanInStation()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    animHuman->startAnimation(animTypeIdle);
    
    Point finalPosition=Point(405*imgStageBackground->getScaleX(),appDelegate->winSize.height/2 - 180*imgStageBackground->getScaleY());
    if(nodeHuman->getPosition()==finalPosition)
    {
        Station *station=Station::sharedManager();
        
        if(station->addHumanInStation(selectedHuman))
        {
            AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
            appDelegate->gnode->removeHumanFromQueue();
        }
    }
}



