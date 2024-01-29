//
//  BuyJadeLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/5/13.
//
//

#ifndef __NabuzaI__BuyJadeLayer__
#define __NabuzaI__BuyJadeLayer__

// #import <Foundation/Foundation.h>

#include "cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;

class BuyJadeLayer : public cocos2d::CCLayerColor {
private:
    ~BuyJadeLayer(void);
    bool init();
    void onEnter();
    void close();
    void registCoupon();
    void onBuyJadeButtonTapped(CCObject *object);

    void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);

    // Notification Funtions
    void purchasingIAP(CCObject *obj);
    void purchasedIAP(CCObject *obj);
    void failedIAP(CCObject *obj);
    void restoredIAP(CCObject *obj);

    // Touches
    bool ccTouchBegan(CCTouch *touch, CCEvent *pEvent);
    void registerWithTouchDispatcher();

public:
    CREATE_FUNC(BuyJadeLayer);
};

#endif /* defined(__NabuzaI__BuyJadeLayer__) */
