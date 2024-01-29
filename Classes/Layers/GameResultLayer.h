//
//  GameResultLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/2/13.
//
//

#ifndef __NabuzaI__GameResultLayer__
#define __NabuzaI__GameResultLayer__

#include "cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GameResultLayer : public cocos2d::CCLayerColor {
public:
    static GameResultLayer *createWithGameScore(int gameScore);

private:
    enum eGameResultStats {
        kGAMERESULTSTATE_READY,
        kGAMERESULTSTATE_ADD_COINCOUNT,
        kGAMERESULTSTATE_DISPLAY_GOLD,
        kGAMERESULTSTATE_DONE
    };

    unsigned int gameScore;           // 점수
    unsigned int levelBonusScore;     // 레벨 보너스 점수
    unsigned int bonusGoldCount;      // 올라가는 골드 점수
    unsigned int nextLevelGoldCount;  // 다음 레벨까지 필요한 골드
    unsigned int highscore;           // 최고 점수
    unsigned int gameTickScore;  // 점수까지 올라가는데 바뀌는 틱점수
    unsigned int tickTerm;       // 한번 틱 할 때 올라가는 점수
    bool isPlayCoinCount;        // 현재 소리가 나는지 유무
    eGameResultStats kGameResultState;
    void setGameScore(unsigned int v);
    void setGameResultState(eGameResultStats kGameResultState);
    void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);
    CCSprite *playSpeechSprite;
    bool init();
    void onEnter();
    void close();
    void changeScore();
    bool ccTouchBegan(CCTouch *touch, CCEvent *pEvent);
    void registerWithTouchDispatcher();
};

void playSoundCoinCount();

#endif /* defined(__NabuzaI__GameResultLayer__) */
