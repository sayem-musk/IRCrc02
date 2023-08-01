//
//  Config.cpp
//  MUSK-mobile
//
//  Created by Tarek Saazeb on 5/25/18.
//

#include "Config.h"
#include "AppDelegate.h"
#include "../CustomClass/ApplicationWrapper.h"

static Config *sharedInstance=NULL;

Config* Config::sharedManager()
{
    if(sharedInstance==NULL)
    {
        sharedInstance=Config::create();
    }
    return sharedInstance;
}


#pragma mark- Init Method

Config::~Config()
{
    
}

Config::Config()
{
    
}

Config* Config::create()
{
    Config* ret = new Config();
    if(ret && ret->init()) {
        return ret;
    } else {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool Config::init()
{
    bundleIdentifier=ApplicationWrapper::sharedManager()->getBundleId();
    gameId="1227695755";
    
#ifdef ANDROID
    admob_adunit_id_25 = "ca-app-pub-9984529693050185/3148240732";
    admob_adunit_id_20 = "ca-app-pub-9984529693050185/9522077394";
    admob_adunit_id_15 = "ca-app-pub-9984529693050185/8208995720";
    admob_adunit_id_10 = "ca-app-pub-9984529693050185/8499805611";
    admob_adunit_id_05 = "ca-app-pub-9984529693050185/6895914053";
    admob_adunit_id_default = "ca-app-pub-9984529693050185/4269750719";
    admob_adunit_id_interstitial = "ca-app-pub-9984529693050185/6496712394";
#else
    admob_adunit_id_25 = "ca-app-pub-9984529693050185/8669419909";
    admob_adunit_id_20 = "ca-app-pub-9984529693050185/4730174893";
    admob_adunit_id_15 = "ca-app-pub-9984529693050185/8781100545";
    admob_adunit_id_10 = "ca-app-pub-9984529693050185/8477848218";
    admob_adunit_id_05 = "ca-app-pub-9984529693050185/7468018872";
    admob_adunit_id_default = "ca-app-pub-9984529693050185/1864338407";
    admob_adunit_id_interstitial = "ca-app-pub-9984529693050185/8584013204";
#endif
    
#pragma mark- GoogleAnalytics Key
    google_analytics_key = "233233583";
    
#pragma mark- Android InAppKey
    strAndroidInAppKey="MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAmLH97N3qwawxXydRTzn/wRjAnOB6eGPKVoIgdBOR3J3kBqc+PrYQHGG1RMYacp42Agw5SJ7XYBJhSTPfKJDVdX37D7xz2b64V2dLizqHvCbCKYaK7n9MHL6YqtUyMPIAU6vb456zVe9vwdbfs7eebNFPvl7lhKePLJsh56UMYsi4/zJo4Rwln1jVu3KBRIGUoaSb8G2vQvgnUIKpMGFMoIlp3B118iZYQ5POIGsG116Z327xoYgwqpyc7Klld11ZC4E2StALEq6f5rrAkjDL9Nbg9F+TxQEd6ipspui7PJfWRMHs0tO0t0pXcnb4jYDDFo/EQX9cly7Dg+6ZVTC4YwIDAQAB";
    
    return true;
}



