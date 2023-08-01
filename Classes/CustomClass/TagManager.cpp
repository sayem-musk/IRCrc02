//
//  TagManager.cpp
//  IRC-mobile
//
//  Created by Tarek Saazeb on 5/13/20.
//

#include "TagManager.h"
#include "AppDelegate.h"
#include "../Framework/Firebase/MUSKFirebaseManager.h"

vector<int> *TagManager::getAdSearchOrder()
{
    AppDelegate *appDelegate = (AppDelegate*)AppDelegate::sharedApplication();
    
    vector<int> *defaultAdSearchOrder = new vector<int>();
    string remoteValueStr = MUSKFirebaseManager::sharedManager()->getRemoteConfigValue("adSearchOrder");
    if (!remoteValueStr.empty() && remoteValueStr != "") {
        vector<string> *remoteValueArray = appDelegate->componentSeparatedByString(remoteValueStr, ",");
        if (remoteValueArray->size() > 0) {
            defaultAdSearchOrder->clear();
            for (int i = 0; i < remoteValueArray->size(); ++i) {
                defaultAdSearchOrder->push_back(stoi(remoteValueArray->at(i)));
            }
        }
    }
    
    if(defaultAdSearchOrder->size()==0)
    {
        defaultAdSearchOrder->clear();
        defaultAdSearchOrder=TagManager::getDefaultAdsSearchOrder();
    }
    return defaultAdSearchOrder;
}

vector<int> *TagManager::getDefaultAdsSearchOrder()
{
    vector<int> *defaultAdSearchOrder = new vector<int>();
    
    string strDefaultValue="201,202,203,204,205,206";
    
    if(strDefaultValue!="")
    {
        vector<string> *arrDefaultValue=AppDelegate::componentSeparatedByWord(strDefaultValue, ",");
        for (int i=0; i<arrDefaultValue->size(); i++)
        {
            defaultAdSearchOrder->push_back(stoi(arrDefaultValue->at(i)));
        }
    }
    return defaultAdSearchOrder;
}

int TagManager::getAnalyticsService()
{
    // 0 = Google Analytics and Firebase Analytics Both
    // 1 = Firebase Analytics
    // 2 = Google Analytics
    // others = nothing
    int defaultValue = 0;
    
    string remoteValueStr = MUSKFirebaseManager::sharedManager()->getRemoteConfigValue("AnalyticsService");
    if (!remoteValueStr.empty() && remoteValueStr != "") {
        defaultValue = stoi(remoteValueStr);
    }
    
    return defaultValue;
}
