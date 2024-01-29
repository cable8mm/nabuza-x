//
//  LastChanceLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 6/28/13.
//
//

#ifndef __NabuzaI__LastChanceLayer__
#define __NabuzaI__LastChanceLayer__

#include "cocos2d.h"
using namespace cocos2d;

class LastChanceLayer : public cocos2d::CCLayerColor {
public:
    CREATE_FUNC(LastChanceLayer);

private:
    CCSprite *playSpeechSprite;
    bool init();
    void onEnter();
    void speechStart();
    void close();
};

#endif /* defined(__NabuzaI__LastChanceLayer__) */
