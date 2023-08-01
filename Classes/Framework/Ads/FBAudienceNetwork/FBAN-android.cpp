

#include "FBAN.h"
#include "FBANManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"

static const string helperClassName = "org/cocos2dx/cpp/FBAudienceNetworkManager";

#pragma mark- FB Audience Network Interstitial Ad Callback Listeners

//public static native void onInterstitialLoad(Boolean isLoaded, int errorCode);
extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onInterstitialLoad(JNIEnv* env, jobject thiz, jboolean isLoaded, jint errorCode);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onInterstitialLoad(JNIEnv* env, jobject thiz, jboolean isLoaded, jint errorCode)
{
    CCLOG("Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onInterstitialLoad");
    bool _isLoaded = isLoaded;
    int _errorCode = errorCode;
    FBANManager::sharedManager()->onInterstitialLoad(_isLoaded, _errorCode);
}

//public static native void onInterstitialDisplayed();
extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onInterstitialDisplayed(JNIEnv* env, jobject thiz);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onInterstitialDisplayed(JNIEnv* env, jobject thiz)
{
    CCLOG("Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onInterstitialDisplayed");
    FBANManager::sharedManager()->onInterstitialDisplayed();
}
//public static native void onInterstitialDismissed();
extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onInterstitialDismissed(JNIEnv* env, jobject thiz);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onInterstitialDismissed(JNIEnv* env, jobject thiz)
{
    CCLOG("Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onInterstitialDismissed");
    FBANManager::sharedManager()->onInterstitialDismissed();
}

//public static native void onError();
extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onError(JNIEnv* env, jobject thiz);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onError(JNIEnv* env, jobject thiz)
{
    CCLOG("Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onError");
    FBANManager::sharedManager()->onError();
}

//public static native void onAdLoaded();
extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onAdLoaded(JNIEnv* env, jobject thiz);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onAdLoaded(JNIEnv* env, jobject thiz)
{
    CCLOG("Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onAdLoaded");
    FBANManager::sharedManager()->onAdLoaded();
}

//public static native void onAdClicked();
extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onAdClicked(JNIEnv* env, jobject thiz);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onAdClicked(JNIEnv* env, jobject thiz)
{
    CCLOG("Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onAdClicked");
    FBANManager::sharedManager()->onAdClicked();
}

extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onLoggingImpression(JNIEnv* env, jobject thiz);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onLoggingImpression(JNIEnv* env, jobject thiz)
{
    CCLOG("Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onLoggingImpression");
    FBANManager::sharedManager()->onLoggingImpression();
}

// rewarded video
extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onRewardedError(JNIEnv* env, jobject thiz, jstring name, jstring msg);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onRewardedError(JNIEnv* env, jobject thiz, jstring name, jstring msg)
{
    CCLOG("Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onRewardedError");
    const char* _name = env->GetStringUTFChars(name, NULL);
    const char* _msg = env->GetStringUTFChars(msg, NULL);
    FBANManager::sharedManager()->onRewardedError(std::string(_name),std::string(_msg));
}

extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onRewardedAdLoaded(JNIEnv* env, jobject thiz, jstring name);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onRewardedAdLoaded(JNIEnv* env, jobject thiz, jstring name)
{
    CCLOG("Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onRewardedAdLoaded");
    const char* _name = env->GetStringUTFChars(name, NULL);
    FBANManager::sharedManager()->onRewardedAdLoaded(std::string(_name));
}

extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onRewardedAdClicked(JNIEnv* env, jobject thiz, jstring name);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onRewardedAdClicked(JNIEnv* env, jobject thiz, jstring name)
{
    CCLOG("Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onRewardedAdClicked");
    const char* _name = env->GetStringUTFChars(name, NULL);
    FBANManager::sharedManager()->onRewardedAdClicked(std::string(_name));
}

extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onRewardedLoggingImpression(JNIEnv* env, jobject thiz, jstring name);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onRewardedLoggingImpression(JNIEnv* env, jobject thiz, jstring name)
{
    CCLOG("Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onRewardedLoggingImpression");
    const char* _name = env->GetStringUTFChars(name, NULL);
    FBANManager::sharedManager()->onRewardedLoggingImpression(std::string(_name));
}

extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onRewardedVideoCompleted(JNIEnv* env, jobject thiz, jdouble amount, jstring name);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onRewardedVideoCompleted(JNIEnv* env, jobject thiz, jdouble amount, jstring name)
{
    CCLOG("Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onRewardedVideoCompleted");
    const char* _name = env->GetStringUTFChars(name, NULL);
    double _amount = amount;
    FBANManager::sharedManager()->onRewardedVideoCompleted(_amount, std::string(_name));
}

extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onRewardedVideoClosed(JNIEnv* env, jobject thiz, jstring name);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onRewardedVideoClosed(JNIEnv* env, jobject thiz, jstring name)
{
    CCLOG("Java_org_cocos2dx_cpp_FBAudienceNetworkManager_onRewardedVideoClosed");
    const char* _name = env->GetStringUTFChars(name, NULL);
    FBANManager::sharedManager()->onRewardedVideoClosed(std::string(_name));
}

#pragma mark- FB Audience Network Interstitial Ad
void FBAN::initInterstitialAd(string placementID){
    JniHelper::callStaticVoidMethod(helperClassName, "initInterstitialAd", placementID);
    CCLOG("88 FBAN::initInterstitialAd");
}

void FBAN::loadInterstitialAd(){
    JniHelper::callStaticVoidMethod(helperClassName, "loadInterstitialAd");
}

bool FBAN::isInterstitialAdLoaded(){
    return JniHelper::callStaticBooleanMethod(helperClassName, "isInterstitialAdLoaded");
}

void FBAN::showInterstitialAd(){
    JniHelper::callStaticVoidMethod(helperClassName, "showInterstitialAd");
}

#pragma mark- FB Audience Network Interstitial Ad 2
void FBAN::initInterstitialAd2(string placementID){
    JniHelper::callStaticVoidMethod(helperClassName, "initInterstitialAd2", placementID);
    CCLOG("88 FBAN::initInterstitialAd2");
}

void FBAN::loadInterstitialAd2(){
    JniHelper::callStaticVoidMethod(helperClassName, "loadInterstitialAd2");
}

bool FBAN::isInterstitialAdLoaded2(){
    return JniHelper::callStaticBooleanMethod(helperClassName, "isInterstitialAdLoaded2");
}

void FBAN::showInterstitialAd2(){
    JniHelper::callStaticVoidMethod(helperClassName, "showInterstitialAd2");
}

#pragma mark- FB Audience Network Rewarded Video
void FBAN::initRewardedAd()
{
    JniHelper::callStaticVoidMethod(helperClassName, "initRewardedAd");
}

void FBAN::loadRewardedAd(string placeMentID)
{
    JniHelper::callStaticVoidMethod(helperClassName, "loadRewardedAd", placeMentID);
}

bool FBAN::isRewardedAdLoaded()
{
    return JniHelper::callStaticBooleanMethod(helperClassName, "isRewardedAdLoaded");
}

void FBAN::showRewardedAd()
{
    JniHelper::callStaticVoidMethod(helperClassName, "showRewardedAd");
}

#pragma mark- FB Audience Network Rewarded Video 2
void FBAN::initRewardedAd2()
{
    JniHelper::callStaticVoidMethod(helperClassName, "initRewardedAd2");
}

void FBAN::loadRewardedAd2(string placeMentID)
{
    JniHelper::callStaticVoidMethod(helperClassName, "loadRewardedAd2", placeMentID);
}

bool FBAN::isRewardedAdLoaded2()
{
    return JniHelper::callStaticBooleanMethod(helperClassName, "isRewardedAdLoaded2");
}

void FBAN::showRewardedAd2()
{
    JniHelper::callStaticVoidMethod(helperClassName, "showRewardedAd2");
}

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
