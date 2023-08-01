//
//  HumanExit.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 4/5/20.
//

#include "HumanExit.h"
#include "AppDelegate.h"
#include "../StoreLayer/StorePanel.h"

#pragma mark- Init Method

HumanExit::~HumanExit()
{
    
}

HumanExit::HumanExit()
{
    
}

HumanExit* HumanExit::create(int _selectedHuman)
{
    HumanExit* ret = new HumanExit();
    if(ret && ret->init(_selectedHuman)) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool HumanExit::init(int _selectedHuman)
{
    if(Node::init())
    {
        AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
        imgStageBackground=appDelegate->gnode->imgStageBackground;
        
        selectedHuman=_selectedHuman;
        
        loadAnimation();
        
        return true;
    }
    return false;
}

void HumanExit::removeFromParentAndCleanup(bool cleanup)
{
    if(AppDelegate::isContainObject(this, nodeHuman))
        nodeHuman->removeFromParentAndCleanup(true);
    Node::removeFromParentAndCleanup(cleanup);
}

#pragma mark- Animation

void HumanExit::loadAnimation()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    
    if(AppDelegate::isContainObject(this, nodeHuman))
        nodeHuman->removeFromParentAndCleanup(true);
    
    string strAnimation=folderImagesHuman+to_string(selectedHuman)+"b";
    nodePosition=Point(150*imgStageBackground->getScaleX(),appDelegate->winSize.height/2-210*imgStageBackground->getScaleY());
    float scaleValue=1;
    
    nodeHuman=Node::create();
    nodeHuman->setPosition(nodePosition);
    this->addChild(nodeHuman,1000);
    
    animHuman=SpineObject::create(strAnimation, 0.1f);
    nodeHuman->addChild(animHuman,1000);
    
    animHuman->setScaleX(scaleValue*animHuman->getScaleX());
    
    setAnimation();
}

void HumanExit::setAnimation()
{
    setNodeCoinsAnimation();

    animHuman->startAnimation(animTypeWalk);
    
    nodeHuman->stopAllActions();
    
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    
    Point finalPosition=Point(-50*imgStageBackground->getScaleX(),appDelegate->winSize.height/2-325*imgStageBackground->getScaleY());
    
    double staticDistance=525.0f;
    double distance=sqrt(pow((finalPosition.y-nodeHuman->getPosition().y), 2)+pow((finalPosition.x-nodeHuman->getPosition().x), 2));
    double animationTime=(15.0f*distance)/staticDistance;
    
    MoveTo *moveto=MoveTo::create(animationTime, finalPosition);
    Sequence *sequenceMove=Sequence::create(moveto,CallFunc::create(std::bind(&HumanExit::removeFromParentAndCleanup,this,true)),NULL);
    nodeHuman->runAction(sequenceMove);
}

void HumanExit::setNodeCoinsAnimation()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();

    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    vector<string> *arrReward=screenData->getCoinsRewards();

    Node *nodeGetCoins=Node::create();
    nodeGetCoins->setPosition(nodePosition+Point(50*appDelegate->deviceScaleFloat,100*appDelegate->deviceScaleFloat));
    this->addChild(nodeGetCoins,1000);

    Label *lblGetCoins=StorePanel::createLabelWithBold("+"+ClickerCalculation::getAbbreviationForValue(arrReward), 30*appDelegate->deviceScaleFloat);
    lblGetCoins->setDimensions(200*appDelegate->deviceScaleFloat, 200*appDelegate->deviceScaleFloat);
    //lblGetCoins->setPosition(nodePosition+Point(0,0));
    lblGetCoins->setColor(Color3B(243,190,66));
    lblGetCoins->setAlignment(TextHAlignment::LEFT,TextVAlignment::CENTER);
    nodeGetCoins->addChild(lblGetCoins);

    MoveTo *moveTo=MoveTo::create(0.5f,Point(nodePosition.x + 50*appDelegate->deviceScaleFloat,nodePosition.y+130*appDelegate->deviceScaleFloat));
    Sequence *sequence=Sequence::create(moveTo,CallFunc::create(CC_CALLBACK_0(Label::removeFromParentAndCleanup, nodeGetCoins, true)),NULL);
    nodeGetCoins->runAction(sequence);
}



