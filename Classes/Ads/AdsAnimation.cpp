//
//  AdsAnimation.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 7/4/20.
//

#include "AdsAnimation.h"
#include "AppDelegate.h"
#include "../Ads/AdsZonePanel.h"

static AdsAnimation *sharedInstance=NULL;
AdsAnimation* AdsAnimation::sharedManager()
{
    if(sharedInstance==NULL)
    {
        sharedInstance=AdsAnimation::create();
    }
    return sharedInstance;
}

#pragma mark- Init Method

AdsAnimation::~AdsAnimation()
{
    
}

AdsAnimation::AdsAnimation()
{
    
}

AdsAnimation* AdsAnimation::create()
{
    AdsAnimation* ret = new AdsAnimation();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool AdsAnimation::init()
{
    if(Node::init())
    {
        currentAdsType=-1;
        this->scheduleOnce(schedule_selector(AdsAnimation::loadAds) , TimeGap);

        return true;
    }
    return false;
}

void AdsAnimation::removeFromParentAndCleanup(bool cleanup)
{
    Node::removeFromParentAndCleanup(cleanup);
}

#pragma mark- Ads Animation

void AdsAnimation::loadAdsAnimation()
{
    if(AppDelegate::isContainObject(this, nodeCoinsDoubleFor5Min)==false)
        loadCoinsDoubleFor5Min();
    
    if(AppDelegate::isContainObject(this, nodeCoinsAnimation)==false)
        loadCoinsNode();
}

void AdsAnimation::removeAdsAnimation()
{
    if(AppDelegate::isContainObject(this, nodeCoinsDoubleFor5Min))
        nodeCoinsDoubleFor5Min->removeFromParentAndCleanup(true);
    
    if(AppDelegate::isContainObject(this, nodeCoinsAnimation))
        nodeCoinsAnimation->removeFromParentAndCleanup(true);
}

void AdsAnimation::loadAds(float dt)
{
    if(VideoAdsManager::sharedManager()->isVideoAdsAvailable()==true)
    {
        this->loadAdsAnimation();
        return;
    }
    
    //this->unschedule(schedule_selector(AdsAnimation::loadAds));
    this->scheduleOnce(schedule_selector(AdsAnimation::loadAds) , TimeGap);
}

#pragma mark- Coins Double Animation

void AdsAnimation::loadCoinsDoubleFor5Min()
{
    if(AppDelegate::isContainObject(this, nodeCoinsDoubleFor5Min))
        nodeCoinsDoubleFor5Min->removeFromParentAndCleanup(true);
    
    if(VideoAdsManager::sharedManager()->isVideoAdsAvailable()==false)
        return;
    
    UserDefault *userDefault=UserDefault::getInstance();
    int timeSpent=userDefault->getIntegerForKey(strCoinsDoubleFor5Min.c_str());
    
    int timeLeft=AppDelegate::getTime()-timeSpent;
    if(timeLeft<CoinsDoubleFor5Min)
        return;
    
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    
    nodeCoinsDoubleFor5Min=Node::create();
    this->addChild(nodeCoinsDoubleFor5Min);
    
    MenuItemSprite *btnAdsAnimation=StorePanel::createButton(folderImagesAds+"btn-ads-coins-double.png");
    btnAdsAnimation->setScale(appDelegate->deviceScaleFloat);
    btnAdsAnimation->setCallback(CC_CALLBACK_1(AdsAnimation::coinsDoubleFor5MinCallback, this));
    btnAdsAnimation->setTag(0);
    Menu *menuAdsAnimation=Menu::create(btnAdsAnimation, NULL);
    menuAdsAnimation->alignItemsHorizontallyWithPadding(0*appDelegate->deviceScaleFloat);
    menuAdsAnimation->setPosition(Point(appDelegate->winSize.width - btnAdsAnimation->getScaleX()*btnAdsAnimation->getContentSize().width/2 , appDelegate->winSize.height/2+370*appDelegate->deviceScaleFloat));
    nodeCoinsDoubleFor5Min->addChild(menuAdsAnimation, 1);
}

void AdsAnimation::coinsDoubleFor5MinCallback(cocos2d::Ref *pSender)
{
    currentAdsType=adsTypeCoinsDouble;
    
    VideoAdsManager::sharedManager()->setRunningAdsType(VideoAdsManager::VideoAdsType::VA_AdMob);
    VideoAdsManager::sharedManager()->showVideoAds(this);
}

void AdsAnimation::giveCoinsDoubleFor5MinReward()
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    
    UserDefault *userDefault=UserDefault::getInstance();
    userDefault->setIntegerForKey(strCoinsDoubleFor5Min.c_str(), AppDelegate::getTime());
    
    this->scheduleOnce(schedule_selector(AdsAnimation::loadAds), CoinsDoubleFor5Min);
    
    appDelegate->gnode->setDoubleCoinsFor5Min();
    
    if(AppDelegate::isContainObject(this, nodeCoinsDoubleFor5Min))
        nodeCoinsDoubleFor5Min->removeFromParentAndCleanup(true);
    
    string message="You enable x2 coins reward for 5 min." ;
    AlertView *alert=AlertView::create("Reward???",message,this);
    alert->addButtonWithTitle("OK");
    alert->tag=1;
    alert->show();
}

