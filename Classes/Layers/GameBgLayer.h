//
//  GameBgLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 5/20/13.
//
//

#ifndef __NabuzaI__GameBgLayer__
#define __NabuzaI__GameBgLayer__

#include "cocos2d.h"
using namespace cocos2d;

class GameBgLayer : public cocos2d::CCLayerColor
{
private:
    GameBgLayer(void);
    ~GameBgLayer();
    bool isNabuzaTime;

    CCSprite *playBgTopSprite;
    CCSprite *playBgBottomSprite;
    CCSprite *playNabuzaDragonSprite;
    
    bool init();
    void nabuzaTimeDoneCallback();
    void nabuzaTimeFinishCallback();
    void update();
    void removeNabuzaSprite(CCSprite *obj);
    
public:
    CREATE_FUNC(GameBgLayer);
    void setIsNabuzaTime(bool yorn);    
};

#endif /* defined(__NabuzaI__GameBgLayer__) */
