//
//  GameNode.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 3/14/20.
//

#include "GameNode.h"
#include "AppDelegate.h"
#include "../StoreLayer/StorePanel.h"
#include "../DBClasses/DBAttributesInfo.h"
#include "../GameLayer/Station.h"
#include "../GameLayer/Ornaments.h"
#include "../Framework/Ads/VideoAdsManager.h"
#include "../Ads/AdsAnimation.h"


Scene* GameNode::createScene()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    
    Scene *mainScene=Scene::create();
    
    Size winSize=Director::getInstance()->getWinSize();
    
    LayerColor *skyColor=LayerColor::create(Color4B(135.0f,206.0f,250.0f,255.0f), winSize.width, winSize.height);
    mainScene->addChild(skyColor);
    
    /*Sprite *imgStageBackground=Sprite::create(folderImagesStage+"stage-background.png");
    imgStageBackground->setScale(winSize.width/imgStageBackground->getContentSize().width,winSize.height/imgStageBackground->getContentSize().height);
    imgStageBackground->setPosition(Point(imgStageBackground->getScaleX()*imgStageBackground->getContentSize().width/2, imgStageBackground->getScaleY()*imgStageBackground->getContentSize().height/2));
    mainScene->addChild(imgStageBackground);*/
    
    GameHud *gameHud=GameHud::create();
    appDelegate->gHud=gameHud;
    mainScene->addChild(gameHud,2);
    
    GameNode *gameNode = GameNode::create();
    appDelegate->gnode=gameNode;
    mainScene->addChild(gameNode);
    
    //appDelegate->gHud->startGoal();
    
    return mainScene;
}

#pragma mark- Init Method

GameNode::~GameNode()
{
    
}

GameNode::GameNode()
{
    
}

GameNode* GameNode::create()
{
    GameNode* ret = new GameNode();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool GameNode::init()
{
    if(Node::init())
    {
        VideoAdsManager::sharedManager();
        
        allHuman=new vector<Human*>();
        allChairToFinish=new vector<int>();
        allWaiter=new vector<Waiter*>();
        
        this->scheduleOnce(schedule_selector(GameNode::callAfterTime),0.2f);
        this->scheduleOnce(schedule_selector(GameNode::callAfterTimeForAds),1.2f);
        playBackgroundMusic();
        
        this->doubleCoinsFor5MinTime=-1;
        this->loadDoubleCoinsFor5Min();
        
        return true;
    }
    return false;
}

void GameNode::removeFromParentAndCleanup(bool cleanup)
{
    Node::removeFromParentAndCleanup(cleanup);
}

#pragma mark- Call After Time

void GameNode::callAfterTime(float dt)
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    
    strStageFolder=folderImagesStage+"Stage-"+to_string(screenData->screenInfo->screen_id)+"/";
    
    this->addChild(AdsAnimation::sharedManager(),30);
    
    loadStage();
    loadOtherStageElement();
    loadTableChair();
    loadHuman();
    loadHumanExit();
    setWaiter();
    
    this->addChild(Ornaments::sharedManager(),5);
    
    setTouchEnable();
}

void GameNode::callAfterTimeForAds(float dt)
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    appDelegate->gHud->loadOfflineEarning();
}

#pragma mark- Load Stage

void GameNode::loadStage()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    
    imgStageBackground=Sprite::create(strStageFolder+"stage-background.png");
    imgStageBackground->setScale(appDelegate->winSize.width/imgStageBackground->getContentSize().width,appDelegate->winSize.height/imgStageBackground->getContentSize().height);
    //imgStageBackground->setScale(appDelegate->deviceScaleFloat);
    imgStageBackground->setPosition(Point(appDelegate->winSize.width/2, imgStageBackground->getScaleY()*imgStageBackground->getContentSize().height/2));
    //imgStageBackground->setPosition(Point(appDelegate->winSize.width/2, appDelegate->winSize.height/2));
    this->addChild(imgStageBackground);
    
    Sprite *imgLeftFence=Sprite::create(strStageFolder+"fence-left.png");
    imgLeftFence->setScale(appDelegate->winSize.width/imgLeftFence->getContentSize().width,appDelegate->winSize.height/imgLeftFence->getContentSize().height);
    //imgLeftFence->setScale(appDelegate->deviceScaleFloat);
    imgLeftFence->setPosition(imgStageBackground->getPosition());
    this->addChild(imgLeftFence,10);
    
    Sprite *imgRightFence=Sprite::create(strStageFolder+"fence-right.png");
    imgRightFence->setScale(appDelegate->winSize.width/imgRightFence->getContentSize().width,appDelegate->winSize.height/imgRightFence->getContentSize().height);
    //imgRightFence->setScale(appDelegate->deviceScaleFloat);
    imgRightFence->setPosition(imgStageBackground->getPosition());
    this->addChild(imgRightFence,10);
}

