//
//  GameHud.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 3/14/20.
//

#include "GameHud.h"
#include "AppDelegate.h"
#include "../CustomClass/MUSKScoreBar.h"
#include "../StoreLayer/GateAttributes.h"
#include "../StoreLayer/ThemePanel.h"
#include "../StoreLayer/OrnamentsPanel.h"
#include "../StoreLayer/OfflineEarning.h"
#include "../StoreLayer/LevelUpPanel.h"
#include "../StoreLayer/SettingsPanel.h"
#include "../Framework/Firebase/MUSKFirebaseManager.h"

#pragma mark- Init Method

GameHud::~GameHud()
{
    
}

GameHud::GameHud()
{
    
}

GameHud* GameHud::create()
{
    GameHud* ret = new GameHud();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool GameHud::init()
{
    if(Node::init())
    {
        isInterstitialAdLoadCalled=false;
        
        this->addChild(MUSKScoreBar::sharedManager());
        loadLowerButtons();
        loadGateButtons();
        loadThemeButtons();
        loadOrnamentsButtons();
        
        //loadOfflineEarning();
        
        return true;
    }
    return false;
}

void GameHud::removeFromParentAndCleanup(bool cleanup)
{
    Node::removeFromParentAndCleanup(cleanup);
}

void GameHud::loadStorePanel(int panelId)
{
    switch (panelId)
    {
        case panelGateAttributes:
        {
            GateAttributes *gateAttributes=GateAttributes::create();
            this->addChild(gateAttributes,1);
        }
            break;
            
        case panelThemePanel:
        {
            ThemePanel *themePanel=ThemePanel::create();
            this->addChild(themePanel,1);
        }
            break;
        case panelOrnamentsPanel:
        {
            OrnamentsPanel *ornamentsPanel=OrnamentsPanel::create();
            this->addChild(ornamentsPanel,1);
        }
            break;
            
        case panelLevelUpPanel:
        {
            LevelUpPanel *levelUpPanel=LevelUpPanel::create();
            this->addChild(levelUpPanel,1);
        }
            break;
        case panelSettingsPanel:
        {
             SettingsPanel *settingsPanel=SettingsPanel::create();
             this->addChild(settingsPanel,1);
        }
            break;
    }
}

#pragma mark- Lower Buttons

void GameHud::loadLowerButtons()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    
    Size buttonSize=Size(0,0);
    
    menuLowerButton=Menu::create();
    
    string strButtonName=folderImagesButton+"btn-ticket.png";
    int tag=TypeTicketPrice;
    string strName="Ticket";
    int levelid=1;
    //vector<string> *arrBuyPrice=ClickerCalculation::getNewVector("100");
    
    for (int i=0; i<3; i++)
    {
        switch (i)
        {
            case 0:
            {
                strButtonName=folderImagesButton+"btn-bottom.png";
                tag=TypeTicketPrice;
                strName="Revenue";
                levelid=screenData->myScreen->ticket_price_level;
            }
                break;
                
            case 1:
            {
                strButtonName=folderImagesButton+"btn-bottom.png";
                tag=TypeSpeed;
                strName="Speed";
                levelid=screenData->myScreen->speed_level;
            }
                break;
                
            case 2:
            {
                strButtonName=folderImagesButton+"btn-bottom.png";
                tag=TypeCars;
                strName="Chair";
                levelid=screenData->myScreen->cars_level;
            }
                break;
                
            default:
                break;
        }
        
        MenuItemSprite *btnLowerButton=StorePanel::createButton(strButtonName);
        btnLowerButton->setScale(appDelegate->deviceScaleFloat);
        btnLowerButton->setCallback(CC_CALLBACK_1(GameHud::lowerButtonCallBack, this));
        btnLowerButton->setTag(tag);
        btnLowerButton->setName("btnLowerButton-"+to_string(tag));
        
        buttonSize=Size(btnLowerButton->getContentSize().width, btnLowerButton->getContentSize().height) ;
        
        Sprite *imgIcon=Sprite::create(folderImagesIconAttributes+"i-attributes-"+to_string(tag)+".png");
        imgIcon->setScale(45/imgIcon->getContentSize().width);
        imgIcon->setPosition(buttonSize.width/2-60,buttonSize.height/2+25);
        btnLowerButton->addChild(imgIcon);
        
        Label *lblName=StorePanel::createLabelWithBold(strName, 22);
        lblName->setDimensions(buttonSize.width, buttonSize.height);
        lblName->setPosition(buttonSize.width/2+70,buttonSize.height/2+40);
        lblName->setColor(Color3B::BLACK);
        lblName->setAlignment(TextHAlignment::LEFT,TextVAlignment::CENTER);
        btnLowerButton->addChild(lblName);
        
        Label *lblLevel=StorePanel::createLabel("Lv "+to_string(levelid), 16);
        lblLevel->setName("lblLevel");
        lblLevel->setDimensions(buttonSize.width, buttonSize.height);
        lblLevel->setPosition(lblName->getPosition()+Point(10,-22.5));
        lblLevel->setColor(Color3B::BLACK);
        lblLevel->setAlignment(TextHAlignment::LEFT,TextVAlignment::CENTER);
        btnLowerButton->addChild(lblLevel);
        
        /*Sprite *imgCoins=Sprite::create(folderImagesResourcesBar+"r-"+to_string(coinsIndex)+".png");
        imgCoins->setName("imgCoins");
        imgCoins->setScale(40/imgCoins->getContentSize().width);
        imgCoins->setPosition(buttonSize.width/2-30,buttonSize.height/2-30);
        btnLowerButton->addChild(imgCoins);*/
        
        //arrBuyPrice=screenData->getPriceForType(tag);
        //string strBuyPrice=ClickerCalculation::getAbbreviationForValue(arrBuyPrice);
        
        Label *lblBuyPrice=StorePanel::createLabelWithBold("lblBuyPrice", 22);
        lblBuyPrice->setName("lblBuyPrice");
        lblBuyPrice->setDimensions(buttonSize.width, buttonSize.height);
        //lblBuyPrice->setPosition(imgCoins->getPosition()+Point(imgCoins->getScaleX()*imgCoins->getContentSize().width/2+0,0));
        //lblBuyPrice->setPosition(imgCoins->getPosition()+Point(buttonSize.width/2+imgCoins->getScaleX()*imgCoins->getContentSize().width/2+5,0));
        lblBuyPrice->setPosition(Point(buttonSize.width/2+0,buttonSize.height/2-35));
        lblBuyPrice->setColor(Color3B::WHITE);
        lblBuyPrice->setAlignment(TextHAlignment::CENTER,TextVAlignment::CENTER);
        btnLowerButton->addChild(lblBuyPrice);
        
        Label *lblMax=StorePanel::createLabelWithBold("MAX", 22);
        lblMax->setName("lblMax");
        lblMax->setDimensions(buttonSize.width, buttonSize.height);
        lblMax->setPosition(buttonSize.width/2, buttonSize.height/2-35);
        lblMax->setColor(Color3B::WHITE);
        lblMax->setAlignment(TextHAlignment::CENTER,TextVAlignment::CENTER);
        btnLowerButton->addChild(lblMax);
        
        if(i==2)
        {
            Sprite *imgChairBarBG=Sprite::create(folderImagesStore+"bg-cars-progress-bar.png");
            imgChairBarBG->setPosition(buttonSize.width/2, buttonSize.height/2-7);
            btnLowerButton->addChild(imgChairBarBG);
            
            chairBarNode=ProgressTimer::create(Sprite::create(folderImagesStore+"cars-progress-bar.png"));
            chairBarNode->setPosition(Point(imgChairBarBG->getContentSize().width/2, imgChairBarBG->getContentSize().height/2));
            chairBarNode->setAnchorPoint(Point(0.5,0.5));
            chairBarNode->setType(ProgressTimer::Type::BAR);
            chairBarNode->setMidpoint(Point(0, 0));
            chairBarNode->setBarChangeRate(Point(1, 0));
            imgChairBarBG->addChild(chairBarNode,0);
            
            float percentage=((levelid%5)*100)/5;
            if((levelid%5)==0)
                percentage=100;

            chairBarNode->setPercentage(percentage);
            
            buttonSize=Size(btnLowerButton->getScaleX()*btnLowerButton->getContentSize().width, btnLowerButton->getScaleX()*btnLowerButton->getContentSize().height) ;
        }
        
        menuLowerButton->addChild(btnLowerButton);
        
        setButtonInfo(btnLowerButton);
    }
    
    menuLowerButton->alignItemsHorizontallyWithPadding(20*appDelegate->deviceScaleFloat);
    menuLowerButton->setPosition(appDelegate->winSize.width/2,appDelegate->getUIRect().origin.y+buttonSize.height/2+10*appDelegate->deviceScaleFloat);
    this->addChild(menuLowerButton, 1);
}

