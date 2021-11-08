//
//  TimeNabuzaGaugeSprite.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 5/22/13.
//
//

#include "TimeNabuzaGaugeSprite.h"

float const SIZE_WIDTH  = 155.;
float const SIZE_HEIGHT = 44.;

TimeNabuzaGaugeSprite::TimeNabuzaGaugeSprite(void)
:value(25) {}

// on "init" you need to initialize your instance
bool TimeNabuzaGaugeSprite::init()
{
    
    //////////////////////////////
    // 1. super init first
    CCTexture2D *texture    = CCTextureCache::sharedTextureCache()->textureForKey("play_n_time_rainbow.png");
    if( !TimeNabuzaGaugeSprite::initWithTexture(texture, CCRect(0., 0., SIZE_WIDTH, SIZE_HEIGHT)))
    {
        return false;
    }
    
    this->setVisible(false);
    
    this->originalPoint   = ccp(62.+78., 800.-127.-22.);

    this->runAction(CCRepeatForever::create(
                                            CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("time_nabuza_gauge_animation"))
                                            ));
    
    return true;
}

void TimeNabuzaGaugeSprite::nabuzaTimeDoneCallback() {
    this->setVisible(true);
    this->value = 25;
    CCLog("TimeGoldSprite NOTIFICATION");
}

void TimeNabuzaGaugeSprite::initialize() {
    this->setValue(25);
}

void TimeNabuzaGaugeSprite::isNabuzaTime(bool yn) {
    if (yn == true) {
        this->setValue(25);
        this->resumeSchedulerAndActions();
        this->setVisible(true);
        return;
    }
    
    this->pauseSchedulerAndActions();
    this->setVisible(false);
}

// true : 나부자 끝 false : 나부자 유지
bool TimeNabuzaGaugeSprite::addValueFromRollingCount(unsigned int rollingCoinCount) {
    if (rollingCoinCount > 9) {
        return false;
    }
    int changed   = -1*(10-rollingCoinCount);
    
    if (this->value + changed < 0) {
        changed = -1 * this->value;
    }

    if (this->value+changed < 1) {
        return true;
    }
    
    this->setValue(this->value+changed);
    return false;
}

void TimeNabuzaGaugeSprite::setValue(int v) {
    float changed   = (this->value - v)*(-6.2);
    this->value = v;
    if (v == 25) {
        this->setPosition(this->originalPoint);
        return;
    }
    this->runAction(CCMoveBy::create(.2, ccp(changed, 0.)));
}