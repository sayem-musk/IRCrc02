package org.cocos2dx.cpp;

import android.content.Context;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import androidx.annotation.NonNull;
import android.util.Log;
import android.widget.Toast;

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.InterstitialAd;
import com.google.firebase.iid.FirebaseInstanceId;
import com.google.firebase.iid.InstanceIdResult;
import com.insparofaith.restaurant.R;
import com.insparofaith.restaurant.BuildConfig;

import com.google.firebase.analytics.FirebaseAnalytics;

import com.google.firebase.remoteconfig.FirebaseRemoteConfig;
import com.google.firebase.remoteconfig.FirebaseRemoteConfigSettings;

import com.google.android.gms.ads.reward.RewardItem;
import com.google.android.gms.ads.reward.RewardedVideoAdListener;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.MobileAds;
import com.google.android.gms.ads.reward.RewardedVideoAd;

import java.util.concurrent.CountDownLatch;

public class FirebaseManager {

    private static final String TAG = AppActivity.class.getSimpleName();
    private static AppActivity sActivity;

    // Firebase Analytics
    private static FirebaseAnalytics mFirebaseAnalytics;

    // Firebase RemoteConfig
    private static FirebaseRemoteConfig mFirebaseRemoteConfig;
    public static native void onRemoteFetchComplete(boolean isSuccess);

    // Firebase AdMob
    private static RewardedVideoAd mRewardedVideoAd;
    private static AdRequest.Builder bulder;

    private static final String AD_NAME="Rewarded";
    private static InterstitialAd mInterstitialAd;
    private static final String interstitialName = "Interstitial";

    public static native void onFireAdMobRewarded(String name, String currency, Double amount);
    public static native void onFireAdmobRewardedVideoAdLeftApplication(String name);
    public static native void onFireAdmobRewardedVideoAdClosed(String name);
    public static native void onFireAdmobRewardedVideoAdFailedToLoad(String name);
    public static native void onFireAdmobRewardedVideoAdLoaded(String name);
    public static native void onFireAdmobRewardedVideoAdOpened(String name);
    public static native void onFireAdmobRewardedVideoStarted(String name);
    public static native void onFireAdmobRewardedVideoCompleted(String name);

    //Firebase
    public static void logFirebaseInstanceID(){
        FirebaseInstanceId.getInstance().getInstanceId().addOnCompleteListener(new OnCompleteListener<InstanceIdResult>() {
            @Override
            public void onComplete(@NonNull Task<InstanceIdResult> task) {
                if (!task.isSuccessful()) {
                    Log.w(TAG, "Firebase Instance ID get: failed", task.getException());
                    return;
                }
                // Get new Instance ID token
                String fid = task.getResult().getToken();

                // Log
                Log.d(TAG, "Firebase Instance ID: "+fid);
            }
        });
    }

    // Firebase Analytics
    public static void initFireAnalytics() {
        sActivity = AppActivity.getActivity();
        mFirebaseAnalytics = FirebaseAnalytics.getInstance(sActivity);
        MobileAds.initialize(sActivity, sActivity.getResources().getString(R.string.admob_app_id));
    }

    public static void logAnalyticEvent(String eventName,String eventCategory,String eventLabel,int eventValue){

        Bundle bundle = new Bundle();
        bundle.putString("event_category", eventCategory);
        bundle.putString("event_label", eventLabel);
        bundle.putInt("event_value", eventValue);

        mFirebaseAnalytics.logEvent(eventName, bundle);

        System.out.println("Log ---> AnalyticsEventLog"+ eventName+", "+eventCategory+", "+eventLabel+", "+eventValue);
    }

    public static void sendVirtualCurrencyEvent(String _eventName, String _itemName, String _currencyName, int _value) {

        Bundle bundle = new Bundle();
        bundle.putString(FirebaseAnalytics.Param.ITEM_NAME, _itemName);
        bundle.putDouble(FirebaseAnalytics.Param.VALUE, _value);
        bundle.putString(FirebaseAnalytics.Param.VIRTUAL_CURRENCY_NAME, _currencyName);
        mFirebaseAnalytics.logEvent(FirebaseAnalytics.Event.SPEND_VIRTUAL_CURRENCY, bundle);
    }

