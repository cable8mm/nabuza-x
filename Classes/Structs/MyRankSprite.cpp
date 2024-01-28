//
//  MyRankSprite.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 7/25/13.
//
//

#include "MyRankSprite.h"

#define TEXTURE_SIZE_W 70.
#define TEXTURE_SIZE_H 60.

MyRankSprite *MyRankSprite::create() {
    MyRankSprite *pobSprite = new MyRankSprite;
    pobSprite->setVisible(false);
    if (pobSprite &&
        pobSprite->initWithFile(
            "t_me.png", CCRect(0., 0., TEXTURE_SIZE_W, TEXTURE_SIZE_H))) {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void MyRankSprite::startAnimation() {
    CCAnimation *myRankAnimation =
        CCAnimationCache::sharedAnimationCache()->animationByName(
            "my_rank_animation");
    CCAnimate *myRankAnimate = CCAnimate::create(myRankAnimation);

    this->runAction(CCRepeatForever::create(myRankAnimate));
}

void MyRankSprite::onEnter() {
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    this->setPosition(ccp(visibleSize.width / 2, 800.-138.-25.));
    CCSprite::onEnter();
}
