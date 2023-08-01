//
//  StorePanel.cpp
//  MUSK
//
//  Created by Tarek Saazeb on 7/28/16.
//
//

#include "StorePanel.h"
#include "../CustomClass/ClickerCalculation.h"

bool StorePanel::init()
{
    if(Node::init())
    {
        imgBackground=NULL;
        appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
        this->setContentSize(Size(appDelegate->winSize.width, appDelegate->winSize.height));
        this->clickerMarketSize=Size(appDelegate->winSize.width,1015*appDelegate->deviceScaleFloat);
        
        loadBackGroundColor();
        
        setTouchEnable();
        
        return true;
    }
    return false;
}

bool StorePanel::initWithSmallWindow()
{
    if(Node::init())
    {
        imgBackground=NULL;
        appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
        this->setContentSize(Size(appDelegate->winSize.width, appDelegate->winSize.height));
        
        loadBackGroundColor();
        
        EventListenerTouchOneByOne *touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = CC_CALLBACK_2(StorePanel::onTouchBeganSmallWindow, this);
        touchListener->onTouchMoved = CC_CALLBACK_2(StorePanel::onTouchMovedSmallWindow, this);
        touchListener->onTouchEnded = CC_CALLBACK_2(StorePanel::onTouchEndedSmallWindow, this);
        touchListener->onTouchCancelled = CC_CALLBACK_2(StorePanel::onTouchCancelledSmallWindow, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
        
        return true;
    }
    return false;
}

bool StorePanel::initWithCustomContentSize()
{
    if(Node::init())
    {
        imgBackground=NULL;
        appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
        
        return true;
    }
    return false;
}

#pragma mark- BackGroundColor

void StorePanel::loadBackGroundColor()
{
    colorBackground=LayerColor::create(Color4B::BLACK, this->getContentSize().width, this->getContentSize().height);
    colorBackground->setName("colorBackground");
    colorBackground->setOpacity(0.5*255);
    this->addChild(colorBackground, -1);
}

#pragma mark- Touch

void StorePanel::setTouchEnable()
{
    EventListenerTouchOneByOne *touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(StorePanel::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(StorePanel::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(StorePanel::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(StorePanel::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool StorePanel::onTouchBegan(Touch *touch, Event *event)
{
    Point touchLocation = this->convertTouchToNodeSpace(touch);
    Rect bbox = Rect(0, 0, this->getContentSize().width, this->getContentSize().height);
    
    if (bbox.containsPoint(touchLocation))
    {
        return true;
    }
    return false;
}

void StorePanel::onTouchMoved(Touch *touch, Event *event)
{
    
}

void StorePanel::onTouchEnded(Touch *touch, Event *event)
{
    
}

void StorePanel::onTouchCancelled(Touch *touch, Event *event)
{
}

bool StorePanel::onTouchBeganSmallWindow(Touch *touch, Event *event)
{
    return true;
}

void StorePanel::onTouchMovedSmallWindow(Touch *touch, Event *event)
{
    
}

void StorePanel::onTouchEndedSmallWindow(Touch *touch, Event *event)
{
    Point touchLocation = this->convertTouchToNodeSpace(touch);
    Rect bbox;
    if(imgBackground==NULL)
    {
        bbox = Rect(0, 0, this->getContentSize().width, this->getContentSize().height);
    }
    else
    {
        bbox = Rect(imgBackground->getPosition().x-imgBackground->getScaleX()*imgBackground->getContentSize().width/2, imgBackground->getPosition().y-imgBackground->getScaleY()*imgBackground->getContentSize().height/2, imgBackground->getScaleX()*imgBackground->getContentSize().width, imgBackground->getScaleY()*imgBackground->getContentSize().height);
    }
    
    if (!bbox.containsPoint(touchLocation))
    {
        this->removeFromParentAndCleanup(true);
    }
}

void StorePanel::onTouchCancelledSmallWindow(Touch *touch, Event *event)
{
    
}

#pragma mark- Load Background

void StorePanel::loadBackGround()
{
    loadBackGround(folderImagesStore+"bg-store.png");
}

void StorePanel::loadBackGround(string strImageName)
{
    imgBackground=Sprite::create(strImageName);
    imgBackground->setScaleX(appDelegate->winSize.width/imgBackground->getContentSize().width);
    imgBackground->setScaleY(appDelegate->winSize.height/imgBackground->getContentSize().height);
    imgBackground->setPosition(Point(this->getContentSize().width/2,this->getContentSize().height/2));
    this->addChild(imgBackground);
}

void StorePanel::loadSmallBackground()
{
    loadSmallBackground(folderImagesStore+"bg-store.png");
}

void StorePanel::loadSmallBackground(string strImageName)
{
    this->imgBackground=Sprite::create(strImageName);
    this->imgBackground->setScale(appDelegate->deviceScaleFloat);
    this->imgBackground->setPosition(appDelegate->winSize.width/2, appDelegate->winSize.height/2);
    this->addChild(this->imgBackground);
}

void StorePanel::loadTopBar()
{
    loadTopBar(folderImagesStore+"top-bar.png");
}

void StorePanel::loadTopBar(string strImageName)
{
    imgTopBar=Sprite::create(strImageName);
    imgTopBar->setScale(appDelegate->winSize.width/imgTopBar->getContentSize().width);
    imgTopBar->setPosition(Point(this->getContentSize().width/2,this->getContentSize().height-imgTopBar->getScale()*imgTopBar->getContentSize().height/2));
    this->addChild(imgTopBar,1);
}

void StorePanel::loadBottomBar()
{
    loadBottomBar(folderImagesStore+"top-bar.png");
}

void StorePanel::loadBottomBar(string strImageName)
{
    imgBottomBar=Sprite::create(strImageName);
    imgBottomBar->setScale(appDelegate->deviceScaleFloat);
    imgBottomBar->setPosition(Point(this->getContentSize().width/2,imgBottomBar->getScale()*imgBottomBar->getContentSize().height/2));
    this->addChild(imgBottomBar);
}

#pragma mark- Cross Button

void StorePanel::loadCrossButton()
{
    btnCross=StorePanel::createButton(folderImagesStore+"btn-cross.png");
    btnCross->setScale(appDelegate->deviceScaleFloat);
    
    btnCross->setCallback(CC_CALLBACK_1(StorePanel::crossCallBack, this));
    Menu *menuCross=Menu::create(btnCross, NULL);
    menuCross->setName("menuCross");
    
    btnCross->setPosition(Point(appDelegate->uiRect.size.width/2-btnCross->getScale()*btnCross->getContentSize().width/2-5*appDelegate->deviceScaleFloat,this->getContentSize().height/2-btnCross->getScale()*btnCross->getContentSize().height/2-5*appDelegate->deviceScaleFloat));
    
    this->addChild(menuCross, 15);
}

void StorePanel::loadScrollCrossButton()
{
    btnScrollCross=ScrollableButton::create(folderImagesStore+"btn-cross.png", folderImagesStore+"btn-cross.png");
    //btnScrollCross->setScale(appDelegate->deviceScaleFloat);
    
    btnScrollCross->setCallback(CC_CALLBACK_1(StorePanel::crossCallBack, this));
    btnScrollCross->setPosition(Point(appDelegate->uiRect.origin.x+appDelegate->uiRect.size.width-btnScrollCross->getScale()*btnScrollCross->getContentSize().width/2-5*appDelegate->deviceScaleFloat,this->getContentSize().height-btnScrollCross->getScale()*btnScrollCross->getContentSize().height/2-5*appDelegate->deviceScaleFloat));
    
    this->addChild(btnScrollCross, 15);
}

void StorePanel::crossCallBack(Ref* pSender)
{
    //SimpleAudioEngine::getInstance()->playEffect((folderSound+"click.mp3").c_str());
    this->removeFromParentAndCleanup(true);
}

#pragma mark- Back Button

void StorePanel::loadBackButton()
{
    btnBack=StorePanel::createButton(folderImagesStore+"btn-back.png");
    btnBack->setScale(appDelegate->deviceScaleFloat);
    btnBack->setCallback(CC_CALLBACK_1(StorePanel::backCallBack, this));
    
    Menu *menuBack = Menu::create(btnBack, NULL);
    menuBack->setPosition(Point(appDelegate->uiRect.origin.x+btnBack->getScale()*btnBack->getContentSize().width/2+5*appDelegate->deviceScaleFloat,this->getContentSize().height-btnBack->getScale()*btnBack->getContentSize().height/2-5*appDelegate->deviceScaleFloat));
    this->addChild(menuBack, 1);
}

void StorePanel::backCallBack(cocos2d::Ref* pSender)
{
    this->removeFromParentAndCleanup(true);
}

#pragma mark- Title

void StorePanel::loadTitle(string _panel_title)
{
    if(AppDelegate::isContainObject(this, titleLabel)==false)
    {
        titleLabel=StorePanel::createLabel(_panel_title, 28*appDelegate->deviceScaleFloat);
        if(imgBackground!=NULL)
            titleLabel->setDimensions(imgBackground->getScaleX()*imgBackground->getContentSize().width-200*appDelegate->deviceScaleFloat, 74*appDelegate->deviceScaleFloat);
        else
            titleLabel->setDimensions(this->getContentSize().width-200*appDelegate->deviceScaleFloat, 74*appDelegate->deviceScaleFloat);
        titleLabel->setAlignment(TextHAlignment::CENTER,TextVAlignment::CENTER);
        titleLabel->setPosition(Point(this->getContentSize().width/2,this->getContentSize().height-titleLabel->getDimensions().height/2));
        this->addChild(titleLabel,1);
    }
    titleLabel->setString(_panel_title);
}

#pragma mark- Create Button

MenuItemSprite* StorePanel::createButton(string imageName)
{
    Sprite *normalImage=Sprite::create(imageName);
    Sprite *selectedImage=Sprite::create(imageName);
    selectedImage->setColor(Color3B::GRAY);
    
    return MenuItemSprite::create(normalImage,selectedImage);
}

MenuItemSprite* StorePanel::createButton(string imageNameNormal,string imageNameSelected)
{
    Sprite *normalImage=Sprite::create(imageNameNormal);
    Sprite *selectedImage=Sprite::create(imageNameSelected);
    
    return MenuItemSprite::create(normalImage,selectedImage);
}

MenuItemSprite* StorePanel::createButtonWithLabel(string imageName,string strButtonTitle,float fontSize)
{
    Sprite *normalImage=Sprite::create(imageName);
    Sprite *selectedImage=Sprite::create(imageName);
    selectedImage->setColor(Color3B::GRAY);
    
    MenuItemSprite *btnButton=MenuItemSprite::create(normalImage,selectedImage);
    
    Label *lblButtonTitle=StorePanel::createLabel(strButtonTitle, fontSize);
    lblButtonTitle->setName("lblButtonTitle");
    lblButtonTitle->setDimensions(btnButton->getContentSize().width, btnButton->getContentSize().height);
    lblButtonTitle->setPosition(Point(btnButton->getContentSize().width/2,btnButton->getContentSize().height/2));
    lblButtonTitle->setColor(Color3B::WHITE);
    lblButtonTitle->setAlignment(TextHAlignment::CENTER,TextVAlignment::CENTER);
    btnButton->addChild(lblButtonTitle,1);
    
    return btnButton;
}

Label* StorePanel::createLabel(string strLabel,float fontSize)
{
    //Label *lblLabel=Label::createWithTTF(strLabel, folderFont+"ChangaOne-Regular.ttf", fontSize);
    Label *lblLabel=Label::createWithTTF(strLabel, folderFont+"arial.ttf", fontSize);
    return lblLabel;
}

Label* StorePanel::createLabelWithBold(string strLabel,float fontSize)
{
    Label *lblLabel=Label::createWithTTF(strLabel, folderFont+"arial.ttf", fontSize);
    lblLabel->enableBold();
    return lblLabel;
}

Label* StorePanel::createBattleLabel(string strLabel,float fontSize)
{
    Label *lblLabel=Label::createWithTTF(strLabel, folderFont+"Verdana Bold.ttf", fontSize);
    lblLabel->enableBold();
    //lblLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);
    //    lblLabel->enableOutline(Color4B::BLACK, 1);
    return lblLabel;
}

Label* StorePanel::createLabelForGoal(string strLabel,float fontSize)
{
    Label *lblLabel=Label::createWithTTF(strLabel, folderFont+"RifficFree-Bold.ttf", fontSize);
    lblLabel->enableBold();
    //lblLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);
    //    lblLabel->enableOutline(Color4B::BLACK, 1);
    return lblLabel;
}

Label* StorePanel::createBattleLabelWithoutBold(string strLabel,float fontSize)
{
    Label *lblLabel=Label::createWithTTF(strLabel, folderFont+"Verdana Bold.ttf", fontSize);
    //lblLabel->enableBold();
    //lblLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);
    //    lblLabel->enableOutline(Color4B::BLACK, 1);
    return lblLabel;
}

Label* StorePanel::setFontSize(Label *lblLabel,float fontSize)
{
    TTFConfig config = lblLabel->getTTFConfig();
    config.fontSize = fontSize;
    lblLabel->setTTFConfig(config);
    return lblLabel;
}

ScrollableButton* StorePanel::createScrollableButton(string imageName)
{
    return ScrollableButton::create(imageName,imageName);
}

ScrollableButton* StorePanel::createScrollableButton(string imageNameNormal,string imageNameSelected)
{
    return ScrollableButton::create(imageNameNormal,imageNameSelected);
}

#pragma mark- TouchDetection

bool StorePanel::detect_alpha(Sprite *mainSprite, Touch *touch, string imagename)
{
    Point tap=mainSprite->convertTouchToNodeSpace(touch);
    
    Image *imgPtr=new Image();
    imgPtr->initWithImageFile(imagename);
    
    const int width=imgPtr ->getWidth();
    const int height=imgPtr ->getHeight();
    
    unsigned x=unsigned( tap.x ) % width;
    /// Don't forget to invert y coordinate.
    unsigned y=unsigned( height - tap.y ) % height;
    unsigned index=x + y * width;
    unsigned dataLen=(unsigned)imgPtr ->getDataLen();
    CCAssert( index < dataLen, "index is bigger than image size." );
    unsigned char* pixel=imgPtr ->getData() + (4 * index);
    return !(0==pixel[0] && 0==pixel[1] && 0==pixel[2] && 0== pixel[3]);
}

bool StorePanel::checkSpriteTouch(Sprite *mainSprite,Point touchLocation)
{
    Point point=mainSprite->convertToNodeSpace(touchLocation);
    Size size=Size(mainSprite->getContentSize().width, mainSprite->getContentSize().height) ;
    if(point.x>0 && point.y>0 && point.x<size.width && point.y<size.height)
        return true;
    else
        return false;
}

#pragma mark- Score Bar

Node *StorePanel::loadResourceNodeForScore(int _resourceType,string _resourceAmount)
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    Node *nodeResource=Node::create();
    nodeResource->setTag(_resourceType);

    Resources *resources=Resources::sharedManager();
    DBResourceInfo *resource=resources->getResourceInfo(_resourceType);
    string strImageName=folderImagesResourcesBar+"r-"+to_string(resource->resourceid) +".png";
    
    Label *lblAmountResource2=StorePanel::createLabel(_resourceAmount,24*appDelegate->deviceScaleFloat);
    
    Sprite *btnScoreBarBack=Sprite::create(strImageName);
    btnScoreBarBack->setScale(appDelegate->deviceScaleFloat);
    btnScoreBarBack->setPosition(Point(-lblAmountResource2->getScaleX()*lblAmountResource2->getContentSize().width/2-0*appDelegate->deviceScaleFloat,0));
    nodeResource->addChild(btnScoreBarBack, 1);
    
    Label *lblAmountResource=StorePanel::createLabel(_resourceAmount,24*appDelegate->deviceScaleFloat);
    lblAmountResource->setName("lblAmountResource");
    lblAmountResource->setDimensions(100*appDelegate->deviceScaleFloat, btnScoreBarBack->getScaleY()*btnScoreBarBack->getContentSize().height);
    lblAmountResource->setPosition(btnScoreBarBack->getPosition()+Point(btnScoreBarBack->getScaleX()*btnScoreBarBack->getContentSize().width+10*appDelegate->deviceScaleFloat,-0*appDelegate->deviceScaleFloat));
    lblAmountResource->setColor(Color3B::BLACK);
    lblAmountResource->setAlignment(TextHAlignment::LEFT,TextVAlignment::CENTER);
    nodeResource->addChild(lblAmountResource,1);
    
    nodeResource->setContentSize(Size(btnScoreBarBack->getScaleX()*btnScoreBarBack->getContentSize().width+lblAmountResource2->getScaleX()*lblAmountResource2->getContentSize().width+5*appDelegate->deviceScaleFloat,btnScoreBarBack->getScaleY()*btnScoreBarBack->getContentSize().height+10*appDelegate->deviceScaleFloat));
    return nodeResource;
}

Node *StorePanel::loadResourceNodeForScore(int _resourceType,vector<string> *_resourceAmount)
{
    string _strAmount=ClickerCalculation::getAbbreviationForValue(_resourceAmount->at(0),_resourceAmount->at(1));
    return StorePanel::loadResourceNodeForScore(_resourceType,_strAmount);
}

#pragma mark- Time Calculation

int StorePanel::getStringTimeInSecond(string strTimeValue)
{
    vector<string> *vecStrTimeValue=AppDelegate::componentSeparatedByString(strTimeValue, " ");
    int totalSecond=0;
    for (int i=0; i<vecStrTimeValue->size(); i++)
    {
        string strSingleTimeValue=vecStrTimeValue->at(i);
        int timeValue=stoi(strSingleTimeValue.substr(0,strSingleTimeValue.size()-1));
        
        switch (strSingleTimeValue[strSingleTimeValue.size()-1])
        {
            case 'd':
                totalSecond=totalSecond+timeValue*24*60*60;
                break;
            case 'h':
                totalSecond=totalSecond+timeValue*60*60;
                break;
            case 'm':
                totalSecond=totalSecond+timeValue*60;
                break;
            case 's':
                totalSecond=totalSecond+timeValue;
                break;
            default:
                totalSecond=totalSecond;
                break;
        }
    }
    return totalSecond;
}

string StorePanel::convertTimeToString(int timeValue)
{
    string timeString="";
    
    if(timeValue>24*60*60)
    {
        timeString=to_string(timeValue/(24*60*60))+"d";
        timeValue=timeValue%(24*60*60);
    }
    if(timeValue>60*60)
    {
        timeString=timeString+" "+to_string(timeValue/(60*60))+"h";
        timeValue=timeValue%(60*60);
    }
    if(timeValue>60)
    {
        timeString=timeString+" "+to_string(timeValue/60)+"m";
        timeValue=timeValue%(60);
    }
    if(timeValue>=0)
        timeString=timeString+" "+to_string(timeValue)+"s";
    return timeString;
}

string StorePanel::convertTimeToClockString(int timeValue)
{
    string timeString="";
    
    /*if(timeValue>24*60*60)
     {
     if(timeValue/(24*60*60)>9)
     timeString=to_string(timeValue/(24*60*60))+":";
     else
     timeString="0"+to_string(timeValue/(24*60*60))+":";
     timeValue=timeValue%(24*60*60);
     }
     else
     {
     timeString="00:";
     }*/
    if(timeValue>60*60)
    {
        if(timeValue/(60*60)>9)
            timeString=timeString+to_string(timeValue/(60*60))+":";
        else
            timeString=timeString+"0"+to_string(timeValue/(60*60))+":";
        timeValue=timeValue%(60*60);
    }
    else
    {
        timeString=timeString+"00:";
    }
    if(timeValue>60)
    {
        if(timeValue/(60)>9)
            timeString=timeString+to_string(timeValue/(60))+":";
        else
            timeString=timeString+"0"+to_string(timeValue/(60))+":";
        
        timeValue=timeValue%(60);
    }
    else
    {
        timeString=timeString+"00:";
    }
    
    if(timeValue>=0)
    {
        if(timeValue>9)
            timeString=timeString+to_string(timeValue);
        else
            timeString=timeString+"0"+to_string(timeValue);
    }
    else
    {
        timeString=timeString+"00";
    }
    return timeString;
}

string StorePanel::convertTimeToClockStringSmall(int timeValue)
{
    string timeString="";
    
    /*if(timeValue>24*60*60)
     {
     if(timeValue/(24*60*60)>9)
     timeString=to_string(timeValue/(24*60*60))+":";
     else
     timeString="0"+to_string(timeValue/(24*60*60))+":";
     timeValue=timeValue%(24*60*60);
     }
     else
     {
     timeString="00:";
     }
    if(timeValue>60*60)
    {
        if(timeValue/(60*60)>9)
            timeString=timeString+to_string(timeValue/(60*60))+":";
        else
            timeString=timeString+"0"+to_string(timeValue/(60*60))+":";
        timeValue=timeValue%(60*60);
    }
    else
    {
        timeString=timeString+"00:";
    }*/
    if(timeValue>60)
    {
        if(timeValue/(60)>9)
            timeString=timeString+to_string(timeValue/(60))+":";
        else
            timeString=timeString+"0"+to_string(timeValue/(60))+":";
        
        timeValue=timeValue%(60);
    }
    else
    {
        timeString=timeString+"00:";
    }
    
    if(timeValue>=0)
    {
        if(timeValue>9)
            timeString=timeString+to_string(timeValue);
        else
            timeString=timeString+"0"+to_string(timeValue);
    }
    else
    {
        timeString=timeString+"00";
    }
    return timeString;
}
