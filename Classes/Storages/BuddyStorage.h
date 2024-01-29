//
//  BuddyStorage.h
//  NabuzaI
//
//  Created by Lee Samgu on 8/19/13.
//
//

#ifndef __NabuzaI__BuddyStorage__
#define __NabuzaI__BuddyStorage__

#include "cocos-ext.h"
#include "cocos2d.h"
USING_NS_CC;
USING_NS_CC_EXT;

#include "BuddyModel.h"

class BuddyStorage : public CCObject {
private:
    bool init();

public:
    CCArray* buddies;

    BuddyStorage();
    ~BuddyStorage();
    static BuddyStorage* sharedBuddyStorage(void);
};

#endif /* defined(__NabuzaI__BuddyStorage__) */
