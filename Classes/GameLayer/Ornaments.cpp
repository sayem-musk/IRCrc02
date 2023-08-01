//
//  Ornaments.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 7/10/20.
//

#include "Ornaments.h"
#include "AppDelegate.h"

#pragma mark- Init Method

static Ornaments *sharedInstance=NULL;
Ornaments* Ornaments::sharedManager()
{
    if(sharedInstance==NULL)
    {
        sharedInstance=Ornaments::create();
    }
    return sharedInstance;
}

Ornaments::~Ornaments()
{
    
}

Ornaments::Ornaments()
{
    
}

Ornaments* Ornaments::create()
{
    Ornaments* ret = new Ornaments();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool Ornaments::init()
{
    if(Node::init())
    {
        loadBallons();
        loadIceCream();
        
        return true;
    }
    return false;
}

void Ornaments::removeFromParentAndCleanup(bool cleanup)
{
    Node::removeFromParentAndCleanup(cleanup);
}

#pragma Ballons

void Ornaments::loadBallons()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    if(AppDelegate::isContainObject(appDelegate->gnode,animBallons))
        animBallons->removeFromParentAndCleanup(true);

    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    
    if(screenData->myScreen->balloons_level>0)
    {
        string strSub="a";
        
        switch (screenData->myScreen->balloons_level%3)
        {
            case 1:
                strSub="a";
            break;
            case 2:
                strSub="b";
                break;
            case 0:
                strSub="c";
                break;
                
            default:
                break;
        }
        
        string strAnimation=folderImagesOrnaments+to_string(TypeBalloons)+strSub;
        
        animBallons=SpineObject::create(strAnimation, 0.1f);
        appDelegate->gnode->addChild(animBallons,25);
        
        animBallons->setPosition(Point(appDelegate->winSize.width/2+140*appDelegate->deviceScaleFloat,appDelegate->winSize.height/2-150*appDelegate->deviceScaleFloat));
        //animBallons->animationObject->showAnimationNames();
        animBallons->startAnimation(animTypeOther);
    }
}

#pragma IceCream

void Ornaments::loadIceCream()
{
    AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
    if(AppDelegate::isContainObject(appDelegate->gnode,animIceCream))
        animIceCream->removeFromParentAndCleanup(true);

    ScreenData *screenData=appDelegate->allScreenData->at(appDelegate->selectedScreenIndex);
    
    if(screenData->myScreen->icecream_level>0)
    {
        string strSub="a";
        
        switch (screenData->myScreen->icecream_level%3)
        {
            case 1:
                strSub="a";
            break;
            case 2:
                strSub="b";
                break;
            case 0:
                strSub="c";
                break;
                
            default:
                break;
        }
        
        string strAnimation=folderImagesOrnaments+to_string(TypeIceCream)+strSub;
        
        animIceCream=SpineObject::create(strAnimation, 0.1f);
        appDelegate->gnode->addChild(animIceCream,5);
        
        animIceCream->setPosition(Point(appDelegate->winSize.width/2+270*appDelegate->deviceScaleFloat,appDelegate->winSize.height/2-0*appDelegate->deviceScaleFloat));
        //animIceCream->animationObject->showAnimationNames();
        animIceCream->startAnimation(animTypeOther);
    }
}
