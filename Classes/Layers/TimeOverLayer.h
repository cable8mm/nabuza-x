//
//  TimeOverLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 6/27/13.
//
//

#ifndef __NabuzaI__TimeOverLayer__
#define __NabuzaI__TimeOverLayer__

#include "cocos2d.h"
using namespace cocos2d;

class TimeOverLayer : public cocos2d::CCLayerColor
{
public:
    void onEnter();
    CREATE_FUNC(TimeOverLayer);
    
private:
    void speechStart();
    void close();
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void registerWithTouchDispatcher();
};

#endif /* defined(__NabuzaI__TimeOverLayer__) */
