//
//  ItemInfoSprite.h
//  NabuzaI
//
//  Created by Lee Samgu on 6/11/13.
//
//

#ifndef __NabuzaI__ItemInfoSprite__
#define __NabuzaI__ItemInfoSprite__

#include "cocos2d.h"
USING_NS_CC;

class ItemInfoSprite : public cocos2d::CCSprite {
private:
    unsigned int itemKey;
    unsigned int playerLevel;
    bool init();
    ItemInfoSprite();

public:
    CREATE_FUNC(ItemInfoSprite);
    void setItemKeyWithLevel(unsigned int itemKey, unsigned int playerLevel);
    void setItemKey(unsigned int itemKey);
    void reset();
};

#endif /* defined(__NabuzaI__ItemInfoSprite__) */
