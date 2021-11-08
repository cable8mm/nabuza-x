//
//  InAppPurchase.h
//  NabuzaI
//
//  Created by Lee Samgu on 8/27/13.
//
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>

@interface InAppPurchase : NSObject <SKProductsRequestDelegate, SKPaymentTransactionObserver>

+(id)sharedInstance;
-(id)init;
-(void)requestProductData:(int)productKey;
-(void)completeTransaction:(SKPaymentTransaction *)transaction;
-(void)restoreTransaction:(SKPaymentTransaction *)transaction;
-(void)failedTransaction:(SKPaymentTransaction *)transaction;
-(BOOL) canMakePayments;


@end
