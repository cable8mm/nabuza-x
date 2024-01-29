//
//  TimeGoldGaugeSprite.h
//  NabuzaI
//
//  Created by Lee Samgu on 5/8/13.
//
//

#ifndef __NabuzaI__TimeGoldGaugeSprite__
#define __NabuzaI__TimeGoldGaugeSprite__

#include "cocos2d.h"
USING_NS_CC;

class TimeGoldGaugeSprite : public cocos2d::CCSprite {
public:
    TimeGoldGaugeSprite();
    static TimeGoldGaugeSprite* createWithCustom();
    void start();
    void changeRemovingCoinCount(unsigned int v);
    void addValue(unsigned int v);
    void minusValue(unsigned int v);
    void isNabuzaTime(bool yn);

private:
    CCPoint originPosition;
    unsigned int value;
    unsigned int tickPerSecond;
    void onEnter();
    void tick();
    void setValue(unsigned int v);
    void nabuzaTimeDoneCallback();
    void nabuzaTimeFinishCallback();
};

#endif /* defined(__NabuzaI__TimeGoldGaugeSprite__) */
