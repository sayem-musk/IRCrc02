package org.cocos2dx.cpp;

import android.util.Log;

import com.facebook.ads.Ad;
import com.facebook.ads.AdError;
import com.facebook.ads.AudienceNetworkAds;
import com.facebook.ads.InterstitialAd;
import com.facebook.ads.InterstitialAdListener;
import com.facebook.ads.RewardedVideoAd;
import com.facebook.ads.RewardedVideoAdListener;
import com.google.android.gms.ads.AdRequest;

public class FBAudienceNetworkManager {
    private static final String TAG = AppActivity.class.getSimpleName();
    private static String PLACEMENT_ID = "1360477144092228_1360492880757321";
    private static InterstitialAd interstitialAd = null;
    private static InterstitialAd interstitialAd2 = null;

    //native functions

    public static native void onInterstitialDisplayed();
    public static native void onInterstitialDismissed();
    public static native void onError();
    public static native void onAdLoaded();
    public static native void onAdClicked();
    public static native void onLoggingImpression();

    public static native void onInterstitialLoad(boolean isLoaded, int errorCode);

    public static void initInterstitialAd(){
        initInterstitialAd(PLACEMENT_ID);
    }

    public static void initAudienceNetwork() {
        AudienceNetworkAds.initialize(AppActivity.getActivity());
    }

    public static void initInterstitialAd(String placementID){

        if (interstitialAd != null)
        {
            interstitialAd = null;
        }

        interstitialAd = new InterstitialAd(AppActivity.getActivity(), placementID);
        Log.i(TAG, "Interstitial ad initializing.");
        //Log.i(TAG,"Interstitial ad : Multi-process support ?"+AudienceNetworkAds.isInAdsProcess(AppActivity.getActivity()));
        //interstitialAd.loadAd(interstitialAd.buildLoadAdConfig());
        interstitialAd.loadAd(interstitialAd.buildLoadAdConfig()
        .withAdListener(new InterstitialAdListener() {
            @Override
            public void onInterstitialDisplayed(Ad ad) {
                // Interstitial ad displayed callback
                Log.i(TAG, "Interstitial ad displayed.");
//                FBAudienceNetworkManager.onInterstitialDisplayed();
                FBAudienceNetworkManager.onRewardedVideoCompleted(10, "name");
            }

            @Override
            public void onInterstitialDismissed(Ad ad) {
                // Interstitial dismissed callback
                Log.i(TAG, "Interstitial ad dismissed.");
//                FBAudienceNetworkManager.onInterstitialDismissed();
                FBAudienceNetworkManager.onRewardedVideoClosed("name");
                interstitialAd.loadAd();
            }

            @Override
            public void onError(Ad ad, AdError adError) {
                // Ad error callback
                Log.e(TAG, "Interstitial ad failed to load: " + adError.getErrorMessage());
//                FBAudienceNetworkManager.onError();
                FBAudienceNetworkManager.onRewardedError("name","error: "+adError.getErrorMessage());

//                new java.util.Timer().schedule(
//                    new java.util.TimerTask() {
//                        @Override
//                        public void run() {
//                            Log.e(TAG, "Interstitial ad waiting in other thread");
//                            FBAudienceNetworkManager.loadInterstitialAd();
//                        }
//                    },30000
//                );
            }

            @Override
            public void onAdLoaded(Ad ad) {
                // Interstitial ad is loaded and ready to be displayed
                Log.d(TAG, "Interstitial ad is loaded and ready to be displayed!");
//                FBAudienceNetworkManager.onAdLoaded();
                FBAudienceNetworkManager.onRewardedAdLoaded("name");
                // Show the ad
                //interstitialAd.show();
            }

            @Override
            public void onAdClicked(Ad ad) {
                // Ad clicked callback
                Log.d(TAG, "Interstitial ad clicked!");
//                FBAudienceNetworkManager.onAdClicked();
                FBAudienceNetworkManager.onRewardedAdClicked("name");
            }

            @Override
            public void onLoggingImpression(Ad ad) {
                // Ad impression logged callback
                Log.d(TAG, "Interstitial ad impression logged!");
//                FBAudienceNetworkManager.onLoggingImpression();
                FBAudienceNetworkManager.onRewardedLoggingImpression("name");
            }
        }).build());

        //AdRequest.Builder.addTestDevice("BECCCF36029948165F6DEF4A39C10AE1");

        // For auto play video ads, it's recommended to load the ad
        // at least 30 seconds before it is shown
        interstitialAd.loadAd();

    }

    public static void  loadInterstitialAd(){

        Log.i(TAG, "Interstitial ad - inside load ad request");
        if(interstitialAd != null)interstitialAd.loadAd();
    }

    public static boolean isInterstitialAdLoaded(){
        if (interstitialAd != null)
            return interstitialAd.isAdLoaded();
        return false;
    }

