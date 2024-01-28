//
//  GameEventLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/3/13.
//
//

#ifndef __NabuzaI__GameEventLayer__
#define __NabuzaI__GameEventLayer__

#include "cocos2d.h"
using namespace cocos2d;

enum eGameEventResults {
    kGAMEEVENTRESULT_FAILURE = 3,
    kGAMEEVENTRESULT_FIRST = 0,
    kGAMEEVENTRESULT_SECOND = 1,
    kGAMEEVENTRESULT_THIRD = 2
};

class GameEventLayer : public cocos2d::CCLayerColor {
public:
    static GameEventLayer *createWithEventResult(eGameEventResults key);

private:
    eGameEventResults gameEventResult;

    CCSprite *playSpeechSprite;
    void onEnter();
    void close();
};

#endif /* defined(__NabuzaI__GameEventLayer__) */