#pragma mark- Coins

void AdsAnimation::loadCoinsNode()
{
    if(AppDelegate::isContainObject(this, nodeCoinsAnimation))
        nodeCoinsAnimation->removeFromParentAndCleanup(true);
    
    if(VideoAdsManager::sharedManager()->isVideoAdsAvailable()==false)
        return;
    
    UserDefault *userDefault=UserDefault::getInstance();
    int timeSpent=userDefault->getIntegerForKey(strCoinsRewardTime.c_str());
    
    int timeLeft=AppDelegate::getTime()-timeSpent;
    if(timeLeft<CoinsRewardTime)
        return;
    
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    
    nodeCoinsAnimation=Node::create();
    this->addChild(nodeCoinsAnimation);
    
    MenuItemSprite *btnCoins=StorePanel::createButton(folderImagesAds+"btn-adcoin.png");
    btnCoins->setScale(appDelegate->deviceScaleFloat);
    btnCoins->setCallback(CC_CALLBACK_1(AdsAnimation::coinsCallback, this));
    btnCoins->setTag(0);
    Menu *menuCoins=Menu::create(btnCoins, NULL);
    menuCoins->alignItemsHorizontallyWithPadding(0*appDelegate->deviceScaleFloat);
    menuCoins->setPosition(Point(0,0));
    nodeCoinsAnimation->addChild(menuCoins, 1);
    
    SpineObject *spineCoins=SpineObject::create(folderImagesAds+"adcoin", 0.2f);
    btnCoins->addChild(spineCoins,1);
    
    //spineCoins->animationObject->showAnimationNames();
    spineCoins->setPosition(Point(btnCoins->getContentSize().width/2,0));
    spineCoins->startAnimation(animTypeOther);
    
    nodeCoinsAnimation->setPosition(-100*appDelegate->deviceScaleFloat,appDelegate->winSize.height/2+300*appDelegate->deviceScaleFloat);
    
    CCLOG("loadCoinsNode--------5");
    loadCoinsNodeAnimation();
}

