//
//  SMSLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 8/12/13.
//
//

#ifndef __NabuzaI__SMSLayer__
#define __NabuzaI__SMSLayer__

#include "cocos2d.h"
USING_NS_CC;

class SMSLayer : public cocos2d::CCLayer
{
private:
    //        CCMenu * menu;
    //        Label *label;
    int mWebViewLoadCounter;
    std::string message;
    
public:
    SMSLayer();
    ~SMSLayer();
    static SMSLayer *createWithMessage(std::string message);
    static SMSLayer *create();
    bool init();
    void webViewDidFinishLoad();
    void onBackbuttonClick();
};

#endif /* defined(__NabuzaI__SMSLayer__) */
