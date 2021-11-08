//
//  SaleInvitationSprite.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 7/29/13.
//
//

#include "SaleInvitationSprite.h"

#define TEXTURE_SIZE_W 400.
#define TEXTURE_SIZE_H 80.

SaleInvitationSprite* SaleInvitationSprite::createWithItemKey(unsigned int key) {
    SaleInvitationSprite *pobSprite = new SaleInvitationSprite;
    pobSprite->key  = key;
    if (pobSprite && pobSprite->initWithFile("sale_btn_invitation.png", CCRect(0., key*TEXTURE_SIZE_H, TEXTURE_SIZE_W, TEXTURE_SIZE_H)))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

SaleInvitationSprite* SaleInvitationSprite::createWithItemKeyTapped(unsigned int key) {
    SaleInvitationSprite *pobSprite = new SaleInvitationSprite;
    pobSprite->key  = key;

    float offsetY   = key * TEXTURE_SIZE_H;
    
    pobSprite->setScale(1.1);
    pobSprite->setPosition(ccp(pobSprite->getPositionX()-20., pobSprite->getPositionY()-4.));   // 길이의 1/20
    
    if (pobSprite && pobSprite->initWithFile("sale_btn_invitation.png", CCRect(0., offsetY, TEXTURE_SIZE_W, TEXTURE_SIZE_H)))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}