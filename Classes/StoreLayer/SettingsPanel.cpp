//
//  SettingsPanel.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 6/3/20.
//

#include "SettingsPanel.h"
#include "AppDelegate.h"

#pragma mark- Init Method

SettingsPanel::~SettingsPanel()
{
    
}

SettingsPanel::SettingsPanel()
{
    
}

SettingsPanel* SettingsPanel::create()
{
    SettingsPanel* ret = new SettingsPanel();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool SettingsPanel::init()
{
    if(StorePanel::initWithSmallWindow())
    {
        appDelegate->gHud->setInterstitialAd();
        loadBackGroundColor();
        
        this->loadSmallBackground(folderImagesSettingsPanel+"bg-settings.png");
        loadCrossButton();
        btnCross->setPosition(Point(imgBackground->getScaleX()*imgBackground->getContentSize().width/2-btnCross->getScale()*btnCross->getContentSize().width/2-5*appDelegate->deviceScaleFloat,imgBackground->getScaleY()*imgBackground->getContentSize().height/2-btnCross->getScale()*btnCross->getContentSize().height/2-10*appDelegate->deviceScaleFloat));
        
        loadMusicButtons();
        loadVibrationButtons();
        loadInAppButton();
        
        return true;
    }
    return false;
}

void SettingsPanel::removeFromParentAndCleanup(bool cleanup)
{
    appDelegate->gHud->showInterstitialAd();
    Node::removeFromParentAndCleanup(cleanup);
}

#pragma mark- Music

void SettingsPanel::loadMusicButtons()
{
    btnMusic=StorePanel::createButton(folderImagesSettingsPanel+"icon-music-on.png");
    btnMusic->setScale(appDelegate->deviceScaleFloat);
    btnMusic->setCallback(CC_CALLBACK_1(SettingsPanel::musicCallBack, this));
    btnMusic->setTag(0);
    Menu *menuMusic=Menu::create(btnMusic, NULL);
    menuMusic->alignItemsHorizontallyWithPadding(0*appDelegate->deviceScaleFloat);
    menuMusic->setPosition(Point(appDelegate->winSize.width/2-140*appDelegate->deviceScaleFloat,appDelegate->winSize.height/2+40*appDelegate->deviceScaleFloat));
    this->addChild(menuMusic, 1);
    
    setMusicButtonsSprite();
}

void SettingsPanel::setMusicButtonsSprite()
{
    UserDefault *userDefault=UserDefault::getInstance();
    bool soundValue=userDefault->getBoolForKey(strSoundVaule.c_str(),true);
    if(soundValue==false)
    {
        btnMusic->setNormalImage(Sprite::create(folderImagesSettingsPanel+"icon-music-off.png"));
        btnMusic->setSelectedImage(Sprite::create(folderImagesSettingsPanel+"icon-music-off.png"));
    }
    else
    {
        btnMusic->setNormalImage(Sprite::create(folderImagesSettingsPanel+"icon-music-on.png"));
        btnMusic->setSelectedImage(Sprite::create(folderImagesSettingsPanel+"icon-music-on.png"));
    }
}

void SettingsPanel::musicCallBack(cocos2d::Ref *pSender)
{
    UserDefault *userDefault=UserDefault::getInstance();
    bool soundValue=userDefault->getBoolForKey(strSoundVaule.c_str(),true);
    if(soundValue==false)
    {
        userDefault->setBoolForKey(strSoundVaule.c_str(),true);
    }
    else
    {
        userDefault->setBoolForKey(strSoundVaule.c_str(),false);
    }
    
    userDefault->flush();
    
    setMusicButtonsSprite();
    appDelegate->gnode->setMUsicSound();
}

#pragma mark- Vibration

void SettingsPanel::loadVibrationButtons()
{
    btnVibration=StorePanel::createButton(folderImagesSettingsPanel+"icon-vibration-on.png");
    btnVibration->setScale(appDelegate->deviceScaleFloat);
    btnVibration->setCallback(CC_CALLBACK_1(SettingsPanel::vibrationCallBack, this));
    btnVibration->setTag(0);
    Menu *menuVibration=Menu::create(btnVibration, NULL);
    menuVibration->alignItemsHorizontallyWithPadding(0*appDelegate->deviceScaleFloat);
    menuVibration->setPosition(Point(appDelegate->winSize.width/2+120*appDelegate->deviceScaleFloat,appDelegate->winSize.height/2+40*appDelegate->deviceScaleFloat));
    this->addChild(menuVibration, 1);
    
    setVibrationButtonsSprite();
}

void SettingsPanel::setVibrationButtonsSprite()
{
    UserDefault *userDefault=UserDefault::getInstance();
    bool vibrationValue=userDefault->getBoolForKey(strVibrationVaule.c_str(),true);
    if(vibrationValue==false)
    {
        btnVibration->setNormalImage(Sprite::create(folderImagesSettingsPanel+"icon-vibration-off.png"));
        btnVibration->setSelectedImage(Sprite::create(folderImagesSettingsPanel+"icon-vibration-off.png"));
    }
    else
    {
        btnVibration->setNormalImage(Sprite::create(folderImagesSettingsPanel+"icon-vibration-on.png"));
        btnVibration->setSelectedImage(Sprite::create(folderImagesSettingsPanel+"icon-vibration-on.png"));
    }
}

void SettingsPanel::vibrationCallBack(cocos2d::Ref *pSender)
{
    UserDefault *userDefault=UserDefault::getInstance();
    bool vibrationValue=userDefault->getBoolForKey(strVibrationVaule.c_str(),true);
    if(vibrationValue==false)
    {
        userDefault->setBoolForKey(strVibrationVaule.c_str(),true);
    }
    else
    {
        userDefault->setBoolForKey(strVibrationVaule.c_str(),false);
    }
    userDefault->flush();
    
    setVibrationButtonsSprite();
}

#pragma mark- InApp

void SettingsPanel::loadInAppUnitData()
{
    inAppUnit=InAppUnit::getNoAdsInappIds();
    CCLOG("inAppUnit->identifier %s",inAppUnit->identifier.c_str());
}

void SettingsPanel::loadInAppButton()
{
    loadInAppUnitData();
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();

    Sprite *imgInApp=Sprite::create(folderImagesSettingsPanel+"icon-no-ads.png");
    imgInApp->setScale(appDelegate->deviceScaleFloat);
    imgInApp->setPosition(Point(appDelegate->winSize.width/2-50*appDelegate->deviceScaleFloat,appDelegate->winSize.height/2-110*appDelegate->deviceScaleFloat));
    this->addChild(imgInApp);
    
    MenuItemSprite *btnInApp=StorePanel::createButton(folderImagesSettingsPanel+"btn-in-app.png");
    btnInApp->setScale(appDelegate->deviceScaleFloat);
    btnInApp->setCallback(CC_CALLBACK_1(SettingsPanel::inAppCallBack, this));
    btnInApp->setTag(0);
    
    menuInApp=Menu::create(btnInApp, NULL);
    ///menuInApp->alignItemsVerticallyWithPadding(10*appDelegate->deviceScaleFloat);
    menuInApp->setPosition(imgInApp->getPosition()+Point(imgInApp->getScaleX()*imgInApp->getContentSize().width/2 + btnInApp->getScaleX() * btnInApp->getContentSize().width/2 +10*appDelegate->deviceScaleFloat,0*appDelegate->deviceScaleFloat));
    this->addChild(menuInApp, 1);
    
    Sprite *imgRestore=Sprite::create(folderImagesSettingsPanel+"icon-restore.png");
    imgRestore->setScale(appDelegate->deviceScaleFloat);
    imgRestore->setPosition(Point(imgInApp->getPosition().x,imgInApp->getPosition().y-imgInApp->getScaleY()*imgInApp->getContentSize().height/2-20*appDelegate->deviceScaleFloat));
    this->addChild(imgRestore);
    
    MenuItemSprite *btnRestore=StorePanel::createButton(folderImagesSettingsPanel+"btn-in-app-restore.png");
    btnRestore->setScale(appDelegate->deviceScaleFloat);
    btnRestore->setCallback(CC_CALLBACK_1(SettingsPanel::restoreCallBack, this));
    btnRestore->setTag(0);
    
    menuRestore=Menu::create(btnRestore, NULL);
    //menuRestore->alignItemsVerticallyWithPadding(10*appDelegate->deviceScaleFloat);
    menuRestore->setPosition(Point(imgRestore->getPosition() + Point(imgRestore->getScaleX()*imgRestore->getContentSize().width/2 + btnRestore->getScaleX() * btnRestore->getContentSize().width/2 + 10*appDelegate->deviceScaleFloat,0*appDelegate->deviceScaleFloat)));
    this->addChild(menuRestore, 1);
}

void SettingsPanel::loadForInApp()
{
    UserDefault *defaults=UserDefault::getInstance();
    if(defaults->getBoolForKey(noadsInAppComplete.c_str())==true)
    {
        menuInApp->setVisible(false);
        menuRestore->setVisible(false);
    }
    
}

void SettingsPanel::inAppCallBack(cocos2d::Ref *pSender)
{
    InAppController::sharedManager()->delegate=this;
    InAppController::sharedManager()->startPurchase(inAppUnit->identifier);
    //provideContent(inAppUnit->identifier);
}

void SettingsPanel::restoreCallBack(cocos2d::Ref *pSender)
{
    InAppController::sharedManager()->delegate=this;
    InAppController::sharedManager()->restorePurchase(inAppUnit->identifier);
}

#pragma mark- Provide Content

void SettingsPanel::provideContent(string identifier)
{
    UserDefault *defaults=UserDefault::getInstance();
    
    defaults->setBoolForKey(noadsInAppComplete.c_str(), true);
    defaults->flush();
    
    loadForInApp();
}
