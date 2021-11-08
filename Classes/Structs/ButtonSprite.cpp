//
//  ButtonSprite.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 7/2/13.
//
//

#include "ButtonSprite.h"

#define TEXTURE_SIZE_W 215.
#define TEXTURE_SIZE_H 58.

ButtonSprite* ButtonSprite::createWithItemKey(eGameButtons key) {
    ButtonSprite *pobSprite = new ButtonSprite;
    
    float offsetX   = key % 2 * TEXTURE_SIZE_W;
    float offsetY   = floorf(key/2) * TEXTURE_SIZE_H;
    
    if (pobSprite && pobSprite->initWithFile("alert_view_btn.png", CCRect(offsetX, offsetY, TEXTURE_SIZE_W, TEXTURE_SIZE_H)))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}