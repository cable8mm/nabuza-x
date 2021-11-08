//
//  GameScene.h
//  NabuzaI
//
//  Created by Lee Samgu on 4/22/13.
//
//

#ifndef __NabuzaI__GameScene__
#define __NabuzaI__GameScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Structs/CoinSprite.h"
#include "Structs/TimeGoldGaugeSprite.h"
#include "Structs/TimeNabuzaGaugeSprite.h"
#include "Structs/TimeGoldSprite.h"
#include "Layers/GameBgLayer.h"
#include "Layers/NabuzaTimeTitleLayer.h"

#define MATRIX_XY_COIN_COUNT      7

USING_NS_CC;
USING_NS_CC_EXT;

typedef struct int_point{
    int x,y;
} intPoint;

class GameScene : public cocos2d::CCLayer
{
public:
    ~GameScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    static cocos2d::CCScene* sceneWithItems(CCArray *choosedItems);
    // a selector callback
    void pauseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
    bool ccTouchBegan(CCTouch *touch, CCEvent *pEvent);
    void ccTouchMoved(CCTouch *touch, CCEvent *event);
    void ccTouchEnded(CCTouch *touch, CCEvent *event);
    void ccTouchCancelled(CCTouch *touch, CCEvent *pEvent);
    void tiktok();
    bool canRolling(intPoint xy);
    
    unsigned int remainSeconds;
    CCArray *coinSprites;
    
    // for game logic
    unsigned int selectingCoinNumber;    // 선택된 코인 색깔
    bool coinsMatrix[MATRIX_XY_COIN_COUNT][MATRIX_XY_COIN_COUNT];   // 현재 회전하고 있는지 여부
    bool coinsMarkedMatrix[MATRIX_XY_COIN_COUNT][MATRIX_XY_COIN_COUNT];   // 현재 회전하고 있는지 여부
    unsigned int rollingCoinCount;
    unsigned int gameScore;
    unsigned int getAddingGameScore();
    
    CoinSprite *previousSelectingCoinSprite;
    CoinSprite *currentSelectingCoinSprite;
    
    CCArray *choosedItems;
    
    void addCoin(unsigned int key, unsigned int coinNumber);
    void addRandomCoinAtTop(unsigned int x);
    
    // notifications
    void resume(CCObject* obj);
    void restart(CCObject* obj);
    void quit(CCObject* obj);
    void notiTimeOverDone(CCObject* obj);
    void timeGoldGaugeMaxNotification(unsigned int goldKey);
    
    // game sprite management
    void addGameScore(int score);
    void setGameScore(int score);

private:
    enum eGameStats
    {
        kGAMESTATE_SHOW_LEVEL,
        kGAMESTATE_READY,
        kGAMESTATE_PLAYING,
        kGAMESTATE_LASTCHANCE_ALERT,
        kGAMESTATE_LASTCHANCE,
        kGAMESTATE_TIMEOVER,
        kGAMESTATE_GAMERESULT,
        kGAMESTATE_LUCKY7RANKING,
        kGAMESTATE_GAMEEVENT,
        kGAMESTATE_GAMEOVER
    };
    
    eGameStats kGameState;
    
    CCLabelBMFont *lbRemainSeconds;
    unsigned int nabuzaTimeCount;
    unsigned int needCoinCountForNabuzaTime;
    TimeGoldGaugeSprite *timeGoldGaugeSprite;
    TimeNabuzaGaugeSprite *timeNabuzaGaugeSprite;
    TimeGoldSprite *timeGoldSprite;
    GameBgLayer *gameBgLayer;
    NabuzaTimeTitleLayer *nabuzaTimeTitleLayer;
    
    unsigned int lastChanceCount;
    unsigned int gameMode;  // 일반 0, 라스트타임 1
    
    void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);
    void setGameState(eGameStats kGameState);
    void resetCoinsMatrix();
    void go();
    void nabuzaTimeFinishCallback();
    void setNabuzaTimeCount(unsigned int v);
    void removeCoin(CoinSprite *obj);
    void registerWithTouchDispatcher();
    void timeOver();
    void setGameMode(unsigned int mode);
    
    // notification callback methods
    void notiEndGameEvent(CCObject *obj);
    void notiEndLucky7Ranking(CCObject *obj);
    void notiEndGameResult(CCObject *obj);
    void notiGamePlaying(CCObject *obj);
    void notiGameLastChance(CCObject *obj);
    
    bool canSelecting;  // 처음 선택 한 색깔을 선택하고 있을 경우 true;
    bool isValidTouchBegan;
};

unsigned int GetRandomCoinNumber();
unsigned int GetRandomKey();

intPoint GetXYFromPoint(float x, float y);
unsigned int GetXFromKey(unsigned int key);
unsigned int GetKeyFromXY(unsigned int x, unsigned int y);
intPoint GetXYFromKey(unsigned int key);
CCPoint GetCCPFromKey(unsigned int key);
unsigned int GetYFromKey(unsigned int key);
bool isValidXY(intPoint xy);
bool isValidXY(int x, int y);
bool isValidSelectingXY(intPoint previousPoint, intPoint currentPoint);
bool isValidSelectingXY(unsigned int kPreviousPoint, unsigned int kCurrentPoint);
int getMultiplyConstant(unsigned int coinCount);    // 동전 갯수 배수 구하기

void playSoundJing(unsigned int rollingCoinCount);
void playSoundNabuzaTime();
void playSoundNabuzaVoice(unsigned int rollingCoinCount);
void playSoundGameReady();
void playSoundGameStart();
void playSoundTimeOver();
void playSoundLastChange();
void playSoundDropCoins(unsigned int coinCount);
void playBgGamePlay();
void playBgGameNabuzaPlay();
void stopBgGamePlay();
#endif /* defined(__NabuzaI__GameScene__) */
