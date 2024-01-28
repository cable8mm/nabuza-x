//
//  TimeGoldSprite.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 5/8/13.
//
//

#include "TimeGoldSprite.h"

TimeGoldSprite::TimeGoldSprite(void) : currentColor(0) {
}

TimeGoldSprite *TimeGoldSprite::createWithCustom() {
    TimeGoldSprite *pobSprite = new TimeGoldSprite;
    if (pobSprite &&
        pobSprite->initWithFile("time_gold.png", CCRect(0., 0., 62., 61.))) {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void TimeGoldSprite::startAnimation() {
    CCAnimation *timeGoldWhiteEffectAnimation =
        CCAnimationCache::sharedAnimationCache()->animationByName(
            "time_gold_white_effect_animation");
    CCAnimate *timeGoldWhiteEffectAnimate =
        CCAnimate::create(timeGoldWhiteEffectAnimation);
    CCAnimation *timeGoldYellowEffectAnimation =
        CCAnimationCache::sharedAnimationCache()->animationByName(
            "time_gold_yellow_effect_animation");
    CCAnimate *timeGoldYellowEffectAnimate =
        CCAnimate::create(timeGoldYellowEffectAnimation);

    this->runAction(CCRepeatForever::create(CCSequence::create(
        timeGoldYellowEffectAnimate,
        CCCallFunc::create(this,
                           callfunc_selector(TimeGoldSprite::toogleColor)),
        timeGoldWhiteEffectAnimate,
        CCCallFunc::create(this,
                           callfunc_selector(TimeGoldSprite::toogleColor)),
        NULL)));
}

void TimeGoldSprite::nabuzaTimeDoneCallback() {
    CCLog("TimeGoldSprite NOTIFICATION");
    this->pauseSchedulerAndActions();
    this->setTextureRect(CCRect(124., 0., 62., 61.));
    this->stopAllActions();
    CCLog("TimeGoldSprite NOTIFICATION END");
}

void TimeGoldSprite::nabuzaTimeFinishCallback() {
    this->resumeSchedulerAndActions();
}

void TimeGoldSprite::setIsNabuzaTime(bool yn) {
    if (yn == false) {
        this->resumeSchedulerAndActions();
        return;
    }

    this->pauseSchedulerAndActions();
    this->setTextureRect(CCRect(124., 0., 62., 61.));
}

void TimeGoldSprite::animationTypeWhiteYellowCross() {
}

void TimeGoldSprite::toogleColor() {
    if (this->currentColor == 0) {
        this->currentColor = 1;
        return;
    }
    this->currentColor = 0;
    return;
}