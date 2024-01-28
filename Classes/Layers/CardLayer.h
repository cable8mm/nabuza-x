//
//  CardLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 6/28/13.
//
//

#ifndef __NabuzaI__CardLayer__
#define __NabuzaI__CardLayer__

#include "cocos2d.h"
USING_NS_CC;

#include "UserStorage.h"

class CardLayer : public cocos2d::CCLayerColor {
public:
    ~CardLayer();
    void onEnter();
    CREATE_FUNC(CardLayer);
    void setDisplayCardCount(int cardCount);

private:
    int cardCount;
    int countDownClock;  // 초대장이 5개에서 4개가 될 때의 countDown()값이
                         // 저장된다.
    void tick();
    void close();
    void onChangedCardCount(CCObject *obj);
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void registerWithTouchDispatcher();
};

#endif /* defined(__NabuzaI__CardLayer__) */
