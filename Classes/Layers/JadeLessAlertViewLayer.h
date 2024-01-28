//
//  AlertViewLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/30/13.
//
//

#ifndef __NabuzaI__JadeLessAlertViewLayer__
#define __NabuzaI__JadeLessAlertViewLayer__

#include "cocos2d.h"
USING_NS_CC;

enum eJadeLessKeys {
    kJADELESSKEY_NOT_GOLD = 0,
    kJADELESSKEY_NOT_INVITATION = 1,
    kJADELESSKEY_NOT_GIFT = 2
};

class JadeLessAlertViewLayer : public cocos2d::CCLayerColor {
public:
    static JadeLessAlertViewLayer *createWithKey(eJadeLessKeys key);

private:
    eJadeLessKeys key;
    void onEnter();
    void yes();
    void no();
};

#endif /* defined(__NabuzaI__JadeLessAlertViewLayer__) */
