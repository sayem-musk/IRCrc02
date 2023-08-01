//
//  Station.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 4/4/20.
//

#include "Station.h"
#include "AppDelegate.h"
#include "../DBClasses/DBAttributesInfo.h"

static Station *sharedInstance=NULL;

Station* Station::sharedManager()
{
    if(sharedInstance==NULL)
    {
        sharedInstance=Station::create();
    }
    return sharedInstance;
}


#pragma mark- Init Method

Station::~Station()
{
    
}

Station::Station()
{
    
}

Station* Station::create()
{
    Station* ret = new Station();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool Station::init()
{
    if(Node::init())
    {
        AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
        imgStageBackground=appDelegate->gnode->imgStageBackground;
        
        allHumanId=new vector<int>();
        
        loadStation();
        setStationSchedule();
        
        return true;
    }
    return false;
}

void Station::removeFromParentAndCleanup(bool cleanup)
{
    Node::removeFromParentAndCleanup(cleanup);
}

void Station::loadStation()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    
    string strStageFolder=folderImagesStage+"Stage-"+to_string(screenData->screenInfo->screen_id)+"/";
    
    imgStation=Sprite::create(strStageFolder+"gate-"+to_string(1)+".png");
    imgStation->setScale(appDelegate->winSize.width/imgStation->getContentSize().width,appDelegate->winSize.height/imgStation->getContentSize().height);
    //imgGate->setScale(appDelegate->deviceScaleFloat);
    imgStation->setPosition(appDelegate->winSize.width/2, imgStation->getScaleY()*imgStation->getContentSize().height/2);
    this->addChild(imgStation,20);
}

void Station::loadAnimation(int selectedHuman)
{
    allHumanId->push_back(selectedHuman);
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    
    if(AppDelegate::isContainObject(this, nodeHuman))
        nodeHuman->removeFromParentAndCleanup(true);
    
    string strAnimation=folderImagesHuman+to_string(selectedHuman)+"a";
    Point nodePosition=Point(400*imgStageBackground->getScaleX(),appDelegate->winSize.height/2-150*imgStageBackground->getScaleY());
    
    nodeHuman=Node::create();
    nodeHuman->setPosition(nodePosition);
    this->addChild(nodeHuman,10);
    
    animHuman=SpineObject::create(strAnimation, 0.1f);
    nodeHuman->addChild(animHuman,1000);
    
//    animHuman->setScaleX(scaleValue*animHuman->getScaleX());
    animHuman->startAnimation(animTypeIdle);
}

#pragma mark- queue

bool Station::addHumanInStation(int selectedHuman)
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    
    DBAttributesInfo *attributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(TypeStationCapacity,screenData->myScreen->station_capacity_level);
    
    if(allHumanId->size()<stoi(attributesInfo->attributes_effect))
    {
        loadAnimation(selectedHuman);
        return true;
    }
    return false;
}

bool Station::removeHumanFromStation()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    //ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    
    vector<int> *allAvailableChair=new vector<int>();
    
    for (int i=0; i<appDelegate->allChair->size(); i++)
    {
        Chair *chair=appDelegate->allChair->at(i);
        if(chair->isEmpty==true)
        {
            allAvailableChair->push_back(i);
        }
    }
    
    if(allAvailableChair->size()>0)
    {
        int index=allAvailableChair->at(arc4random()%allAvailableChair->size());
        Chair *chair=appDelegate->allChair->at(index);
        chair->addHumanInChair(allHumanId->at(0));
        
        return true;
    }
    
    return false;
}

#pragma mark- Station Schedule

void Station::setStationSchedule()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    
    DBAttributesInfo *attributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(TypeSpeed,screenData->myScreen->speed_level);
    
    this->unschedule(schedule_selector(Station::stationSchedule));
    this->schedule(schedule_selector(Station::stationSchedule),stof(attributesInfo->attributes_effect));
}

void Station::stationSchedule(float dt)
{
    if(allHumanId->size()>0)
    {
        if(removeHumanFromStation())
        {
            allHumanId->erase(allHumanId->begin()+0);
            if(allHumanId->size()==0)
            {
                if(AppDelegate::isContainObject(this, nodeHuman))
                    nodeHuman->removeFromParentAndCleanup(true);
            }
        }
    }
}

