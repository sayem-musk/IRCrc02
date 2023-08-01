//
//  AdsZonePanel.cpp
//  TapStar-mobile
//
//  Created by Tarek Saazeb on 12/12/19.
//

#include "AdsZonePanel.h"
#include "AppDelegate.h"
#include "../Ads/AdsAnimation.h"
#include "../CustomClass/ClickerCalculation.h"

#pragma mark- Init Method

AdsZonePanel::~AdsZonePanel()
{
    
}

AdsZonePanel::AdsZonePanel()
{
    
}

AdsZonePanel* AdsZonePanel::create(int _adType)
{
    AdsZonePanel* ret = new AdsZonePanel();
    if(ret && ret->init(_adType)) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool AdsZonePanel::init(int _adType)
{
    if(StorePanel::initWithSmallWindow())
    {
        adType=_adType;
        
        loadSmallBackground(folderImagesAds+"bg-ad-panel.png");
        /*loadCrossButton();
        btnCross->setPosition(Point(appDelegate->winSize.width/2-btnCross->getScale()*btnCross->getContentSize().width/2-5*appDelegate->deviceScaleFloat,this->imgBackground->getContentSize().height/2+btnCross->getScale()*btnCross->getContentSize().height/2+5*appDelegate->deviceScaleFloat));*/
        
        string strResource=folderImagesAds+"ad-panel-gold-icon.png";
        if(adType==adsTypeCoins)
            strResource=folderImagesAds+"ad-panel-gold-icon.png";
        else if(adType==adsTypeGems)
            strResource=folderImagesAds+"ad-panel-gem-icon.png";
    
        Sprite *imgResource=Sprite::create(strResource);
        imgResource->setScale(appDelegate->deviceScaleFloat);
        imgResource->setPosition(appDelegate->winSize.width/2,appDelegate->winSize.height/2+50*appDelegate->deviceScaleFloat);
        this->addChild(imgResource);
        
        vector<string> *arrGetRewardData=new vector<string>();
        int resourceIndex=coinsIndex;
        
        if(adType==adsTypeCoins)
        {
            arrGetRewardData=AdsAnimation::sharedManager()->getCoinsValue();
            resourceIndex=coinsIndex;
        }
        else if(adType==adsTypeGems)
        {
            //arrGetRewardData=ClickerCalculation::getNewVector(to_string(AdsAnimation::sharedManager()->getBucksValue()),"0");
            //resourceIndex=bucksIndex;
        }
        
        Node *nodeScore=this->loadResourceNodeForScore(resourceIndex,arrGetRewardData);
        nodeScore->setPosition(appDelegate->winSize.width/2,appDelegate->winSize.height/2-150*appDelegate->deviceScaleFloat);
        this->addChild(nodeScore);
        
        loadAllButtons();
        
        return true;
    }
    return false;
}

void AdsZonePanel::removeFromParentAndCleanup(bool cleanup)
{
    StorePanel::removeFromParentAndCleanup(cleanup);
}

void AdsZonePanel::loadAllButtons()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    MenuItemSprite *btnCancel=StorePanel::createButton(folderImagesAds+"btn-cancel-ad.png");
    btnCancel->setScale(appDelegate->deviceScaleFloat);
    btnCancel->setCallback(CC_CALLBACK_1(AdsZonePanel::cancelCallBack, this));
    btnCancel->setTag(0);
    
    MenuItemSprite *btnWatch=StorePanel::createButton(folderImagesAds+"btn-watch-ad.png");
    btnWatch->setScale(appDelegate->deviceScaleFloat);
    btnWatch->setCallback(CC_CALLBACK_1(AdsZonePanel::watchCallBack, this));
    btnWatch->setTag(0);
    
    Menu *menu=Menu::create(btnCancel,btnWatch, NULL);
    menu->alignItemsHorizontallyWithPadding(50*appDelegate->deviceScaleFloat);
    menu->setPosition(appDelegate->winSize.width/2,appDelegate->winSize.height/2-250*appDelegate->deviceScaleFloat);
    this->addChild(menu, 1);
}

void AdsZonePanel::cancelCallBack(cocos2d::Ref *pSender)
{
    this->removeFromParentAndCleanup(true);
}

void AdsZonePanel::watchCallBack(cocos2d::Ref *pSender)
{
    if(adType==adsTypeCoins)
        AdsAnimation::sharedManager()->coinsCallbackFinal();
    //else if(adType==adsTypeGems)
     //   AdsAnimation::sharedManager()->bucksCallbackFinal();
    
    this->removeFromParentAndCleanup(true);
}

Node *AdsZonePanel::loadResourceNodeForScore(int _resourceType,vector<string> *arrResourceAmount)
{
    string _resourceAmount=ClickerCalculation::getAbbreviationForValue(arrResourceAmount);
    
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    Node *nodeResource=Node::create();
    nodeResource->setTag(_resourceType);
    
    Resources *resources=Resources::sharedManager();
    DBResourceInfo *resource=resources->getResourceInfo(_resourceType);
    string strImageName=folderImagesResourcesBar+"r-"+to_string(resource->resourceid) +".png";
    
    Label *lblAmountResource2=StorePanel::createLabel(_resourceAmount,32*appDelegate->deviceScaleFloat);
    
    Sprite *btnScoreBarBack=Sprite::create(strImageName);
    btnScoreBarBack->setScale(0.75*appDelegate->deviceScaleFloat);
    btnScoreBarBack->setPosition(Point(-lblAmountResource2->getScaleX()*lblAmountResource2->getContentSize().width/2-0*appDelegate->deviceScaleFloat,0));
    nodeResource->addChild(btnScoreBarBack, 1);
    
    Label *lblAmountResource=StorePanel::createLabel(_resourceAmount,32*appDelegate->deviceScaleFloat);
    lblAmountResource->setName("lblAmountResource");
    //lblAmountResource->setDimensions(200*appDelegate->deviceScaleFloat, btnScoreBarBack->getScaleY()*btnScoreBarBack->getContentSize().height);//
    //lblAmountResource->setPosition(btnScoreBarBack->getPosition()+Point(btnScoreBarBack->getScaleX()*btnScoreBarBack->getContentSize().width+30*appDelegate->deviceScaleFloat,-2.5*appDelegate->deviceScaleFloat));
    
    lblAmountResource->setPosition(btnScoreBarBack->getPosition()+Point(lblAmountResource->getContentSize().width/2+btnScoreBarBack->getScaleX()*btnScoreBarBack->getContentSize().width/2+1.5*appDelegate->deviceScaleFloat,0*appDelegate->deviceScaleFloat));
    
    lblAmountResource->setColor(Color3B::BLACK);
    lblAmountResource->setAlignment(TextHAlignment::LEFT,TextVAlignment::CENTER);
    nodeResource->addChild(lblAmountResource,1);
    
    nodeResource->setContentSize(Size(btnScoreBarBack->getScaleX()*btnScoreBarBack->getContentSize().width+lblAmountResource2->getScaleX()*lblAmountResource2->getContentSize().width+5*appDelegate->deviceScaleFloat,btnScoreBarBack->getScaleY()*btnScoreBarBack->getContentSize().height+10*appDelegate->deviceScaleFloat));
    
    return nodeResource;
}

