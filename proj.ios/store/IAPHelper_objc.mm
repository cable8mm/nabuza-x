//
//  IAPHelper_objc.m
//  NabuzaI
//
//  Created by Lee Samgu on 8/21/13.
//
//

#import "IAPHelper_objc.h"

@implementation IAPHelper_objc

@synthesize productIdentifiers = _productIdentifiers;
@synthesize products = _products;
@synthesize purchasedProducts = _purchasedProducts;
@synthesize request = _request;

- (id)initWithProductIdentifiers:(NSSet *)productIdentifiers{
	latestIAPCallback = nil;
    
	if ((self = [super init])) {
		_productIdentifiers = [productIdentifiers retain];
        
		// Check for previously purchased products
		NSMutableSet * purchasedProducts = [NSMutableSet set];
		for (NSString * productIdentifier in _productIdentifiers)
		{
			BOOL productPurchased = [[NSUserDefaults standardUserDefaults] boolForKey:productIdentifier];
			if (productPurchased)
			{
				[purchasedProducts addObject:productIdentifier];
				NSLog(@"Previously purchased: %@", productIdentifier);
			}
			NSLog(@"Not purchased: %@", productIdentifier);
		}
        
		self.purchasedProducts = purchasedProducts;
	}
	return self;
}

- (bool)canMakePayments
{
	return [SKPaymentQueue canMakePayments];
}

- (void)requestProductsWithCallback:(iOSBridge::Callbacks::IAPCallback*)callback
{
	latestIAPCallback = callback;
	[self requestProducts];
}

- (void)requestProducts {
	self.request = [[[SKProductsRequest alloc] initWithProductIdentifiers:_productIdentifiers] autorelease];
	_request.delegate = self;
	[_request start];
    
}

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response {
    
	NSLog(@"Received products results...");
	self.products = response.products;
	self.request = nil;
    
	[[NSNotificationCenter defaultCenter] postNotificationName:kProductsLoadedNotification object:_products];
    
//	std::vector items;
    
	// populate UI
//	for(int i=0;iproductsDownloaded(items);
}
        
- (void)productsLoaded:(NSNotification *)notification {
    [NSObject cancelPreviousPerformRequestsWithTarget:self];
}
        
- (void)dealloc
{
    [_productIdentifiers release];
    _productIdentifiers = nil;
    [_products release];
    _products = nil;
    [_purchasedProducts release];
    _purchasedProducts = nil;
    [_request release];
    _request = nil;
    [super dealloc];
}

@end