void GameNode::loadOtherStageElement()
{
    if(AppDelegate::isContainObject(this, imgGate))
    {
        imgGate->removeFromParentAndCleanup(true);
    }
    
    if(AppDelegate::isContainObject(this, imgTruck))
    {
        imgTruck->removeFromParentAndCleanup(true);
    }
    
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    
    this->addChild(Station::sharedManager(),19);
    
    int carIndex=1+screenData->myScreen->cars_level/5;
    
    imgTruck=Sprite::create(strStageFolder+"truck-"+to_string(carIndex)+".png");
    imgTruck->setScale(appDelegate->deviceScaleFloat);
    imgTruck->setPosition(appDelegate->winSize.width/2+5*imgStageBackground->getScaleX(),appDelegate->winSize.height/2+230*imgStageBackground->getScaleY());
    this->addChild(imgTruck,5);
}

void GameNode::changeOtherElement()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    
    int carIndex=1+screenData->myScreen->cars_level/5;
    imgTruck->setTexture(strStageFolder+"truck-"+to_string(carIndex)+".png");
}

#pragma mark- Load Cars

void GameNode::removeAllTableChair()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    
    for(int i=0;i<arrTableSprite->size();i++)
    {
        arrTableSprite->at(i)->removeFromParentAndCleanup(true);
    }
    arrTableSprite->clear();
    
    for(int i=0;i<appDelegate->allChair->size();i++)
    {
        appDelegate->allChair->at(i)->removeFromParentAndCleanup(true);
    }
    appDelegate->allChair->clear();
}

void GameNode::loadTableChair()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    
    arrTableSprite=new vector<Sprite*>();
    
    for (int i=0; i<screenData->myScreen->cars_level; i++)
    {
        addNewTableChair(i);
    }
}

void GameNode::loadTableSprite()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    Point tablePosition=Point(appDelegate->winSize.width/2,appDelegate->winSize.height/2);
    switch (arrTableSprite->size()) {
        case 0:
            tablePosition=Point(appDelegate->winSize.width/2-60*imgStageBackground->getScaleX(),appDelegate->winSize.height/2+110*imgStageBackground->getScaleY());
            break;
            
        case 1:
            tablePosition=Point(appDelegate->winSize.width/2-230*imgStageBackground->getScaleX(),appDelegate->winSize.height/2+0*imgStageBackground->getScaleY());
            break;
            
        case 2:
            tablePosition=Point(appDelegate->winSize.width/2+130*imgStageBackground->getScaleX(),appDelegate->winSize.height/2+80*imgStageBackground->getScaleY());
            break;
            
        case 3:
            tablePosition=Point(appDelegate->winSize.width/2-0*imgStageBackground->getScaleX(),appDelegate->winSize.height/2-20*imgStageBackground->getScaleY());
            break;
            
        case 4:
            tablePosition=Point(appDelegate->winSize.width/2-140*imgStageBackground->getScaleX(),appDelegate->winSize.height/2-110*imgStageBackground->getScaleY());
            break;
            
        default:
            break;
    }
    
    Sprite *imgTable=Sprite::create(folderImagesTableChair+"table.png");
    imgTable->setScale(appDelegate->deviceScaleFloat);
    imgTable->setPosition(tablePosition);
    this->addChild(imgTable,10);
    
    arrTableSprite->push_back(imgTable);
}

Sprite *GameNode::getTableSprite(int tableIndex)
{
    return arrTableSprite->at(tableIndex);
}

void GameNode::addNewTableChair(int chairIndex)
{
    if(chairIndex%NoChairInTable==0)
    {
        loadTableSprite();
    }
    
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    //CCLOG("chairIndex %d",chairIndex);
    
    Chair *chair=Chair::create(chairIndex);
    this->addChild(chair,10);
    appDelegate->allChair->push_back(chair);
    setWaiter();
}


#pragma mark- Human

void GameNode::loadHuman()
{
    allHuman->clear();
    setHumanSchedule();
}

