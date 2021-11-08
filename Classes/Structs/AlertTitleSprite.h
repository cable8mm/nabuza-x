//
//  AlertTitleSprite.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/2/13.
//
//

#ifndef __NabuzaI__AlertTitleSprite__
#define __NabuzaI__AlertTitleSprite__

#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d;

enum eGameAlertTitles
{
    // title_alert_text.png
    kGAMEALERTTITLE_NEED_MORE_CARD       = 0,
    kGAMEALERTTITLE_CONGRATULATION       = 1,
    kGAMEALERTTITLE_GAMERESULT           = 2,
    kGAMEALERTTITLE_RANKING_CHANGED      = 3,
    kGAMEALERTTITLE_INVITE_FRIEND        = 4,
    kGAMEALERTTITLE_MESSAGE_BOX          = 5,
    kGAMEALERTTITLE_BUY_GOLD             = 6,
    kGAMEALERTTITLE_BUY_CARD             = 7,
    kGAMEALERTTITLE_BUY_JADE             = 8,
    kGAMEALERTTITLE_INVITING_FRIEND      = 9,
    kGAMEALERTTITLE_LASTWEEK_RESULT      = 10,
    kGAMEALERTTITLE_LEVEL_UP             = 11,
    kGAMEALERTTITLE_TOURNAMENT_RESULT    = 12,
    kGAMEALERTTITLE_BOASTING             = 13,
    kGAMEALERTTITLE_LOSING               = 14,
    kGAMEALERTTITLE_SENDING_GIFT         = 15
};

class AlertTitleSprite : public cocos2d::CCSprite
{
private:
    void onEnter();
public:
    static AlertTitleSprite* createWithItemKey(eGameAlertTitles key);
};

#endif /* defined(__NabuzaI__AlertTitleSprite__) */
