//
//  AlertTitleSprite.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 7/2/13.
//
//

#include "AlertTitleSprite.h"

#define TEXTURE_SIZE_W 400.
#define TEXTURE_SIZE_H 50.

AlertTitleSprite* AlertTitleSprite::createWithItemKey(eGameAlertTitles key) {
    AlertTitleSprite* pobSprite = new AlertTitleSprite;

    if (pobSprite &&
        pobSprite->initWithFile(
            "title_alert_text.png",
            CCRect(0., TEXTURE_SIZE_H * key, TEXTURE_SIZE_W, TEXTURE_SIZE_H))) {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void AlertTitleSprite::onEnter() {
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    this->setPosition(ccp(visibleSize.width / 2, 800. - 138. - 25.));
    CCSprite::onEnter();
}