void GameHud::setButtonInfo(MenuItemSprite *btnLowerButton)
{
    int tag=btnLowerButton->getTag();
    setButtonInfoByTag(tag);
}

void GameHud::setButtonInfoByTag(int tag)
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);

    MenuItemSprite *btnLowerButton=(MenuItemSprite*)menuLowerButton->getChildByName("btnLowerButton-"+to_string(tag));
    
    vector<string> *arrBuyPrice=screenData->getPriceForType(tag);
    
    //Sprite *imgCoins=(Sprite*)btnLowerButton->getChildByName("imgCoins");
    Label *lblBuyPrice=(Label*)btnLowerButton->getChildByName("lblBuyPrice");
    
    Label *lblMax=(Label*)btnLowerButton->getChildByName("lblMax");
    
    if(ClickerCalculation::isNumberZero(arrBuyPrice))
    {
        //imgCoins->setVisible(false);
        lblBuyPrice->setVisible(false);
        lblMax->setVisible(true);
    }
    else
    {
        //imgCoins->setVisible(true);
        lblBuyPrice->setVisible(true);
        lblMax->setVisible(false);
        
        string strBuyPrice=ClickerCalculation::getAbbreviationForValue(arrBuyPrice);
        lblBuyPrice->setString(strBuyPrice);
    }
}

