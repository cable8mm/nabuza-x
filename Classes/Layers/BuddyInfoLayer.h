//
//  BuddyInfoLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 8/8/13.
//
//

#ifndef __NabuzaI__BuddyInfoLayer__
#define __NabuzaI__BuddyInfoLayer__

#include "BuddyModel.h"
#include "cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;

class BuddyInfoLayer : public cocos2d::CCLayerColor {
private:
    int playerKey;
    BuddyModel *buddyModel;
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void onEnter();
    void close();
    void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);
    void registerWithTouchDispatcher();

public:
    static BuddyInfoLayer *createWithPlayerKey(int PlayerKey);
    static BuddyInfoLayer *createWithBuddyKey(int BuddyKey);
};

std::string GetStringFromInt(int v);

#endif /* defined(__NabuzaI__BuddyInfoLayer__) */
