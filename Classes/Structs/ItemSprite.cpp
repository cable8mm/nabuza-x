//
//  ItemSprite.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 6/10/13.
//
//

#include "ItemSprite.h"

#define TEXTURE_SIZE_W 132.
#define TEXTURE_SIZE_H 88.

ItemSprite* ItemSprite::createWithItemKey(unsigned int key) {
    CCAssert(key >= 0 && 6 > key, "range of itemSprite key is not valid");
    ItemSprite* pobSprite = new ItemSprite;

    pobSprite->key = key;
    pobSprite->isActive = true;

    switch (key) {
        case 0:
        case 1:
        case 2:
            pobSprite->needJadeCount = 1;
            break;
        case 3:
        case 4:
        case 5:
            pobSprite->needJadeCount = 2;
            break;
    }

    float itemChoiceRectX;
    float itemChoiceRectY;

    itemChoiceRectX = TEXTURE_SIZE_W * 2 * key + TEXTURE_SIZE_W;
    itemChoiceRectY = 0.;

    if (pobSprite &&
        pobSprite->initWithFile("item_choice_btn.png",
                                CCRect(itemChoiceRectX, itemChoiceRectY,
                                       TEXTURE_SIZE_W, TEXTURE_SIZE_H))) {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void ItemSprite::setIsActive(bool isActive) {
    if (this->isActive == isActive) {
        return;
    }
    this->isActive = isActive;

    CCRect itemButtonRect = this->getTextureRect();
    itemButtonRect.origin.x = (this->isActive == true)
                                  ? itemButtonRect.origin.x + TEXTURE_SIZE_W
                                  : itemButtonRect.origin.x - TEXTURE_SIZE_W;
    this->setTextureRect(itemButtonRect);
}

bool ItemSprite::getIsActive() {
    return this->isActive;
}

unsigned int ItemSprite::getKey() {
    return this->key;
}

unsigned int ItemSprite::getNeedJadeCount() {
    return this->needJadeCount;
}