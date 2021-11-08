//
//  IAPWrapper.h
//  NabuzaI
//
//  Created by Lee Samgu on 8/21/13.
//
//

#import "IAPHelper_objc.h"
#import "IAPCallback.h"

class IAPWrapper
{
public:
    // Some users might have IAP disabled
    bool canMakePayments();
    
    void requestProducts(iOSBridge::Callbacks::IAPCallback* callback);
    
    void buyProductIdentifier(const std::string& productID);
    
};

#endif

@interface IAPWrapper : NSObject

@end
