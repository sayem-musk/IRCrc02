//
//  OfflineEarning.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 5/9/20.
//

#include "OfflineEarning.h"
#include "AppDelegate.h"

static OfflineEarning *sharedInstance=NULL;
OfflineEarning* OfflineEarning::sharedManager()
{
    if(sharedInstance==NULL)
    {
        sharedInstance=OfflineEarning::create();
    }
    return sharedInstance;
}


#pragma mark- Init Method

OfflineEarning::~OfflineEarning()
{
    
}

OfflineEarning::OfflineEarning()
{
    
}

OfflineEarning* OfflineEarning::create()
{
    OfflineEarning* ret = new OfflineEarning();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool OfflineEarning::init()
{
    if(StorePanel::initWithSmallWindow())
    {
        loadBackGroundColor();
        
        totalEarning=new vector<string>();
        
        this->loadSmallBackground(folderImagesOfflineEarning+"bg-offline-earning.png");
        loadCrossButton();
        btnCross->setPosition(Point(imgBackground->getScaleX()*imgBackground->getContentSize().width/2-btnCross->getScale()*btnCross->getContentSize().width/2-5*appDelegate->deviceScaleFloat,imgBackground->getScaleY()*imgBackground->getContentSize().height/2-btnCross->getScale()*btnCross->getContentSize().height/2-10*appDelegate->deviceScaleFloat));
        
        this->getTotalOfflineEarning();
        if(ClickerCalculation::isNumberZero(this->totalEarning)==false)
            this->loadTotalCoin();
        
        return true;
    }
    return false;
}

void OfflineEarning::removeFromParentAndCleanup(bool cleanup)
{
    this->acceptReward();
    Node::removeFromParentAndCleanup(cleanup);
}

#pragma mark- Total Earning

void OfflineEarning::getTotalOfflineEarning()
{
    this->totalEarning=ClickerCalculation::getNewVector("0", "0");
    
    UserDefault *userDefault=UserDefault::getInstance();
    
    int lastTimePlay=userDefault->getIntegerForKey(strLastTimePlay.c_str(),0);
    if(lastTimePlay==0)
    {
        //appDelegate->zoneNode->startLastTimePlay();
    }
    else
    {
        int currentTime=AppDelegate::getTime();
        int timeSpent=MIN(currentTime-lastTimePlay, 6*30*60*60);
        
        AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
        ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
        
        vector<string> *earnPerSec=screenData->getCoinsRewards();
        this->totalEarning=ClickerCalculation::multiplication(earnPerSec, ClickerCalculation::getNewVector(to_string(timeSpent)));
    }
    
    appDelegate->gnode->startLastTimePlay();
}

void OfflineEarning::loadTotalCoin()
{
    Sprite *imgCoins=Sprite::create(folderImagesResourcesBar+"r-"+to_string(coinsIndex)+".png");
    imgCoins->setScale(appDelegate->deviceScaleFloat);
    //imgCoins->setPosition(lblTotalCoin->getPosition()+Point(-60*appDelegate->deviceScaleFloat,-80*appDelegate->deviceScaleFloat));
    this->addChild(imgCoins);
    
    lblCoins=StorePanel::createLabel(ClickerCalculation::getAbbreviationForValue(this->totalEarning), 50*appDelegate->deviceScaleFloat);
    //lblCoins->setDimensions(500*appDelegate->deviceScaleFloat, 500*appDelegate->deviceScaleFloat);
    //lblCoins->setPosition(imgCoins->getPosition()+Point(lblCoins->getScaleX()*lblCoins->getContentSize().width/2+imgCoins->getScaleX()*imgCoins->getContentSize().width/2+0*appDelegate->deviceScaleFloat,0*appDelegate->deviceScaleFloat));
    lblCoins->setColor(Color3B::BLACK);
    lblCoins->setAlignment(TextHAlignment::LEFT,TextVAlignment::CENTER);
    this->addChild(lblCoins);
    
    imgCoins->setPosition(Point(appDelegate->winSize.width/2,appDelegate->winSize.height/2)+Point(-this->lblCoins->getContentSize().width/2-5*appDelegate->deviceScaleFloat,-150*appDelegate->deviceScaleFloat));
    
    this->lblCoins->setPosition(imgCoins->getPosition()+Point(this->lblCoins->getContentSize().width/2+imgCoins->getScaleX()*imgCoins->getContentSize().width/2+5*appDelegate->deviceScaleFloat,0));
    
    MenuItemSprite *btnAccept=StorePanel::createButton(folderImagesOfflineEarning+"btn-offline-earning-collect.png");
    btnAccept->setScale(appDelegate->deviceScaleFloat);
    btnAccept->setCallback(CC_CALLBACK_1(OfflineEarning::acceptCallBack, this));
    btnAccept->setTag(0);
    Menu *menuAccept=Menu::create(btnAccept, NULL);
    menuAccept->alignItemsHorizontallyWithPadding(0*appDelegate->deviceScaleFloat);
    menuAccept->setPosition(Point(appDelegate->winSize.width/2,appDelegate->winSize.height/2-250*appDelegate->deviceScaleFloat));
    this->addChild(menuAccept, 1);
}

void OfflineEarning::acceptCallBack(cocos2d::Ref *pSender)
{
    VideoAdsManager::sharedManager()->setRunningAdsType(VideoAdsManager::VideoAdsType::VA_AdMob);
    VideoAdsManager::sharedManager()->showVideoAds(this);
}

void OfflineEarning::acceptReward()
{
    Resources *resources=Resources::sharedManager();
    resources->addResource(coinsIndex, this->totalEarning);
}

void OfflineEarning::provideContentForViewAdd(string identifier)
{
    this->totalEarning=ClickerCalculation::multiplication(this->totalEarning, ClickerCalculation::getNewVector("3"));
    
    this->removeFromParentAndCleanup(true);
}




