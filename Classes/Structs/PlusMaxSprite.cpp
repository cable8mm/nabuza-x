//
//  PlusMaxSprite.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 7/29/13.
//
//

#include "PlusMaxSprite.h"

#define TEXTURE_SIZE_W 50.
#define TEXTURE_SIZE_H 50.

PlusMaxSprite* PlusMaxSprite::create() {
    PlusMaxSprite* pobSprite = new PlusMaxSprite;

    if (pobSprite && pobSprite->initWithFile(
                         "letter_mini_btn.png",
                         CCRect(0., 0., TEXTURE_SIZE_W, TEXTURE_SIZE_H))) {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}