void GameHud::lowerButtonCallBack(cocos2d::Ref *pSender)
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    
    int tag=((MenuItemImage*)pSender)->getTag();
    vector<string> *arrBuyPrice=screenData->getPriceForType(tag);
    if(ClickerCalculation::isNumberZero(arrBuyPrice))
    {
        return;
    }
    
    Resources *resources=Resources::sharedManager();
    
    if(resources->checkResourceAvailable(coinsIndex,arrBuyPrice,false))
    {
        resources->subResource(coinsIndex,arrBuyPrice);
        
        int levelid=1;
        switch (tag)
        {
            case TypeTicketPrice:
            {
                screenData->myScreen->ticket_price_level++;
                levelid=screenData->myScreen->ticket_price_level;
            }
                break;
            case TypeSpeed:
            {
                screenData->myScreen->speed_level++;
                levelid=screenData->myScreen->speed_level;
            }
                break;
            case TypeCars:
            {
                screenData->myScreen->cars_level++;
                levelid=screenData->myScreen->cars_level;
            }
                break;
                
            default:
                break;
        }
        screenData->myScreen->updateDatabase();
        
        MenuItemSprite *btnLowerButton=(MenuItemSprite*)pSender;
        Label *lblLevel=(Label*)btnLowerButton->getChildByName("lblLevel");
        lblLevel->setString("Lv "+to_string(levelid));
        
        setButtonInfo(btnLowerButton);
        
        if(tag==TypeCars)
        {
            appDelegate->gnode->addNewTableChair((int)appDelegate->allChair->size());
            if(levelid%5==0)
              appDelegate->gnode->changeOtherElement();
            float percentage=((levelid%5)*100)/5;
            if((levelid%5)==0)
                percentage=100;
            
            chairBarNode->setPercentage(percentage);
        }
    }
}

#pragma mark- Gate Buttons

void GameHud::loadGateButtons()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    MenuItemSprite *btnGate=StorePanel::createButton(folderImagesButton+"btn-gate.png");
    btnGate->setScale(appDelegate->deviceScaleFloat);
    btnGate->setCallback(CC_CALLBACK_1(GameHud::gateCallBack, this));
    btnGate->setTag(0);
    Menu *menuGate=Menu::create(btnGate, NULL);
    menuGate->alignItemsHorizontallyWithPadding(0*appDelegate->deviceScaleFloat);
    menuGate->setPosition(btnGate->getScaleX()*btnGate->getContentSize().width/2+5*appDelegate->deviceScaleFloat,appDelegate->getUIRect().origin.y+appDelegate->getUIRect().size.height-280*appDelegate->deviceScaleFloat);
    this->addChild(menuGate, 1);
}

void GameHud::gateCallBack(cocos2d::Ref *pSender)
{
    int tag=((MenuItemImage*)pSender)->getTag();
    CCLOG("tag %d",tag);
    
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    appDelegate->gHud->loadStorePanel(panelGateAttributes);
}

#pragma mark- Theme Buttons

