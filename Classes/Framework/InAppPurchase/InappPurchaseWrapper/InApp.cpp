//
//  InApp.cpp
//  ITIW
//
//  Created by itiw on 3/3/18.
//
//

#include "InApp.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS && CC_TARGET_PLATFORM != CC_PLATFORM_MAC && CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)

void InApp::initInApp()
{
    
}

#pragma mark- InApp custom methods
void InApp::purchase(string _productId)
{
    
}

void InApp::restorePurchase(string _productId)
{
    
}

bool InApp::isInappServiceAvailable()
{
    return false;
}

void InApp::loadInappProducts(string productIds, string seperator)
{
    
}

void InApp::subscribe(string _productId)
{
    
}

bool InApp::isSubscribed(string _productId)
{
    return false;
}

bool InApp::isCancelled(string _productId)
{
    return true;
}

#endif // (CC_TARGET_PLATFORM != CC_PLATFORM_IOS && CC_PLATFORM != CC_PLATFORM_ANDROID)

