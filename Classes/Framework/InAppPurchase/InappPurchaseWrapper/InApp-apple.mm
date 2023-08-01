//
//  ITIWCrashlytics-apple.m
//  ITIW
//
//  Created by itiw on 3/3/18.
//
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

#import "InApp.h"
#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>
#include "InAppManager.h"
#include "../../InAppPurchase/SubscriptionUnitManager.h"

#pragma mark- InAppPurchase

@protocol StoreKitSinglePurchaseDelegate <NSObject>
-(void) provideContent: (NSString*) productIdentifier;
@end

@interface StoreKitSinglePurchase : NSObject<SKProductsRequestDelegate, SKPaymentTransactionObserver> {
    //NSMutableArray *purchasableObjects;
    id <StoreKitSinglePurchaseDelegate> delegate;
    BOOL isInAppDataUpdate;
    int updateInAppCount;
    vector<LocalisedInappValues> returnResults;
}

@property (nonatomic, strong) id <StoreKitSinglePurchaseDelegate> delegate;
@property (readwrite, assign) BOOL isInAppDataUpdate;

+ (StoreKitSinglePurchase*)sharedPurchase;
- (void) purchaseWithIdentifier: (NSString*) _identifier;
- (void) restoreWithIdentifier: (NSString*) _identifier;
- (void) provideContent: (NSString*) productIdentifier;

#pragma mark SKPaymentTransactionObserver
- (void) paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions;
- (void) failedTransaction: (SKPaymentTransaction *)transaction;
- (void) completeTransaction: (SKPaymentTransaction *)transaction;
- (void) restoreTransaction: (SKPaymentTransaction *)transaction;

- (void) loadInAppProduct:(NSString*)productIds seperator:(NSString*) seperator;

@end

@implementation StoreKitSinglePurchase

static StoreKitSinglePurchase *_sharedStoreManager=nil;

@synthesize delegate;
@synthesize isInAppDataUpdate;

+ (StoreKitSinglePurchase*)sharedPurchase
{
    if (_sharedStoreManager == nil)
        _sharedStoreManager=[[self alloc] init];
    
    return _sharedStoreManager;
}

-(id)init {
    if((self = [super init])) {
        
        isInAppDataUpdate=false;
    }
    return self;
}

#pragma mark SKProductRequestDelegate
- (void)request:(SKRequest *)request didFailWithError:(NSError *)error
{
    
}

- (void)requestDidFinish:(SKRequest *)request
{
    // Release the request
    //[request release];
}

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    SKProduct *product = [[response products] lastObject];
    
    if(isInAppDataUpdate==true)
    {
        updateInAppCount--;
    }
    
    if (!product)
    {
        NSLog(@"Error retrieving product information from App Store. Sorry! Please try again later");
        return;
    }
    
    if(isInAppDataUpdate==false)
    {
        [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
        SKPayment *payment = [SKPayment paymentWithProduct:product];
        [[SKPaymentQueue defaultQueue] addPayment:payment];
    }
    else
    {
        //NSString *price = [NSString stringWithFormat:@"%@%@ %@", [product.priceLocale objectForKey:NSLocaleCurrencySymbol], product.price, [product.priceLocale objectForKey:NSLocaleCurrencyCode]];
        
        LocalisedInappValues inappValues;
        inappValues.productId = [product.productIdentifier cStringUsingEncoding:[NSString defaultCStringEncoding]];
        inappValues.currency = [[product.priceLocale objectForKey:NSLocaleCurrencyCode] cStringUsingEncoding:[NSString defaultCStringEncoding]];
        inappValues.priceValue = [product.price doubleValue];
        
        returnResults.push_back(inappValues);
        
       /* NSLog(@"[product.priceLocale objectForKey:NSLocaleCurrencyCode] %@",[product.priceLocale objectForKey:NSLocaleCurrencyCode]);
        NSString * tmpTitle = product.productIdentifier;
        NSString * tmpMsg = [NSString stringWithFormat:@"%s ---- %f",inappValues.currency.c_str() ,inappValues.priceValue];
        UIAlertController * alert = [UIAlertController
                                     alertControllerWithTitle:tmpTitle
                                     message:tmpMsg
                                     preferredStyle:UIAlertControllerStyleAlert];
        
        
        
        UIAlertAction* yesButton = [UIAlertAction
                                    actionWithTitle:@"OK"
                                    style:UIAlertActionStyleDefault
                                    handler:^(UIAlertAction * action) {
                                        //Handle your yes please button action here
                                    }];
        
        [alert addAction:yesButton];
        
        [[[[[UIApplication sharedApplication] delegate] window] rootViewController] presentViewController:alert animated:YES completion:nil];*/
        
        if(updateInAppCount==0)
        {
            isInAppDataUpdate=false;
            InAppManager::sharedManager()->onGetInappProducts(returnResults);
        }
    }
}

