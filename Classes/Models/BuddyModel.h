//
//  BuddyModel.h
//  NabuzaI
//
//  Created by Lee Samgu on 8/19/13.
//
//

#ifndef __NabuzaI__BuddyModel__
#define __NabuzaI__BuddyModel__

#include "cocos2d.h"
USING_NS_CC;

class BuddyModel : public cocos2d::CCObject {
public:
    int idx;
    int rank;
    int ownGoldCount;
    std::string nickname;
    int weeklyHighscore;
    int highscore;
    int ownGoldMedalCount;
    int ownSilverMedalCount;
    int ownBronzeMedalCount;
    bool isMe;
    bool isInvitationNotification;
};

#endif /* defined(__NabuzaI__BuddyModel__) */
