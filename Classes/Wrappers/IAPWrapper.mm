//
//  IAPWrapper.m
//  NabuzaI
//
//  Created by Lee Samgu on 8/21/13.
//
//

#import "IAPWrapper.h"

bool IAPWrapper::canMakePayments()
{
    return [[IAPHelperFight_objc sharedHelper] canMakePayments];
}

void IAPWrapper::requestProducts(iOSBridge::Callbacks::IAPCallback* callback)
{
    [[IAPHelperFight_objc sharedHelper] requestProductsWithCallback: callback];
}

void IAPWrapper::buyProductIdentifier(const std::string& productID)
{
    NSString *nsID = [NSString stringWithCString:productID.c_str()
                                        encoding:[NSString defaultCStringEncoding]];
    
    [[IAPHelperFight_objc sharedHelper] buyProductIdentifier:nsID];
}
