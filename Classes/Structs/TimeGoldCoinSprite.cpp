//
//  TimeGoldCoinSprite.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 5/15/13.
//
//

#include "TimeGoldCoinSprite.h"

TimeGoldCoinSprite* TimeGoldCoinSprite::createWithColor(unsigned int color) {
    TimeGoldCoinSprite *pobSprite = new TimeGoldCoinSprite;
    
    CCTexture2D *coinTexture  = CCTextureCache::sharedTextureCache()->textureForKey("coin_effect.png");
    CCRect offset = CCRectMake(66.*(5.+color), 0., 66., 66.);
    
//    156.*i, 0., 156., 156.
    if (pobSprite && pobSprite->initWithTexture(coinTexture, offset))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void TimeGoldCoinSprite::move(float x, float y) {
    float const TIME_GOLD_COIN_MOVING_TERM  = .3;
    float currentX  = this->getPositionX();
    float currentY  = this->getPositionY();
    this->setScale(.8);
    this->runAction(
                    CCSequence::create(
                                       CCSpawn::create(
                                                       CCEaseIn::create(CCMoveTo::create(TIME_GOLD_COIN_MOVING_TERM, ccp(currentX, y)), 2.)
                                                       ,CCEaseOut::create(CCMoveTo::create(TIME_GOLD_COIN_MOVING_TERM, ccp(x, currentY)), 2.)
                                                       ,CCScaleTo::create(TIME_GOLD_COIN_MOVING_TERM, 1.)
                                                       ,NULL
                                                       )
                                       ,CCCallFunc::create(this, callfunc_selector(TimeGoldCoinSprite::close))
                                       ,NULL));
}

void TimeGoldCoinSprite::close() {
    this->stopAllActions();
    this->removeFromParentAndCleanup(true);
}