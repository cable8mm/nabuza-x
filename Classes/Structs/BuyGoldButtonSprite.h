//
//  BuyGoldButtonSprite.h
//  NabuzaI
//
//  Created by Lee Samgu on 8/14/13.
//
//

#ifndef __NabuzaI__BuyGoldButtonSprite__
#define __NabuzaI__BuyGoldButtonSprite__

#include "cocos2d.h"
USING_NS_CC;

class BuyGoldButtonSprite : public cocos2d::CCSprite
{
private:
    unsigned int key;
    bool isActive;
public:
    static BuyGoldButtonSprite* createWithItemKey(unsigned int key);
    static BuyGoldButtonSprite* createWithItemKeyTapped(unsigned int key);
};

#endif /* defined(__NabuzaI__BuyGoldButtonSprite__) */