    public static void setCurrentScreen(final String _screenName, final String _screenClass) {

        sActivity = AppActivity.getActivity();
        // mFirebaseAnalytics.setCurrentScreen(this, screenName, null /* class override */);
        Handler handler = new Handler(Looper.getMainLooper());
        handler.post(new Runnable() {
            @Override
            public void run() {
                //Your UI code here
                mFirebaseAnalytics.setCurrentScreen(sActivity, _screenName, _screenClass);
            }
        });

    }
    
    public static void logAnalyticEventUsingExternalContext(Context context, String eventName, String eventCategory, String eventLabel, int eventValue){

        Bundle bundle = new Bundle();
        bundle.putString("event_category", eventCategory);
        bundle.putString("event_label", eventLabel);
        bundle.putInt("event_value", eventValue);
        FirebaseAnalytics mFirebaseAnalytics2 = FirebaseAnalytics.getInstance(context);
        mFirebaseAnalytics2.logEvent(eventName, bundle);
        mFirebaseAnalytics2 = null;
        System.out.println("Log ---> AnalyticsEventLog2"+ eventName+", "+eventCategory+", "+eventLabel+", "+eventValue);
    }

    // Firebase RemoteConfig
    public static void initRemoteConfig() {

        sActivity = AppActivity.getActivity();

        mFirebaseRemoteConfig = FirebaseRemoteConfig.getInstance();
        mFirebaseRemoteConfig.setDefaults(R.xml.remote_config);
        FirebaseRemoteConfigSettings configSettings = new FirebaseRemoteConfigSettings.Builder()
                .setDeveloperModeEnabled(BuildConfig.DEBUG)
                .build();
        mFirebaseRemoteConfig.setConfigSettings(configSettings);

        long cacheExpiration = 3600; // 1 hour in seconds.

        if (mFirebaseRemoteConfig.getInfo().getConfigSettings().isDeveloperModeEnabled()) {
            cacheExpiration = 0;
        }
        mFirebaseRemoteConfig.fetch(cacheExpiration)
                .addOnCompleteListener(sActivity, new OnCompleteListener<Void>() {
                    @Override
                    public void onComplete(@NonNull Task<Void> task) {
                        if (task.isSuccessful()) {
                            Log.v(TAG,"Fetch Succeeded");

                            // After config data is successfully fetched, it must be activated before newly fetched
                            // values are returned.
                            mFirebaseRemoteConfig.activateFetched();
                        } else {
                            Log.v(TAG,"Fetch Failed");
                        }
                        onRemoteFetchComplete(task.isSuccessful());
                    }
                });
    }

    public static String getRemoteConfigValue(String key){

        if(mFirebaseRemoteConfig == null){
            Log.e(TAG, "mFirebaseRemoteConfig not initialized");
            return "";
        }
		if(key!=null && key!="")
	        return mFirebaseRemoteConfig.getString(key);
        return "";
    }

