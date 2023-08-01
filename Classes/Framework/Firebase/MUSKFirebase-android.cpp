//
//  MUSKFirebase.cpp
//  MUSK-mobile
//
//  Created by Tarek Saazeb on 5/25/18.
//

#include "MUSKFirebase.h"
#include "MUSKFirebaseManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"

static const string helperClassName = "org/cocos2dx/cpp/FirebaseManager";
static const string helperGoogleAnalyticsClassName = "org/cocos2dx/cpp/MUSKGoogleAnalytics";

#pragma mark- Firebase RemoteConfig Listener
extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onRemoteFetchComplete(JNIEnv* env, jobject thiz, jboolean isSuccess);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onRemoteFetchComplete(JNIEnv* env, jobject thiz, jboolean isSuccess)
{
    CCLOG("Java_org_cocos2dx_cpp_FirebaseManager_onRemoteFetchComplete");
    bool isSuccessBool = isSuccess;
    MUSKFirebaseManager::sharedManager()->onRemoteFetchCompleted(isSuccessBool);
}

#pragma mark- Firebase Admob Listener
extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onFireAdMobRewarded(JNIEnv* env, jobject thiz, jstring name, jstring currency, jdouble amount);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onFireAdMobRewarded(JNIEnv* env, jobject thiz, jstring name, jstring currency, jdouble amount)
{
    CCLOG("Java_org_cocos2dx_cpp_FirebaseManager_onFireAdMobRewarded");
    double _amount = amount;
    const char* _name = env->GetStringUTFChars(name, NULL);
    const char* _currency = env->GetStringUTFChars(currency, NULL);
    MUSKFirebaseManager::sharedManager()->onFireAdMobRewarded(std::string(_name), std::string(_currency), _amount);
}

extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onFireAdmobRewardedVideoAdLeftApplication(JNIEnv* env, jobject thiz, jstring name);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onFireAdmobRewardedVideoAdLeftApplication(JNIEnv* env, jobject thiz, jstring name)
{
    CCLOG("Java_org_cocos2dx_cpp_FirebaseManager_onFireAdmobRewardedVideoAdLeftApplication");
    const char* _name = env->GetStringUTFChars(name, NULL);
    MUSKFirebaseManager::sharedManager()->onFireAdmobRewardedVideoAdLeftApplication(std::string(_name));
}

extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onFireAdmobRewardedVideoAdClosed(JNIEnv* env, jobject thiz, jstring name);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onFireAdmobRewardedVideoAdClosed(JNIEnv* env, jobject thiz, jstring name)
{
    CCLOG("Java_org_cocos2dx_cpp_FirebaseManager_onFireAdmobRewardedVideoAdClosed");
    const char* _name = env->GetStringUTFChars(name, NULL);
    MUSKFirebaseManager::sharedManager()->onFireAdmobRewardedVideoAdClosed(std::string(_name));
}


extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onFireAdmobRewardedVideoAdFailedToLoad(JNIEnv* env, jobject thiz, jstring name);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onFireAdmobRewardedVideoAdFailedToLoad(JNIEnv* env, jobject thiz, jstring name)
{
    CCLOG("Java_org_cocos2dx_cpp_FirebaseManager_onFireAdmobRewardedVideoAdFailedToLoad");
    const char* _name = env->GetStringUTFChars(name, NULL);
    MUSKFirebaseManager::sharedManager()->onFireAdmobRewardedVideoAdFailedToLoad(std::string(_name));
}

extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onFireAdmobRewardedVideoAdLoaded(JNIEnv* env, jobject thiz, jstring name);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onFireAdmobRewardedVideoAdLoaded(JNIEnv* env, jobject thiz, jstring name)
{
    CCLOG("Java_org_cocos2dx_cpp_FirebaseManager_onFireAdmobRewardedVideoAdLoaded");
    const char* _name = env->GetStringUTFChars(name, NULL);
    MUSKFirebaseManager::sharedManager()->onFireAdmobRewardedVideoAdLoaded(std::string(_name));
}

extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onFireAdmobRewardedVideoAdOpened(JNIEnv* env, jobject thiz, jstring name);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onFireAdmobRewardedVideoAdOpened(JNIEnv* env, jobject thiz, jstring name)
{
    CCLOG("Java_org_cocos2dx_cpp_FirebaseManager_onFireAdmobRewardedVideoAdOpened");
    //const char* _name = env->GetStringUTFChars(name, NULL);
    //MUSKFirebaseManager::sharedManager()->onFireAdmobRewardedVideoAdOpened(std::string(_name));
}


extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onFireAdmobRewardedVideoStarted(JNIEnv* env, jobject thiz, jstring name);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onFireAdmobRewardedVideoStarted(JNIEnv* env, jobject thiz, jstring name)
{
    CCLOG("Java_org_cocos2dx_cpp_FirebaseManager_onFireAdmobRewardedVideoStarted");
    const char* _name = env->GetStringUTFChars(name, NULL);
    MUSKFirebaseManager::sharedManager()->onFireAdmobRewardedVideoStarted(std::string(_name));
}


extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onFireAdmobRewardedVideoCompleted(JNIEnv* env, jobject thiz, jstring name);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onFireAdmobRewardedVideoCompleted(JNIEnv* env, jobject thiz, jstring name)
{
    CCLOG("Java_org_cocos2dx_cpp_FirebaseManager_onFireAdmobRewardedVideoCompleted");
    const char* _name = env->GetStringUTFChars(name, NULL);
    MUSKFirebaseManager::sharedManager()->onFireAdmobRewardedVideoCompleted(std::string(_name));
}

#pragma mark- Firebase Analytics
void MUSKFirebase::initFireAnalytics()
{
    JniHelper::callStaticVoidMethod(helperClassName, "initFireAnalytics");
}

void MUSKFirebase::sendAnalyticsEvent(string _eventName, string _eventCategory, string _eventLabel, int _eventValue)
{
    JniHelper::callStaticVoidMethod(helperClassName, "logAnalyticEvent", _eventName, _eventCategory, _eventLabel, _eventValue);
}

void MUSKFirebase::sendVirtualCurrencyEvent(string _eventName, string _itemName, string _currencyName, int _value)
{
    JniHelper::callStaticVoidMethod(helperClassName, "sendVirtualCurrencyEvent", _eventName, _itemName, _currencyName, _value);
}

#pragma mark- Firebase Screen

void MUSKFirebase::setCurrentScreen(string _screenName, string _screenClass)
{
    JniHelper::callStaticVoidMethod(helperClassName, "setCurrentScreen", _screenName, _screenClass);
}

#pragma mark- Google Analytics
void MUSKFirebase::initGoogleAnalytics()
{
    JniHelper::callStaticVoidMethod(helperGoogleAnalyticsClassName, "initGoogleAnalytics");
}

void MUSKFirebase::sendGoogleAnalyticsEvent(string _eventName, string _eventCategory, string _eventLabel, int _eventValue)
{
    JniHelper::callStaticVoidMethod(helperGoogleAnalyticsClassName, "sendGoogleAnalyticsEvent", _eventName, _eventCategory, _eventLabel, _eventValue);
}

#pragma mark- Firebase RemoteConfig
void MUSKFirebase::initRemoteConfig()
{
    JniHelper::callStaticVoidMethod(helperClassName, "initRemoteConfig");
}

string MUSKFirebase::getRemoteConfigValue(string key)
{
    return JniHelper::callStaticStringMethod(helperClassName, "getRemoteConfigValue", key);
}

#pragma mark- Firebase AdMob
void MUSKFirebase::initAdmob()
{
    CCLOG("initAdmob-cpp");
    JniHelper::callStaticVoidMethod(helperClassName, "initAdmob");
}

void MUSKFirebase::loadRewardedVideoAd(string adUnitId)
{
    JniHelper::callStaticVoidMethod(helperClassName, "loadRewardedVideoAd", adUnitId);
}

void MUSKFirebase::showRewardedAd()
{
    JniHelper::callStaticVoidMethod(helperClassName, "showRewardedAd");
}

bool MUSKFirebase::isAdsAvailable()
{
    return JniHelper::callStaticBooleanMethod(helperClassName, "isAdsAvailable");
}

#pragma mark- Firebase AdMob Interstitial

void MUSKFirebase::initInterstitialAd()
{
    CCLOG("initAdmob-cpp");
    JniHelper::callStaticVoidMethod(helperClassName, "initInterstitialAd");
}

void MUSKFirebase::loadInterstitialAd(string adUnitId)
{
    JniHelper::callStaticVoidMethod(helperClassName, "loadInterstitialAd", adUnitId);
}

void MUSKFirebase::showInterstitialAd()
{
    JniHelper::callStaticVoidMethod(helperClassName, "showInterstitialAd");
}

bool MUSKFirebase::isInterstitialAdsAvailable()
{
    return JniHelper::callStaticBooleanMethod(helperClassName, "isInterstitialAdsAvailable");
}

#pragma mark- Firebase In App Messaging
extern "C"
{
JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onFirebaseInAppMessagingParamsReceived(JNIEnv* env, jobject thiz, jstring params);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onFirebaseInAppMessagingParamsReceived(JNIEnv* env, jobject thiz, jstring params)
{
    CCLOG("Java_org_cocos2dx_cpp_FirebaseManager_onFirebaseInAppMessagingParamsReceived");
    const char* _params = env->GetStringUTFChars(params, NULL);
    MUSKFirebaseManager::sharedManager()->onFirebaseInAppMessagingParamsReceived(std::string(_params));
}


#pragma mark- Firebase Messaging
extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onFirebaseMessagingParamsReceived(JNIEnv* env, jobject thiz, jstring params);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FirebaseManager_onFirebaseMessagingParamsReceived(JNIEnv* env, jobject thiz, jstring params)
{
    CCLOG("Java_org_cocos2dx_cpp_FirebaseManager_onFirebaseMessagingParamsReceived");
    const char* _params = env->GetStringUTFChars(params, NULL);
    MUSKFirebaseManager::sharedManager()->onFirebaseMessagingParamsReceived(std::string(_params));
}

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
