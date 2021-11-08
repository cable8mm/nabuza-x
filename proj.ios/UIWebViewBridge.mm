//
//  UIWebViewBridge.m
//  NabuzaI
//
//  Created by Lee Samgu on 7/3/13.
//
//

#import "UIWebViewBridge.h"
#import "EAGLView.h"

@implementation UIWebViewBridge
- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
    }
    
    urlString   = @"http://google.com";
    
    return self;
}

- (id)initWithUrl : (NSString *)url {
    self = [super init];
    if (self) {
        // Initialization code here.
    }
    
    urlString   = url;
    
    return self;
}

- (void)dealloc
{
   	[mBackButton release];
    [mToolbar release];
	[mWebView release];
	[mView release];
    [super dealloc];
}


-(void) setLayerWebView : (WebViewLayer*) iLayerWebView
{
    mLayerWebView = iLayerWebView;
    cocos2d::CCSize size = mLayerWebView->getContentSize();
    
    CGRect screenBound = [[UIScreen mainScreen] bounds];
    
    CGFloat screenWidth = screenBound.size.width;
    CGFloat screenHeight    = screenBound.size.height;
    
    mView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, screenWidth , screenHeight)];
    
    NSLog(@"UIView width : %f, height : %f", screenWidth, screenHeight);
    
    // create webView
    int wBottomMargin = screenHeight*0.10;
    int wWebViewHeight = screenHeight - wBottomMargin;
    mWebView = [[UIWebView alloc] initWithFrame:CGRectMake(0, 0, screenWidth, wWebViewHeight)];
    mWebView.delegate = self;
    [mWebView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlString ]]];
    [mWebView setUserInteractionEnabled:NO]; //don't let the user scroll while things are
    
    
    //create a tool bar for the bottom of the screen to hold the back button
    mToolbar = [UIToolbar new];
    [mToolbar setFrame:CGRectMake(0, wWebViewHeight, screenWidth, wBottomMargin)];
    mToolbar.barStyle = UIBarStyleBlackOpaque;
    
    //Create a button
    mBackButton = [[UIBarButtonItem alloc] initWithTitle:@"닫기"
                                                   style: UIBarButtonItemStyleDone
                                                  target: self
                                                  action:@selector(backClicked:)];
    //[backButton setBounds:CGRectMake(0.0, 0.0, 95.0, 34.0)];
    [mToolbar setItems:[NSArray arrayWithObjects:mBackButton,nil] animated:YES];
    [mView addSubview:mToolbar];
    //[mToolbar release];
    
    // add the webView to the view
    [mView addSubview:mWebView];
    [[EAGLView sharedEGLView] addSubview:mView];
}


- (void)webViewDidStartLoad:(UIWebView *)thisWebView {
	
    
}

- (void)webViewDidFinishLoad:(UIWebView *)thisWebView{
    [mWebView setUserInteractionEnabled:YES];
    mLayerWebView->webViewDidFinishLoad();
}

- (void)webView:(UIWebView *)thisWebView didFailLoadWithError:(NSError *)error
{
	if ([error code] != -999 && error != NULL) { //error -999 happens when the user clicks on something before it's done loading.
		
		UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Network Error" message:@"MultiTest was unable to load the page. Please try again later when you have a network connection."
													   delegate:self cancelButtonTitle:nil otherButtonTitles:@"OK", nil];
		[alert show];
		[alert release];
		
	}
    
}


-(void) backClicked:(id)sender {
	mWebView.delegate = nil; //keep the webview from firing off any extra messages
    
	//remove items from the Superview...just to make sure they're gone
	[mToolbar removeFromSuperview];
	[mWebView removeFromSuperview];
	[mView removeFromSuperview];
    
	mLayerWebView->onBackbuttonClick();
}

@end
