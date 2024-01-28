//
//  MyRankSprite.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/25/13.
//
//

#ifndef __NabuzaI__MyRankSprite__
#define __NabuzaI__MyRankSprite__

#include "cocos2d.h"
USING_NS_CC;

class MyRankSprite : public cocos2d::CCSprite {
private:
    void onEnter();

public:
    static MyRankSprite *create();
    void startAnimation();
};

#endif /* defined(__NabuzaI__MyRankSprite__) */
