//
//  LevelUpPanel.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 6/2/20.
//

#include "LevelUpPanel.h"
#include "AppDelegate.h"
#include "../DBClasses/DBLevels.h"

#pragma mark- Init Method

LevelUpPanel::~LevelUpPanel()
{
    
}

LevelUpPanel::LevelUpPanel()
{
    
}

LevelUpPanel* LevelUpPanel::create()
{
    LevelUpPanel* ret = new LevelUpPanel();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool LevelUpPanel::init()
{
     if(StorePanel::initWithSmallWindow())
    {
        appDelegate->gHud->setInterstitialAd();
        
        loadBackGroundColor();
        
        loadSmallBackground(folderImagesLevelUpPanel+"bg-level-up.png");
        loadCrossButton();
        btnCross->setPosition(Point(imgBackground->getScaleX()*imgBackground->getContentSize().width/2-btnCross->getScale()*btnCross->getContentSize().width/2-5*appDelegate->deviceScaleFloat,imgBackground->getScaleY()*imgBackground->getContentSize().height/2-btnCross->getScale()*btnCross->getContentSize().height/2-10*appDelegate->deviceScaleFloat));
        
        this->loadTotalCoin();
        
        return true;
    }
    return false;
}

void LevelUpPanel::removeFromParentAndCleanup(bool cleanup)
{
    appDelegate->gHud->showInterstitialAd();
    this->acceptReward();
    Node::removeFromParentAndCleanup(cleanup);
    MUSKScoreBar::sharedManager()->levelUp();
}

void LevelUpPanel::loadTotalCoin()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    
    DBLevels *currentLevel=DBLevels::getLevels(screenData->myScreen->screen_level);
    totalEarning=ClickerCalculation::getNewVector(currentLevel->rewards, "0");
    
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
    
    MenuItemSprite *btnAccept=StorePanel::createButton(folderImagesLevelUpPanel+"btn-level-up.png");
    btnAccept->setScale(appDelegate->deviceScaleFloat);
    btnAccept->setCallback(CC_CALLBACK_1(LevelUpPanel::acceptCallBack, this));
    btnAccept->setTag(0);
    Menu *menuAccept=Menu::create(btnAccept, NULL);
    menuAccept->alignItemsHorizontallyWithPadding(0*appDelegate->deviceScaleFloat);
    menuAccept->setPosition(Point(appDelegate->winSize.width/2,appDelegate->winSize.height/2-250*appDelegate->deviceScaleFloat));
    this->addChild(menuAccept, 1);
}

void LevelUpPanel::acceptCallBack(cocos2d::Ref *pSender)
{
    //int tag=((MenuItemImage*)pSender)->getTag();
    VideoAdsManager::sharedManager()->setRunningAdsType(VideoAdsManager::VideoAdsType::VA_AdMob);
    VideoAdsManager::sharedManager()->showVideoAds(this);
}

void LevelUpPanel::acceptReward()
{
    Resources *resources=Resources::sharedManager();
    resources->addResource(coinsIndex, this->totalEarning);
}

void LevelUpPanel::provideContentForViewAdd(string identifier)
{
    this->totalEarning=ClickerCalculation::multiplication(this->totalEarning, ClickerCalculation::getNewVector("3"));
    
    this->removeFromParentAndCleanup(true);
}
