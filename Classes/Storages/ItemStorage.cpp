//
//  ItemStorage.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 6/12/13.
//
//

#include "ItemStorage.h"

const char *USER_DEFAULT_ITEMS_KEY    = "ITEM_STORAGES";

ItemStorage* ItemStorage::create()
{
    ItemStorage* pItemStorage = new ItemStorage();
    
    if (pItemStorage && pItemStorage->init())
    {
        pItemStorage->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pItemStorage);
    }
    
    return pItemStorage;
}

void ItemStorage::reset() {
    this->userDefault->setIntegerForKey(USER_DEFAULT_ITEMS_KEY, 0);
}

bool ItemStorage::init()
{
    this->userDefault   = CCUserDefault::sharedUserDefault();
    return true;
}

void ItemStorage::addItem(int itemKey) {
    // itemKey는 0부터 6까지 있다. 이 것들의 배열을 스트링으로 넣기 위해서 1을 더한다. 
    int itemStorages    = this->userDefault->getIntegerForKey(USER_DEFAULT_ITEMS_KEY, 0);
    
    if (itemStorages > 9999) {  // 아이템은 5개 까지.
        return;
    }
    
    itemStorages    = itemStorages * 10 + itemKey + 1;
    CCLog("ItemKey : %i, Item %i", itemKey, itemStorages);
    this->userDefault->setIntegerForKey(USER_DEFAULT_ITEMS_KEY, itemStorages);
}

CCArray* ItemStorage::getItems() {
    CCArray *items   = new CCArray;
    unsigned int itemStorages    = this->userDefault->getIntegerForKey(USER_DEFAULT_ITEMS_KEY);
    
    if (itemStorages == 0) {
        return items;
    }
    
    while (itemStorages != 0) {
        float fItemStorages = (float)itemStorages;
        int itemKey = itemStorages % 10 - 1;
        
        items->addObject(CCInteger::create(itemKey));
        
        fItemStorages    = floorf(fItemStorages/10);
        itemStorages    = (int)fItemStorages;
    }
    
    return items;
}

void ItemStorage::flush() {
    this->userDefault->flush();
}

void ItemStorage::purgeItemStorage() {
    this->userDefault->purgeSharedUserDefault();
}