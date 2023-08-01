//
//  Chair.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 3/30/20.
//

#include "Chair.h"
#include "AppDelegate.h"
#include "../CustomClass/SpineObject.h"
#include "../GameLayer/HumanExit.h"

#pragma mark- Init Method

Chair::~Chair()
{
    
}

Chair::Chair()
{
    
}

Chair* Chair::create(int _objectAtIndex)
{
    Chair* ret = new Chair();
    if(ret && ret->init(_objectAtIndex)) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool Chair::init(int _objectAtIndex)
{
    if(Node::init())
    {
        objectAtIndex=_objectAtIndex;
        chairIndex=objectAtIndex%NoChairInTable;
        tableIndex=objectAtIndex/NoChairInTable;
        isEmpty=true;
        
        this->scheduleOnce(schedule_selector(Chair::loadAll),0.0f);
        
        return true;
    }
    return false;
}

void Chair::removeFromParentAndCleanup(bool cleanup)
{
    Node::removeFromParentAndCleanup(cleanup);
}

#pragma mark- Load All

void Chair::loadAll(float dt)
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    imgTable=appDelegate->gnode->getTableSprite(tableIndex);
    
    //CCLOG("chairIndex %d",chairIndex);
    //CCLOG("tableIndex %d",tableIndex);
    //CCLOG("tableIndex %f %f",imgTable->getPosition().x,imgTable->getPosition().y);

    this->loadChairSprite();
}

#pragma mark- Load Sprite

void Chair::loadChairSprite()
{
    int zIndex=0;
    
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    string strChairSprite=folderImagesTableChair+"chair-1.png";
    Point point=Point(0,0);
    
    switch (chairIndex)
    {
        case 0:
            strChairSprite=folderImagesTableChair+"chair-1.png";
            point=Point(imgTable->getScaleX()*imgTable->getContentSize().width/2+5*appDelegate->deviceScaleFloat,imgTable->getScaleY()*imgTable->getContentSize().height/2+0*appDelegate->deviceScaleFloat);
            zIndex=10-1;
            break;
            
        case 1:
            strChairSprite=folderImagesTableChair+"chair-2.png";
            point=Point(-imgTable->getScaleX()*imgTable->getContentSize().width/2-5*appDelegate->deviceScaleFloat,imgTable->getScaleY()*imgTable->getContentSize().height/2+0*appDelegate->deviceScaleFloat);
            zIndex=10-1;
            break;
         
        case 2:
            strChairSprite=folderImagesTableChair+"chair-3.png";
            point=Point(-imgTable->getScaleX()*imgTable->getContentSize().width/2-0*appDelegate->deviceScaleFloat,-imgTable->getScaleY()*imgTable->getContentSize().height/2+10*appDelegate->deviceScaleFloat);
            zIndex=10+1;
            break;
    
        case 3:
            strChairSprite=folderImagesTableChair+"chair-4.png";
            point=Point(+imgTable->getScaleX()*imgTable->getContentSize().width/2+10*appDelegate->deviceScaleFloat,-imgTable->getScaleY()*imgTable->getContentSize().height/2+10*appDelegate->deviceScaleFloat);
            
            zIndex=10+1;
            break;
            
        default:
            break;
    }
    
    imgChair=Sprite::create(strChairSprite);
    imgChair->setScale(appDelegate->deviceScaleFloat);
    imgChair->setPosition(imgTable->getPosition()+point);
    this->addChild(imgChair);
    
    this->getParent()->reorderChild(this,zIndex);
}

void Chair::addHumanInChair(int _selectedHuman)
{
    selectedHuman=_selectedHuman;
 
    isEmpty=false;
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    
    if(AppDelegate::isContainObject(this, nodeHuman))
        nodeHuman->removeFromParentAndCleanup(true);
    
    nodeHuman=Node::create();
    this->addChild(nodeHuman,10);
    
    string strAnimation=folderImagesHuman+to_string(selectedHuman)+"d";
    nodePosition=Point(imgChair->getPosition()+Point(0*appDelegate->deviceScaleFloat,-30*appDelegate->deviceScaleFloat));
    
    float scaleValue=1;
    
    switch (chairIndex) {
        case 0:
        {
            strAnimation=folderImagesHuman+to_string(selectedHuman)+"d";
            nodePosition=Point(imgChair->getPosition()+Point(0*appDelegate->deviceScaleFloat,-30*appDelegate->deviceScaleFloat));
            scaleValue=1;
        }
            break;
        case 1:
        {
            strAnimation=folderImagesHuman+to_string(selectedHuman)+"d";
            nodePosition=Point(imgChair->getPosition()+Point(0*appDelegate->deviceScaleFloat,-30*appDelegate->deviceScaleFloat));
            scaleValue=-1;
        }
            break;
            
        case 2:
        {
            strAnimation=folderImagesHuman+to_string(selectedHuman)+"c";
            nodePosition=Point(imgChair->getPosition()+Point(0*appDelegate->deviceScaleFloat,-30*appDelegate->deviceScaleFloat));
            scaleValue=-1;
        }
            break;
            
        case 3:
        {
            strAnimation=folderImagesHuman+to_string(selectedHuman)+"c";
            nodePosition=Point(imgChair->getPosition()+Point(0*appDelegate->deviceScaleFloat,-30*appDelegate->deviceScaleFloat));
            scaleValue=1;
        }
            break;
            
        default:
            break;
    }
    
    nodeHuman->setVisible(false);
    nodeHuman->setPosition(nodePosition);
    //nodeHuman->setPosition(Point(appDelegate->winSize.width,appDelegate->winSize.height/2));
    
    animHuman=SpineObject::create(strAnimation, 0.1f);
    animHuman->setScaleX(scaleValue*animHuman->getScaleX());
    animHuman->startAnimation(animTypeEat);
    
    nodeHuman->addChild(animHuman,1000);
    
    this->scheduleOnce(schedule_selector(Chair::animHumanLoaded),0.1f);
}

void Chair::animHumanLoaded(float dt)
{
    imgChair->setVisible(false);
    
    nodeHuman->setVisible(true);
    
    animationCount=5;
    
    animHuman->animationObject->setCompleteListener([&] (spTrackEntry* entry) {
        this->animationFinish();
    });
}

void Chair::animationFinish()
{
    animationCount--;
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    
    if(animationCount==0)
    {
        appDelegate->gnode->setChairToFinish(objectAtIndex);
    }
}

void Chair::setFinishEating()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    screenData->addCoinsExperience();
    
    this->scheduleOnce(schedule_selector(Chair::finishEating),0.3f);
}

void Chair::finishEating(float dt)
{
    if(AppDelegate::isContainObject(this, nodeHuman))
        nodeHuman->removeFromParentAndCleanup(true);
    
    imgChair->setVisible(true);
    
    isEmpty=true;
    
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();

    HumanExit *humanExit=HumanExit::create(selectedHuman);
    appDelegate->gnode->addChild(humanExit,20);
    
    appDelegate->gnode->updateObjectAtIndexHuman();
}


