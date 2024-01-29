//
//  SaleInvitationLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/29/13.
//
//

#ifndef __NabuzaI__SaleInvitationLayer__
#define __NabuzaI__SaleInvitationLayer__

#include "cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SaleInvitationLayer : public cocos2d::CCLayerColor {
public:
    CREATE_FUNC(SaleInvitationLayer);

private:
    CCSprite *touchedSprite;
    void onEnter();
    void buyInvitation(CCObject *pSender);
    void close();
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void registerWithTouchDispatcher();
    void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);
};

#endif /* defined(__NabuzaI__SaleInvitationLayer__) */
