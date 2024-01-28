//
//  SwitchSprite.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/3/13.
//
//

#ifndef __NabuzaI__SwitchSprite__
#define __NabuzaI__SwitchSprite__

#include "cocos2d.h"
USING_NS_CC;

class SwitchSprite : public cocos2d::CCSprite {
private:
    bool v;

public:
    static SwitchSprite* createWithValue(bool v);
    bool getValue();
    void setV(bool v);
    void toggle();
};

#endif /* defined(__NabuzaI__SwitchSprite__) */