void GameHud::loadThemeButtons()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    MenuItemSprite *btnTheme=StorePanel::createButton(folderImagesButton+"btn-theme.png");
    btnTheme->setScale(appDelegate->deviceScaleFloat);
    btnTheme->setCallback(CC_CALLBACK_1(GameHud::themeCallBack, this));
    btnTheme->setTag(0);
    Menu *menuTheme=Menu::create(btnTheme, NULL);
    menuTheme->alignItemsHorizontallyWithPadding(0*appDelegate->deviceScaleFloat);
    menuTheme->setPosition(btnTheme->getScaleX()*btnTheme->getContentSize().width/2+5*appDelegate->deviceScaleFloat,appDelegate->getUIRect().origin.y+appDelegate->getUIRect().size.height-200*appDelegate->deviceScaleFloat);
    this->addChild(menuTheme, 1);
}

void GameHud::themeCallBack(cocos2d::Ref *pSender)
{
    int tag=((MenuItemImage*)pSender)->getTag();
    CCLOG("tag %d",tag);
    
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    appDelegate->gHud->loadStorePanel(panelThemePanel);
}

#pragma mark- Ornaments Buttons

void GameHud::loadOrnamentsButtons()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    MenuItemSprite *btnOrnaments=StorePanel::createButton(folderImagesButton+"btn-ornaments.png");
    btnOrnaments->setScale(appDelegate->deviceScaleFloat);
    btnOrnaments->setCallback(CC_CALLBACK_1(GameHud::ornamentsCallBack, this));
    btnOrnaments->setTag(0);
    Menu *menuOrnaments=Menu::create(btnOrnaments, NULL);
    menuOrnaments->alignItemsHorizontallyWithPadding(0*appDelegate->deviceScaleFloat);
    menuOrnaments->setPosition(btnOrnaments->getScaleX()*btnOrnaments->getContentSize().width/2+5*appDelegate->deviceScaleFloat,appDelegate->getUIRect().origin.y+appDelegate->getUIRect().size.height-360*appDelegate->deviceScaleFloat);
    this->addChild(menuOrnaments, 1);
}

void GameHud::ornamentsCallBack(cocos2d::Ref *pSender)
{
    int tag=((MenuItemImage*)pSender)->getTag();
    CCLOG("tag %d",tag);
    
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    appDelegate->gHud->loadStorePanel(panelOrnamentsPanel);
}


#pragma mark- Offline Earning

void GameHud::loadOfflineEarning()
{
    OfflineEarning *offlineEarning=OfflineEarning::sharedManager();
    //offlineEarning->setStartGame(isStartGame);
    
    if(AppDelegate::isContainObject(this, offlineEarning)==false)
    {
        this->addChild(offlineEarning,1);
        
        //AppDelegate *appDelegate=AppDelegate::sharedApplication();
        
        if(ClickerCalculation::isNumberZero(offlineEarning->totalEarning)==true)
        {
            offlineEarning->removeFromParentAndCleanup(true);
        }
    }
    else
    {
        //offlineEarning->updateOffineEarning();
    }
}

#pragma mark- Show Add

void GameHud::setInterstitialAd()
{
    UserDefault *defaults=UserDefault::getInstance();
    if(defaults->getBoolForKey(noadsInAppComplete.c_str())==false)
    {
        if(isInterstitialAdLoadCalled==false)
        {
            log("isInterstitialAdLoadCalled----");
            VideoAdsManager::sharedManager()->loadAds(VideoAdsManager::VideoAdsType::VA_Admob_Interstitial, Config::sharedManager()->admob_adunit_id_interstitial);
            isInterstitialAdLoadCalled=true;
        }
    }
}

void GameHud::loadInterstitialAdFailed()
{
    UserDefault *defaults=UserDefault::getInstance();
    if(defaults->getBoolForKey(noadsInAppComplete.c_str())==false)
    {
        if(MUSKFirebaseManager::sharedManager()->isInterstitialAdsAvailable()==false)
            isInterstitialAdLoadCalled=false;
    }
}

void GameHud::showInterstitialAd()
{
    if(MUSKFirebaseManager::sharedManager()->isInterstitialAdsAvailable())
    {
        VideoAdsManager::sharedManager()->setRunningAdsType(VideoAdsManager::VideoAdsType::VA_Admob_Interstitial);
        VideoAdsManager::sharedManager()->showVideoAds(this);
        isInterstitialAdLoadCalled=false;
    }
}

void GameHud::provideContentForViewAdd(string identifier)
{
}







