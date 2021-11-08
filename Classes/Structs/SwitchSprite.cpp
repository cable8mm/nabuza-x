//
//  SwitchSprite.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 7/3/13.
//
//

#include "SwitchSprite.h"

#define TEXTURE_SIZE_W 130.
#define TEXTURE_SIZE_H 60.

SwitchSprite* SwitchSprite::createWithValue(bool v) {
    SwitchSprite *pobSprite = new SwitchSprite;
    
    pobSprite->v = v;
    
    float offsetY   = floorf(v/2) * TEXTURE_SIZE_H;
    
    if (pobSprite && pobSprite->initWithFile("set_switch.png", CCRect(0., offsetY, TEXTURE_SIZE_W, TEXTURE_SIZE_H)))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

bool SwitchSprite::getValue() {
    return this->v;
}

void SwitchSprite::setV(bool v) {
    if (this->v == v) {
        return;
    }
    
    this->v = v;
    
    float offsetY   = v == true? 0. : TEXTURE_SIZE_H;
    
    this->setTextureRect(CCRect(0., offsetY, TEXTURE_SIZE_W, TEXTURE_SIZE_H));
}

void SwitchSprite::toggle() {
    if (this->v) {
        this->setV(false);
        return;
    }
    
    this->setV(true);
}