//
//  AlertLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 8/13/13.
//
//

#ifndef __NabuzaI__AlertLayer__
#define __NabuzaI__AlertLayer__

#include "cocos2d.h"

USING_NS_CC;

class AlertLayer : public cocos2d::CCLayerColor {
public:
    static AlertLayer *sharedAlertLayer(void);
    //    static AlertLayer *createWithMessage(std::string title, std::string
    //    message);
    void show(std::string title, std::string message);

private:
    std::string title;
    std::string message;
    bool init();
    void close();
    bool ccTouchBegan(CCTouch *touch, CCEvent *pEvent);
    void registerWithTouchDispatcher();
};

#endif /* defined(__NabuzaI__AlertLayer__) */
