//
//  AdsZonePanel.h
//  TapStar-mobile
//
//  Created by Tarek Saazeb on 12/12/19.
//

#ifndef AdsZonePanel_h
#define AdsZonePanel_h

#include "../StoreLayer/StorePanel.h"

USING_NS_CC;

class AdsZonePanel : public StorePanel
{
public:
    int adType;
    
#pragma mark- Init Method
    ~AdsZonePanel();
    AdsZonePanel();
    static AdsZonePanel* create(int _adType);
    virtual bool init(int _adType);
    void removeFromParentAndCleanup(bool cleanup);
    
    void loadAllButtons();
    void cancelCallBack(cocos2d::Ref *pSender);
    void watchCallBack(cocos2d::Ref *pSender);
    
    Node *loadResourceNodeForScore(int _resourceType,vector<string> *arrResourceAmount);
    
};

#endif /* AdsZonePanel_h */
