LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
					$(LOCAL_PATH)/../../../Classes/Ads/AdsZonePanel.cpp \
                    $(LOCAL_PATH)/../../../Classes/Ads/AdsAnimation.cpp \
                    $(LOCAL_PATH)/../../../Classes/GameLayer/GameHud.cpp \
                    $(LOCAL_PATH)/../../../Classes/GameLayer/Station.cpp \
                    $(LOCAL_PATH)/../../../Classes/GameLayer/HumanExit.cpp \
                    $(LOCAL_PATH)/../../../Classes/GameLayer/Chair.cpp \
                    $(LOCAL_PATH)/../../../Classes/GameLayer/Ornaments.cpp \
                    $(LOCAL_PATH)/../../../Classes/GameLayer/Waiter.cpp \
                    $(LOCAL_PATH)/../../../Classes/GameLayer/Human.cpp \
                    $(LOCAL_PATH)/../../../Classes/GameLayer/GameNode.cpp \
                    $(LOCAL_PATH)/../../../Classes/sqlite3.c \
                    $(LOCAL_PATH)/../../../Classes/Framework/Ads/AdMob/AdMobController.cpp \
                    $(LOCAL_PATH)/../../../Classes/Framework/Ads/VideoAdsManager.cpp \
                    $(LOCAL_PATH)/../../../Classes/Framework/Ads/FBAudienceNetwork/FBANManager.cpp \
                    $(LOCAL_PATH)/../../../Classes/Framework/Ads/FBAudienceNetwork/FBAN-android.cpp \
                    $(LOCAL_PATH)/../../../Classes/Framework/Ads/FBAudienceNetwork/FBAN.cpp \
                    $(LOCAL_PATH)/../../../Classes/Framework/Firebase/MUSKFirebase.cpp \
                    $(LOCAL_PATH)/../../../Classes/Framework/Firebase/MUSKFirebase-android.cpp \
                    $(LOCAL_PATH)/../../../Classes/Framework/Firebase/MUSKFirebaseManager.cpp \
                    $(LOCAL_PATH)/../../../Classes/Framework/InAppPurchase/InappPurchaseWrapper/InApp.cpp \
                    $(LOCAL_PATH)/../../../Classes/Framework/InAppPurchase/InappPurchaseWrapper/InAppManager.cpp \
                    $(LOCAL_PATH)/../../../Classes/Framework/InAppPurchase/InappPurchaseWrapper/InApp-android.cpp \
                    $(LOCAL_PATH)/../../../Classes/Framework/InAppPurchase/SubscriptionUnitManager.cpp \
                    $(LOCAL_PATH)/../../../Classes/Framework/InAppPurchase/InAppUnit.cpp \
                    $(LOCAL_PATH)/../../../Classes/Framework/InAppPurchase/InAppController.cpp \
                    $(LOCAL_PATH)/../../../Classes/DBClasses/DBMyScreen.cpp \
                    $(LOCAL_PATH)/../../../Classes/DBClasses/DBAttributesInfo.cpp \
                    $(LOCAL_PATH)/../../../Classes/DBClasses/Resources.cpp \
                    $(LOCAL_PATH)/../../../Classes/DBClasses/DBUserInfo.cpp \
                    $(LOCAL_PATH)/../../../Classes/DBClasses/DBScreenInfo.cpp \
                    $(LOCAL_PATH)/../../../Classes/DBClasses/DBResourceInfo.cpp \
                    $(LOCAL_PATH)/../../../Classes/DBClasses/DBLevels.cpp \
                    $(LOCAL_PATH)/../../../Classes/StoreLayer/LevelUpPanel.cpp \
                    $(LOCAL_PATH)/../../../Classes/StoreLayer/GateAttributes.cpp \
                    $(LOCAL_PATH)/../../../Classes/StoreLayer/SettingsPanel.cpp \
                    $(LOCAL_PATH)/../../../Classes/StoreLayer/OrnamentsPanel.cpp \
                    $(LOCAL_PATH)/../../../Classes/StoreLayer/OfflineEarning.cpp \
                    $(LOCAL_PATH)/../../../Classes/StoreLayer/ThemePanel.cpp \
                    $(LOCAL_PATH)/../../../Classes/StoreLayer/StorePanel.cpp \
                    $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp \
                    $(LOCAL_PATH)/../../../Classes/DataStructure/ScreenData.cpp \
                    $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
                    $(LOCAL_PATH)/../../../Classes/CustomClass/LoadingLayer.cpp \
                    $(LOCAL_PATH)/../../../Classes/CustomClass/TagManager.cpp \
                    $(LOCAL_PATH)/../../../Classes/CustomClass/MUSKScoreBar.cpp \
                    $(LOCAL_PATH)/../../../Classes/CustomClass/AlertView.cpp \
                    $(LOCAL_PATH)/../../../Classes/CustomClass/ScrollableButton.cpp \
                    $(LOCAL_PATH)/../../../Classes/CustomClass/ClickerCalculation.cpp \
                    $(LOCAL_PATH)/../../../Classes/CustomClass/ApplicationWrapper-android.cpp \
                    $(LOCAL_PATH)/../../../Classes/CustomClass/Config.cpp \
                    $(LOCAL_PATH)/../../../Classes/CustomClass/ApplicationWrapper.cpp \
                    $(LOCAL_PATH)/../../../Classes/CustomClass/CustomMath.cpp \
                    $(LOCAL_PATH)/../../../Classes/CustomClass/SpineObject.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cc_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