    public static void showInterstitialAd(){
        if(interstitialAd != null){
            interstitialAd.show();
        }
    }

    // FB Audience Network Intersitial Ad 2

    public static void initInterstitialAd2(){
        initInterstitialAd2(PLACEMENT_ID);
    }

    public static void initInterstitialAd2(String placementID){

        if (interstitialAd2 != null)
        {
            interstitialAd2 = null;
        }

        interstitialAd2 = new InterstitialAd(AppActivity.getActivity(), placementID);
        Log.i(TAG, "Interstitial ad initializing.");
        //Log.i(TAG,"Interstitial ad : Multi-process support ?"+AudienceNetworkAds.isInAdsProcess(AppActivity.getActivity()));
        interstitialAd2.loadAd(interstitialAd2.buildLoadAdConfig()
        .withAdListener(new InterstitialAdListener() {
            @Override
            public void onInterstitialDisplayed(Ad ad) {
                // Interstitial ad displayed callback
                Log.i(TAG, "Interstitial ad displayed.");
//                FBAudienceNetworkManager.onInterstitialDisplayed();
                FBAudienceNetworkManager.onRewardedVideoCompleted(10, "name");
            }

            @Override
            public void onInterstitialDismissed(Ad ad) {
                // Interstitial dismissed callback
                Log.i(TAG, "Interstitial ad dismissed.");
                FBAudienceNetworkManager.onInterstitialDismissed();
                //FBAudienceNetworkManager.onRewardedVideoClosed("name");
                //interstitialAd2.loadAd();
            }

            @Override
            public void onError(Ad ad, AdError adError) {
                // Ad error callback
                Log.e(TAG, "Interstitial ad failed to load: " + adError.getErrorMessage());
//                FBAudienceNetworkManager.onRewardedError("name","error: "+adError.getErrorMessage());
                FBAudienceNetworkManager.onInterstitialLoad(false, adError.getErrorCode());

            }

            @Override
            public void onAdLoaded(Ad ad) {
                // Interstitial ad is loaded and ready to be displayed
                Log.d(TAG, "Interstitial ad is loaded and ready to be displayed!");
                //FBAudienceNetworkManager.onRewardedAdLoaded("name");
                FBAudienceNetworkManager.onInterstitialLoad(true, 0);
            }

            @Override
            public void onAdClicked(Ad ad) {
                // Ad clicked callback
                Log.d(TAG, "Interstitial ad clicked!");
//                FBAudienceNetworkManager.onAdClicked();
                FBAudienceNetworkManager.onRewardedAdClicked("name");
            }

            @Override
            public void onLoggingImpression(Ad ad) {
                // Ad impression logged callback
                Log.d(TAG, "Interstitial ad impression logged!");
//                FBAudienceNetworkManager.onLoggingImpression();
                FBAudienceNetworkManager.onRewardedLoggingImpression("name");
            }
        }).build());

        // For auto play video ads, it's recommended to load the ad
        // at least 30 seconds before it is shown
        interstitialAd2.loadAd();

    }

    public static void  loadInterstitialAd2() {

        Log.i(TAG, "Interstitial ad2 - inside load ad request");
        if(interstitialAd2 != null)interstitialAd2.loadAd();
    }

    public static boolean isInterstitialAdLoaded2(){
        if (interstitialAd2 != null)
            return interstitialAd2.isAdLoaded();
        return false;
    }

    public static void showInterstitialAd2(){
        if(interstitialAd2 != null){
            interstitialAd2.show();
        }
    }

    // Rewarded Video
    private static final String rewardedVideoName = "Rewarded";
    private static RewardedVideoAd rewardedVideoAd = null;
    private static RewardedVideoAd rewardedVideoAd2 = null;

    private static native void onRewardedError(String name, String msg);
    private static native void onRewardedAdLoaded(String name);
    private static native void onRewardedAdClicked(String name);
    private static native void onRewardedLoggingImpression(String name);
    private static native void onRewardedVideoCompleted(double amount, String name);
    private static native void onRewardedVideoClosed(String name);

    public static void initRewardedAd()
    {

    }

