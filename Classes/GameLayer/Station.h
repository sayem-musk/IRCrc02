//
//  Station.hpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 4/4/20.
//

#ifndef Station_h
#define Station_h

#include "cocos2d.h"
#include "../CustomClass/SpineObject.h"

USING_NS_CC;

class Station : public Node
{
public:
    Sprite *imgStageBackground;
    
    static Station* sharedManager();
    
#pragma mark- Init Method
    ~Station();
    Station();
    static Station* create();
    virtual bool init();
    void removeFromParentAndCleanup(bool cleanup);
    
#pragma mark- Station
    
    Sprite *imgStation;
    
    void loadStation();
    
#pragma mark- Animation
    Node *nodeHuman;
    SpineObject *animHuman;
    
    void loadAnimation(int selectedHuman);
    
#pragma mark- queue
    vector<int> *allHumanId;
    
    bool addHumanInStation(int selectedHuman);
    bool removeHumanFromStation();
    
#pragma mark- Station Schedule
    void setStationSchedule();
    void stationSchedule(float dt);
    
};

#endif /* Station_h */