- (void) purchaseWithIdentifier: (NSString*) _identifier {
    
    if ([SKPaymentQueue canMakePayments])
    {
        isInAppDataUpdate=false;
        
        SKProductsRequest *preq = [[SKProductsRequest alloc] initWithProductIdentifiers:[NSSet setWithObject:_identifier]];
        preq.delegate = self;
        [preq start];
    }
}

- (void) restoreWithIdentifier: (NSString*) _identifier
{
    if ([SKPaymentQueue canMakePayments])
     {
         isInAppDataUpdate=false;
         
         SKProductsRequest *preq = [[SKProductsRequest alloc] initWithProductIdentifiers:[NSSet setWithObject:_identifier]];
         preq.delegate = self;
         [preq start];
     }
}

-(void) provideContent: (NSString*) productIdentifier
{
    NSData *receiptData = [NSData dataWithContentsOfURL:[[NSBundle mainBundle] appStoreReceiptURL]];
    NSString *receiptStr = [receiptData base64EncodedStringWithOptions:0];//[[NSString alloc] initWithData:receiptData encoding:NSASCIIStringEncoding];
    InAppManager::sharedManager()->onProductPurchasedInapp([productIdentifier cStringUsingEncoding:[NSString defaultCStringEncoding]],"purchaseToken",[receiptStr UTF8String]);
}
/*
 #pragma mark SKPaymentTransactionObserver
 -(BOOL)paymentQueue:(SKPaymentQueue *)queue shouldAddStorePayment:(SKPayment *)payment forProduct:(SKProduct *)product
 {
 return YES;
 }
 */
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    for (SKPaymentTransaction *transaction in transactions)
    {
        switch (transaction.transactionState)
        {
                /*case SKPaymentTransactionStateDeferred:
                 // ASk for buy
                 NSLog(@"SDN-AskforBuy");
                 break;*/
            case SKPaymentTransactionStatePurchasing:
                // on progress
                NSLog(@"SDN-OnProgress");
                break;
            case SKPaymentTransactionStatePurchased:
                [self completeTransaction:transaction];
                break;
                
            case SKPaymentTransactionStateFailed:
                [self failedTransaction:transaction];
                break;
                
            case SKPaymentTransactionStateRestored:
                [self restoreTransaction:transaction];
                break;
                
            default:
                break;
        }
    }
}

- (void) failedTransaction: (SKPaymentTransaction *)transaction
{
    CCLOG("transaction.error.code %ld",transaction.error.code);
    if (transaction.error.code != SKErrorPaymentCancelled)
    {
        NSString *messageToBeShown = [NSString stringWithFormat:@"Reason: %@, You can try: %@", [transaction.error localizedFailureReason], [transaction.error localizedRecoverySuggestion]];
        InAppManager::sharedManager()->onBillingErrorInapp((int)transaction.error.code, [messageToBeShown cStringUsingEncoding:[NSString defaultCStringEncoding]]);
    }
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}

- (void) completeTransaction: (SKPaymentTransaction *)transaction
{
    SingleSubscriptionUnit *singleSubscriptionUnit=SubscriptionUnitManager::sharedManager()->subscriptionUnitForIdentifier([transaction.payment.productIdentifier UTF8String]);
    if(singleSubscriptionUnit!=NULL)
    {
        UserDefault *userDefault=UserDefault::getInstance();
        userDefault->setBoolForKey([transaction.payment.productIdentifier UTF8String], true);
        userDefault->flush();
    }
    else
        [self provideContent:transaction.payment.productIdentifier];
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}

