//
//  UIMessageViewBridge.h
//  NabuzaI
//
//  Created by Lee Samgu on 8/12/13.
//
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "cocos2d.h"
#import <UIKit/UIKit.h>
#import <MessageUI/MessageUI.h>

#import "SMSLayer.h"

@interface UIMessageViewBridge : UIViewController {
    SMSLayer *mSMSLayer;
    UIView    *mView;
    NSString *message;
    MFMessageComposeViewController    *messageViewController;
}

-(void) setLayerWebView : (SMSLayer*) iLayerSMSView;

@property (nonatomic, retain) NSString *message;

@end
