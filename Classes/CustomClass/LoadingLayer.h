//
//  LoadingLayer.h
//  ITIW-mobile
//
//  Created by game1 on 2/20/18.
//

#ifndef LoadingLayer_h
#define LoadingLayer_h

#include "cocos2d.h"
#include "../StoreLayer/StorePanel.h"

USING_NS_CC;

class LoadingLayer : public StorePanel
{
public:
#pragma mark- Init Method
    ~LoadingLayer();
    LoadingLayer();
    static LoadingLayer* create();
    virtual bool init();
    
    void removeFromParentAndCleanup(bool cleanup);
};

#endif /* LoadingLayer_h */
