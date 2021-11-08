//
//  ItemInfoSprite.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 6/11/13.
//
//

#include "ItemInfoSprite.h"

#define TEXTURE_SIZE_W  362.
#define TEXTURE_SIZE_H  94.

ItemInfoSprite::ItemInfoSprite(void)
:itemKey(0)
,playerLevel(0){
}

// on "init" you need to initialize your instance
bool ItemInfoSprite::init()
{
    //////////////////////////////
    // 1. super init first
    if( !ItemInfoSprite::initWithFile("item_info.png", CCRect(0., 0.,TEXTURE_SIZE_W, TEXTURE_SIZE_H)))
    {
        return false;
    }
    
    return true;
}

void ItemInfoSprite::setItemKeyWithLevel(unsigned int itemKey, unsigned int playerLevel) {
    this->itemKey   = itemKey;
    
    float offsetY   = (itemKey+1) * TEXTURE_SIZE_H;
    
//    if (this->itemKey == 5) {
//        offsetY = (itemKey+playerLevel+1) * 137.;
//    } else if (this->itemKey == 6) {
//        offsetY = (itemKey+3) * 137.;
//    } else {
//        offsetY = (itemKey+1) * 137.;
//    }
    
    CCRect itemInfoRect   = this->getTextureRect();
    itemInfoRect.origin.y   = offsetY;
    this->setTextureRect(itemInfoRect);
}

void ItemInfoSprite::setItemKey(unsigned int itemKey) {
    this->setItemKeyWithLevel(itemKey, 0);
}

void ItemInfoSprite::reset() {
    this->setTextureRect(CCRectMake(0., 0., TEXTURE_SIZE_W, TEXTURE_SIZE_H));
}