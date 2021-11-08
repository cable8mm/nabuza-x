//
//  WebViewLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 7/3/13.
//
//  Reference : http://www.cocos2d-x.org/boards/6/topics/4450

#include "WebViewLayer.h"
#include "UIWebViewBridge.h"

static UIWebViewBridge *gUIWebViewBridge=nil;

WebViewLayer::WebViewLayer()
{
    
}

WebViewLayer::~WebViewLayer()
{
    [gUIWebViewBridge release];
}

void WebViewLayer::webViewDidFinishLoad()
{
    
}

WebViewLayer* WebViewLayer::createWithUrl(std::string url) {
    WebViewLayer *webViewLayer = new WebViewLayer;
    
    if (webViewLayer && webViewLayer->initWithUrl(url))
    {
        webViewLayer->autorelease();
        return webViewLayer;
    }
    CC_SAFE_DELETE(webViewLayer);
    return NULL;
}

void WebViewLayer::onBackbuttonClick()
{
    //    cocos2d::CCDirector::sharedDirector()->replaceScene(,
    //                                                                                                              HelloWorld::scene()));
}

bool WebViewLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    gUIWebViewBridge = [[UIWebViewBridge alloc] init];
    [gUIWebViewBridge setLayerWebView : this];
    return true;
}

bool WebViewLayer::initWithUrl(std::string url)
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    NSString *urlString   = [NSString stringWithUTF8String:url.c_str()];
    gUIWebViewBridge = [[UIWebViewBridge alloc] initWithUrl:urlString];
    [gUIWebViewBridge setLayerWebView : this];
    return true;
}