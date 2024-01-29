//
//  PlayTimeProgressSprite.h
//  NabuzaI
//
//  Created by Lee Samgu on 5/10/13.
//
//

#ifndef __NabuzaI__PlayTimeProgressSprite__
#define __NabuzaI__PlayTimeProgressSprite__

#include "cocos2d.h"
USING_NS_CC;

class PlayTimeProgressSprite : public cocos2d::CCProgressTimer {
public:
    static PlayTimeProgressSprite* createWithCustom(unsigned int duration);
    void start();

private:
    float duration;
};

#endif /* defined(__NabuzaI__PlayTimeProgressSprite__) */
