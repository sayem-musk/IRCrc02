//
//  Config.h
//  MUSK-mobile
//
//  Created by Tarek Saazeb on 5/25/18.
//

#ifndef Config_h
#define Config_h

#include <stdio.h>
#include "IncludeAndroid.h"

using namespace std;

class Config
{
public:
    static Config* sharedManager();
#pragma mark- Init Method
    ~Config();
    Config();
    static Config* create();
    virtual bool init();
    
    string gameId;
    string bundleIdentifier;
    
#pragma mark- AdCredentials
    string admob_adunit_id_25;
    string admob_adunit_id_20;
    string admob_adunit_id_15;
    string admob_adunit_id_10;
    string admob_adunit_id_05;
    string admob_adunit_id_default;
    
    string admob_adunit_id_interstitial;
    
    string fb_2_interstitial_id_01;
    string fb_placement_id;
    string fb_2_placement_id_01;
    
#pragma mark- GoogleAnalytics Key
    string google_analytics_key;

#pragma mark- Android InAppKey
    string strAndroidInAppKey;
    
};

#endif /* Config_h */
