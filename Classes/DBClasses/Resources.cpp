
//
//  Resources.cpp
//  MUSK
//
//  Created by Tarek Saazeb on 6/12/16.
//
//

#include "Resources.h"
#include "AppDelegate.h"
#include "../CustomClass/CustomMath.h"
#include "../CustomClass/ClickerCalculation.h"

#pragma mark- Init Method

static Resources *sharedInstance=NULL;
Resources* Resources::sharedManager()
{
    if(sharedInstance==NULL)
    {
        sharedInstance=Resources::create();
    }
    return sharedInstance;
}

Resources::~Resources()
{
    
}

Resources::Resources()
{
    
}

Resources* Resources::create()
{
    Resources* ret = new Resources();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool Resources::init()
{
    allResourceInfo=new vector<DBResourceInfo*>();
    
    return true;
}

void Resources::loadData(int _screen_id)
{
    allResourceInfo->clear();
    AppDelegate *appDelegate=AppDelegate::sharedApplication();
    
    sqlite3_stmt *iresource_statement=NULL;
    
    string strQuery="select resourceid from resources where screen_id="+to_string(_screen_id);
    
    if (sqlite3_prepare_v2(appDelegate->database, strQuery.c_str(), -1, &iresource_statement, NULL) == SQLITE_OK)
    {
        while (sqlite3_step(iresource_statement) == SQLITE_ROW)
        {
            int resid=sqlite3_column_int(iresource_statement,0);
            allResourceInfo->push_back(DBResourceInfo::create(resid));
        }
    }
    else
    {
        CCLOG("%s", sqlite3_errmsg(appDelegate->database));
    }
    
    // Reset the statement for future reuse.
    sqlite3_reset(iresource_statement);
    sqlite3_finalize(iresource_statement);
}

#pragma mark- DBResource

DBResourceInfo* Resources::getResourceInfo(int _resid)
{
    for (int i=0; i<allResourceInfo->size(); i++)
    {
        DBResourceInfo *resourceInfo=allResourceInfo->at(i);
        if(_resid==resourceInfo->resourceid)
        {
            return resourceInfo;
        }
    }
    return DBResourceInfo::create(_resid);
}

vector<string> *Resources::amountOfResource(int _resid)
{
    if (this->allResourceInfo->size() ==0)
    {
        DBUserInfo *userInfo=DBUserInfo::sharedManager();
        this->loadData(userInfo->screen_id);
    }
    
    vector<string> *finalValue=new vector<string>();
    for (int i=0; i<allResourceInfo->size(); i++)
    {
        DBResourceInfo *resourceInfo=allResourceInfo->at(i);
        if(_resid==resourceInfo->resourceid)
        {
            finalValue->push_back(resourceInfo->amount);
            finalValue->push_back(resourceInfo->amount_exp);
            break;
        }
    }
    return finalValue;
}

void Resources::addResource(int _resid,vector<string> *_amount)
{
    for (int i=0; i<allResourceInfo->size(); i++)
    {
        DBResourceInfo *resourceInfo=allResourceInfo->at(i);
        if(_resid==resourceInfo->resourceid)
        {
            vector<string> *arrResourceAmount=new vector<string>();
            arrResourceAmount->push_back(resourceInfo->amount);
            arrResourceAmount->push_back(resourceInfo->amount_exp);
            
            vector<string> *finalAnswer=ClickerCalculation::addition(arrResourceAmount, _amount);
            resourceInfo->amount=finalAnswer->at(0);
            resourceInfo->amount_exp=finalAnswer->at(1);
            resourceInfo->updateDatabase();
        }
    }
  
    //MUSKScoreBar::sharedManager()->updateScoreBar();
}

void Resources::subResource(int _resid,vector<string> *_amount)
{
    for (int i=0; i<allResourceInfo->size(); i++)
    {
        DBResourceInfo *resourceInfo=allResourceInfo->at(i);
        if(_resid==resourceInfo->resourceid)
        {
            vector<string> *arrResourceAmount=Resources::amountOfResource(_resid);
            
            if(ClickerCalculation::isSmaller(arrResourceAmount, _amount)==false)
            {
                vector<string> *finalAnswer=ClickerCalculation::subtraction(arrResourceAmount, _amount);
                resourceInfo->amount=finalAnswer->at(0);
                resourceInfo->amount_exp=finalAnswer->at(1);
                resourceInfo->updateDatabase();
            }
        }
    }
    
    //MUSKScoreBar::sharedManager()->updateScoreBar();
}

void Resources::addResourcePercentage(int _resid,string _percentage)
{
    DBResourceInfo *resourceInfo=Resources::getResourceInfo(_resid);
    
    vector<string> *arrAmount=new vector<string>();
    arrAmount->push_back(resourceInfo->amount);
    arrAmount->push_back(resourceInfo->amount_exp);
    
    string strResourceAmount=resourceInfo->amount+"e"+resourceInfo->amount_exp;
    
    vector<string> *percentage=ClickerCalculation::multiplication(strResourceAmount,_percentage);
    percentage=ClickerCalculation::division(percentage,100);
    
    vector<string> *finalAnswer=ClickerCalculation::addition(percentage,arrAmount);
    resourceInfo->amount=finalAnswer->at(0);
    resourceInfo->amount_exp=finalAnswer->at(1);
    resourceInfo->updateDatabase();
}

bool Resources::checkResourceAvailable(int _resid,vector<string> *_amount,bool _isShow)
{
    vector<string> *arrResourceAmount=Resources::amountOfResource(_resid);
    
    if(ClickerCalculation::isSmaller(arrResourceAmount, _amount)==false)
        return true;
    else
    {
        if(_isShow)
        {
            CCLOG("Show Alert");
            string message="You do not have enough resource to buy this item." ;
            AlertView *alert=AlertView::create("Can't Purchase!",message,this);
            alert->addButtonWithTitle("BUY");
            alert->addButtonWithTitle("LATER");
            alert->tag=1;
            alert->show();
        }
        return false;
    }
}

void Resources::alertViewCallBack(int tag,int buttonIndex)
{
    if(tag==1)
    {
        //CCLog("buttonIndex--> %d",buttonIndex);
        if(buttonIndex==0)
        {
            //AppDelegate *appDelegate=AppDelegate::sharedApplication();
            //appDelegate->gHud->loadStorePanel(panelInAppPurchase);
        }
    }
    else if(tag==2)
    {
    }
    else if(tag==3)
    {
    }
}

float Resources::bucksValueForResource(int _resid)
{
    for (int i=0; i<allResourceInfo->size(); i++)
    {
        DBResourceInfo *resourceInfo=allResourceInfo->at(i);
        if(_resid==resourceInfo->resourceid)
        {
            return (stof(resourceInfo->bucks_value)/100.0f);
        }
    }
    return 0;
}

void Resources::addResourceForScreenInfo(int _screen_id)
{
    for(int i=0;i<2;i++)
    {
        int resourceType=coinsIndex;
        string strResourceName="Coin";
        string strResourceAmount="100";
        switch(i)
        {
            case 0:
            {
                resourceType=coinsIndex;
                strResourceName="Coin";
                strResourceAmount="100";
            }
                break;
            case 1:
            {
                resourceType=bucksIndex;
                strResourceName="Gems";
                strResourceAmount="50";
            }
                break;
        }

        //strResourceAmount="99999999";
        
        DBResourceInfo *resourceInfo=DBResourceInfo::create();
        
        resourceInfo->resource_type=resourceType;
        resourceInfo->resource_name=strResourceName;
        resourceInfo->screen_id=_screen_id;
        resourceInfo->amount=strResourceAmount;
        resourceInfo->amount_exp="0";
        resourceInfo->capacity="0";
        resourceInfo->bucks_value="0";
        resourceInfo->ext1="0";
        resourceInfo->ext2="0";
        resourceInfo->ext3="0";
        resourceInfo->ext4="0";
        resourceInfo->ext5="0";
        resourceInfo->ext6="0";
        resourceInfo->ext7="0";
        resourceInfo->ext8="0";
        resourceInfo->ext9="0";
        
        resourceInfo->insertIntoDatabase();
    }
}