void GameNode::setHumanSchedule()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    
    DBAttributesInfo *attributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(TypeSpeed,screenData->myScreen->speed_level);
    
    this->unschedule(schedule_selector(GameNode::humanSchedule));
    float scheduleTime=stof(attributesInfo->attributes_effect);
    
    DBAttributesInfo *airshipAttributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(TypeAirShip,screenData->myScreen->airship_level);
    
    if(airshipAttributesInfo->attributes_id!=0)
    {
        float effect=stof(airshipAttributesInfo->attributes_effect);
        scheduleTime=scheduleTime-(scheduleTime*effect)/100.0f;
    }
    
    this->schedule(schedule_selector(GameNode::humanSchedule),scheduleTime);
}

void GameNode::humanSchedule(float dt)
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    
    DBAttributesInfo *queueAttributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(TypeQueueCapacity,screenData->myScreen->queue_capacity_level);
    int totalQueue=stoi(queueAttributesInfo->attributes_effect);
    
    DBAttributesInfo *balloonsAttributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(TypeBalloons,screenData->myScreen->balloons_level);
    
    if(balloonsAttributesInfo->attributes_id!=0)
        totalQueue=totalQueue+stoi(balloonsAttributesInfo->attributes_effect);
    
    if(allHuman->size()<totalQueue)
    {
        Human *human=Human::create((int)allHuman->size());
        this->addChild(human,20);
        
        allHuman->push_back(human);
    }
}

void GameNode::removeHumanFromQueue()
{
    Human *human=allHuman->at(0);
    human->removeFromParentAndCleanup(true);
    allHuman->erase(allHuman->begin()+0);
    
    updateObjectAtIndexHuman();
}

void GameNode::updateObjectAtIndexHuman()
{
    for(int i=0;i<allHuman->size();i++)
    {
        Human *human=allHuman->at(i);
        human->updateObjectAtIndex(i);
    }
}

#pragma mark- HumanExit

void GameNode::setChairToFinish(int chairIndex)
{
    allChairToFinish->push_back(chairIndex);
}

void GameNode::loadHumanExit()
{
    setHumanExitSchedule();
}

void GameNode::setHumanExitSchedule()
{
   // AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    //ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    
    //DBAttributesInfo *attributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(TypeSpeed,screenData->myScreen->speed_level);
    
    this->unschedule(schedule_selector(GameNode::humanExitSchedule));
    this->schedule(schedule_selector(GameNode::humanExitSchedule),2.0f);
}

void GameNode::humanExitSchedule(float dt)
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    //ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    
    if(allChairToFinish->size()>0)
    {
        Chair *chair=appDelegate->allChair->at(allChairToFinish->at(0));
        chair->setFinishEating();
        
        allChairToFinish->erase(allChairToFinish->begin()+0);
    }
}

#pragma mark- Touch

