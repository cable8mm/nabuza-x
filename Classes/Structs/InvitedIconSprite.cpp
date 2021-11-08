//
//  InvitedIconSprite.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 7/29/13.
//
//

#include "InvitedIconSprite.h"

#define TEXTURE_SIZE_W 60.
#define TEXTURE_SIZE_H 60.

InvitedIconSprite* InvitedIconSprite::create() {
    InvitedIconSprite *pobSprite = new InvitedIconSprite;

    if (pobSprite && pobSprite->initWithFile("letter_box.png", CCRect(0., 0., TEXTURE_SIZE_W, TEXTURE_SIZE_H)))
    {
        pobSprite->setStat(kINVITEDICONSTATE_UNSENT);
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

InvitedIconSprite* InvitedIconSprite::create(eInvitedIconStats stat) {
    InvitedIconSprite *pobSprite = new InvitedIconSprite;
    if (pobSprite && pobSprite->initWithFile("letter_box.png", CCRect(0., 0., TEXTURE_SIZE_W, TEXTURE_SIZE_H)))
    {
        pobSprite->setStat(stat);
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void InvitedIconSprite::onEnter() {
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    this->setPosition(ccp(visibleSize.width / 2, 800.-138.-25.));
    CCSprite::onEnter();
}

void InvitedIconSprite::setStat(eInvitedIconStats v) {
    if (this->stat == v) {
        return;
    }
    
    this->stat  = v;
    if (this->stat == kINVITEDICONSTATE_SENT) {
        this->setTextureRect(CCRect(TEXTURE_SIZE_W, 0., TEXTURE_SIZE_W, TEXTURE_SIZE_H));
    }
}