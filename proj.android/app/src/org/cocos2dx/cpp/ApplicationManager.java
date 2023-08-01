package org.cocos2dx.cpp;

import com.insparofaith.restaurant.R;
import com.insparofaith.restaurant.BuildConfig;
import android.provider.Settings;
import android.provider.Settings.Secure;
import android.util.Log;
import android.app.Activity;
import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;

import org.cocos2dx.lib.Cocos2dxActivity;

public class ApplicationManager extends Cocos2dxActivity {

    private static final String TAG = AppActivity.class.getSimpleName();

    public static String getApplicationPackageName() {
        Log.v(TAG, "getApplicationPackageName");
        return BuildConfig.APPLICATION_ID;
    }

    public static String getDeviceUDID() {
        Log.v(TAG, "getDeviceUDID");
        String android_id = Settings.Secure.getString(getContext().getContentResolver(),
                Secure.ANDROID_ID);
        return android_id;
    }

    public static String getDeviceOSVersion() {
        Log.v(TAG, "getDeviceOSVersion");
        String osVersion =  android.os.Build.VERSION.RELEASE;
        return osVersion;
    }

    public static String getDeviceName() {
        Log.v(TAG, "getDeviceName");
        String deviceBrand =  android.os.Build.BRAND;
        String deviceName =  deviceBrand +"-"+ android.os.Build.MODEL;
        return deviceName;
    }

    public static void setUserIdentifier(String _userIdentifier) {
        Log.v(TAG, "setUserIdentifier");
        //Crashlytics.setUserIdentifier(_userIdentifier);
    }

    public static void setUserEmail(String _userEmail) {
        Log.v(TAG, "setUserEmail");
        //Crashlytics.setUserEmail(_userEmail);
    }

    public static void setUserName(String _userName) {
        Log.v(TAG, "setUserName");
        //Crashlytics.setUserName(_userName);
    }

    public static void setString(String _key, String _value) {
        Log.v(TAG, "setString");
        //Crashlytics.setString(_key, _value);
    }

    public static boolean isConnectedToInternet() {
        ConnectivityManager cm = (ConnectivityManager)AppActivity.getActivity().getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo nInfo = cm.getActiveNetworkInfo();
        return cm != null && nInfo != null && nInfo.isConnected();
    }
}
