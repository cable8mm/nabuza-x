//
//  WebViewLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/3/13.
//
//

#ifndef __NabuzaI__WebViewLayer__
#define __NabuzaI__WebViewLayer__

#include "cocos2d.h"
USING_NS_CC;

class WebViewLayer : public cocos2d::CCLayer
{
private:
    //        CCMenu * menu;
    //        Label *label;
    int mWebViewLoadCounter;
public:
    WebViewLayer();
    ~WebViewLayer();
    static WebViewLayer *createWithUrl(std::string url);
    virtual bool init();
    bool initWithUrl(std::string url);
    void webViewDidFinishLoad();
    void onBackbuttonClick();
};

#endif /* defined(__NabuzaI__WebViewLayer__) */