void GameNode::setTouchEnable()
{
    EventListenerTouchOneByOne *touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(GameNode::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameNode::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameNode::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameNode::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool GameNode::onTouchBegan(Touch *touch, Event *event)
{
    Point touchLocation = this->convertTouchToNodeSpace(touch);
    CCLOG("touchLocation %f %f",touchLocation.x,touchLocation.y);
    
    UserDefault *userDefault=UserDefault::getInstance();
    bool vibrationValue=userDefault->getBoolForKey(strVibrationVaule.c_str(),true);
    if(vibrationValue==true)
    {
        Device::vibrate(0.005f);
    }
    
    return true;
}

void GameNode::onTouchMoved(Touch *touch, Event *event)
{
  
}

void GameNode::onTouchEnded(Touch *touch, Event *event)
{
    //AppDelegate *appDelegate=AppDelegate::sharedApplication();
    Point location=touch->getLocation();    
    CCLOG("location x %d y %d",(int)location.x,(int)location.y);
}

void GameNode::onTouchCancelled(Touch *touch, Event *event)
{
}

#pragma mark- Last Time Play

void GameNode::startLastTimePlay()
{
    this->lastTimePlay(0.0f);
    this->unschedule(schedule_selector(GameNode::lastTimePlay));
    this->schedule(schedule_selector(GameNode::lastTimePlay) , 20.0);
}

void GameNode::lastTimePlay(float dt)
{
    int currentTime=AppDelegate::getTime();
    UserDefault *userDefault=UserDefault::getInstance();
    userDefault->setIntegerForKey(strLastTimePlay.c_str(), currentTime);
}


#pragma mark- Music

void GameNode::playBackgroundMusic()
{
    SimpleAudioEngine::getInstance()->playBackgroundMusic((folderSound+"background-music.mp3").c_str(),true);
    setMUsicSound();
}

void GameNode::stopBackgroundMusic()
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void GameNode::setMUsicSound()
{
    UserDefault *userDefault=UserDefault::getInstance();
    bool soundValue=userDefault->getBoolForKey(strSoundVaule.c_str(),true);
    if(soundValue==false)
    {
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);
        SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
    }
    else
    {
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(100.0f);
        SimpleAudioEngine::getInstance()->setEffectsVolume(100.0f);
    }
}

#pragma mark- DoubleCoinsFor5Min

void GameNode::loadDoubleCoinsFor5Min()
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    
    UserDefault *userDefault=UserDefault::getInstance();
    int time_stamp=userDefault->getIntegerForKey(strCoinsDoubleFor5Min.c_str());
    
    vector<string> *arrTotalTime=ClickerCalculation::getNewVector(to_string(CoinsDoubleFor5Min));
    int totalTime=stoi(arrTotalTime->at(0));
    
    int currentTime=AppDelegate::getTime();
    this->doubleCoinsFor5MinTime=totalTime-(currentTime-time_stamp);
    
    if(this->doubleCoinsFor5MinTime>=0)
    {
        if(AppDelegate::isContainObject(this, imgDoubleCoinsFor5Min)==false)
        {
            imgDoubleCoinsFor5Min=Sprite::create(folderImagesAds+"bg-ads-coins-double.png");
            imgDoubleCoinsFor5Min->setScale(appDelegate->deviceScaleFloat);
            this->addChild(imgDoubleCoinsFor5Min,2);
            
            lblDoubleCoinsFor5Min=StorePanel::createLabel(StorePanel::convertTimeToString(this->doubleCoinsFor5MinTime), 24);
            lblDoubleCoinsFor5Min->setPosition(Point(this->imgDoubleCoinsFor5Min->getContentSize().width/2,this->imgDoubleCoinsFor5Min->getContentSize().height/2));
            lblDoubleCoinsFor5Min->setColor(Color3B::BLACK);
            lblDoubleCoinsFor5Min->setAlignment(TextHAlignment::CENTER,TextVAlignment::CENTER);
            this->imgDoubleCoinsFor5Min->addChild(lblDoubleCoinsFor5Min,2);
            
            imgDoubleCoinsFor5Min->setPosition(Point(appDelegate->winSize.width - imgDoubleCoinsFor5Min->getScaleX()*imgDoubleCoinsFor5Min->getContentSize().width/2 , appDelegate->winSize.height/2+370*appDelegate->deviceScaleFloat));
        }
        
        this->unschedule(schedule_selector(GameNode::doubleCoinsFor5MinSchudule));
        this->schedule(schedule_selector(GameNode::doubleCoinsFor5MinSchudule) , 1.0f);
    }
}

void GameNode::setDoubleCoinsFor5Min()
{
    this->loadDoubleCoinsFor5Min();
}

void GameNode::doubleCoinsFor5MinSchudule(float dt)
{
    this->doubleCoinsFor5MinTime--;
    this->lblDoubleCoinsFor5Min->setString(StorePanel::convertTimeToString(this->doubleCoinsFor5MinTime));
    if(this->doubleCoinsFor5MinTime==0)
    {
        if(AppDelegate::isContainObject(this, imgDoubleCoinsFor5Min))
        {
            this->lblDoubleCoinsFor5Min->removeFromParentAndCleanup(true);
            this->imgDoubleCoinsFor5Min->removeFromParentAndCleanup(true);
        }
        this->unschedule(schedule_selector(GameNode::doubleCoinsFor5MinSchudule));
    }
}

#pragma mark- Waiter

void GameNode::setWaiter()
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    totalWaiterCount = 1;
    if(appDelegate->allChair->size() >=5 && appDelegate->allChair->size()<16)
    {
        totalWaiterCount = 2;
    }
    else if(appDelegate->allChair->size()>=16)
    {
        totalWaiterCount = 3;
    }
    loadWaiter();
}

void GameNode::loadWaiter()
{
    for (int i=(int)allWaiter->size(); i<totalWaiterCount ; i++)
    {
        int waiterId=5001;
        if(allWaiter->size()%2==0)
            waiterId=5002;
        
        loadWaiter(waiterId);
    }
}

void GameNode::loadWaiter(int waiterId)
{
    Waiter *waiter=Waiter::create((int)allWaiter->size(),waiterId);
    this->addChild(waiter,20);

    allWaiter->push_back(waiter);
}
