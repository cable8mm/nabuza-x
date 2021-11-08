//
//  NabuzaTimeTitleLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 5/23/13.
//
//

#ifndef __NabuzaI__NabuzaTimeTitleLayer__
#define __NabuzaI__NabuzaTimeTitleLayer__

#include "cocos2d.h"
using namespace cocos2d;

class NabuzaTimeTitleLayer : public cocos2d::CCLayerColor
{
private:
    bool init();
    
public:
    CREATE_FUNC(NabuzaTimeTitleLayer);
    
    CCSprite *nabuzaTitleCoin;
    CCSprite *nabuzaTitleBalloon;
    
    void setNabuzaTimeCount(unsigned int nabuzaTimeCount);
};


#endif /* defined(__NabuzaI__NabuzaTimeTitleLayer__) */
