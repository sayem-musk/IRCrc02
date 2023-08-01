//
//  LoadingLayer.cpp
//  ITIW-mobile
//
//  Created by game1 on 2/20/18.
//

#include "LoadingLayer.h"

#pragma mark- Init Method

LoadingLayer::~LoadingLayer() { }

LoadingLayer::LoadingLayer() { }

LoadingLayer* LoadingLayer::create()
{
    LoadingLayer* ret = new LoadingLayer();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool LoadingLayer::init()
{
    if(StorePanel::init())
    {
        Label *lblLoading = StorePanel::createLabelWithBold("LOADING",22*appDelegate->deviceScaleFloat);
        lblLoading->setPosition(Point(appDelegate->winSize.width/2,appDelegate->winSize.height/2+14*appDelegate->deviceScaleFloat));
        lblLoading->setColor(Color3B::WHITE);
        //lblOfferInfo->setName("lblOfferInfo");
        this->addChild(lblLoading, 20);
        
        return true;
    }
    return false;
}

void LoadingLayer::removeFromParentAndCleanup(bool cleanup)
{
    StorePanel::removeFromParentAndCleanup(cleanup);
}



