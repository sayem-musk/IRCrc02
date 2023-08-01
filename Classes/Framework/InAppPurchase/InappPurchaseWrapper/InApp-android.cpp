//
//  ITIWCrashlytics-android.cpp
//  ITIW
//
//  Created by itiw on 3/3/18.
//
//

#include "InApp.h"
#include "InAppManager.h"
#include "../../../CustomClass/Config.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"

static const string helperClassName = "org/cocos2dx/cpp/ITIWInappPurchase";

#pragma mark- Inapp Purchase Listener
extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_ITIWInappPurchase_onProductPurchasedInapp(JNIEnv* env, jobject thiz, jstring productId, jstring purchaseToken, jstring purchaseSignature);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_ITIWInappPurchase_onProductPurchasedInapp(JNIEnv* env, jobject thiz, jstring productId, jstring purchaseToken, jstring purchaseSignature)
{
    CCLOG("Java_org_cocos2dx_cpp_ITIWInappPurchase_onProductPurchasedInapp");
    const char* _productId = env->GetStringUTFChars(productId, NULL);
    const char* _purchaseToken = env->GetStringUTFChars(purchaseToken, NULL);
    const char* _purchaseSignature = env->GetStringUTFChars(purchaseSignature, NULL);
    InAppManager::sharedManager()->onProductPurchasedInapp(std::string(_productId),std::string(_purchaseToken),std::string(_purchaseSignature));
}

extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_ITIWInappPurchase_onPurchaseHistoryRestoredInapp(JNIEnv* env, jobject thiz);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_ITIWInappPurchase_onPurchaseHistoryRestoredInapp(JNIEnv* env, jobject thiz)
{
    CCLOG("Java_org_cocos2dx_cpp_ITIWInappPurchase_onPurchaseHistoryRestoredInapp");
    InAppManager::sharedManager()->onPurchaseHistoryRestoredInapp();
}

extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_ITIWInappPurchase_onBillingErrorInapp(JNIEnv* env, jobject thiz, jint errorCode, jstring errorMessage);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_ITIWInappPurchase_onBillingErrorInapp(JNIEnv* env, jobject thiz, jint errorCode, jstring errorMessage)
{
    CCLOG("Java_org_cocos2dx_cpp_ITIWInappPurchase_onBillingErrorInapp");
    int _errorCode = errorCode;
    const char* _errorMessage = env->GetStringUTFChars(errorMessage, NULL);
    InAppManager::sharedManager()->onBillingErrorInapp(_errorCode, std::string(_errorMessage));
}

extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_ITIWInappPurchase_onBillingInitializedInapp(JNIEnv* env, jobject thiz);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_ITIWInappPurchase_onBillingInitializedInapp(JNIEnv* env, jobject thiz)
{
    CCLOG("Java_org_cocos2dx_cpp_ITIWInappPurchase_onBillingInitializedInapp");
    InAppManager::sharedManager()->onBillingInitializedInapp();
}

extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_ITIWInappPurchase_onGetInappProducts(JNIEnv* env, jobject thiz, jobjectArray results);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_ITIWInappPurchase_onGetInappProducts(JNIEnv* env, jobject thiz, jobjectArray results)
{
    CCLOG("Java_org_cocos2dx_cpp_ITIWInappPurchase_onGetInappProducts");
    
    std::vector<LocalisedInappValues> returnResults;
    int size = env->GetArrayLength(results);
    CCLOG("size-test: %d",size);
    for (int i=0; i < size; ++i)
    {
        
        LocalisedInappValues inappValues;
        jobject jobjectElement = env->GetObjectArrayElement(results, i);
        jclass objectClass = (jclass)env->GetObjectClass(jobjectElement);
        
        // currency
        jfieldID jproductIdFId = env->GetFieldID(objectClass, "productId", "Ljava/lang/String;");
        if (NULL == jproductIdFId) return;
        
        jstring jproductIdStr = (jstring)env->GetObjectField(jobjectElement, jproductIdFId);
        std::string  productId = cocos2d::StringUtils::getStringUTFCharsJNI(env, jproductIdStr);
        inappValues.productId = productId;
        
        // currency
        jfieldID jcurrencyFId = env->GetFieldID(objectClass, "currency", "Ljava/lang/String;");
        if (NULL == jcurrencyFId) return;
        
        jstring jcurrencyStr = (jstring)env->GetObjectField(jobjectElement, jcurrencyFId);
        std::string  currency = cocos2d::StringUtils::getStringUTFCharsJNI(env, jcurrencyStr);
        inappValues.currency = currency;
        
        jfieldID jpriceValueFId = env->GetFieldID(objectClass, "priceValue", "D");
        if (NULL == jpriceValueFId) return;
        
        jdouble jpriceValue = (jdouble)env->GetDoubleField(jobjectElement, jpriceValueFId);
        double priceValue = jpriceValue;
        inappValues.priceValue = priceValue;
        
        returnResults.push_back(inappValues);
    }
    InAppManager::sharedManager()->onGetInappProducts(returnResults);
}

extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_ITIWInappPurchase_onProductSubscription(JNIEnv* env, jobject thiz, jstring productId, jstring purchaseToken, jstring purchaseSignature);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_ITIWInappPurchase_onProductSubscription(JNIEnv* env, jobject thiz, jstring productId, jstring purchaseToken, jstring purchaseSignature)
{
    CCLOG("Java_org_cocos2dx_cpp_ITIWInappPurchase_onProductSubscription");
    const char* _productId = env->GetStringUTFChars(productId, NULL);
    const char* _purchaseToken = env->GetStringUTFChars(purchaseToken, NULL);
    const char* _purchaseSignature = env->GetStringUTFChars(purchaseSignature, NULL);
    InAppManager::sharedManager()->onProductSubscription(std::string(_productId),std::string(_purchaseToken),std::string(_purchaseSignature));
}

#pragma mark- ITIWInapp init methods
void InApp::initInApp()
{
    CCLOG("initInApp-cpp");
    JniHelper::callStaticVoidMethod(helperClassName, "initInApp" , Config::sharedManager()->strAndroidInAppKey);
}

#pragma mark- InApp custom methods
void InApp::purchase(string _productId)
{
    JniHelper::callStaticVoidMethod(helperClassName, "purchase", _productId);
}

void InApp::restorePurchase(string _productId)
{
    JniHelper::callStaticVoidMethod(helperClassName, "purchase", _productId);
}

bool InApp::isInappServiceAvailable()
{
    return JniHelper::callStaticBooleanMethod(helperClassName, "isInappServiceAvailable");
}

void InApp::loadInappProducts(string productIds, string seperator)
{
    JniHelper::callStaticVoidMethod(helperClassName, "loadInappProducts",productIds, seperator);
}

void InApp::subscribe(string _productId)
{
    JniHelper::callStaticVoidMethod(helperClassName, "subscribe", _productId);
}

bool InApp::isSubscribed(string _productId)
{
    return JniHelper::callStaticBooleanMethod(helperClassName, "isSubscribed", _productId);
}

bool InApp::isCancelled(string _productId)
{
    return JniHelper::callStaticBooleanMethod(helperClassName, "isCancelled", _productId);
}

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
