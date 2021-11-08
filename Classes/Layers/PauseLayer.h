//
//  PauseLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 5/6/13.
//
//

#ifndef __NabuzaI__PauseLayer__
#define __NabuzaI__PauseLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;

class PauseLayer : public cocos2d::CCLayerColor
{
public:
    PauseLayer();
    ~PauseLayer();
    
    // a selector callback
    void resumeCallback(CCObject* pSender);
    void quitCallback(CCObject* pSender);
    void restartCallback(CCObject* pSender);
    
    bool init();
    void menuResumeCallback(CCObject* pSender);
    void menuRestartCallback(CCObject* pSender);
    void menuGotoMenuCallback(CCObject* pSender);
    
    CREATE_FUNC(PauseLayer);
private:
    bool ccTouchBegan(CCTouch *touch, CCEvent *pEvent);
    void registerWithTouchDispatcher();
};


#endif /* defined(__NabuzaI__PauseLayer__) */
