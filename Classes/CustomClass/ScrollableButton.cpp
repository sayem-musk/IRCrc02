//
//  ScrollableButton.cpp
//  MUSK
//
//  Created by Tarek Saazeb on 3/13/17.
//
//

#include "ScrollableButton.h"
#include "AppDelegate.h"
#include "../StoreLayer/StorePanel.h"

static bool touchSwallow=false;

ScrollableButton::~ScrollableButton()
{
    
}

ScrollableButton::ScrollableButton()
{
    
}

ScrollableButton* ScrollableButton::create(string normalImage,string selectedImage)
{
    ScrollableButton* ret = new ScrollableButton();
    if(ret && ret->init(normalImage,selectedImage)) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool ScrollableButton::init(string normalImage,string selectedImage)
{
    if(Node::init())
    {
        AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
        strNormal=normalImage;
        strSelected=selectedImage;
        isDraging=false;
        
        colorEnable=false;
        
        if(strNormal==strSelected)
            colorEnable=true;
        
        btnSprite=Sprite::create(strNormal);
        btnSprite->setScale(appDelegate->deviceScaleFloat);
        this->addChild(btnSprite);
        
        originalColor=btnSprite->getColor();
        buttonTapColor=Color3B::GRAY;
        
        this->setContentSize(Size(btnSprite->getScaleX()*btnSprite->getContentSize().width,btnSprite->getScaleY()*btnSprite->getContentSize().height));
        
        setTouchEnable();
        
        return true;
    }
    return false;
}

void ScrollableButton::removeFromParentAndCleanup(bool cleanup)
{
    Node::removeFromParentAndCleanup(cleanup);
}

#pragma mark- Image

void ScrollableButton::setImage(string strImageName,ScrollableButton::State controlState)
{
    switch (controlState)
    {
        case ScrollableButton::State::Normal:
        {
            strNormal=strImageName;
            btnSprite->setTexture(strNormal);
        }
            break;
        case ScrollableButton::State::Selected:
        {
            strSelected=strImageName;
            //btnSprite->setTexture(strNormal);
        }
            break;
            
        default:
            break;
    }
}

#pragma mark- Callback

void ScrollableButton::setCallback(const ccMenuCallback& _callback)
{
    callback=_callback;
}

#pragma mark- Touch

void ScrollableButton::setTouchEnable()
{
    EventListenerTouchOneByOne *touchListener = EventListenerTouchOneByOne::create();
    
    //touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(ScrollableButton::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(ScrollableButton::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(ScrollableButton::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(ScrollableButton::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool ScrollableButton::onTouchBegan(Touch *touch, Event *event)
{
    if(btnSprite->isVisible()==false)
        return false;
    
    isDraging=false;
    Point location=touch->getLocation();
    
    if(touchSwallow==false && StorePanel::checkSpriteTouch(btnSprite,location))// && StorePanel::detect_alpha(btnSprite,touch,strNormal))
    {
        btnSprite->setTexture(strSelected);
        if(colorEnable)
            btnSprite->setColor(buttonTapColor);
        touchSwallow=true;
        return true;
    }
    return false;
}

void ScrollableButton::onTouchMoved(Touch *touch, Event *event)
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    Point location=touch->getLocation();
    Point locationPrev=touch->getPreviousLocation();
    float touchDist=location.getDistance(locationPrev);
    if(touchDist<1*appDelegate->deviceScaleFloat)
        return;
    
    if(!isDraging)
    {
        btnSprite->setTexture(strNormal);
        if(colorEnable)
            btnSprite->setColor(originalColor);
    }
    isDraging=true;
    touchSwallow=false;
}

void ScrollableButton::onTouchEnded(Touch *touch, Event *event)
{
    if(!isDraging)
    {
        btnSprite->setTexture(strNormal);
        if(colorEnable)
            btnSprite->setColor(originalColor);
        if( callback )
        {
            callback(this);
        }
    }
    isDraging=false;
    touchSwallow=false;
}

void ScrollableButton::onTouchCancelled(Touch *touch, Event *event)
{
}

void ScrollableButton::setButtonColor(const cocos2d::Color3B &color)
{
    originalColor=color;
    btnSprite->setColor(originalColor);
}

void ScrollableButton::setButtonColorEnable(const cocos2d::Color3B &color)
{
    buttonTapColor=originalColor;
    originalColor=color;
    btnSprite->setColor(originalColor);
}






