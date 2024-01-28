//
//  TouchScoreSprite.h
//  NabuzaI
//
//  Created by Lee Samgu on 5/8/13.
//
//

#ifndef __NabuzaI__TouchScoreSprite__
#define __NabuzaI__TouchScoreSprite__

#include "cocos2d.h"
USING_NS_CC;

class TouchScoreSprite : public cocos2d::CCLabelBMFont {
public:
    static TouchScoreSprite* createWithXY(float x, float y, int addGameScore,
                                          int multiplyConstant = 0,
                                          int nabuzaTimeConstant = 0);
    void show();

private:
    void removeCallback();
};

#endif /* defined(__NabuzaI__TouchScoreSprite__) */
