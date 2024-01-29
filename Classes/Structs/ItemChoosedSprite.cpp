//
//  ItemChoosedSprite.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 6/10/13.
//
//

#include "ItemChoosedSprite.h"

#define TEXTURE_SIZE_W 132.
#define TEXTURE_SIZE_H 85.

ItemChoosedSprite::ItemChoosedSprite(void) {
}

ItemChoosedSprite *ItemChoosedSprite::createWithKeys(int itemKey,
                                                     unsigned int positionKey) {
    ItemChoosedSprite *pobSprite = new ItemChoosedSprite;
    pobSprite->setPositionKey(positionKey);
    pobSprite->itemKey = itemKey;

    // 0,1,2,3은 필요한 비취 숫자 1이며, 4,5는 필요한 비취 숫자가 2임.
    if (itemKey < 4) {
        pobSprite->needJadeCount = 1;
    } else {
        pobSprite->needJadeCount = 2;
    }

    CCTexture2D *coinTexture =
        CCTextureCache::sharedTextureCache()->textureForKey("item_box_btn.png");
    CCRect offset =
        CCRect(itemKey * TEXTURE_SIZE_W, 0., TEXTURE_SIZE_W, TEXTURE_SIZE_H);

    if (pobSprite && pobSprite->initWithTexture(coinTexture, offset)) {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void ItemChoosedSprite::runAnimation() {
    this->runAction(CCRepeatForever::create(CCSequence::create(
        CCScaleTo::create(.2, 1.2), CCScaleTo::create(.2, 1.), NULL)));
}

void ItemChoosedSprite::setPositionKey(unsigned int key) {
    this->positionKey = key;
    // ccp(84.+78.*i, 561.5)
    //    (ccp(41.+135.*i + 64.5, 800. - (161. + 42.5)));
    this->setPosition(ccp(41. + 135. * key + 64.5, 800. - (161. + 42.5)));
}

unsigned int ItemChoosedSprite::getPositionKey() {
    return this->positionKey;
}

// void ItemChoosedSprite::setItemKey(int key) {
//     this->itemKey  = key;
//     this->setTextureRect(CCRect((key%3)*74., floorf(key/3)*75., 74., 75.));
// }

int ItemChoosedSprite::getItemKey() {
    return this->itemKey;
}

// void ItemChoosedSprite::setSelectedItem(unsigned int v) {
//     this->selectedItem  = v;
//
//     this->setTextureRect(CCRect((v%3)*74., floorf(v/3)*75., 74., 75.));
// }
//
// unsigned int ItemChoosedSprite::getSelectedItem() {
//     return this->selectedItem;
// }
