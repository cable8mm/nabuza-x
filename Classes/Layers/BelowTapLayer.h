//
//  BelowTapLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 8/14/13.
//
//

#ifndef __NabuzaI__BelowTapLayer__
#define __NabuzaI__BelowTapLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class BelowTapLayer : public cocos2d::CCLayerColor
{
public:
    CREATE_FUNC(BelowTapLayer);
    static BelowTapLayer *createWithIsStartGame(bool v);
    bool isGameStart;
    BelowTapLayer();
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

#endif /* defined(__NabuzaI__BelowTapLayer__) */