- (void) restoreTransaction: (SKPaymentTransaction *)transaction
{
    [self provideContent:transaction.payment.productIdentifier];
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}

-(void) provideContentForTransaction: (NSString*) productIdentifier
{
    //NSData *receiptData = [NSData dataWithContentsOfURL:[[NSBundle mainBundle] appStoreReceiptURL]];
    //NSString *receiptStr = [receiptData base64EncodedStringWithOptions:0];//[[NSString alloc] initWithData:receiptData encoding:NSASCIIStringEncoding];
    //InAppManager::sharedManager()->onProductPurchasedInapp([productIdentifier cStringUsingEncoding:[NSString defaultCStringEncoding]],"purchaseToken",[receiptStr UTF8String]);
}

-(void) loadInAppProduct:(NSString*)productIds seperator:(NSString*) seperator
{
    NSArray *productList = [productIds componentsSeparatedByString:seperator];
    
    if ([SKPaymentQueue canMakePayments])
    {
        updateInAppCount=(int)[productList count];
        returnResults.clear();
        for (int i=0; i<[productList count]; i++)
        {
            NSString *strProductIdentifire=[productList objectAtIndex:i];
            
            SKProductsRequest *preq = [[SKProductsRequest alloc] initWithProductIdentifiers:[NSSet setWithObject:strProductIdentifire]];
            preq.delegate = self;
            [preq start];
            
            /*NSString * tmpTitle = strProductIdentifire;
            NSString * tmpMsg = @"";
            UIAlertController * alert = [UIAlertController
                                         alertControllerWithTitle:tmpTitle
                                         message:tmpMsg
                                         preferredStyle:UIAlertControllerStyleAlert];
            
            
            
            UIAlertAction* yesButton = [UIAlertAction
                                        actionWithTitle:@"OK"
                                        style:UIAlertActionStyleDefault
                                        handler:^(UIAlertAction * action) {
                                            //Handle your yes please button action here
                                        }];
            
            [alert addAction:yesButton];
            
            [[[[[UIApplication sharedApplication] delegate] window] rootViewController] presentViewController:alert animated:YES completion:nil];*/
        }
    }
}

void InApp::initInApp()
{
    InAppManager::sharedManager()->loadInappProducts();
}

#pragma mark- InApp custom methods

void InApp::purchase(string _productId)
{
    NSString *_identifier = [NSString stringWithCString:_productId.c_str() encoding:[NSString defaultCStringEncoding]];
    
    [[StoreKitSinglePurchase sharedPurchase] purchaseWithIdentifier:_identifier];
}

void InApp::restorePurchase(string _productId)
{
    NSString *_identifier = [NSString stringWithCString:_productId.c_str() encoding:[NSString defaultCStringEncoding]];
    
    [[StoreKitSinglePurchase sharedPurchase] restoreWithIdentifier:_identifier];
}

bool InApp::isInappServiceAvailable()
{
    return false;
}

void InApp::loadInappProducts(string productIds, string seperator)
{
    [StoreKitSinglePurchase sharedPurchase].isInAppDataUpdate=true;
    NSString *_productIds = [NSString stringWithCString:productIds.c_str() encoding:[NSString defaultCStringEncoding]];
    NSString *_seperator = [NSString stringWithCString:seperator.c_str() encoding:[NSString defaultCStringEncoding]];
    
    [[StoreKitSinglePurchase sharedPurchase] loadInAppProduct:_productIds seperator:_seperator];
}

void InApp::subscribe(string _productId)
{
    purchase(_productId);
}

bool InApp::isSubscribed(string _productId)
{
    UserDefault *userDefault=UserDefault::getInstance();
    bool isSubscribe=userDefault->getBoolForKey(_productId.c_str());
    if(isSubscribe==true)
        return true;
    //return true;
//    if([StoreKitSinglePurchase sharedPurchase] isProductPurchased:_productId]) {
//        return true;
//    }
    return false;
}

bool InApp::isCancelled(string _productId)
{
    return true;
}

@end

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

