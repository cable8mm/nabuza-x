//
//  InAppPurchase.m
//  NabuzaI
//
//  Created by Lee Samgu on 8/27/13.
//
//

#import "InAppPurchase.h"
#include "cocos2d.h"

@implementation InAppPurchase

+(id)sharedInstance
{
    static dispatch_once_t pred = 0;
    __strong static id _sharedObject = nil;
    dispatch_once(&pred, ^{
        _sharedObject = [[self alloc] init];
    });
    return _sharedObject;
}

-(id)init {
    if ((self = [super init]) == nil) {
        return nil;
    }
    return self;
}

-(BOOL) canMakePayments {
    if ([SKPaymentQueue canMakePayments] == NO) {
        return NO;
    }
    
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
    
    return YES;
}

-(void)requestProductData:(int)productKey {
    // 0 부터 순서대로 NABUZA_PRODUCT_JADE_80 - 
    NSSet *productIdentifiers;
    switch (productKey) {
        case 0:
            productIdentifiers   = [NSSet setWithObject:@"NABUZA_PRODUCT_JADE_20"];
            break;
        case 1:
            productIdentifiers   = [NSSet setWithObject:@"NABUZA_PRODUCT_JADE_80"];
            break;
        case 2:
            productIdentifiers   = [NSSet setWithObject:@"NABUZA_PRODUCT_JADE_180"];
            break;
        case 3:
            productIdentifiers   = [NSSet setWithObject:@"NABUZA_PRODUCT_JADE_500"];
            break;
        case 4:
            productIdentifiers   = [NSSet setWithObject:@"NABUZA_PRODUCT_JADE_1500"];
            break;
    }
    SKProductsRequest *request  = [[SKProductsRequest alloc] initWithProductIdentifiers:productIdentifiers];
    request.delegate    = self;
    [request start];
}

-(void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response {
    for (SKProduct *product in response.products) {
        if (product != nil) {
            // 구매 요청
            SKPayment *payment  = [SKPayment paymentWithProduct:product];
            [[SKPaymentQueue defaultQueue] addPayment:payment];
        }
    }
    
    [request release];
    
    for (NSString *invalidProductId in response.invalidProductIdentifiers)
    {
        NSLog(@"InAppPurchase Invalid product id: %@", invalidProductId);
    }
}

-(void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions {
    for (SKPaymentTransaction *transaction in transactions) {
        switch (transaction.transactionState) {
            case SKPaymentTransactionStatePurchasing:
                NSLog(@"서버에 거래 처리중 / PURCHASING_IAP_NOTIFICATION");
                cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification("PURCHASING_IAP_NOTIFICATION");
                break;
            case SKPaymentTransactionStatePurchased:
                NSLog(@"구매 완료 / PURCHASED_IAP_NOTIFICATION");
                
                [self completeTransaction:transaction];
                
                break;
            case SKPaymentTransactionStateFailed:
            {
                NSLog(@"거래 실패 또는 취소 / FAILED_IAP_NOTIFICATION");
                [self failedTransaction:transaction];
            }
                break;
            case SKPaymentTransactionStateRestored:
                NSLog(@"재구매 / RESTORED_IAP_NOTIFICATION");
                [self restoreTransaction:transaction];
                break;
        }
    }
}

-(void)completeTransaction:(SKPaymentTransaction *)transaction {
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
    
    std::string productId   = [transaction.payment.productIdentifier UTF8String];
    cocos2d::CCString *productIdentifier     = cocos2d::CCString::create(productId.c_str());

    cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification("PURCHASED_IAP_NOTIFICATION", productIdentifier);
}

-(void)restoreTransaction:(SKPaymentTransaction *)transaction {
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];

    cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification("RESTORED_IAP_NOTIFICATION");
}

-(void)failedTransaction:(SKPaymentTransaction *)transaction {
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
    
    std::string productId   = [transaction.payment.productIdentifier UTF8String];
    cocos2d::CCString *productIdentifier     = cocos2d::CCString::create(productId.c_str());
    cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification("FAILED_IAP_NOTIFICATION", productIdentifier);
}



@end
