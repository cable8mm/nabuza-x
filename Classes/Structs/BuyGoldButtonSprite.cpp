//
//  BuyGoldButtonSprite.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 8/14/13.
//
//

#include "BuyGoldButtonSprite.h"

#define TEXTURE_SIZE_W 400.
#define TEXTURE_SIZE_H 80.

BuyGoldButtonSprite* BuyGoldButtonSprite::createWithItemKey(unsigned int key) {
    BuyGoldButtonSprite* pobSprite = new BuyGoldButtonSprite;

    float offsetY = key * TEXTURE_SIZE_H;

    if (pobSprite && pobSprite->initWithFile(
                         "sale_btn_gold.png",
                         CCRect(0., offsetY, TEXTURE_SIZE_W, TEXTURE_SIZE_H))) {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

BuyGoldButtonSprite* BuyGoldButtonSprite::createWithItemKeyTapped(
    unsigned int key) {
    BuyGoldButtonSprite* pobSprite = new BuyGoldButtonSprite;

    float offsetY = key * TEXTURE_SIZE_H;

    pobSprite->setScale(1.1);
    pobSprite->setPosition(ccp(pobSprite->getPositionX() - 20.,
                               pobSprite->getPositionY() - 4.));  // 길이의 1/20

    if (pobSprite && pobSprite->initWithFile(
                         "sale_btn_gold.png",
                         CCRect(0., offsetY, TEXTURE_SIZE_W, TEXTURE_SIZE_H))) {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}