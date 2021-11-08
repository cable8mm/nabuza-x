//
//  CouponLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 8/13/13.
//
//

#ifndef __NabuzaI__CouponLayer__
#define __NabuzaI__CouponLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CouponLayer : public cocos2d::CCLayerColor
{
public:
    CREATE_FUNC(CouponLayer);
    
private:
    std::stringstream couponNumber;
    void addCouponNumber(int v);
    void drawCouponNumber();
    void onEnter();
    void close();
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void registerWithTouchDispatcher();
    void registerCoupon();
    void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);
};

#endif /* defined(__NabuzaI__CouponLayer__) */
