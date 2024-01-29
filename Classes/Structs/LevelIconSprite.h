//
//  LevelIconSprite.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/2/13.
//
//

#ifndef __NabuzaI__LevelIconSprite__
#define __NabuzaI__LevelIconSprite__

#include "cocos2d.h"
USING_NS_CC;

class LevelIconSprite : public cocos2d::CCSprite {
private:
public:
    static LevelIconSprite* createWithItemKey(unsigned int key);
    static LevelIconSprite* createWithGoldCount(unsigned int goldCount);
};

#endif /* defined(__NabuzaI__LevelIconSprite__) */
