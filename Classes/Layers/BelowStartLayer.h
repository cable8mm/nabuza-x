//
//  BelowStartLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 8/22/13.
//
//

#ifndef __NabuzaI__BelowStartLayer__
#define __NabuzaI__BelowStartLayer__

#include "cocos-ext.h"
#include "cocos2d.h"
USING_NS_CC;
USING_NS_CC_EXT;

class BelowStartLayer : public cocos2d::CCLayerColor {
public:
    CREATE_FUNC(BelowStartLayer);
    static BelowStartLayer *createWithIsStartGame(bool v);
    bool isGameStart;
    BelowStartLayer();

private:
    CCSprite *touchedSprite;
    void onEnter();
    void close();
    void onStartGame();
    void replaceGameScene();
    // Touches
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void registerWithTouchDispatcher();
};

#endif /* defined(__NabuzaI__BelowStartLayer__) */
