//
//  LetterBigSprite.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 8/20/13.
//
//

#include "LetterBigSprite.h"

#define TEXTURE_SIZE_W 210.
#define TEXTURE_SIZE_H 332.

LetterBigSprite *LetterBigSprite::createWithPosition(CCPoint pt,
                                                     SEL_CallFunc selector) {
    LetterBigSprite *pobSprite = new LetterBigSprite;
    pobSprite->setPosition(pt);
    pobSprite->selector = selector;
    pobSprite->setScale(.21);

    if (pobSprite &&
        pobSprite->initWithFile(
            "letter_big.png", CCRect(0, 0., TEXTURE_SIZE_W, TEXTURE_SIZE_H))) {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void LetterBigSprite::runAnimation() {
    CCTexture2D *texture =
        CCTextureCache::sharedTextureCache()->addImage("letter_big.png");
    CCArray *frames = new CCArray;
    for (unsigned int i = 0; i < 10; i++) {
        CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(
            texture,
            CCRect(TEXTURE_SIZE_W * (i % 4), TEXTURE_SIZE_H * floorf(i / 4),
                   TEXTURE_SIZE_W, TEXTURE_SIZE_H));
        frames->addObject(frame);
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, .2);
    CCAnimate *animate = CCAnimate::create(animation);

    this->runAction(CCSequence::create(
        CCSpawn::create(
            CCEaseOut::create(
                CCMoveTo::create(1., ccp(240., this->getPositionY())), .5),
            CCEaseIn::create(
                CCMoveTo::create(1., ccp(this->getPositionX(), 400.)), .5),
            CCEaseIn::create(CCScaleTo::create(1., 1.), .2), NULL),
        animate, CCCallFunc::create(this, this->selector), NULL));
}