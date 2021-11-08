//
//  UIMessageViewBridge.m
//  NabuzaI
//
//  Created by Lee Samgu on 8/12/13.
//
//

#import "UIMessageViewBridge.h"
#import "EAGLView.h"

//@synthe

@interface UIMessageViewBridge () <
MFMailComposeViewControllerDelegate,
MFMessageComposeViewControllerDelegate,
UINavigationControllerDelegate
>

@end

@implementation UIMessageViewBridge

@synthesize message;

-(void) setLayerWebView : (SMSLayer*) iLayerSMSView
{
    mSMSLayer = iLayerSMSView;
    cocos2d::CCSize size = mSMSLayer->getContentSize();
    
    CGRect screenBound = [[UIScreen mainScreen] bounds];
    
    CGFloat screenWidth = screenBound.size.width;
    CGFloat screenHeight    = screenBound.size.height;
    
    mView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, screenWidth , screenHeight)];
    
    NSLog(@"UIView width : %f, height : %f", screenWidth, screenHeight);
    
    // create webView
//    int wBottomMargin = screenHeight*0.10;
//    int wWebViewHeight = screenHeight - wBottomMargin;
//    mWebView = [[UIWebView alloc] initWithFrame:CGRectMake(0, 0, screenWidth, wWebViewHeight)];
//    mWebView.delegate = self;
//    [mWebView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlString ]]];
//    [mWebView setUserInteractionEnabled:NO]; //don't let the user scroll while things are
    
    messageViewController = [[MFMessageComposeViewController alloc] init];
    messageViewController.messageComposeDelegate = self;
    
    MFMessageComposeViewController *picker = [[MFMessageComposeViewController alloc] init];
    picker.messageComposeDelegate = self;
    
    // You can specify one or more preconfigured recipients.  The user has
    // the option to remove or add recipients from the message composer view
    // controller.
    /* picker.recipients = @[@"Phone number here"]; */
    
    // You can specify the initial message text that will appear in the message
    // composer view controller.
    picker.body = message;
    
    [[UIApplication sharedApplication].keyWindow.rootViewController presentViewController:picker animated:YES completion:NULL];
    
    // add the webView to the view
//    [mView addSubview:picker.view];
//    [[EAGLView sharedEGLView] addSubview:mView];
    
    // add the webView to the view
//    [self displaySMSComposerSheet];
    
}

#pragma mark - Rotation

#if __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_6_0
// -------------------------------------------------------------------------------
//	shouldAutorotateToInterfaceOrientation:
//  Disable rotation on iOS 5.x and earlier.  Note, for iOS 6.0 and later all you
//  need is "UISupportedInterfaceOrientations" defined in your Info.plist
// -------------------------------------------------------------------------------
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
#endif

#pragma mark - Delegate Methods

// -------------------------------------------------------------------------------
//	mailComposeController:didFinishWithResult:
//  Dismisses the email composition interface when users tap Cancel or Send.
//  Proceeds to update the message field with the result of the operation.
// -------------------------------------------------------------------------------
- (void)mailComposeController:(MFMailComposeViewController*)controller
          didFinishWithResult:(MFMailComposeResult)result error:(NSError*)error
{
	[[UIApplication sharedApplication].keyWindow.rootViewController dismissViewControllerAnimated:YES completion:NULL];
}

// -------------------------------------------------------------------------------
//	messageComposeViewController:didFinishWithResult:
//  Dismisses the message composition interface when users tap Cancel or Send.
//  Proceeds to update the feedback message field with the result of the
//  operation.
// -------------------------------------------------------------------------------
- (void)messageComposeViewController:(MFMessageComposeViewController *)controller
                 didFinishWithResult:(MessageComposeResult)result
{
	[[UIApplication sharedApplication].keyWindow.rootViewController dismissViewControllerAnimated:YES completion:NULL];
}

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
