//
//  ScreenData.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 2/16/20.
//

#include "ScreenData.h"
#include "AppDelegate.h"
#include "../DBClasses/DBAttributesInfo.h"
#include "../DBClasses/DBLevels.h"

#pragma mark- Init Method

ScreenData::~ScreenData()
{
    
}

ScreenData::ScreenData()
{
    
}

ScreenData* ScreenData::create()
{
    ScreenData* ret = new ScreenData();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool ScreenData::init()
{
   return true;
}

ScreenData* ScreenData::create(int _my_screen_id)
{
    ScreenData* ret = new ScreenData();
    if(ret && ret->init(_my_screen_id)) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool ScreenData::init(int _my_screen_id)
{
    myScreen=DBMyScreen::create(_my_screen_id);
    screenInfo=DBScreenInfo::create(myScreen->screen_id);
    
    return true;
}

vector<string>* ScreenData::getPriceForType(int type)
{
    DBAttributesInfo *attributesInfo;
    vector<string> *arrPrice=ClickerCalculation::getNewVector("0", "0");
    switch(type)
    {
        case TypeTicketPrice:
        {
            attributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(TypeTicketPrice,myScreen->ticket_price_level+1);
            
        }
            break;
        case TypeSpeed:
        {
            attributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(TypeSpeed,myScreen->speed_level+1);
        }
            break;
        case TypeCars:
        {
            attributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(TypeCars,myScreen->cars_level+1);
        }
            break;
    
        case TypeCustomerFrequency:
        {
            attributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(TypeCustomerFrequency,myScreen->customer_frequency_level+1);
        }
            break;
        case TypeStationCapacity:
        {
            attributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(TypeStationCapacity,myScreen->station_capacity_level+1);
        }
            break;
        case TypeQueueCapacity:
        {
            attributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(TypeQueueCapacity,myScreen->queue_capacity_level+1);
        }
            break;
            
        case TypeBalloons:
        {
            attributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(TypeBalloons,myScreen->balloons_level+1);
        }
            break;
            
        case TypeIceCream:
        {
            attributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(TypeIceCream,myScreen->icecream_level+1);
        }
            break;
            
        case TypeFastFood:
        {
            attributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(TypeFastFood,myScreen->fastfood_level+1);
        }
            break;
            
        case TypeAirShip:
        {
            attributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(TypeAirShip,myScreen->airship_level+1);
        }
            break;
    }
    
    if(attributesInfo->attributes_id!=0)
    {
        vector<string> *arrAttributes=AppDelegate::componentSeparatedByString(attributesInfo->attributes_price, ",");
        if (arrAttributes->size()==2)
            arrPrice=ClickerCalculation::getNewVector(arrAttributes->at(1));
    }
    
    return arrPrice;
}

void ScreenData::unlockScreen()
{
    myScreen->is_unlocked=1;
    myScreen->collect_coins_per_sec=1;
    myScreen->updateDatabase();
}

vector<string>* ScreenData::getCoinsRewards()
{
    DBLevels *currentLevel=DBLevels::getLevels(this->myScreen->screen_level);
    
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    
    vector<string> *arrReward=ClickerCalculation::getNewVector(currentLevel->rewards, currentLevel->rewards_xp);

    DBAttributesInfo *ticketAttributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(TypeTicketPrice,myScreen->ticket_price_level);

    if(ticketAttributesInfo->attributes_id!=0)
    {
        int effect=stoi(ticketAttributesInfo->attributes_effect);
        arrReward=ClickerCalculation::addition(arrReward, ClickerCalculation::getNewVector(to_string(effect)));
    }

    if(appDelegate->gnode->doubleCoinsFor5MinTime>=0)
    {
        arrReward=ClickerCalculation::multiplication(arrReward, ClickerCalculation::getNewVector("2"));
    }
    
    DBAttributesInfo *icecreamAttributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(TypeIceCream,myScreen->icecream_level);
    vector<string> *icecreamAddReward=ClickerCalculation::getNewVector("0");
    if(icecreamAttributesInfo->attributes_id!=0)
    {
        int effect=stoi(icecreamAttributesInfo->attributes_effect);
        
        icecreamAddReward=ClickerCalculation::multiplication(arrReward, ClickerCalculation::getNewVector(to_string(effect)));
        icecreamAddReward=ClickerCalculation::division(icecreamAddReward, ClickerCalculation::getNewVector("100"));
    }
    
    DBAttributesInfo *fastfoodAttributesInfo=DBAttributesInfo::getAttributesInfoForTypeLevel(TypeIceCream,myScreen->fastfood_level);
    
    vector<string> *fastfoodAddReward=ClickerCalculation::getNewVector("0");
    if(fastfoodAttributesInfo->attributes_id!=0)
    {
        int effect=stoi(fastfoodAttributesInfo->attributes_effect);
        
        fastfoodAddReward=ClickerCalculation::multiplication(arrReward, ClickerCalculation::getNewVector(to_string(effect)));
        fastfoodAddReward=ClickerCalculation::division(fastfoodAddReward, ClickerCalculation::getNewVector("100"));
    }

    arrReward=ClickerCalculation::addition(arrReward, fastfoodAddReward);
    arrReward=ClickerCalculation::addition(arrReward, icecreamAddReward);
    
    return arrReward;
}

void ScreenData::addCoinsExperience()
{
    vector<string> *arrReward=this->getCoinsRewards();
    
    Resources *resources=Resources::sharedManager();
    resources->addResource(coinsIndex, arrReward);
    
    DBLevels *nextLevel=DBLevels::getLevels(this->myScreen->screen_level+1);
    //CCLOG("nextLevel-- %d %d",nextLevel->experience,nextLevel->experience_per_customer);
    int experience=MIN(this->myScreen->screen_experience+nextLevel->experience_per_customer, nextLevel->experience);
    
    this->myScreen->screen_experience=experience;
    this->myScreen->updateDatabase();
    
    MUSKScoreBar::sharedManager()->setExperiencePrograssBar();

    if(experience==nextLevel->experience)
    {
        MUSKScoreBar::sharedManager()->setLevelUpShow(true);
    }
    //CCLOG("this->myScreen->screen_experience %d",this->myScreen->screen_experience);
}

void ScreenData::setLevelUpButton()
{
    DBLevels *nextLevel=DBLevels::getLevels(this->myScreen->screen_level+1);
    
    if(nextLevel->levelid!=0)
    {
        if(this->myScreen->screen_experience==nextLevel->experience)
        {
            MUSKScoreBar::sharedManager()->setLevelUpShow(true);
        }
        else
        {
            MUSKScoreBar::sharedManager()->setLevelUpShow(false);
        }
    }
    else
    {
        MUSKScoreBar::sharedManager()->setLevelUpShow(false);
    }
}

#pragma mark- ScreenData

void ScreenData::reloadScreenData()
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    appDelegate->allScreenData->clear();
    
    string str_screen="select my_screen_id from my_screen";
    const char *sql_screen=str_screen.c_str();
    sqlite3_stmt *statement_screen;
    
    if (sqlite3_prepare_v2(appDelegate->database, sql_screen, -1, &statement_screen, NULL) == SQLITE_OK) {
        while (sqlite3_step(statement_screen) == SQLITE_ROW) {
            int primaryKey=sqlite3_column_int(statement_screen, 0);
            ScreenData::addScreenData(primaryKey);
        }
    }
    sqlite3_finalize(statement_screen);
}
void ScreenData::addScreenData(int _my_screen_id)
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    
    ScreenData *screenData=ScreenData::create(_my_screen_id);
    appDelegate->allScreenData->push_back(screenData);
}

