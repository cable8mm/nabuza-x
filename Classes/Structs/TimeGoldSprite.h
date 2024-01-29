//
//  TimeGoldSprite.h
//  NabuzaI
//
//  Created by Lee Samgu on 5/8/13.
//
//

#ifndef __NabuzaI__TimeGoldSprite__
#define __NabuzaI__TimeGoldSprite__

#include "cocos2d.h"
USING_NS_CC;

class TimeGoldSprite : public cocos2d::CCSprite {
private:
    void nabuzaTimeDoneCallback();
    void nabuzaTimeFinishCallback();

public:
    TimeGoldSprite();
    static TimeGoldSprite* createWithCustom();
    void setAnimationType(unsigned int i);
    void animationTypeWhiteYellowCross();
    unsigned currentColor;
    void setIsNabuzaTime(bool yn);
    void startAnimation();

private:
    void toogleColor();
};

#endif /* defined(__NabuzaI__TimeGoldSprite__) */