    public static void loadRewardedAd(String placeMentID)
    {
        Log.v(TAG,"initRewardedAd");
        if (rewardedVideoAd != null)
        {
            rewardedVideoAd = null;
        }
        rewardedVideoAd = new RewardedVideoAd(AppActivity.getActivity(), placeMentID);
        rewardedVideoAd.loadAd(rewardedVideoAd.buildLoadAdConfig()
        .withAdListener(new RewardedVideoAdListener() {
            @Override
            public void onError(Ad ad, AdError error) {
                // Rewarded video ad failed to load
                Log.e(TAG, "Rewarded video ad failed to load: " + error.getErrorMessage());
                FBAudienceNetworkManager.onRewardedError(rewardedVideoName, error.getErrorMessage());
            }

            @Override
            public void onAdLoaded(Ad ad) {
                // Rewarded video ad is loaded and ready to be displayed
                Log.d(TAG, "Rewarded video ad is loaded and ready to be displayed!");
                FBAudienceNetworkManager.onRewardedAdLoaded(rewardedVideoName);
            }

            @Override
            public void onAdClicked(Ad ad) {
                // Rewarded video ad clicked
                Log.d(TAG, "Rewarded video ad clicked!");
                FBAudienceNetworkManager.onRewardedAdClicked(rewardedVideoName);
            }

            @Override
            public void onLoggingImpression(Ad ad) {
                // Rewarded Video ad impression - the event will fire when the
                // video starts playing
                Log.d(TAG, "Rewarded video ad impression logged!");
                FBAudienceNetworkManager.onRewardedLoggingImpression(rewardedVideoName);
            }

            @Override
            public void onRewardedVideoCompleted() {
                // Rewarded Video View Complete - the video has been played to the end.
                // You can use this event to initialize your reward
                Log.d(TAG, "Rewarded video completed!");

                // Call method to give reward
                // giveReward();
                FBAudienceNetworkManager.onRewardedVideoCompleted(10 ,rewardedVideoName);
            }

            @Override
            public void onRewardedVideoClosed() {
                // The Rewarded Video ad was closed - this can occur during the video
                // by closing the app, or closing the end card.
                Log.d(TAG, "Rewarded video ad closed!");
                FBAudienceNetworkManager.onRewardedVideoClosed(rewardedVideoName);
            }
        }).build());
        rewardedVideoAd.loadAd();
    }

    public static boolean isRewardedAdLoaded()
    {
        return rewardedVideoAd != null && rewardedVideoAd.isAdLoaded();
    }

    public static void showRewardedAd()
    {
        if (FBAudienceNetworkManager.isRewardedAdLoaded())
        {
            rewardedVideoAd.show();
        }
        else {
            Log.v(TAG,"rewardedVideoAd is not loaded");
        }
    }

    // FBAudience Network for different purpose

    public static void initRewardedAd2()
    {

    }

    public static void loadRewardedAd2(String placeMentID)
    {
        Log.v(TAG,"initRewardedAd");
        if (rewardedVideoAd2 != null)
        {
            rewardedVideoAd2 = null;
        }
        rewardedVideoAd2 = new RewardedVideoAd(AppActivity.getActivity(), placeMentID);
        rewardedVideoAd2.loadAd(rewardedVideoAd2.buildLoadAdConfig()
        .withAdListener(new RewardedVideoAdListener() {
            @Override
            public void onError(Ad ad, AdError error) {
                // Rewarded video ad failed to load
                Log.e(TAG, "Rewarded video ad failed to load: " + error.getErrorMessage());
                //FBAudienceNetworkManager.onRewardedError(rewardedVideoName, error.getErrorMessage());
            }

            @Override
            public void onAdLoaded(Ad ad) {
                // Rewarded video ad is loaded and ready to be displayed
                Log.d(TAG, "Rewarded video ad is loaded and ready to be displayed!");
                FBAudienceNetworkManager.onRewardedAdLoaded(rewardedVideoName);
            }

            @Override
            public void onAdClicked(Ad ad) {
                // Rewarded video ad clicked
                Log.d(TAG, "Rewarded video ad clicked!");
                FBAudienceNetworkManager.onRewardedAdClicked(rewardedVideoName);
            }

            @Override
            public void onLoggingImpression(Ad ad) {
                // Rewarded Video ad impression - the event will fire when the
                // video starts playing
                Log.d(TAG, "Rewarded video ad impression logged!");
                FBAudienceNetworkManager.onRewardedLoggingImpression(rewardedVideoName);
            }

            @Override
            public void onRewardedVideoCompleted() {
                // Rewarded Video View Complete - the video has been played to the end.
                // You can use this event to initialize your reward
                Log.d(TAG, "Rewarded video completed!");

                // Call method to give reward
                // giveReward();
                FBAudienceNetworkManager.onRewardedVideoCompleted(10 ,rewardedVideoName);
            }

            @Override
            public void onRewardedVideoClosed() {
                // The Rewarded Video ad was closed - this can occur during the video
                // by closing the app, or closing the end card.
                Log.d(TAG, "Rewarded video ad closed!");
                FBAudienceNetworkManager.onRewardedVideoClosed(rewardedVideoName);
            }
        }).build());
        rewardedVideoAd2.loadAd();
    }

    public static boolean isRewardedAdLoaded2()
    {
        return rewardedVideoAd2 != null && rewardedVideoAd2.isAdLoaded();
    }

    public static void showRewardedAd2()
    {
        if (FBAudienceNetworkManager.isRewardedAdLoaded2())
        {
            rewardedVideoAd2.show();
        }
        else {
            Log.v(TAG,"rewardedVideoAd2 is not loaded");
        }
    }

}
