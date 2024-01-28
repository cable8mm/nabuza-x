//
//  SaleInvitationSprite.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/29/13.
//
//

#ifndef __NabuzaI__SaleInvitationSprite__
#define __NabuzaI__SaleInvitationSprite__

#include "cocos2d.h"
USING_NS_CC;

class SaleInvitationSprite : public cocos2d::CCSprite {
private:
public:
    int key;
    static SaleInvitationSprite *createWithItemKey(unsigned int key);
    static SaleInvitationSprite *createWithItemKeyTapped(unsigned int key);
};

#endif /* defined(__NabuzaI__SaleInvitationSprite__) */
