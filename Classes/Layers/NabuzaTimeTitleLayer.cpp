//
//  NabuzaTimeTitleLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 5/23/13.
//
//

#include "NabuzaTimeTitleLayer.h"

const int LAYER_TITLE_BALLOON = 70000;
const int LAYER_TITLE_COIN = 60000;

// on "init" you need to initialize your instance
bool NabuzaTimeTitleLayer::init() {
    //////////////////////////////
    // 1. super init first
    if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))  // RGBA
    {
        return false;
    }

    this->nabuzaTitleBalloon =
        CCSprite::create("play_titile_n_time.png", CCRect(0., 0., 162., 90.));
    this->nabuzaTitleCoin =
        CCSprite::create("n_coin.png", CCRect(0., 0., 210., 140.));

    this->addChild(this->nabuzaTitleCoin, LAYER_TITLE_COIN);
    this->addChild(this->nabuzaTitleBalloon, LAYER_TITLE_BALLOON);

    this->setVisible(false);

    return true;
}

void NabuzaTimeTitleLayer::setNabuzaTimeCount(unsigned int nabuzaTimeCount) {
    CCLog("NabuzaTitleCoin RetainCount : %i",
          this->nabuzaTitleCoin->retainCount());
    if (nabuzaTimeCount == 0) {
        this->setVisible(false);
        return;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    unsigned int nabuzaConstant =
        (nabuzaTimeCount < 45) ? nabuzaTimeCount + 1 : 45;

    float offsetX = ((nabuzaConstant - 2) % 4 == 0)
                        ? 0.
                        : 162. * ((nabuzaConstant - 2) % 4);
    float offsetY = floorf((nabuzaConstant - 2) / 4) * 90.;

    CCLog("offsetX, offsetY : %f, %f, %u, %u", offsetX, offsetY,
          nabuzaTimeCount, nabuzaConstant);

    // nabuzaTitleCoin 준비
    this->nabuzaTitleCoin->setPosition(ccp(visibleSize.width / 2., 800. + 90.));
    // nabuzaTitleBalloon 준비
    this->nabuzaTitleBalloon->setPosition(
        ccp(visibleSize.width / 2, visibleSize.height / 2));
    this->nabuzaTitleBalloon->setTextureRect(
        CCRect(offsetX, offsetY, 162., 90.));

    this->setVisible(true);

    //    this->nabuzaTitleCoin->runAction(CCSequence::create(
    //                                                        CCMoveBy::create(.5,
    //                                                        ccp(0., -164.))
    //                                                        ,CCJumpBy::create(.5,
    //                                                        ccp(0., 0.), 50.,
    //                                                        4) ,NULL
    //                                                        ));    // 800 - 72
    //                                                        : 최종 목적지 Y
    //                                                        좌표

    //    this->nabuzaTitleCoin->runAction(CCEaseBounceOut::create(
    //                                                          CCMoveBy::create(.5,
    //                                                          ccp(0., -164.))
    //                                                          ));
    this->nabuzaTitleCoin->runAction(
        CCEaseElasticOut::create(CCMoveBy::create(.5, ccp(0., -164.))));

    this->nabuzaTitleBalloon->runAction(CCSequence::create(
        CCScaleTo::create(.1, 2.), CCDelayTime::create(.15),
        CCSpawn::create(
            CCEaseIn::create(CCMoveBy::create(.1, ccp(-136., 0)), 1.5),
            CCEaseOut::create(CCMoveBy::create(.1, ccp(0., 331.)), 1.5),
            CCScaleTo::create(.1, 1.), NULL),
        NULL));  // 94, 54 : 최종 목적지 XY 죄표
}