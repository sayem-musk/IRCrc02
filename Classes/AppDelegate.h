#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"
#include <sqlite3.h>

#include "CustomClass/ResourceConfig.h"
#include "CustomClass/Config.h"
#include "CustomClass/CustomMath.h"

#include "DBClasses/Resources.h"

#include "DBClasses/DBUserInfo.h"
#include "DBClasses/DBScreenInfo.h"
#include "DataStructure/ScreenData.h"

#include "GameLayer/GameNode.h"
#include "GameLayer/GameHud.h"
#include "GameLayer/Chair.h"

#include "CustomClass/ClickerCalculation.h"
#include "CustomClass/MUSKScoreBar.h"
#include "CustomClass/TagManager.h"

#include "Framework/Firebase/MUSKFirebase.h"

#include "audio/include/SimpleAudioEngine.h"

using namespace CocosDenshion;

using namespace std;
USING_NS_CC;

#define NoChairInTable 4

enum
{
    xpIndex=-1,
    coinsIndex=1,
    bucksIndex=2,
    foodsIndex=3,
};

enum
{
    TypeCustomerFrequency=101,
    TypeStationCapacity=102,
    TypeQueueCapacity=103,
    
    TypeTicketPrice=201,
    TypeSpeed=202,
    TypeCars=203,
    
    TypeBalloons=301,
    TypeIceCream=302,
    TypeFastFood=303,
    TypeAirShip=304,
};

enum
{
    panelGateAttributes     =   1,
    panelThemePanel         =   2,
    panelOrnamentsPanel     =   3,
    panelLevelUpPanel       =   4,
    panelSettingsPanel      =   5,
};

static string strLastTimePlay="LastTimePlay";
static string strSoundVaule="SoundVaule";
static string strVibrationVaule="VibrationVaule";

static string noadsInAppComplete="noadsInAppComplete";

/**
@brief    The cocos2d Application.

Private inheritance here hides part of interface from Director.
*/
class  AppDelegate : private cocos2d::Application
{
public:
    static AppDelegate* sharedApplication();
    AppDelegate();
    virtual ~AppDelegate();

    virtual void initGLContextAttrs();

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  Called when the application moves to the background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  Called when the application reenters the foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
    GameNode *gnode;
    GameHud *gHud;
    
    int selectedScreenIndex;
    
#pragma mark- init Game Objects
    cocos2d::Size winSize;
    cocos2d::Rect uiRect;
    float deviceScaleFloat;
    
    cocos2d::Rect getUIRect();
    void initVariable();
    void initGameObjects();
    
#pragma mark- database
    int lastDBUpdateVersion;
    int currentAppVersion;
    
    sqlite3 *database;
    sqlite3 *databaseBinary;
    
    void loadAllData();
    void createEditableCopyOfDatabaseIfNeeded();
    void createEditableCopyOfDatabaseBinaryIfNeeded();
    void initUserDefaults();
    void updateDBSchema();
    int getAppVersion(string strAppVersion);
    
#pragma mark- All Data
    vector<ScreenData*> *allScreenData;
    vector<Chair*> *allChair;
    
#pragma mark- Default
    void addNewUser();
    void addDefaultObject();
    void addAllScreen();
    
    
#pragma mark- static function
    static string convertCharToString(const unsigned char *constChar);
    static vector<string>* componentSeparatedByString(string _string, string separator);
    static vector<string>* componentSeparatedByWord(string _string, string separator);
    static bool isContainObject(cocos2d::Node *parrentNode,cocos2d::Node *childNode);
    
#pragma mark- Time
    static int getTime();
    static tm* getCurrentDateAndTime();
    static string getCurrentDate();
    
#pragma mark- Music
    void playBackgroundMusic();
    void stopBackgroundMusic();

#pragma mark- Test
    bool isTestMode();
    
#pragma mark- AdMob
    bool isAdMobInitCalled;
};

#endif // _APP_DELEGATE_H_

