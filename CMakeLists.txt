#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

cmake_minimum_required(VERSION 3.6)

set(APP_NAME IRC)

project(${APP_NAME})

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

include(CocosBuildSet)
add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
if(APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

# add cross-platforms source files and header files 
list(APPEND GAME_SOURCE
       Classes/Ads/AdsZonePanel.cpp
       Classes/Ads/AdsAnimation.cpp
       Classes/GameLayer/GameHud.cpp
       Classes/GameLayer/Station.cpp
       Classes/GameLayer/HumanExit.cpp
       Classes/GameLayer/Chair.cpp
       Classes/GameLayer/Ornaments.cpp
       Classes/GameLayer/Waiter.cpp
       Classes/GameLayer/Human.cpp
       Classes/GameLayer/GameNode.cpp
       Classes/sqlite3.c
       Classes/Framework/Ads/AdMob/AdMobController.cpp
       Classes/Framework/Ads/VideoAdsManager.cpp
       Classes/Framework/Ads/FBAudienceNetwork/FBANManager.cpp
       Classes/Framework/Ads/FBAudienceNetwork/FBAN-android.cpp
       Classes/Framework/Ads/FBAudienceNetwork/FBAN.cpp
       Classes/Framework/Firebase/MUSKFirebase.cpp
       Classes/Framework/Firebase/MUSKFirebase-android.cpp
       Classes/Framework/Firebase/MUSKFirebaseManager.cpp
       Classes/Framework/InAppPurchase/InappPurchaseWrapper/InApp.cpp
       Classes/Framework/InAppPurchase/InappPurchaseWrapper/InAppManager.cpp
       Classes/Framework/InAppPurchase/InappPurchaseWrapper/InApp-android.cpp
       Classes/Framework/InAppPurchase/SubscriptionUnitManager.cpp
       Classes/Framework/InAppPurchase/InAppUnit.cpp
       Classes/Framework/InAppPurchase/InAppController.cpp
       Classes/DBClasses/DBMyScreen.cpp
       Classes/DBClasses/DBAttributesInfo.cpp
       Classes/DBClasses/Resources.cpp
       Classes/DBClasses/DBUserInfo.cpp
       Classes/DBClasses/DBScreenInfo.cpp
       Classes/DBClasses/DBResourceInfo.cpp
       Classes/DBClasses/DBLevels.cpp
       Classes/StoreLayer/LevelUpPanel.cpp
       Classes/StoreLayer/GateAttributes.cpp
       Classes/StoreLayer/SettingsPanel.cpp
       Classes/StoreLayer/OrnamentsPanel.cpp
       Classes/StoreLayer/OfflineEarning.cpp
       Classes/StoreLayer/ThemePanel.cpp
       Classes/StoreLayer/StorePanel.cpp
       Classes/HelloWorldScene.cpp
       Classes/DataStructure/ScreenData.cpp
       Classes/AppDelegate.cpp
       Classes/CustomClass/LoadingLayer.cpp
       Classes/CustomClass/TagManager.cpp
       Classes/CustomClass/MUSKScoreBar.cpp
       Classes/CustomClass/AlertView.cpp
       Classes/CustomClass/ScrollableButton.cpp
       Classes/CustomClass/ClickerCalculation.cpp
       Classes/CustomClass/ApplicationWrapper-android.cpp
       Classes/CustomClass/Config.cpp
       Classes/CustomClass/ApplicationWrapper.cpp
       Classes/CustomClass/CustomMath.cpp
       Classes/CustomClass/SpineObject.cpp
     )
list(APPEND GAME_HEADER
       Classes/Ads/AdsAnimation.h
       Classes/Ads/AdsZonePanel.h
       Classes/HelloWorldScene.h
       Classes/AppDelegate.h
       Classes/GameLayer/GameNode.h
       Classes/GameLayer/Chair.h
       Classes/GameLayer/Human.h
       Classes/GameLayer/Waiter.h
       Classes/GameLayer/Ornaments.h
       Classes/GameLayer/Station.h
       Classes/GameLayer/GameHud.h
       Classes/GameLayer/HumanExit.h
       Classes/Framework/Ads/VideoAdsManager.h
       Classes/Framework/Ads/AdMob/AdMobController.h
       Classes/Framework/Ads/FBAudienceNetwork/FBANManager.h
       Classes/Framework/Ads/FBAudienceNetwork/FBAN.h
       Classes/Framework/Firebase/MUSKFirebase.h
       Classes/Framework/Firebase/MUSKFirebaseManager.h
       Classes/Framework/InAppPurchase/InappPurchaseWrapper/InApp.h
       Classes/Framework/InAppPurchase/InappPurchaseWrapper/InAppManager.h
       Classes/Framework/InAppPurchase/InAppController.h
       Classes/Framework/InAppPurchase/SubscriptionUnitManager.h
       Classes/Framework/InAppPurchase/InAppUnit.h
       Classes/DBClasses/DBLevels.h
       Classes/DBClasses/DBScreenInfo.h
       Classes/DBClasses/Resources.h
       Classes/DBClasses/DBMyScreen.h
       Classes/DBClasses/DBResourceInfo.h
       Classes/DBClasses/DBUserInfo.h
       Classes/DBClasses/DBAttributesInfo.h
       Classes/StoreLayer/GateAttributes.h
       Classes/StoreLayer/StorePanel.h
       Classes/StoreLayer/OfflineEarning.h
       Classes/StoreLayer/LevelUpPanel.h
       Classes/StoreLayer/ThemePanel.h
       Classes/StoreLayer/OrnamentsPanel.h
       Classes/StoreLayer/SettingsPanel.h
       Classes/DataStructure/ScreenData.h
       Classes/sqlite3.h
       Classes/IncludeAndroid.h
       Classes/CustomClass/AlertView.h
       Classes/CustomClass/ScrollableButton.h
       Classes/CustomClass/ResourceConfig.h
       Classes/CustomClass/Config.h
       Classes/CustomClass/SpineObject.h
       Classes/CustomClass/ApplicationWrapper.h
       Classes/CustomClass/MUSKScoreBar.h
       Classes/CustomClass/CustomMath.h
       Classes/CustomClass/LoadingLayer.h
       Classes/CustomClass/ClickerCalculation.h
       Classes/CustomClass/TagManager.h
     )

if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME MyGame)
    list(APPEND GAME_SOURCE
         proj.android/app/jni/hellocpp/main.cpp
         )
