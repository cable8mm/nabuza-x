//
//  IndicationLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/31/13.
//
//

#ifndef __NabuzaI__IndicationLayer__
#define __NabuzaI__IndicationLayer__

#include "cocos2d.h"

USING_NS_CC;

class IndicationLayer : public cocos2d::CCLayerColor
{
private:
    bool init();
    void registerWithTouchDispatcher();
    bool ccTouchBegan(CCTouch *touch, CCEvent *pEvent);
public:
    CREATE_FUNC(IndicationLayer);
    void onEnter();
    void close();
};

#endif /* defined(__NabuzaI__IndicationLayer__) */
