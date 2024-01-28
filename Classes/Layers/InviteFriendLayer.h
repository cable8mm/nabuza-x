//
//  InviteFriendLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/4/13.
//
//

#ifndef __NabuzaI__InviteFriendLayer__
#define __NabuzaI__InviteFriendLayer__

#include "cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;

class InviteFriendLayer : public cocos2d::CCLayerColor {
public:
    CREATE_FUNC(InviteFriendLayer);

private:
    std::string kakaotalkMessage;
    std::string smsMessage;
    void onEnter();
    void close();
    void sms();
    void kakaotalk();
    void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);

    // Touches
    bool ccTouchBegan(CCTouch *touch, CCEvent *pEvent);
    void ccTouchCancelled(CCTouch *touch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *touch, CCEvent *event);

    void registerWithTouchDispatcher();
};

#endif /* defined(__NabuzaI__InviteFriendLayer__) */
