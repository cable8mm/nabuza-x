//
//  GameLoadingLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 5/9/13.
//
//

#ifndef __NabuzaI__GameLoadingLayer__
#define __NabuzaI__GameLoadingLayer__

#include "cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum eGamePlayerLevels {
    kGAMEPLAYERLEVEL_BEGINNER,
    kGAMEPLAYERLEVEL_ADVANCED,
    kGAMEPLAYERLEVEL_EXPERT
};

class GameLoadingLayer : public cocos2d::CCLayerColor {
private:
    eGamePlayerLevels playerLevel;
    bool init();

public:
    static GameLoadingLayer *createWithLevel(eGamePlayerLevels level);
    void onEnter();
    void close();
    CREATE_FUNC(GameLoadingLayer);
};

// GameEnterLevelSprite Class
class GameEnterLevelSprite : public cocos2d::CCSprite {
private:
    std::string imageName;

public:
    static GameEnterLevelSprite *createWithLevel(eGamePlayerLevels level);
    void onAnimating();
};

// GameEnterLevelFaceSprite
class GameEnterLevelFaceSprite : public cocos2d::CCSprite {
private:
    std::string imageName;

public:
    static GameEnterLevelFaceSprite *createWithLevel(eGamePlayerLevels level);
    void onAnimating();
};
#endif /* defined(__NabuzaI__GameLoadingLayer__) */