elseif(LINUX)
    list(APPEND GAME_SOURCE
         proj.linux/main.cpp
         )
elseif(WINDOWS)
    list(APPEND GAME_HEADER
         proj.win32/main.h
         proj.win32/resource.h
         )
    list(APPEND GAME_SOURCE
         proj.win32/main.cpp
         proj.win32/game.rc
         ${common_res_files}
         )
elseif(APPLE)
    if(IOS)
        list(APPEND GAME_HEADER
             proj.ios_mac/ios/AppController.h
             proj.ios_mac/ios/RootViewController.h
             )
        set(APP_UI_RES
            proj.ios_mac/ios/LaunchScreen.storyboard
            proj.ios_mac/ios/LaunchScreenBackground.png
            proj.ios_mac/ios/Images.xcassets
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/ios/main.m
             proj.ios_mac/ios/AppController.mm
             proj.ios_mac/ios/RootViewController.mm
             proj.ios_mac/ios/Prefix.pch
             ${APP_UI_RES}
             )
    elseif(MACOSX)
        set(APP_UI_RES
            proj.ios_mac/mac/Icon.icns
            proj.ios_mac/mac/Info.plist
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/mac/main.cpp
             proj.ios_mac/mac/Prefix.pch
             ${APP_UI_RES}
             )
    endif()
    list(APPEND GAME_SOURCE ${common_res_files})
endif()

# mark app complie info and libs info
set(all_code_files
    ${GAME_HEADER}
    ${GAME_SOURCE}
    )
if(NOT ANDROID)
    add_executable(${APP_NAME} ${all_code_files})
else()
    add_library(${APP_NAME} SHARED ${all_code_files})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
endif()

target_link_libraries(${APP_NAME} cocos2d)
target_include_directories(${APP_NAME}
        PRIVATE Classes
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
)

# mark app resources
setup_cocos_app_config(${APP_NAME})
if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")
    if(MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES
                              MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist"
                              )
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
        set_xcode_property(${APP_NAME} DEVELOPMENT_TEAM "")
        set_xcode_property(${APP_NAME} CODE_SIGN_IDENTITY "iPhone Developer")
    endif()
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME})
endif()

if(LINUX OR WINDOWS)
    set(APP_RES_DIR "$<TARGET_FILE_DIR:${APP_NAME}>/Resources")
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif()
