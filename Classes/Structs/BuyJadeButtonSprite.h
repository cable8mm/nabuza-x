//
//  BuyJadeButton.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/5/13.
//
//

#ifndef __NabuzaI__BuyJadeButtonSprite___
#define __NabuzaI__BuyJadeButtonSprite___

#include "cocos2d.h"
USING_NS_CC;

class BuyJadeButtonSprite : public cocos2d::CCSprite
{
private:
    unsigned int key;
    bool isActive;
public:
    static BuyJadeButtonSprite* createWithItemKey(unsigned int key);
    static BuyJadeButtonSprite* createWithItemKeyTapped(unsigned int key);
};

#endif /* defined(__NabuzaI__BuyJadeButtonSprite___) */
