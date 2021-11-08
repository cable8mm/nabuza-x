//
//  LevelMoneySprite.h
//  NabuzaI
//
//  Created by Lee Samgu on 8/8/13.
//
//

#ifndef __NabuzaI__LevelMoneySprite__
#define __NabuzaI__LevelMoneySprite__

#include "cocos2d.h"
USING_NS_CC;

class LevelMoneySprite : public cocos2d::CCSprite
{
private:
    
public:
    static LevelMoneySprite* createWithGoldCount(unsigned int goldCount);
};


#endif /* defined(__NabuzaI__LevelMoneySprite__) */
