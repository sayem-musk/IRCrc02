package org.cocos2dx.cpp;

import androidx.annotation.NonNull;

import com.google.android.gms.analytics.HitBuilders;
import com.insparofaith.restaurant.R;

import com.google.android.gms.analytics.GoogleAnalytics;
import com.google.android.gms.analytics.Tracker;

public class MUSKGoogleAnalytics {

    private static final String TAG = AppActivity.class.getSimpleName();
    private static AppActivity sActivity = AppActivity.getActivity();

    private static GoogleAnalytics sAnalytics;
    private static Tracker sTracker;

    public static void initGoogleAnalytics() {
        sAnalytics = GoogleAnalytics.getInstance(sActivity);

        Tracker mTracker = MUSKGoogleAnalytics.getDefaultTracker();
        mTracker.enableExceptionReporting(true);
    }

    synchronized private static Tracker getDefaultTracker() {
        // To enable debug logging use: adb shell setprop log.tag.GAv4 DEBUG
        if (sTracker == null) {
            sTracker = sAnalytics.newTracker(R.xml.global_tracker);
        }

        return sTracker;
    }

    public static void sendGoogleAnalyticsEvent(String eventName,String eventCategory,String eventLabel,int eventValue){

        Tracker mTracker = MUSKGoogleAnalytics.getDefaultTracker();
        mTracker.send(new HitBuilders.EventBuilder()
                .setCategory(eventCategory)
                .setAction(eventName)
                .setLabel(eventLabel)
                .setValue(eventValue)
                .build());

        System.out.println("Log ---> GoogleAnalyticsEventLog"+ eventName+", "+eventCategory+", "+eventLabel+", "+eventValue);
    }

}

