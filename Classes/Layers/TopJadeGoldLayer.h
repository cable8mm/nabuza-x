//
//  TopJadeGoldLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 8/14/13.
//
//

#ifndef __NabuzaI__TopJadeGoldLayer__
#define __NabuzaI__TopJadeGoldLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class TopJadeGoldLayer : public cocos2d::CCLayerColor
{
public:
    CREATE_FUNC(TopJadeGoldLayer);
    void setCanPushJadeButton(bool v);
    void setCanPushGoldButton(bool v);
    
private:
    bool canJadeButton;
    bool canGoldButton;
    
    bool init();
    TopJadeGoldLayer();
    ~TopJadeGoldLayer();
    void onBuyJadeLayer();
    void onChangedJadeCount(CCObject *obj);
    void onChangedGoldCount(CCObject *obj);
    void onEnter();
    void close();
    
    // Touches
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void registerWithTouchDispatcher();
};

#endif /* defined(__NabuzaI__TopJadeGoldLayer__) */
