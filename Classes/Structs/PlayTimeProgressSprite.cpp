//
//  PlayTimeProgressSprite.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 5/10/13.
//
//

#include "PlayTimeProgressSprite.h"

PlayTimeProgressSprite *PlayTimeProgressSprite::createWithCustom(
    unsigned int duration) {
    CCSprite *playTimeSprite =
        CCSprite::create("play_timebar.png", CCRect(0., 0., 480., 32.));

    PlayTimeProgressSprite *pProgressTimerSprite = new PlayTimeProgressSprite();
    pProgressTimerSprite->duration = (float)duration;

    if (pProgressTimerSprite->initWithSprite(playTimeSprite)) {
        pProgressTimerSprite->setType(kCCProgressTimerTypeBar);
        pProgressTimerSprite->setMidpoint(ccp(0., .5));
        pProgressTimerSprite->setBarChangeRate(ccp(1., 0.));
        pProgressTimerSprite->setPercentage(100.);

        pProgressTimerSprite->autorelease();
    } else {
        delete pProgressTimerSprite;
        pProgressTimerSprite = NULL;
    }

    return pProgressTimerSprite;
}

void PlayTimeProgressSprite::start() {
    CCProgressFromTo *progressToZero =
        CCProgressFromTo::create(this->duration, 100., 0.);

    this->runAction(progressToZero);
}