    public static void initAdmob() {
        Log.v("TAG","java initAdmob-java");
        sActivity = AppActivity.getActivity();
        bulder = new AdRequest.Builder();
//        bulder.addTestDevice("F32CE28930616AA15E2D6A2279997B6E");

        // Use an activity context to get the rewarded video instance.
        mRewardedVideoAd = MobileAds.getRewardedVideoAdInstance(sActivity);
        sActivity.runOnUiThread(new Runnable() {
            @Override public void run() {
                mRewardedVideoAd.setRewardedVideoAdListener(new RewardedVideoAdListener() {
                    @Override
                    public void onRewarded(RewardItem reward) {
                        Log.v(TAG,"admob java onRewarded! currency: " + reward.getType() + "  amount: " + reward.getAmount());
                        FirebaseManager.onFireAdMobRewarded(AD_NAME,reward.getType(),new Double(reward.getAmount()));
                    }

                    @Override
                    public void onRewardedVideoAdLeftApplication() {
                        Log.v(TAG,"admob java onRewardedVideoAdLeftApplication");
                        FirebaseManager.onFireAdmobRewardedVideoAdLeftApplication(AD_NAME);
                    }

                    @Override
                    public void onRewardedVideoAdClosed() {
                        Log.v(TAG,"admob java onRewardedVideoAdClosed");
                        FirebaseManager.onFireAdmobRewardedVideoAdClosed(AD_NAME);
                        //FirebaseManager.loadRewardedVideoAd(adUnitId);
                    }

                    @Override
                    public void onRewardedVideoAdFailedToLoad(int errorCode) {
                        Log.v(TAG,"admob java onRewardedVideoAdFailedToLoad errorCode: "+errorCode);
                        FirebaseManager.onFireAdmobRewardedVideoAdFailedToLoad(AD_NAME);
                    }

                    @Override
                    public void onRewardedVideoAdLoaded() {
                        Log.v(TAG,"admob java onRewardedVideoAdLoaded");
                        FirebaseManager.onFireAdmobRewardedVideoAdLoaded(AD_NAME);
                    }

                    @Override
                    public void onRewardedVideoAdOpened() {
                        Log.v(TAG,"admob java onRewardedVideoAdOpened");
                        FirebaseManager.onFireAdmobRewardedVideoAdOpened(AD_NAME);
                    }

                    @Override
                    public void onRewardedVideoStarted() {
                        Log.v(TAG,"admob java onRewardedVideoStarted");
                        FirebaseManager.onFireAdmobRewardedVideoStarted(AD_NAME);
                    }

                    @Override
                    public void onRewardedVideoCompleted() {
                        Log.v(TAG,"admob java onRewardedVideoCompleted");
                        FirebaseManager.onFireAdmobRewardedVideoCompleted(AD_NAME);
                    }
                });
            }
        });
        //FirebaseManager.loadRewardedVideoAd(adUnitId);
    }

    public static void loadRewardedVideoAd(final String adUnitId) {
        Log.v(TAG,"java loadRewardedVideoAd called");
        sActivity = AppActivity.getActivity();
        sActivity.runOnUiThread(new Runnable() {
            @Override public void run() {
                mRewardedVideoAd.loadAd(adUnitId,
                        bulder.build());
            }
        });
    }

    public static void showRewardedAd() {

        sActivity = AppActivity.getActivity();
        sActivity.runOnUiThread(new Runnable() {
            @Override public void run() {
                if (mRewardedVideoAd != null && mRewardedVideoAd.isLoaded()) {
                    Log.v("TAG","mRewardedVideoAd showing admob ad");
                    mRewardedVideoAd.show();
                }
                else {
                    Log.v("TAG","mRewardedVideoAd is not ready");
                    //FirebaseManager.onFireAdmobRewardedVideoNotLoaded();
                }
            }
        });
    }

    private static boolean isAdsAvailable(){
        final CountDownLatch latch = new CountDownLatch(1);
        final boolean[] result = new boolean[1];
        sActivity.runOnUiThread(new Runnable() {
            @Override public void run() {
                result[0] =  (mRewardedVideoAd != null && mRewardedVideoAd.isLoaded());
                latch.countDown();
            }
        });

        try {
            latch.await();
        } catch (InterruptedException e) {
            latch.countDown();
        }

        return result[0];
    }

    // Interstitial Ad

