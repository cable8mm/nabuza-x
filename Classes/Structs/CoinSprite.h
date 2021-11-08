//
//  Coin.h
//  NabuzaI
//
//  Created by Lee Samgu on 4/24/13.
//
//

#ifndef __NabuzaI__CoinSprite__
#define __NabuzaI__CoinSprite__

#include "cocos2d.h"

const float MATRIX_CELL_WH          = 68.;
const float MATRIX_COIN_WH          = 66.;

USING_NS_CC;

class CoinSprite : public cocos2d::CCSprite
{
private:
    //notification
    void nabuzaTimeCallback(CCObject* obj);
    void nabuzaTimeDoneCallback();
    void nabuzaTimeFinishCallback();
    void initializeFrame();
public:
    CoinSprite();
    ~CoinSprite();
    
    static CoinSprite* createWithNumber(unsigned int key, unsigned int coinNumber);
    
    unsigned int key;
    unsigned int number; // CoinNumber(Color)
    bool isNabuzaTime;
    unsigned int mustTapCoinCount;
    
    void setIsRolling(bool isRolling);
    bool isValid;   // 바로 없어지지 않고, 애니메이션 후에 없어지므로, 코인이 삭제될 때 isVaid 값을 이용한다.
    void reset();
    void pang();
    bool isRolling;
    void down();
    void animationDown();
    void downDone(CCNode* sender);
    
    void beTimeGoldSprite(unsigned int goldKey);
    void changeTimeGoldSprite();
    
    void setIsNabuzaTime(bool isNabuzaTime);
    void setIsNabuzaTime(bool isNabuzaTime, bool isAnimation);
    void activeNabuzaAction();
    
    CCSprite *effectSprite;
};

#endif /* defined(__NabuzaI__CoinSprite__) */
