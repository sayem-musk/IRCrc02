//
//  MUSKScoreBar.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 3/14/20.
//

#include "MUSKScoreBar.h"
#include "AppDelegate.h"
#include "../StoreLayer/StorePanel.h"
#include "../DBClasses/DBLevels.h"

#pragma mark- Init Method

static MUSKScoreBar *sharedInstance=NULL;
MUSKScoreBar* MUSKScoreBar::sharedManager()
{
    if(sharedInstance==NULL)
    {
        sharedInstance=MUSKScoreBar::create();
    }
    return sharedInstance;
}

MUSKScoreBar::~MUSKScoreBar()
{
    
}

MUSKScoreBar::MUSKScoreBar()
{
    
}

MUSKScoreBar* MUSKScoreBar::create()
{
    MUSKScoreBar* ret = new MUSKScoreBar();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool MUSKScoreBar::init()
{
    if(Node::init())
    {
        loadScoreBar();
        this->scheduleOnce(schedule_selector(MUSKScoreBar::loadLevelButton),0.1f);
        return true;
    }
    return false;
}

void MUSKScoreBar::removeFromParentAndCleanup(bool cleanup)
{
    Node::removeFromParentAndCleanup(cleanup);
}

#pragma mark- ScoreBar

void MUSKScoreBar::loadScoreBar()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    
    imgTopBar=Sprite::create(folderImagesStore+"bg-top-hud.png");
    imgTopBar->setScale(appDelegate->winSize.width/imgTopBar->getContentSize().width);
    imgTopBar->setPosition(Point(appDelegate->winSize.width/2,appDelegate->getUIRect().origin.y+appDelegate->getUIRect().size.height-imgTopBar->getScaleY()*imgTopBar->getContentSize().height/2));
    this->addChild(imgTopBar);
    
    Sprite *imgTopBarForNotch=Sprite::create(folderImagesStore+"bg-top-hud.png");
    imgTopBarForNotch->setScale(appDelegate->winSize.width/imgTopBar->getContentSize().width);
    imgTopBarForNotch->setPosition(imgTopBar->getPosition()+ Point(0*appDelegate->deviceScaleFloat,imgTopBar->getScaleY()*imgTopBar->getContentSize().height));
    this->addChild(imgTopBarForNotch);
    
    MenuItemSprite *btnCoins=StorePanel::createButton(folderImagesButton+"btn-score-bar-coin.png");
    btnCoins->setScale(appDelegate->deviceScaleFloat);
    btnCoins->setCallback(CC_CALLBACK_1(MUSKScoreBar::coinsCallBack, this));
    btnCoins->setTag(0);
    Menu *menuCoins=Menu::create(btnCoins, NULL);
    menuCoins->alignItemsHorizontallyWithPadding(0*appDelegate->deviceScaleFloat);
    menuCoins->setPosition(imgTopBar->getPosition()+Point(-35*appDelegate->deviceScaleFloat, 0*appDelegate->deviceScaleFloat));
    this->addChild(menuCoins,10);
    
    Sprite *imgCoins=Sprite::create(folderImagesStore+"score-bar-coin.png");
    imgCoins->setScale(appDelegate->deviceScaleFloat);
    imgCoins->setPosition(menuCoins->getPosition()+Point(-btnCoins->getScaleX()*btnCoins->getContentSize().width/2+imgCoins->getScaleX()*imgCoins->getContentSize().width/2+5*appDelegate->deviceScaleFloat, 0*appDelegate->deviceScaleFloat));
    this->addChild(imgCoins,10);
    
    Resources *resources=Resources::sharedManager();
    DBResourceInfo *resourceInfo=resources->getResourceInfo(coinsIndex);
    
    lblCoins=StorePanel::createLabelWithBold(ClickerCalculation::getAbbreviationForValue(resourceInfo->amount,resourceInfo->amount_exp), 20*appDelegate->deviceScaleFloat);
    lblCoins->setDimensions(imgTopBar->getScaleX()*imgTopBar->getContentSize().width, imgTopBar->getScaleY()*imgTopBar->getContentSize().height);
    //lblCoins->setPosition(imgTopBar->getScaleX()*imgTopBar->getContentSize().width/2, imgTopBar->getScaleY()*imgTopBar->getContentSize().height/2);
    lblCoins->setPosition(menuCoins->getPosition()+Point(5*appDelegate->deviceScaleFloat, 0*appDelegate->deviceScaleFloat));
    lblCoins->setColor(Color3B::BLACK);
    lblCoins->setAlignment(TextHAlignment::CENTER,TextVAlignment::CENTER);
    this->addChild(lblCoins,10);
    
    MenuItemSprite *btnSettings=StorePanel::createButton(folderImagesButton+"btn-settings.png");
    btnSettings->setScale(appDelegate->deviceScaleFloat);
    btnSettings->setCallback(CC_CALLBACK_1(MUSKScoreBar::settingsCallBack, this));
    btnSettings->setTag(0);
    Menu *menuSettings=Menu::create(btnSettings, NULL);
    menuSettings->alignItemsHorizontallyWithPadding(0*appDelegate->deviceScaleFloat);
    menuSettings->setPosition(Point(+40*appDelegate->deviceScaleFloat,appDelegate->getUIRect().origin.y+appDelegate->getUIRect().size.height-imgTopBar->getScaleY()*imgTopBar->getContentSize().height/2));
    this->addChild(menuSettings,10);
}

