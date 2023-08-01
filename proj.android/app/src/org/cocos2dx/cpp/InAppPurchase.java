package org.cocos2dx.cpp;

import android.os.AsyncTask;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import android.util.Log;

import com.anjlab.android.iab.v3.BillingProcessor;
import com.anjlab.android.iab.v3.SkuDetails;
import com.anjlab.android.iab.v3.TransactionDetails;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class InAppPurchase {

    public static class LocalisedInappValues
    {
        public String productId;
        public String currency;
        public double priceValue;
    };

    private static final String TAG = AppActivity.class.getSimpleName();
    private static AppActivity sActivity = AppActivity.getActivity();
    //private static final String licenseKeygp = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAgL8m3uKBfIlKYpXaKmPaoh0yLuhUFvvf2vzaBd3S0XGXFciYXNrK7/kIp32Fm8o1Dgew9k/xGC8ZPUK9cVzzTFwz0Pgyd7ABKdy4/0CpeEmyLXfFXP9+GAhv+HY2zTTxspwehc5/YDeNDa76ifnl59OWCdafMSUEB862m27h0KqspRmJnBXkeki8Kl+3/8k1zI8JHDL31iIxYD+4auZyXKJWebyGzsAb0X8VzyFvCgt5RjRdObQczlwFY9aZKCXANGBA/iv/iVmiOZaNiXxV/B0tx5l1Zq/kgyH+WZmq8EsXmbGKPgOGOsfHmIVvGUfG/EkW/cE2Ajk0Bj3hd+QWzQIDAQAB";

    private static native void onProductPurchasedInapp(String productId, String purchaseToken, String purchaseSignature);
    private static native void onPurchaseHistoryRestoredInapp();
    private static native void onBillingErrorInapp(int errorCode, String errorMessage);
    private static native void onBillingInitializedInapp();

    private static native void onProductSubscription(String productId, String purchaseToken, String purchaseSignature);

    private static native void onGetInappProducts(LocalisedInappValues results[]);

    public static void initInApp(String licenseKeygp) {
        Log.v(TAG,"initInApp-java");
        AppActivity.billingProcessor = new BillingProcessor(sActivity, licenseKeygp, new BillingProcessor.IBillingHandler() {
            // IBillingHandler implementation
            @Override
            public void onProductPurchased(@NonNull String productId, @Nullable TransactionDetails details) {
                Log.v(TAG,"onProductPurchased productid: " + productId+" d: "+details.purchaseInfo.responseData+" details: "+details.toString());
                if (AppActivity.billingProcessor.isSubscribed(productId)) {
                    Log.v(TAG,"This is a subscription");
                    InAppPurchase.onProductSubscription(productId, details.purchaseInfo.responseData, details.purchaseInfo.signature);
                }
                else {
                    Log.v(TAG,"This is an inapp");
                    InAppPurchase.onProductPurchasedInapp(productId,details.purchaseInfo.responseData, details.purchaseInfo.signature);
                    AppActivity.billingProcessor.consumePurchase(productId);
                }
            }

            @Override
            public void onPurchaseHistoryRestored() {
                Log.v(TAG,"onPurchaseHistoryRestored");
                InAppPurchase.onPurchaseHistoryRestoredInapp();
            }

            @Override
            public void onBillingError(int errorCode, @Nullable Throwable error) {
                Log.v(TAG,"onBillingError code: "+errorCode);
                InAppPurchase.onBillingErrorInapp(errorCode, "Billing Error");
            }

            @Override
            public void onBillingInitialized() {
                Log.v(TAG,"onBillingInitialized");
                InAppPurchase.onBillingInitializedInapp();
            }
        });
        AppActivity.billingProcessor.initialize();
        // or billingProcessor = BillingProcessor.newBillingProcessor(this, licenseKeygp, this);
        // See below on why this is a useful alternative
    }

    public static void purchase(String _productId) {

        boolean isInappAvailable = InAppPurchase.isInappServiceAvailable() && AppActivity.billingProcessor != null;
        Log.v("TAG","isAvailable: "+isInappAvailable);

        if(isInappAvailable) {
            AppActivity.billingProcessor.purchase(sActivity, _productId);
        }
        else {
            Log.v("TAG","Inapp Purchase is not supported or initialized");
        }
    }

    public static boolean isInappServiceAvailable()
    {
        return BillingProcessor.isIabServiceAvailable(sActivity);
    }

    private static boolean isInappAvailable()
    {
        boolean isInappAvailable = InAppPurchase.isInappServiceAvailable() && AppActivity.billingProcessor != null && AppActivity.billingProcessor.isInitialized();
        return  isInappAvailable;
    }

    public static void loadInappProducts(final String productIds, final String seperator) // Here productIds is a string of multiple productid seperated by seperator(in this case seperator is semi-colon i.e ;)
    {
        AsyncTask.execute(new Runnable() {
            @Override
            public void run() {
                InAppPurchase.loadInappProductsBackground(productIds,seperator);
            }
        });
    }

    private static void loadInappProductsBackground(String productIds, String seperator)
    {
        boolean isInappAvailable = InAppPurchase.isInappAvailable();
        if (!isInappAvailable) return;

        String productIdsArray[] = productIds.split(seperator);
        ArrayList<String> productIdsArrayList =  new ArrayList<String>(Arrays.asList(productIdsArray));
        List<SkuDetails> skuDetailsList = AppActivity.billingProcessor.getPurchaseListingDetails(productIdsArrayList);
        ArrayList<LocalisedInappValues> resultsArray = new ArrayList<LocalisedInappValues>();

        //Log.v("TAG"," result-size: "+Integer.toString(skuDetailsList.size()));

        if (skuDetailsList != null)
        {
            for (int i = 0; i < skuDetailsList.size(); i++) {
                SkuDetails sDetails = skuDetailsList.get(i);
                LocalisedInappValues inappValues = new LocalisedInappValues();
                inappValues.productId = sDetails.productId;
                inappValues.currency = sDetails.currency;
                inappValues.priceValue = sDetails.priceValue;
                resultsArray.add(inappValues);
            }
        }

        LocalisedInappValues results[] = resultsArray.toArray(new LocalisedInappValues[resultsArray.size()]);
        InAppPurchase.onGetInappProducts(results);
    }

    // Subscription implementation

    public static void subscribe(String _productId)
    {
        if (InAppPurchase.isInappAvailable())
        {
            AppActivity.billingProcessor.subscribe(sActivity, _productId);
        }
    }

    public static boolean isSubscribed(String _productId)
    {
        if (InAppPurchase.isInappAvailable()) {
            return AppActivity.billingProcessor.isSubscribed(_productId);
        }

        return false;
    }

    public static boolean isCancelled(String _productId)
    {
        TransactionDetails tDetails = AppActivity.billingProcessor.getSubscriptionTransactionDetails(_productId);
        return !tDetails.purchaseInfo.purchaseData.autoRenewing;
    }
}
