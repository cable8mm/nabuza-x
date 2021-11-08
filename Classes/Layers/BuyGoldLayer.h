//
//  BuyGoldLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 8/14/13.
//
//

#ifndef __NabuzaI__BuyGoldLayer__
#define __NabuzaI__BuyGoldLayer__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class BuyGoldLayer : public cocos2d::CCLayerColor
{
public:
    CREATE_FUNC(BuyGoldLayer);
    
private:
    void onEnter();
    void close();
    void onBuyGoldButtonTapped(CCObject *object);
    bool ccTouchBegan(CCTouch *touch, CCEvent *pEvent);
    void registerWithTouchDispatcher();
    
    void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);
};

#endif /* defined(__NabuzaI__BuyGoldLayer__) */