    public static void initInterstitialAd() {
        Log.v(TAG,"initInterstitialAd");
        if (mInterstitialAd != null)
        	mInterstitialAd = null;
        mInterstitialAd = new InterstitialAd(sActivity);

        sActivity.runOnUiThread(new Runnable() {
            @Override public void run() {
                mInterstitialAd.setAdListener(new AdListener() {
                    @Override
                    public void onAdLoaded() {
                        // Code to be executed when an ad finishes loading.
                        Log.v(TAG,"onAdLoaded");
                        //AdRequest.ERROR_CODE_NETWORK_ERROR
                        FirebaseManager.onFireAdmobRewardedVideoAdLoaded(interstitialName);
                    }

                    @Override
                    public void onAdFailedToLoad(int errorCode) {
                        // Code to be executed when an ad request fails.
                        Log.v(TAG,"onAdFailedToLoad: "+errorCode);
                        FirebaseManager.onFireAdmobRewardedVideoAdFailedToLoad(interstitialName);
                    }

                    @Override
                    public void onAdOpened() {
                        // Code to be executed when the ad is displayed.
                        Log.v(TAG,"onAdOpened");
                        //FirebaseManager.onFireAdmobRewardedVideoAdOpened(interstitialName);
                        FirebaseManager.onFireAdMobRewarded(interstitialName,"Interstitial",new Double(10));
                    }

                    @Override
                    public void onAdLeftApplication() {
                        // Code to be executed when the user has left the app.
                        Log.v(TAG,"onAdLeftApplication");
                        FirebaseManager.onFireAdmobRewardedVideoAdLeftApplication(interstitialName);
                    }

                    @Override
                    public void onAdClosed() {
                        // Code to be executed when the interstitial ad is closed.
                        Log.v(TAG,"onAdClosed");
                        FirebaseManager.onFireAdmobRewardedVideoAdClosed(interstitialName);
                    }
                });
            }
        });
    }

    public static void loadInterstitialAd(final String adUnitId) {
        Log.v(TAG,"loadInterstitialAd");
        sActivity.runOnUiThread(new Runnable() {
            @Override public void run() {
                if (mInterstitialAd != null) {
                    if (!adUnitId.equals(mInterstitialAd.getAdUnitId()))
                    {
                        mInterstitialAd.setAdUnitId(adUnitId);
                    }
                    mInterstitialAd.loadAd(new AdRequest.Builder().build());
                }
            }
        });
    }

    public static void showInterstitialAd() {
        sActivity.runOnUiThread(new Runnable() {
            @Override public void run() {
                if (FirebaseManager.isInterstitialAdsAvailable()) {
                    mInterstitialAd.show();
                } else {
                    Log.d("TAG", "The interstitial wasn't loaded yet.");
                }
            }
        });
    }

    public static boolean isInterstitialAdsAvailable() {
        final CountDownLatch latch = new CountDownLatch(1);
        final boolean[] result = new boolean[1];
        sActivity.runOnUiThread(new Runnable() {
            @Override public void run() {
                result[0] =  (mInterstitialAd != null && mInterstitialAd.isLoaded());
                latch.countDown();
            }
        });

        try {
            latch.await();
        } catch (InterruptedException e) {
            latch.countDown();
        }

        return result[0];
    }

    // Firebase cloud messaging
    public static native void onFirebaseMessagingParamsReceived(String params);
    public static void catchFirebaseCloudMessagingParams(Bundle extras,String ref){
        Log.d("FB_CM", "Ref: "+ref);
        if(extras != null){

            StringBuilder sb = new StringBuilder();
            for (String key : extras.keySet()) {

                sb.append(key+"="+extras.get(key)+"&");
            }
            sb.deleteCharAt(sb.lastIndexOf("&"));

            Log.d("FB_CM", "Extras: "+String.valueOf(sb));

            if(extras.keySet().contains("firebase"))onFirebaseMessagingParamsReceived(sb.toString());
        }
        else{
            Log.e("FB_CM", "Extras is NULL");
        }
    }

    // Firebase in app messaging
    public static native void onFirebaseInAppMessagingParamsReceived(String params);
    public static void catchFirebaseInAppMessagingParams(Uri uri){
        if(uri != null) {
            StringBuilder sb = new StringBuilder();
            for (String key : uri.getQueryParameterNames()) {
                Log.d("FB_IAM", "Key: "+key+", Value: "+uri.getQueryParameter(key));
                sb.append(key+"="+uri.getQueryParameter(key)+"&");
            }
            sb.deleteCharAt(sb.lastIndexOf("&"));
            onFirebaseInAppMessagingParamsReceived(sb.toString());
        }
        else{
            Log.e("FB_IAM", "Uri is null");
        }
    }

    // Custom Methods
    private static void showToast(final String message) {

        Handler handler = new Handler(Looper.getMainLooper());
        handler.post(new Runnable() {
            @Override
            public void run() {
                //Your UI code here
                Toast.makeText(sActivity, message, Toast.LENGTH_LONG).show();
            }
        });
    }
}

