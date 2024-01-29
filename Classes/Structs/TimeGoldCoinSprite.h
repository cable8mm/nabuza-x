//
//  TimeGoldCoinSprite.h
//  NabuzaI
//
//  Created by Lee Samgu on 5/15/13.
//
//

#ifndef __NabuzaI__TimeGoldCoinSprite__
#define __NabuzaI__TimeGoldCoinSprite__

#include "cocos2d.h"
USING_NS_CC;

class TimeGoldCoinSprite : public cocos2d::CCSprite {
private:
public:
    unsigned int mustTapCoinCount;
    static TimeGoldCoinSprite* createWithColor(unsigned int color);
    void move(float x, float y);
    void close();
};

#endif /* defined(__NabuzaI__TimeGoldCoinSprite__) */
