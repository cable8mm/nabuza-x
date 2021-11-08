//
//  GameReadyStartLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 5/10/13.
//
//

#ifndef __NabuzaI__GameReadyStartLayer__
#define __NabuzaI__GameReadyStartLayer__
#include "cocos2d.h"
using namespace cocos2d;

class GameReadyStartLayer : public cocos2d::CCLayerColor
{
public:
    void onEnter();
    void close();
    void speechStart();
    CREATE_FUNC(GameReadyStartLayer);
    
private:
    CCSprite *playSpeechSprite;
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void registerWithTouchDispatcher();
};

#endif /* defined(__NabuzaI__GameReadyStartLayer__) */