void ScreenData::createScreenInDatabase(int _screen_id)
{
    DBScreenInfo *screenInfo=DBScreenInfo::create(_screen_id);
    
    DBMyScreen *newScreen=DBMyScreen::create();
    
    newScreen->screen_id=screenInfo->screen_id;
    newScreen->is_unlocked=0;
    newScreen->screen_level=1;
    newScreen->screen_experience=0;
    newScreen->collect_coins_per_sec=0;
    newScreen->customer_frequency_level=1;
    newScreen->station_capacity_level=1;
    newScreen->queue_capacity_level=1;
    newScreen->ticket_price_level=1;
    newScreen->speed_level=1;
    newScreen->cars_level=1;
    newScreen->balloons_level=0;
    newScreen->icecream_level=0;
    newScreen->fastfood_level=0;
    newScreen->airship_level=0;
    newScreen->ext1="0";
    newScreen->ext2="0";
    newScreen->ext3="0";
    newScreen->ext4="0";
    newScreen->ext5="0";
    newScreen->ext6="0";
    newScreen->ext7="0";
    newScreen->ext8="0";
    newScreen->ext9="0";
    newScreen->insertIntoDatabase();
    
    ScreenData::addScreenData(newScreen->my_screen_id);
}

ScreenData* ScreenData::getSelectedScreenData()
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    for(int i=0;i<appDelegate->allScreenData->size();i++)
    {
        ScreenData *screenData=appDelegate->allScreenData->at(i);
        DBUserInfo *userInfo=DBUserInfo::sharedManager();
        
        if(screenData->screenInfo->screen_id==userInfo->screen_id)
        {
            return screenData;
        }
    }
    return appDelegate->allScreenData->at(0);
}

int ScreenData::getSelectedScreenIndex()
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    for(int i=0;i<appDelegate->allScreenData->size();i++)
    {
        ScreenData *screenData=appDelegate->allScreenData->at(i);
        DBUserInfo *userInfo=DBUserInfo::sharedManager();
        
        if(screenData->screenInfo->screen_id==userInfo->screen_id)
        {
            return i;
        }
    }
    return 0;
}

ScreenData* ScreenData::getScreenData(int screen_id)
{
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    for(int i=0;i<appDelegate->allScreenData->size();i++)
    {
        ScreenData *screenData=appDelegate->allScreenData->at(i);
        
        if(screenData->screenInfo->screen_id==screen_id)
        {
            return screenData;
        }
    }
    return appDelegate->allScreenData->at(0);
}







