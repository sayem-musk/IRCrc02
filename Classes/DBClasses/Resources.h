//
//  Resources.h
//  MUSK
//
//  Created by Tarek Saazeb on 6/12/16.
//
//

#ifndef Resources_h
#define Resources_h

#include <stdio.h>
#include "../DBClasses/DBResourceInfo.h"
#include "../CustomClass/AlertView.h"

enum
{
    experienceIndex = 0,
    coinIndex = 1,
    buckIndex = 2,
    foodIndex = 3,
    darkElixerIndex = 4,
    
    dollarIndex = 101,
    
    productIndex=1001,
};

using namespace std;

class Resources : public AlertViewDelegate
{
public:
#pragma mark- Shared Manager
    static Resources* sharedManager();
    
    vector<DBResourceInfo*> *allResourceInfo;
    
#pragma mark- Init Method
    ~Resources();
    Resources();
    static Resources* create();
    virtual bool init();
   
    void loadData(int _screen_id);
    
#pragma mark- AlertView
    void alertViewCallBack(int tag,int buttonIndex);
    
#pragma mark- DBResource    
    DBResourceInfo *getResourceInfo(int _resid);
    vector<string> *amountOfResource(int _resid);
    void addResource(int _resid,vector<string> *_amount);
    void subResource(int _resid,vector<string> *_amount);
    void addResourcePercentage(int _resid,string _percentage);
    
    bool checkResourceAvailable(int _resid,vector<string> *_amount,bool _isShow);
    
    float bucksValueForResource(int _resid);

#pragma mark- Screen Info
    void addResourceForScreenInfo(int _screen_id);
};

#endif /* Resources_h */
