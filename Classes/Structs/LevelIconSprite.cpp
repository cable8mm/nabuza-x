//
//  LevelIconSprite.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 7/2/13.
//
//

#include "LevelIconSprite.h"

#define TEXTURE_SIZE_W 110.
#define TEXTURE_SIZE_H 58.

LevelIconSprite* LevelIconSprite::createWithItemKey(unsigned int key) {
    LevelIconSprite* pobSprite = new LevelIconSprite;

    if (pobSprite &&
        pobSprite->initWithFile(
            "level_icon.png",
            CCRect(key * TEXTURE_SIZE_W, 0., TEXTURE_SIZE_W, TEXTURE_SIZE_H))) {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

LevelIconSprite* LevelIconSprite::createWithGoldCount(unsigned int goldCount) {
    LevelIconSprite* pobSprite = new LevelIconSprite;
    unsigned int level;

    unsigned int basicGoldCounts[] = {
        0,       100,     500,     1000,    2000,     3000,    4000,    6000,
        8000,    10000,   15000,   20000,   25000,    35000,   45000,   55000,
        80000,   105000,  130000,  160000,  190000,   220000,  300000,  350000,
        400000,  500000,  600000,  700000,  900000,   1100000, 1300000, 2000000,
        2500000, 3000000, 4000000, 5000000, 999999999};

    if (goldCount == 0) {
        level = 0;
    } else if (goldCount > 5000000) {
        level = 35;
    } else {
        for (unsigned int i = 0;
             i < sizeof(basicGoldCounts) / sizeof(basicGoldCounts[0]) - 1;
             i++) {
            if (basicGoldCounts[i] < goldCount &&
                goldCount <= basicGoldCounts[i + 1]) {
                level = i + 1;
                break;
            }
        }
    }

    if (pobSprite &&
        pobSprite->initWithFile(
            "level_icon.png", CCRect(level * TEXTURE_SIZE_W, 0., TEXTURE_SIZE_W,
                                     TEXTURE_SIZE_H))) {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}