//
//  IAPHelper_objc.h
//  NabuzaI
//
//  Created by Lee Samgu on 8/21/13.
//
//

#import <Foundation/Foundation.h>
#import "StoreKit/StoreKit.h"
#include "IAPCallback.h"

#define kProductsLoadedNotification         @"ProductsLoaded"
#define kProductPurchasedNotification       @"ProductPurchased"
#define kProductPurchaseFailedNotification  @"ProductPurchaseFailed"

@interface IAPHelper_objc : NSObject <SKProductsRequestDelegate> {
    NSSet * _productIdentifiers;
    NSArray * _products;
    NSMutableSet * _purchasedProducts;
    SKProductsRequest * _request;
    iOSBridge::Callbacks::IAPCallback* latestIAPCallback;
}

@property (retain) NSSet *productIdentifiers;
@property (retain) NSArray * products;
@property (retain) NSMutableSet *purchasedProducts;
@property (retain) SKProductsRequest *request;

- (void)buyProductIdentifier:(NSString *)productIdentifier;
- (void)requestProducts;
- (id)initWithProductIdentifiers:(NSSet *)productIdentifiers;
- (bool)canMakePayments;
- (void)requestProductsWithCallback:(iOSBridge::Callbacks::IAPCallback*)callback;
- (void)buyProductIdentifier:(NSString *)productIdentifier;

@end