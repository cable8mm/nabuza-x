//
//  UIWebViewBridge.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/3/13.
//
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "cocos2d.h"
#import <UIKit/UIKit.h>

#import "WebViewLayer.h"

@interface UIWebViewBridge : NSObject<UIWebViewDelegate,UIAlertViewDelegate>
{
    WebViewLayer * mLayerWebView;
    UIView    *mView;
    UIWebView *mWebView;
    UIToolbar *mToolbar;
    UIBarButtonItem *mBackButton;
    NSString *urlString;
}
-(void) setLayerWebView : (WebViewLayer*) iLayerWebView ;
-(void) backClicked:(id)sender;

@end