void MUSKScoreBar::updateScoreBar()
{
    Resources *resources=Resources::sharedManager();
    DBResourceInfo *resourceInfo=resources->getResourceInfo(coinsIndex);
    lblCoins->setString(ClickerCalculation::getAbbreviationForValue(resourceInfo->amount,resourceInfo->amount_exp));
}

void MUSKScoreBar::coinsCallBack(cocos2d::Ref *pSender)
{
    
}

void MUSKScoreBar::settingsCallBack(cocos2d::Ref *pSender)
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    appDelegate->gHud->loadStorePanel(panelSettingsPanel);
}

#pragma mark- Level

void MUSKScoreBar::loadLevelButton(float dt)
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    MenuItemSprite *btnLevel=StorePanel::createButton(folderImagesButton+"btn-level-up.png");
    btnLevel->setScale(appDelegate->deviceScaleFloat);
    btnLevel->setCallback(CC_CALLBACK_1(MUSKScoreBar::levelUpCallBack, this));
    btnLevel->setTag(0);
    menuLevel=Menu::create(btnLevel, NULL);
    menuLevel->alignItemsHorizontallyWithPadding(0*appDelegate->deviceScaleFloat);
    menuLevel->setPosition(Point(appDelegate->winSize.width-btnLevel->getScaleX()*btnLevel->getContentSize().width/2-10*appDelegate->deviceScaleFloat,appDelegate->getUIRect().origin.y+appDelegate->getUIRect().size.height-imgTopBar->getScaleY()*imgTopBar->getContentSize().height/2-0*appDelegate->deviceScaleFloat));
    this->addChild(menuLevel, 1);
    
    Sprite *imgLevelProgressBarBG=Sprite::create(folderImagesStore+"bg-level-progress-bar.png");
    imgLevelProgressBarBG->setScale(appDelegate->deviceScaleFloat);
    imgLevelProgressBarBG->setPosition(menuLevel->getPosition());
    this->addChild(imgLevelProgressBarBG);
    
    progressBarLevel=ProgressTimer::create(Sprite::create(folderImagesStore+"level-progress-bar.png"));
    progressBarLevel->setPosition(Point(imgLevelProgressBarBG->getContentSize().width/2, imgLevelProgressBarBG->getContentSize().height/2));
    progressBarLevel->setAnchorPoint(Point(0.5,0.5));
    progressBarLevel->setType(ProgressTimer::Type::BAR);
    progressBarLevel->setMidpoint(Point(0, 0));
    progressBarLevel->setBarChangeRate(Point(1, 0));
    imgLevelProgressBarBG->addChild(progressBarLevel,0);
    
    DBUserInfo *userInfo=DBUserInfo::sharedManager();
    lblLevel=StorePanel::createLabel("LVL: "+to_string(userInfo->levelid), 16);
    lblLevel->setDimensions(imgLevelProgressBarBG->getContentSize().width, imgLevelProgressBarBG->getContentSize().height);
    lblLevel->setPosition(Point(imgLevelProgressBarBG->getContentSize().width/2, -imgLevelProgressBarBG->getContentSize().height/2-2));
    lblLevel->setColor(Color3B::BLACK);
    lblLevel->setAlignment(TextHAlignment::CENTER,TextVAlignment::CENTER);
    imgLevelProgressBarBG->addChild(lblLevel,1);
    
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    screenData->setLevelUpButton();

    this->setExperiencePrograssBar();
}

void MUSKScoreBar::levelUpCallBack(cocos2d::Ref *pSender)
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    appDelegate->gHud->loadStorePanel(panelLevelUpPanel);
}

void MUSKScoreBar::levelUp()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    
    DBLevels *nextLevel=DBLevels::getLevels(screenData->myScreen->screen_level+1);
    
    if(nextLevel->levelid!=0)
    {
        if(screenData->myScreen->screen_experience==nextLevel->experience)
        {
            screenData->myScreen->screen_level=screenData->myScreen->screen_level+1;
            screenData->myScreen->updateDatabase();
            
            DBUserInfo *userInfo=DBUserInfo::sharedManager();
            userInfo->levelid=userInfo->levelid+1;
            userInfo->updateDatabase();
            
            lblLevel->setString("LVL: "+to_string(userInfo->levelid));

            setExperiencePrograssBar();
            setLevelUpShow(false);
        }
    }
}

void MUSKScoreBar::setExperiencePrograssBar()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    screenData->setLevelUpButton();
    
    DBLevels *currentLevel=DBLevels::getLevels(screenData->myScreen->screen_level);
    DBLevels *nextLevel=DBLevels::getLevels(screenData->myScreen->screen_level+1);
    
    if(nextLevel->levelid!=0)
    {
        float totatExperience=(nextLevel->experience-currentLevel->experience);
        float remainExperience=(screenData->myScreen->screen_experience-currentLevel->experience);
        
        progressBarLevel->setPercentage((remainExperience*100)/totatExperience);
    }
}

void MUSKScoreBar::setLevelUpShow(bool isShow)
{
    menuLevel->setVisible(isShow);
}






