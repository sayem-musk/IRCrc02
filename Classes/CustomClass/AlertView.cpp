//
//  AlertView.cpp
//  MUSK
//
//  Created by Tarek Saazeb on 6/12/16.
//
//

#include "AlertView.h"
#include "AppDelegate.h"
#include "../StoreLayer/StorePanel.h"

AlertViewDelegate::~AlertViewDelegate()
{
    
}

void AlertViewDelegate::alertViewCallBack(int tag,int buttonIndex)
{
}

AlertView::~AlertView()
{
    
}

AlertView::AlertView()
{
    
}

AlertView* AlertView::create(string _title,string _message,AlertViewDelegate *pDelegate)
{
    AlertView *alertView=new AlertView();
    alertView->init(_title,_message,pDelegate);
    return alertView;
}

bool AlertView::init(string _title,string _message,AlertViewDelegate *pDelegate)
{
    if(Node::init())
    {
        AppDelegate *appDelegate=AppDelegate::sharedApplication();
        title=_title;
        message=_message;
        alertViewDelegate=pDelegate;
        tag=-1;
        buttonsTitle=new vector<string>();
        
        this->setContentSize(appDelegate->winSize);
        this->setAnchorPoint(Point(0.5f, 0.5f));
        this->setPosition(appDelegate->winSize.width/2,appDelegate->winSize.height/2);
        
        EventListenerTouchOneByOne *touchListenerOneByOne=EventListenerTouchOneByOne::create();
        touchListenerOneByOne->setSwallowTouches(true);
        touchListenerOneByOne->onTouchBegan=CC_CALLBACK_2(AlertView::onTouchBegan, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListenerOneByOne, this);
        
        LayerColor *bakcgroundColor=LayerColor::create(Color4B::BLACK);
        bakcgroundColor->setOpacity(0.5*255);
        this->addChild(bakcgroundColor);
        
        Sprite *backgroundSprite=Sprite::create(folderImagesStore+"bg-store-small.png");
        backgroundSprite->setScale(appDelegate->deviceScaleFloat);
        backgroundSprite->setPosition(Point(appDelegate->winSize.width/2,appDelegate->winSize.height/2));
        this->addChild(backgroundSprite);
        
        Label *lblTitle=StorePanel::createLabel(title, 30*appDelegate->deviceScaleFloat);
        lblTitle->setDimensions(backgroundSprite->getScale()*backgroundSprite->getContentSize().width, 30*appDelegate->deviceScaleFloat);
        lblTitle->setPosition(Point(backgroundSprite->getPosition().x,appDelegate->winSize.height/2+backgroundSprite->getScale()*backgroundSprite->getContentSize().height/2-40*appDelegate->deviceScaleFloat));
        lblTitle->setColor(Color3B::BLACK);
        lblTitle->setAlignment(TextHAlignment::CENTER,TextVAlignment::CENTER);
        this->addChild(lblTitle);
        
        Label *lblMessage=StorePanel::createLabel(message, 30*appDelegate->deviceScaleFloat);
        lblMessage->setDimensions(backgroundSprite->getScale()*backgroundSprite->getContentSize().width-130, 200*appDelegate->deviceScaleFloat);
        lblMessage->setPosition(Point(backgroundSprite->getPosition().x,appDelegate->winSize.height/2+20*appDelegate->deviceScaleFloat));
        lblMessage->setColor(Color3B::BLACK);
        lblMessage->setAlignment(TextHAlignment::CENTER,TextVAlignment::CENTER);
        this->addChild(lblMessage,1);

        buttonMenu=Menu::create();
        buttonMenu->setPosition(Point(appDelegate->winSize.width/2,appDelegate->winSize.height/2-120*appDelegate->deviceScaleFloat));
        this->addChild(buttonMenu);
        
        return true;
    }
    return false;
}

bool AlertView::onTouchBegan(Touch*, Event*)
{
    return true;
}

void AlertView::addButtonWithTitle(string _buttonsTitle)
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    MenuItemSprite *button=StorePanel::createButton(folderImagesButton+"btn_alert_view.png");
    button->setScale(appDelegate->deviceScaleFloat);
    button->setCallback(CC_CALLBACK_1(AlertView::buttonCallBack, this));
    button->setTag((int)buttonsTitle->size());
    buttonMenu->addChild(button);
    
    Label *buttonTItleLabel=StorePanel::createLabel(_buttonsTitle, 24);
    buttonTItleLabel->setDimensions(button->getContentSize().width, button->getContentSize().height);
    buttonTItleLabel->setAlignment(TextHAlignment::CENTER,TextVAlignment::CENTER);
    buttonTItleLabel->setPosition(Point(button->getContentSize().width/2,button->getContentSize().height/2));
    buttonTItleLabel->setColor(Color3B::BLACK);
    button->addChild(buttonTItleLabel);
    
    buttonsTitle->push_back(_buttonsTitle);
}

void AlertView::show()
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    if(buttonsTitle->size()==0)
    {
        this->addButtonWithTitle("OK");
    }
    buttonMenu->alignItemsHorizontallyWithPadding(5.0f*appDelegate->deviceScaleFloat);
    //appDelegate->gHud->addChild(this,1000);
}

void AlertView::buttonCallBack(Ref* pSender)
{
    MenuItemSprite *pMenuItem=(MenuItemSprite*)(pSender);
    if(alertViewDelegate!=NULL)
        alertViewDelegate->alertViewCallBack(tag,pMenuItem->getTag());
    this->removeFromParentAndCleanup(true);
}