void AdsAnimation::loadCoinsNodeAnimation()
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    
    vector<Point> *avaiblePoint=new vector<Point>();
    
    //CCLOG("-------------");
    
    if(nodeCoinsAnimation->getPosition().x<=appDelegate->winSize.width/2 && nodeCoinsAnimation->getPosition().y<=appDelegate->winSize.height/2)
    {
        float posX=nodeCoinsAnimation->getPosition().x+100*appDelegate->deviceScaleFloat+arc4random()%(int)(appDelegate->winSize.width/2);
        float posY=nodeCoinsAnimation->getPosition().y+100*appDelegate->deviceScaleFloat+arc4random()%(int)(appDelegate->winSize.height/2);
        avaiblePoint->push_back(Point(posX,posY));
        
        //CCLOG("nextPoint---1 %f %f",posX,posY);
    }
    if(nodeCoinsAnimation->getPosition().x>=appDelegate->winSize.width/2 && nodeCoinsAnimation->getPosition().y<=appDelegate->winSize.height/2)
    {
        float posX=nodeCoinsAnimation->getPosition().x-100*appDelegate->deviceScaleFloat-arc4random()%(int)(appDelegate->winSize.width/2);
        float posY=nodeCoinsAnimation->getPosition().y+100*appDelegate->deviceScaleFloat+arc4random()%(int)(appDelegate->winSize.height/2);
        avaiblePoint->push_back(Point(posX,posY));
        
        //CCLOG("nextPoint---2 %f %f",posX,posY);
    }
    if(nodeCoinsAnimation->getPosition().x<=appDelegate->winSize.width/2 && nodeCoinsAnimation->getPosition().y>=appDelegate->winSize.height/2)
    {
        float posX=nodeCoinsAnimation->getPosition().x+100*appDelegate->deviceScaleFloat+arc4random()%(int)(appDelegate->winSize.width/2);
        float posY=nodeCoinsAnimation->getPosition().y-100*appDelegate->deviceScaleFloat-arc4random()%(int)(appDelegate->winSize.height/2);
        avaiblePoint->push_back(Point(posX,posY));
        
        //CCLOG("nextPoint---3 %f %f",posX,posY);
    }
    if(nodeCoinsAnimation->getPosition().x>=appDelegate->winSize.width/2 && nodeCoinsAnimation->getPosition().y>=appDelegate->winSize.height/2)
    {
        float posX=nodeCoinsAnimation->getPosition().x-100*appDelegate->deviceScaleFloat-arc4random()%(int)(appDelegate->winSize.width/2);
        float posY=nodeCoinsAnimation->getPosition().y-100*appDelegate->deviceScaleFloat-arc4random()%(int)(appDelegate->winSize.height/2);
        avaiblePoint->push_back(Point(posX,posY));
        
        //CCLOG("nextPoint---4 %f %f",posX,posY);
    }
    
    if(avaiblePoint->size()>0)
    {
        Point nextPoint=avaiblePoint->at(arc4random()%avaiblePoint->size());
        
        float slope=(nextPoint.y-nodeCoinsAnimation->getPosition().y)-(nextPoint.x-nodeCoinsAnimation->getPosition().x);
        if(slope<0)
            slope=slope*(-1);
        //float timeToAnimation=0.02*slope;
        //CCLOG("timeToAnimation %f",timeToAnimation);
        
        MoveTo *moveTo=MoveTo::create(10.0, nextPoint);
        CallFunc *animCoins=CallFunc::create(CC_CALLBACK_0(AdsAnimation::loadCoinsNodeAnimation,this));
        Sequence *sequence=Sequence::create(moveTo,animCoins, NULL);
        nodeCoinsAnimation->runAction(sequence);
    }
}

void AdsAnimation::coinsCallback(cocos2d::Ref *pSender)
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    
    setCoinsValue();
    AdsZonePanel *adsZonePanel=AdsZonePanel::create(adsTypeCoins);
    appDelegate->gHud->addChild(adsZonePanel,10);
}

void AdsAnimation::coinsCallbackFinal()
{
    currentAdsType=adsTypeCoins;
    
    VideoAdsManager::sharedManager()->setRunningAdsType(VideoAdsManager::VideoAdsType::VA_AdMob);
    VideoAdsManager::sharedManager()->showVideoAds(this);
}

vector<string> *AdsAnimation::getCoinsValue()
{
    return arrCoinsReward;
}

void AdsAnimation::setCoinsValue()
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    
    arrCoinsReward=screenData->getCoinsRewards();
    arrCoinsReward=ClickerCalculation::multiplication(arrCoinsReward, ClickerCalculation::getNewVector("60"));
}

void AdsAnimation::giveCoinsReward()
{
    if(AppDelegate::isContainObject(this, nodeCoinsAnimation))
        nodeCoinsAnimation->removeFromParentAndCleanup(true);
    
    Resources *resources=Resources::sharedManager();
    resources->addResource(coinsIndex, arrCoinsReward);
    
    UserDefault *userDefault=UserDefault::getInstance();
    userDefault->setIntegerForKey(strCoinsRewardTime.c_str(), AppDelegate::getTime());
    
    this->scheduleOnce(schedule_selector(AdsAnimation::loadAds), CoinsRewardTime);
    
    if(AppDelegate::isContainObject(this, nodeCoinsAnimation))
        nodeCoinsAnimation->removeFromParentAndCleanup(true);
    
    string message="You get "+ClickerCalculation::getAbbreviationForValue(arrCoinsReward)+" Coins." ;
    AlertView *alert=AlertView::create("Reward???",message,this);
    alert->addButtonWithTitle("OK");
    alert->tag=2;
    alert->show();
}

#pragma mark- Provide Content

void AdsAnimation::provideContentForViewAdd(string identifier)
{
    if(currentAdsType==adsTypeCoinsDouble)
    {
       giveCoinsDoubleFor5MinReward();
    }
    
    this->removeAdsAnimation();
}

#pragma mark- AlertView

void AdsAnimation::alertViewCallBack(int tag,int buttonIndex)
{
    if(tag==1)
    {
    }
    else if(tag==2)
    {
    }
    else if(tag==3)
    {
    }
}

