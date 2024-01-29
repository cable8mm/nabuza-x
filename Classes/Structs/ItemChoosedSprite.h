//
//  ItemChoosedSprite.h
//  NabuzaI
//
//  Created by Lee Samgu on 6/10/13.
//
//

#ifndef __NabuzaI__ItemChoosedSprite__
#define __NabuzaI__ItemChoosedSprite__

#include "cocos2d.h"
USING_NS_CC;

class ItemChoosedSprite : public cocos2d::CCSprite {
private:
    ItemChoosedSprite();
    int itemKey;
    unsigned int positionKey;

public:
    unsigned int needJadeCount;
    static ItemChoosedSprite* createWithKeys(int itemKey,
                                             unsigned int positionKey);

    // Getters / Setters
    //    void setItemKey(int key);
    int getItemKey();
    void setPositionKey(unsigned int key);
    unsigned int getPositionKey();
    void runAnimation();
};

#endif /* defined(__NabuzaI__ItemChoosedSprite__) */
