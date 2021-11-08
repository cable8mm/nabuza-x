//
//  BuddyStorage.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 8/19/13.
//
//

#include "BuddyStorage.h"

static BuddyStorage *s_SharedBuddyStorage = NULL;

BuddyStorage::BuddyStorage() {
    this->buddies   = new CCArray;
}

BuddyStorage::~BuddyStorage() {
    delete(this->buddies);
}

BuddyStorage* BuddyStorage::sharedBuddyStorage(void)
{
    if (!s_SharedBuddyStorage)
    {
        s_SharedBuddyStorage = new BuddyStorage();
        s_SharedBuddyStorage->init();
    }
    
    return s_SharedBuddyStorage;
}

bool BuddyStorage::init()
{
    return true;
}
