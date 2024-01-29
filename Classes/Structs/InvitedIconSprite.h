//
//  InvitedIconSprite.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/29/13.
//
//

#ifndef __NabuzaI__InvitedIconSprite__
#define __NabuzaI__InvitedIconSprite__

#include "cocos2d.h"
USING_NS_CC;

enum eInvitedIconStats { kINVITEDICONSTATE_UNSENT, kINVITEDICONSTATE_SENT };

class InvitedIconSprite : public cocos2d::CCSprite {
private:
    eInvitedIconStats stat;

    void onEnter();

public:
    static InvitedIconSprite *create();
    static InvitedIconSprite *create(eInvitedIconStats stat);
    void setStat(eInvitedIconStats v);
};

#endif /* defined(__NabuzaI__InvitedIconSprite__) */
