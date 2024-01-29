//
//  TimeGoldGaugeSprite.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 5/8/13.
//
//

#include "TimeGoldGaugeSprite.h"

const float TIME_GOLD_GAUGE_COIN_WIDTH = 6;
const float TIME_GOLD_GAUGE_WIDTH = 151.;
const float TIME_GOLD_GAUGE_HEIGHT = 45.;
const unsigned int MAX_GAUGE_COUNT = 25;
const unsigned int MIN_GAUGE_COUNT = 0;

TimeGoldGaugeSprite::TimeGoldGaugeSprite(void)
    : value(0)
      //,tickPerSecond(2) // real
      ,
      tickPerSecond(1) {
}

TimeGoldGaugeSprite* TimeGoldGaugeSprite::createWithCustom() {
    TimeGoldGaugeSprite* pobSprite = new TimeGoldGaugeSprite;

    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        pobSprite,
        callfuncO_selector(TimeGoldGaugeSprite::nabuzaTimeDoneCallback),
        "NABUZA_TIME_DONE_NOTIFICATION", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        pobSprite,
        callfuncO_selector(TimeGoldGaugeSprite::nabuzaTimeFinishCallback),
        "NABUZA_TIME_FINISH_NOTIFICATION", NULL);

    if (pobSprite && pobSprite->initWithFile(
                         "coin_side_all.png",
                         CCRect(0., 0., TIME_GOLD_GAUGE_WIDTH,
                                TIME_GOLD_GAUGE_HEIGHT)))  // 코인 한개당 가로 6
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void TimeGoldGaugeSprite::onEnter() {
    this->setPositionX(this->getPositionX() - TIME_GOLD_GAUGE_WIDTH);
    this->originPosition = this->getPosition();
    CCSprite::onEnter();
}

void TimeGoldGaugeSprite::isNabuzaTime(bool yn) {
    if (yn == true) {
        this->pauseSchedulerAndActions();
        this->setVisible(false);
        return;
    }

    this->resumeSchedulerAndActions();
    this->setVisible(true);
}

void TimeGoldGaugeSprite::nabuzaTimeDoneCallback() {
}

void TimeGoldGaugeSprite::nabuzaTimeFinishCallback() {
}

void TimeGoldGaugeSprite::start() {  // 1초에 2개씩 줄어든다.
    float coinDelay = 1. / this->tickPerSecond;
    CCLog("Time Gold Gauge coinDelay : %f, tickerPerSecond : %u", coinDelay,
          this->tickPerSecond);
    this->runAction(CCRepeatForever::create(CCSequence::create(
        CCDelayTime::create(coinDelay),
        CCCallFunc::create(this, callfunc_selector(TimeGoldGaugeSprite::tick)),
        NULL)));
}

void TimeGoldGaugeSprite::tick() {
    if (this->value == 0) {
        return;
    }
    unsigned int value = this->value - 1;
    this->setValue(value);
}

void TimeGoldGaugeSprite::addValue(unsigned int v) {
    unsigned int changed = this->value + v;
    if (changed > MAX_GAUGE_COUNT || changed == MAX_GAUGE_COUNT) {
        // 복주머니 처리하고 0으로...
        CCNotificationCenter::sharedNotificationCenter()->postNotification(
            "TIME_GOLD_GAUGE_MAX_NOTIFICATION");

        this->setValue(0);
    } else {
        this->setValue(changed);
    }
}

void TimeGoldGaugeSprite::minusValue(unsigned int v) {
    unsigned int changed;

    if (this->value < v) {
        changed = 0;
    } else {
        changed = this->value - v;
    }
    this->setValue(changed);
}

void TimeGoldGaugeSprite::setValue(unsigned int v) {
    float xOffset = TIME_GOLD_GAUGE_COIN_WIDTH * v;
    //    float xOffset    = TIME_GOLD_GAUGE_WIDTH - TIME_GOLD_GAUGE_COIN_WIDTH
    //    * v; this->setTextureRect(CCRect(xOffset, 0., TIME_GOLD_GAUGE_WIDTH,
    //    TIME_GOLD_GAUGE_HEIGHT));
    this->setPositionX(this->originPosition.x + xOffset);
    this->value = v;
}

void TimeGoldGaugeSprite::changeRemovingCoinCount(unsigned int v) {
    this->tickPerSecond = v;
}