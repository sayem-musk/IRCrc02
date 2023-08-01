//
//  ScreenData.hpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 2/16/20.
//

#ifndef ScreenData_h
#define ScreenData_h

#include "../DBClasses/DBScreenInfo.h"
#include "../DBClasses/DBMyScreen.h"

using namespace std;

class ScreenData
{
public:
    DBScreenInfo *screenInfo;
    DBMyScreen *myScreen;
    
#pragma mark- Init Method
    ~ScreenData();
    ScreenData();
    static ScreenData* create();
    virtual bool init();
    
    static ScreenData* create(int _my_screen_id);
    virtual bool init(int _my_screen_id);
    vector<string>* getPriceForType(int type);
    void unlockScreen();
    vector<string>* getCoinsRewards();
    void addCoinsExperience();
    void setLevelUpButton();
    
#pragma mark- ScreenData
    static void reloadScreenData();
    static void addScreenData(int _my_screen_id);
    static void createScreenInDatabase(int _screen_id);
    static ScreenData* getSelectedScreenData();
    static int getSelectedScreenIndex();
    static ScreenData* getScreenData(int screen_id);
};

#endif /* ScreenData_h */
