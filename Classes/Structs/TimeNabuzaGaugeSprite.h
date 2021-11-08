//
//  TimeNabuzaGaugeSprite.h
//  NabuzaI
//
//  Created by Lee Samgu on 5/22/13.
//
//

#ifndef __NabuzaI__TimeNabuzaGaugeSprite__
#define __NabuzaI__TimeNabuzaGaugeSprite__

#include "cocos2d.h"
USING_NS_CC;

class TimeNabuzaGaugeSprite : public cocos2d::CCSprite
{
public:
    bool addValueFromRollingCount(unsigned int rollingCoinCount);
    CREATE_FUNC(TimeNabuzaGaugeSprite);
    void initialize();
    void isNabuzaTime(bool yn);
private:
    TimeNabuzaGaugeSprite(void);
    bool init();
    void nabuzaTimeDoneCallback();
    void setValue(int v);
    int value;
    CCPoint originalPoint;
};

#endif /* defined(__NabuzaI__TimeNabuzaGaugeSprite__) */
