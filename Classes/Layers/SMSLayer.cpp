//
//  SMSLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 8/12/13.
//
//

#include "SMSLayer.h"

#include "AnytaleHTTP.h"
#include "UIMessageViewBridge.h"

static UIMessageViewBridge *gUIMessageViewBridge = nil;

SMSLayer::SMSLayer() {
}

SMSLayer::~SMSLayer() {
    [gUIMessageViewBridge release];
}

void SMSLayer::webViewDidFinishLoad() {
}

SMSLayer *SMSLayer::create() {
    SMSLayer *smsLayer = new SMSLayer;

    if (smsLayer && smsLayer->init()) {
        smsLayer->autorelease();
        return smsLayer;
    }
    CC_SAFE_DELETE(smsLayer);
    return NULL;
}

SMSLayer *SMSLayer::createWithMessage(std::string message) {
    SMSLayer *smsLayer = new SMSLayer;
    smsLayer->message = message;

    if (smsLayer && smsLayer->init()) {
        smsLayer->autorelease();
        return smsLayer;
    }
    CC_SAFE_DELETE(smsLayer);
    return NULL;
}

bool SMSLayer::init() {
    //////////////////////////////
    // 1. super init first
    if (!CCLayer::init()) {
        return false;
    }

    NSString *message = [NSString stringWithUTF8String:this->message.c_str()];
    gUIMessageViewBridge = [[UIMessageViewBridge alloc] init];
    [gUIMessageViewBridge setMessage:message];
    [gUIMessageViewBridge setLayerWebView:this];

    return true;
}
