//
//  ItemSprite.h
//  NabuzaI
//
//  Created by Lee Samgu on 6/10/13.
//
//

#ifndef __NabuzaI__ItemSprite__
#define __NabuzaI__ItemSprite__

#include "cocos2d.h"
USING_NS_CC;

class ItemSprite : public cocos2d::CCSprite {
private:
    unsigned int key;
    bool isActive;
    unsigned int needJadeCount;

public:
    static ItemSprite* createWithItemKey(unsigned int key);
    void setIsActive(bool isActive);
    bool getIsActive();
    unsigned int getKey();
    unsigned int getNeedJadeCount();
};

#endif /* defined(__NabuzaI__ItemSprite__) */
