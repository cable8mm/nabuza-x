//
//  ButtonSprite.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/2/13.
//
//

#ifndef __NabuzaI__ButtonSprite__
#define __NabuzaI__ButtonSprite__

#include "cocos2d.h"
USING_NS_CC;

enum eGameButtons {
    kGAMEBUTTON_UPDATE = 0,
    kGAMEBUTTON_GAMEOVER = 1,
    kGAMEBUTTON_YES = 2,
    kGAMEBUTTON_NO = 3,
    kGAMEBUTTON_CONFIRM = 4,
    kGAMEBUTTON_CANCEL = 5,
    kGAMEBUTTON_CLOSE = 6,
    kGAMEBUTTON_RECEIVE_ALL = 7,
    kGAMEBUTTON_PASSWORD_INPUT = 8,
    kGAMEBUTTON_BUY_JADE = 9,
    kGAMEBUTTON_RETRY = 10,
    kGAMEBUTTON_NEXT = 11,
    kGAMEBUTTON_FACEBOOK_LOGIN = 12,
    kGAMEBUTTON_FACEBOOD_LOGOUT = 13,
    kGAMEBUTTON_COUPON_REGIST = 14,
    kGAMEBUTTON_CONFIRM_REWARD = 15,
    kGAMEBUTTON_BOASTING = 16,
    kGAMEBUTTON_HELP = 17,
    kGAMEBUTTON_MANAGE_ACCOUNT = 18
};

class ButtonSprite : public cocos2d::CCSprite {
private:
    unsigned int key;
    bool isActive;

public:
    static ButtonSprite* createWithItemKey(eGameButtons key);
};

#endif /* defined(__NabuzaI__ButtonSprite__) */
