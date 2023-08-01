#include "AppDelegate.h"
#include "HelloWorldScene.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

#include "Framework/Firebase/MUSKFirebaseManager.h"
#include "Framework/InAppPurchase/InappPurchaseWrapper/InApp.h"

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

static AppDelegate *sharedAppDelegate=NULL;

AppDelegate* AppDelegate::sharedApplication()
{
    return sharedAppDelegate;
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("IRC", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("IRC");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    auto frameSize = glview->getFrameSize();
    glview->setDesignResolutionSize(frameSize.width, frameSize.height, ResolutionPolicy::NO_BORDER);
    // if the frame's height is larger than the height of medium size.
    /*if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }*/

    sharedAppDelegate=this;
    register_all_packages();
    
    this->initVariable();
    this->loadAllData();

    // create a scene. it's an autorelease object
    //auto scene = HelloWorld::createScene();
    auto scene = GameNode::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}

#pragma mark- init Game Objects

Rect AppDelegate::getUIRect()
{
    /*AppDelegate *appDelegate=(AppDelegate*)AppDelegate::sharedApplication();
     string getDeviceModel=TWDevice::getDeviceModel();
     if(getDeviceModel=="iPhone")
     {
     Size rectSize=Director::getInstance()->getWinSize();
     if(rectSize.width==2436 && rectSize.height==1125)
     {
     float bazzleVaue=100;
     return Rect(bazzleVaue,0,appDelegate->winSize.width-bazzleVaue*2,appDelegate->winSize.height-0);
     }
     }\
     return Rect(0,0,appDelegate->winSize.width,appDelegate->winSize.height);*/
    
    return Director::getInstance()->getSafeAreaRect();
}

void AppDelegate::initVariable()
{
    MUSKFirebase::initFireAnalytics();

    MUSKFirebase::initGoogleAnalytics();
    MUSKFirebase::initRemoteConfig();
    
    MUSKFirebaseManager::sharedManager()->sendAnalyticsEvent("AppDelegate", "0", "0", 1);
        
    Size rectSize=Director::getInstance()->getWinSize();
    
    deviceScaleFloat=1.0f;
    
    if(rectSize.height==2208 && rectSize.width==1242) deviceScaleFloat=1.92f;
    else if(rectSize.height==1334 && rectSize.width==750) deviceScaleFloat=1.17f;
    else if(rectSize.height==2048 && rectSize.width==1536) deviceScaleFloat=1.9f;
    else if(rectSize.height==1024 && rectSize.width==768) deviceScaleFloat=0.925f;
    else if(rectSize.height==1704 && rectSize.width==960) deviceScaleFloat=1.50f;
    else if(rectSize.height==2436 && rectSize.width==1125) deviceScaleFloat=1.60f;
    //else if(rectSize.height==2732 && rectSize.width==2048) deviceScaleFloat=3.0f;
    else if(rectSize.height>=2048 && rectSize.width>=640*2.0) deviceScaleFloat=2.0;
    
    CCLOG("deviceScaleFloat %f",deviceScaleFloat);
    
    /*#ifdef ANDROID
     if(rectSize.width==2208 && rectSize.height==1242) deviceScaleFloat=1.92f;
     else if(rectSize.width==1334 && rectSize.height==750) deviceScaleFloat=1.17f;
     else if(rectSize.width==2048 && rectSize.height==1536) deviceScaleFloat=1.9f;
     else if(rectSize.width==1024 && rectSize.height==768) deviceScaleFloat=0.925f;
     else if(rectSize.width==1920 && rectSize.height==1080) deviceScaleFloat=1.7f;
     else if(rectSize.height>=2048/2 && rectSize.width>=(640*2.0)/2) deviceScaleFloat=2.0;
     else if(rectSize.height>=1792/2 && rectSize.width>=(640*1.75)/2) deviceScaleFloat=1.75;
     else if(rectSize.height>=1536/2 && rectSize.width>=(640*1.5)/2) deviceScaleFloat=1.5;
     else if(rectSize.height>=1280/2 && rectSize.width>=(640*1.25)/2) deviceScaleFloat=1.25;
     else if(rectSize.height>=1152/2 && rectSize.width>=(640*1.125)/2) deviceScaleFloat=1.125;
     else if(rectSize.height>=960/2 && rectSize.width>=(640*1.0)/2) deviceScaleFloat=1.0;
     else if(rectSize.height>=840/2 && rectSize.width>=(640*0.875)/2) deviceScaleFloat=0.875;
     else if(rectSize.height>=720/2 && rectSize.width>=(640*0.75)/2) deviceScaleFloat=0.75;
     else if(rectSize.height>=480/2 && rectSize.width>=(640*0.5)/2) deviceScaleFloat=0.5;
     else deviceScaleFloat=0.4;
     //deviceScaleFloat=rectSize.width/rectSize.height;
     #endif*/
    
#if ANDROID
    if(rectSize.height>=2048 && rectSize.width>=640*2.0) deviceScaleFloat=2.0;
    else if(rectSize.height>=1792 && rectSize.width>=640*1.75) deviceScaleFloat=1.75;
    else if(rectSize.height>=1536 && rectSize.width>=640*1.5) deviceScaleFloat=1.5;
    else if(rectSize.height>=1280 && rectSize.width>=640*1.25) deviceScaleFloat=1.25;
    else if(rectSize.height>=1152 && rectSize.width>=640*1.125) deviceScaleFloat=1.125;
    else if(rectSize.height>=960 && rectSize.width>=640*1.0) deviceScaleFloat=1.0;
    else if(rectSize.height>=840 && rectSize.width>=640*0.875) deviceScaleFloat=0.875;
    else if(rectSize.height>=720 && rectSize.width>=640*0.75) deviceScaleFloat=0.75;
    else if(rectSize.height>=480 && rectSize.width>=640*0.5) deviceScaleFloat=0.5;
    else deviceScaleFloat=0.4;
#endif
    
    winSize=Director::getInstance()->getWinSize();
    uiRect=AppDelegate::getUIRect();
    
    CCLOG("rectSize.width %f rectSize.height %f",rectSize.width,rectSize.height);
    CCLOG("deviceScaleFloat %f",deviceScaleFloat);
    
    allScreenData=new vector<ScreenData*>();
    allChair=new vector<Chair*>();
    
    isAdMobInitCalled = false;
    
    //CCLOG("uiRect %f %f %f %f",uiRect.origin.x,uiRect.origin.y,uiRect.size.width,uiRect.size.height);
}

void AppDelegate::initGameObjects()
{
    
}

#pragma mark- database

void AppDelegate::loadAllData()
{
    InApp::initInApp();
    VideoAdsManager::sharedManager();
#ifdef ANDROID
    this->createEditableCopyOfDatabaseBinaryIfNeeded();
#endif
    createEditableCopyOfDatabaseIfNeeded();
    initUserDefaults();
    
    Config *config=Config::sharedManager();
    CCLOG("bundleIdentifier %s",config->bundleIdentifier.c_str());

    addAllScreen();
    
    DBUserInfo *userInfo=DBUserInfo::sharedManager();
    updateDBSchema();
    
    ScreenData::reloadScreenData();
    CCLOG("allScreenData %d",(int)allScreenData->size());
    
    selectedScreenIndex=ScreenData::getSelectedScreenIndex();
    
    Resources *resources=Resources::sharedManager();
    resources->loadData(userInfo->screen_id);
    
    initGameObjects();
}

void AppDelegate::createEditableCopyOfDatabaseIfNeeded()
{
    // First, test for existence.
    FileUtils* fileUtils=FileUtils::getInstance();
    
#ifdef ANDROID
    string binaryPath=fileUtils->getWritablePath()+ "BinaryDatabase/database.sqlite";
#else
    string binaryPath=fileUtils->fullPathForFilename("database.sqlite");
#endif
    
    if (sqlite3_open(binaryPath.c_str(), &databaseBinary) == SQLITE_OK)
    {
        CCLOG("databaseBinary Open");
    }
    else {
        // Even though the open failed, call close to properly clean up resources.
        sqlite3_close(databaseBinary);
        CCLOGWARN("Failed to open Binary database with message '%s'.", sqlite3_errmsg(databaseBinary));
    }
    
    bool success;
    
    string writableDBPath=fileUtils->getWritablePath()+"database.sqlite";
    success=fileUtils->isFileExist(writableDBPath);
    
    if (!success)
    {
        //string defaultPath=fileUtils->fullPathForFilename("database.sqlite");
        Data defaultData=FileUtils::getInstance()->getDataFromFile(binaryPath);
        
        FILE* dest = fopen(writableDBPath.c_str(), "wb");
        fwrite(defaultData.getBytes(), 1, defaultData.getSize(), dest);
        fclose(dest);
    }
    
    CCLOG("writableDBPath %s",writableDBPath.c_str());
    
    if (sqlite3_open(writableDBPath.c_str(), &database) == SQLITE_OK)
    {
        CCLOG("database Open");
    }
    else
    {
        sqlite3_close(database);
    }
}

void AppDelegate::createEditableCopyOfDatabaseBinaryIfNeeded()
{
    FileUtils *fileManager=FileUtils::getInstance();
    fileManager->createDirectory(fileManager->getWritablePath()+"BinaryDatabase/");
    std::string writableDBPath=fileManager->getWritablePath() +"BinaryDatabase/database.sqlite";
    
    string defaultDBPath="database.sqlite";
    CCLOG("SourcePath: %s TargetPathBinary: %s", defaultDBPath.c_str(), writableDBPath.c_str());
    
    auto data= fileManager->getDataFromFile(defaultDBPath);
    FILE* dest=fopen(writableDBPath.c_str(), "wb");
    fwrite(data.getBytes(), 1, data.getSize(), dest);
    fclose(dest);
}

void AppDelegate::initUserDefaults()
{
    UserDefault *defaults=UserDefault::getInstance();
    
    lastDBUpdateVersion=getAppVersion(defaults->getStringForKey("lastDBUpdateVersion", "0.1"));
    
    string strAppVersion=AppDelegate::getVersion();
    CCLOG("strAppVersion %s",strAppVersion.c_str());
    currentAppVersion=getAppVersion(strAppVersion);
    CCLOG("currentAppVersion %d lastDBUpdateVersion %d ",currentAppVersion,lastDBUpdateVersion);
    
    defaults->setStringForKey("lastDBUpdateVersion", strAppVersion);
}

void AppDelegate::updateDBSchema()
{
    bool isUserFound=false;
    
    string str_user="select uid from users";
    const char *sql_user=str_user.c_str();
    sqlite3_stmt *statement_user;
    
    if (sqlite3_prepare_v2(database, sql_user, -1, &statement_user, NULL) == SQLITE_OK) {
        while (sqlite3_step(statement_user) == SQLITE_ROW) {
            isUserFound=true;
        }
        sqlite3_finalize(statement_user);
    }
    
    if(lastDBUpdateVersion==getAppVersion("0.1") && isUserFound==true)
    {
        
    }
    
    /*sqlite3_stmt *insert_update_sql;
     
     for (int i=0; i<sizeof(update_sql)/sizeof(string); i++)
     {
     CCLOG("update_sql %s",update_sql[i].c_str());
     const char *sqli = update_sql[i].c_str();
     if (sqlite3_prepare_v2(database, sqli, -1, &insert_update_sql, NULL) != SQLITE_OK) {
     CCLOG("Error: Cant execute hud_sql '%s'.", sqlite3_errmsg(database));
     }
     
     int success = sqlite3_step(insert_update_sql);
     if(success==SQLITE_ERROR)
     CCLOG("Error: Cant execute hud_sql '%s'.", sqlite3_errmsg(database));
     }*/
}

#pragma mark- AppVersion

int AppDelegate::getAppVersion(string strAppVersion)
{
    vector<string> *arrVersion=AppDelegate::componentSeparatedByString(strAppVersion, ".");
    string strVerion="";
    for (int i=0; i<3; i++)
    {
        if(i<arrVersion->size())
        {
            int subVersion=stoi(arrVersion->at(i));
            if(subVersion<10)
                strVerion=strVerion+"0"+to_string(subVersion);
            else
                strVerion=strVerion+to_string(subVersion);
        }
        else
        {
            strVerion=strVerion+"00";
        }
    }
    //CCLOG("strVerion %s",strVerion.c_str());
    return stoi(strVerion);
}

#pragma mark- Default

void AppDelegate::addNewUser()
{
    int timestamp=AppDelegate::getTime();
    
    vector<DBScreenInfo*> *allScreenInfo=DBScreenInfo::getAllScreenInfo();
    DBScreenInfo *screenInfo=allScreenInfo->at(0);
    
    DBUserInfo *newUser=DBUserInfo::create();
    
    newUser->screen_id  = screenInfo->screen_id;
    newUser->experience  = 0;
    newUser->levelid     = 1;
    newUser->visitat     =   timestamp;
    newUser->ext1       = "0";
    newUser->ext2       = "0";
    newUser->ext3       = "0";
    newUser->ext4       = "0";
    newUser->ext5       = "0";
    newUser->ext6       = "0";
    newUser->ext7       = "0";
    newUser->ext8       = "0";
    newUser->ext9       = "0";
    newUser->insertIntoDatabase();
    
    addDefaultObject();
    
    ScreenData *screenData=ScreenData::getScreenData(screenInfo->screen_id);
    screenData->unlockScreen();;
}

void AppDelegate::addDefaultObject()
{
    UserDefault *userDefault=UserDefault::getInstance();
    userDefault->setFloatForKey("EffectsVolume", 1);
    userDefault->setFloatForKey("BgVolume", 1);
    userDefault->flush();
}

void AppDelegate::addAllScreen()
{
    vector<DBScreenInfo*> *allScreenInfo=DBScreenInfo::getAllScreenInfo();
    
    for (int i=0; i<allScreenInfo->size(); i++)
    {
        DBScreenInfo *screenInfo=allScreenInfo->at(i);
        DBMyScreen *myScreen=DBMyScreen::create(screenInfo->screen_id,false);
        
        if(myScreen->my_screen_id==0)
        {
            ScreenData::createScreenInDatabase(screenInfo->screen_id);
            Resources::sharedManager()->addResourceForScreenInfo(screenInfo->screen_id);
        }
    }
    
}

#pragma mark- static function

string AppDelegate::convertCharToString(const unsigned char *constChar)
{
    //string convertedString=(const char*) constChar;
    //return convertedString;
    string convertedString="";
    if(constChar!=NULL)
    {
        string convertedChar(reinterpret_cast<const char*>(constChar));
        if (&convertedChar==NULL)
            convertedString="";
        else
            convertedString=convertedChar;
    }
    return convertedString;
}

vector<string>* AppDelegate::componentSeparatedByString(string _string, string separator)
{
    vector<string> *elems=new vector<string>();
    size_t pos = 0; string token;
    while ((pos = _string.find(separator)) != std::string::npos)
    {
        token = _string.substr(0, pos);
        elems->push_back(token);
        _string.erase(0, pos + separator.length());
    }
    elems->push_back(_string);
    return elems;
}

vector<string>* AppDelegate::componentSeparatedByWord(string _string, string separator)
{
    vector<string> *elems=new vector<string>();
    
    size_t pos=0;
    string token;
    while ((pos=_string.find(separator)) != std::string::npos) {
        token=_string.substr(0, pos);
        elems->push_back(token);
        _string.erase(0, pos + separator.length());
    }
    elems->push_back(_string);
    
    return elems;
}

bool AppDelegate::isContainObject(Node *parrentNode,Node *childNode)
{
    Vector<Node*> allObject=parrentNode->getChildren();
    for(unsigned int i=0; i < allObject.size(); i++)
    {
        if( allObject.at(i)==childNode)
        {
            return true;
        }
    }
    return false;
}

#pragma mark- Time

int AppDelegate::getTime()
{
    timeval curTime;
    gettimeofday(&curTime, NULL);
    //int milli=curTime.tv_usec/1000;
    return (int)curTime.tv_sec;
}

tm* AppDelegate::getCurrentDateAndTime()
{
    time_t rawtime;
    time ( &rawtime );
    struct tm * timeinfo={0};
    timeinfo = localtime ( &rawtime );
    
    /* CCLOG("year->%d",timeinfo->tm_year+1900);
     CCLOG("month->%d",timeinfo->tm_mon+1);
     CCLOG("date->%d",timeinfo->tm_mday);
     CCLOG("hour->%d",timeinfo->tm_hour);
     CCLOG("minutes->%d",timeinfo->tm_min);
     CCLOG("seconds->%d",timeinfo->tm_sec);*/
    
    timeinfo->tm_year=timeinfo->tm_year+1900;
    timeinfo->tm_mon=timeinfo->tm_mon+1;
    
    return timeinfo;
}

string AppDelegate::getCurrentDate()
{
    tm *timeinfo=AppDelegate::getCurrentDateAndTime();
    string strDate=to_string(timeinfo->tm_year);
    
    if(timeinfo->tm_mon<10)
        strDate=strDate+"-0"+to_string(timeinfo->tm_mon);
    else
        strDate=strDate+"-"+to_string(timeinfo->tm_mon);
    
    if(timeinfo->tm_mday<10)
        strDate=strDate+"-0"+to_string(timeinfo->tm_mday);
    else
        strDate=strDate+"-"+to_string(timeinfo->tm_mday);
    return strDate;
}

#pragma mark- Music

void AppDelegate::playBackgroundMusic()
{
    SimpleAudioEngine::getInstance()->playBackgroundMusic((folderSound+"background-music.mp3").c_str(),true);
    
    /*UserDefault *userDefault=UserDefault::getInstance();
     bool soundValue=userDefault->getBoolForKey(strSoundVaule.c_str());
     if(soundValue==true)
     {
     SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);
     SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
     }
     else
     {
     SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(100.0f);
     SimpleAudioEngine::getInstance()->setEffectsVolume(100.0f);
     }*/
}

void AppDelegate::stopBackgroundMusic()
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

#pragma mark- Test

bool AppDelegate::isTestMode()
{
    return false;
}
