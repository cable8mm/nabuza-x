//
//  CoinSprite.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 4/24/13.
//
//

#include "CoinSprite.h"

CoinSprite::CoinSprite(void)
    : mustTapCoinCount(0),
      isRolling(false),
      isNabuzaTime(false),
      isValid(true) {
}

CoinSprite *CoinSprite::createWithNumber(unsigned int key,
                                         unsigned int coinNumber) {
    CoinSprite *pobSprite = new CoinSprite;
    pobSprite->number = coinNumber;
    pobSprite->key = key;

    CCTexture2D *coinTexture =
        CCTextureCache::sharedTextureCache()->textureForKey("coin_effect.png");

    CCTexture2D *coinEffectTexture =
        CCTextureCache::sharedTextureCache()->textureForKey(
            "coin_all_star_effect.png");
    pobSprite->effectSprite = CCSprite::createWithTexture(
        coinEffectTexture, CCRect(0., 0., 156., 156.));
    pobSprite->effectSprite->setVisible(false);
    pobSprite->isNabuzaTime = false;

    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        pobSprite, callfuncO_selector(CoinSprite::nabuzaTimeCallback),
        "NABUZA_TIME_NOTIFICATION", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        pobSprite, callfuncO_selector(CoinSprite::nabuzaTimeDoneCallback),
        "NABUZA_TIME_DONE_NOTIFICATION", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        pobSprite, callfuncO_selector(CoinSprite::nabuzaTimeFinishCallback),
        "NABUZA_TIME_FINISH_NOTIFICATION", NULL);

    if (pobSprite && pobSprite->initWithTexture(
                         coinTexture, CCRect(coinNumber * MATRIX_COIN_WH, 0.,
                                             MATRIX_COIN_WH, MATRIX_COIN_WH))) {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void CoinSprite::nabuzaTimeDoneCallback() {  // 회전 속도 2배
    this->setIsNabuzaTime(true);
}

void CoinSprite::nabuzaTimeFinishCallback() {
    this->setIsNabuzaTime(false);
}

void CoinSprite::nabuzaTimeCallback(CCObject *obj) {  // 회전 속도 2배
    if (isRolling == false || this->isNabuzaTime == true) {
        return;
    }

    this->stopAllActions();

    this->isNabuzaTime = true;

    int n;
    char animationCacheName[17];
    n = sprintf(animationCacheName, "coin_animation_%u", this->number);
    CCAnimation *rollingAnimation =
        CCAnimationCache::sharedAnimationCache()->animationByName(
            animationCacheName);
    CCAnimate *aniNabuzaTitleCoin = CCAnimate::create(rollingAnimation);

    CCRepeatForever *repeat = CCRepeatForever::create(aniNabuzaTitleCoin);
    CCSpeed *speed = CCSpeed::create(repeat, 2.);

    this->runAction(speed);

    this->effectSprite->stopAllActions();

    // CoinEffect started
    CCAnimation *coinEffectAnimation =
        CCAnimationCache::sharedAnimationCache()->animationByName(
            "coin_yellow_effect_animation");
    CCAnimate *aniCoinEffectAnimation = CCAnimate::create(coinEffectAnimation);

    CCRepeatForever *coinEffectRepeat =
        CCRepeatForever::create(aniCoinEffectAnimation);
    CCSpeed *coinEffectSpeed = CCSpeed::create(coinEffectRepeat, 2.);

    this->effectSprite->runAction(coinEffectSpeed);
}

void CoinSprite::activeNabuzaAction() {
    //    if (isRolling == false || this->isNabuzaTime == true) {
    if (isRolling == false) {
        return;
    }

    this->stopAllActions();

    this->isNabuzaTime = true;

    int n;
    char animationCacheName[17];
    n = sprintf(animationCacheName, "coin_animation_%u", this->number);
    CCAnimation *rollingAnimation =
        CCAnimationCache::sharedAnimationCache()->animationByName(
            animationCacheName);
    CCAnimate *aniNabuzaTitleCoin = CCAnimate::create(rollingAnimation);

    CCRepeatForever *repeat = CCRepeatForever::create(aniNabuzaTitleCoin);
    CCSpeed *speed = CCSpeed::create(repeat, 2.);

    this->runAction(speed);

    this->effectSprite->stopAllActions();

    // CoinEffect started
    CCAnimation *coinEffectAnimation =
        CCAnimationCache::sharedAnimationCache()->animationByName(
            "coin_yellow_effect_animation");
    CCAnimate *aniCoinEffectAnimation = CCAnimate::create(coinEffectAnimation);

    CCRepeatForever *coinEffectRepeat =
        CCRepeatForever::create(aniCoinEffectAnimation);
    CCSpeed *coinEffectSpeed = CCSpeed::create(coinEffectRepeat, 2.);

    this->effectSprite->runAction(coinEffectSpeed);
}

void CoinSprite::setIsNabuzaTime(bool isNabuzaTime, bool isAnimation) {
    if (this->isNabuzaTime == isNabuzaTime) {
        return;
    }

    this->isNabuzaTime = isNabuzaTime;

    CCRect rect = this->getTextureRect();

    if (isNabuzaTime == true) {
        this->setTextureRect(
            CCRect(rect.origin.x, 264., rect.size.width, rect.size.height));
        return;
    }

    this->setTextureRect(
        CCRect(rect.origin.x, 0., rect.size.width, rect.size.height));
}
void CoinSprite::setIsNabuzaTime(bool isNabuzaTime) {
    if (this->isNabuzaTime == isNabuzaTime || this->number > 4) {
        return;
    }

    this->isNabuzaTime = isNabuzaTime;

    if (isNabuzaTime == true) {
        this->isNabuzaTime = isNabuzaTime;
        int n;
        char animationCacheName[19];
        n = sprintf(animationCacheName, "nabuza_animation_%u", this->number);
        CCAnimation *coinNabuzaAnimation =
            CCAnimationCache::sharedAnimationCache()->animationByName(
                animationCacheName);
        this->runAction(CCSequence::create(
            CCAnimate::create(coinNabuzaAnimation),
            CCCallFunc::create(this,
                               callfunc_selector(CoinSprite::initializeFrame)),
            NULL));
        return;
    }

    int n;
    char animationCacheName[21];
    n = sprintf(animationCacheName, "unnabuza_animation_%u", this->number);
    CCAnimation *coinNabuzaAnimation =
        CCAnimationCache::sharedAnimationCache()->animationByName(
            animationCacheName);
    this->runAction(CCSequence::create(
        CCAnimate::create(coinNabuzaAnimation),
        CCCallFunc::create(this,
                           callfunc_selector(CoinSprite::initializeFrame)),
        NULL));
}

void CoinSprite::initializeFrame() {
    if (this->isNabuzaTime) {
        this->setTextureRect(CCRect(MATRIX_COIN_WH * this->number,
                                    MATRIX_COIN_WH * 4, MATRIX_COIN_WH,
                                    MATRIX_COIN_WH));
        return;
    }
    this->setTextureRect(CCRect(MATRIX_COIN_WH * this->number, 0.,
                                MATRIX_COIN_WH, MATRIX_COIN_WH));
    return;
}

void CoinSprite::setIsRolling(bool isRolling) {
    if (this->isRolling == isRolling) {
        return;
    }

    this->isRolling = isRolling;
    CCLog("CoinAnimationNumber : %u", this->number);
    if (isRolling == true) {
        int n;
        char animationCacheName[17];
        n = sprintf(animationCacheName, "coin_animation_%u", this->number);

        CCLog("Coin Animation %u", this->number);

        CCAnimation *rollingAnimation =
            CCAnimationCache::sharedAnimationCache()->animationByName(
                animationCacheName);
        CCAnimate *aniNabuzaTitleCoin = CCAnimate::create(rollingAnimation);

        CCRepeatForever *repeat = CCRepeatForever::create(aniNabuzaTitleCoin);
        CCSpeed *speed = CCSpeed::create(repeat, 2.);

        this->runAction(speed);

        // CoinEffect started
        CCAnimation *coinEffectAnimation =
            CCAnimationCache::sharedAnimationCache()->animationByName(
                "coin_white_effect_animation");
        CCAnimate *aniCoinEffectAnimation =
            CCAnimate::create(coinEffectAnimation);

        CCRepeatForever *coinEffectRepeat =
            CCRepeatForever::create(aniCoinEffectAnimation);
        CCSpeed *coinEffectSpeed = CCSpeed::create(coinEffectRepeat, 2.);

        this->effectSprite->runAction(coinEffectSpeed);
        this->effectSprite->setVisible(true);
    } else {
        this->stopAllActions();
        this->effectSprite->stopAllActions();
        this->initializeFrame();
        this->effectSprite->setVisible(false);
    }
}

void CoinSprite::animationDown() {
#define COIN_ANIMATION_HEIGHT 500
    CCPoint originalPosition = this->getPosition();
    this->setPosition(
        ccp(originalPosition.x, originalPosition.y + COIN_ANIMATION_HEIGHT));
    CCActionInterval *actionMove = CCMoveTo::create(0.1, originalPosition);
    CCEaseIn *actionEaseMove = CCEaseIn::create(actionMove, .5);

    this->runAction(actionEaseMove);
}

void CoinSprite::down() {
    CCPoint position = this->getPosition();

    if (false) {
        this->setPosition(ccp(position.x, position.y - MATRIX_CELL_WH));
        this->effectSprite->setPosition(
            ccp(position.x, position.y - MATRIX_CELL_WH));
    } else {
        CCActionInterval *actionMove =
            CCMoveTo::create(0.1, ccp(position.x, position.y - MATRIX_CELL_WH));
        CCEaseIn *actionEaseMove = CCEaseIn::create(actionMove, .2);
        this->runAction(CCSequence::create(
            actionEaseMove,
            CCCallFuncN::create(this, callfuncN_selector(CoinSprite::downDone)),
            NULL));
    }

    //    CCLog("CoinSprite Down Position %f, %f: ", position.x, position.y);

    this->key -= 7;
}

void CoinSprite::downDone(CCNode *sender) {
    this->effectSprite->setPosition(this->getPosition());
}

void CoinSprite::pang() {
    this->removeFromParentAndCleanup(true);
}

void CoinSprite::reset() {
    this->setTextureRect(CCRect(this->number * MATRIX_CELL_WH, 0.,
                                MATRIX_CELL_WH, MATRIX_CELL_WH));
    this->effectSprite->setTextureRect(CCRect(0., 0., 156., 156.));
}

void CoinSprite::beTimeGoldSprite(unsigned int goldKey) {
    this->number = 5 + goldKey;
    float const TIME_GOLD_COIN_MOVING_TERM = .3;
    // TIME_GOLD_COIN_MOVING_TERM 시간 후에 rect 교체
    this->runAction(CCSequence::create(
        CCDelayTime::create(TIME_GOLD_COIN_MOVING_TERM),
        CCCallFunc::create(this,
                           callfunc_selector(CoinSprite::changeTimeGoldSprite)),
        NULL));
}

void CoinSprite::changeTimeGoldSprite() {
    this->setTextureRect(CCRect(MATRIX_COIN_WH * (this->number), 0.,
                                MATRIX_COIN_WH, MATRIX_COIN_WH));

    unsigned int mustTapCoinCount = (unsigned int)rand() % 3;  // 0, 1, 2

    CCSprite *mustCoinCountSprite = CCSprite::create(
        "play_gold_x.png", CCRect(mustTapCoinCount * 15., 0., 15., 16.));
    CCPoint pos = mustCoinCountSprite->getPosition();
    mustCoinCountSprite->setPosition(ccp(pos.x + 56., pos.y + 16.));
    this->mustTapCoinCount = mustTapCoinCount + 2;
    this->addChild(mustCoinCountSprite);
}

CoinSprite::~CoinSprite() {
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}