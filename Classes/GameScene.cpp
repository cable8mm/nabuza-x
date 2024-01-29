//
//  GameScene.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 4/22/13.
//
//
#include "GameScene.h"

#import <AudioToolbox/AudioToolbox.h>

#include "BaseScene.h"
#include "Layers/GameEventLayer.h"
#include "Layers/GameLoadingLayer.h"
#include "Layers/GameReadyStartLayer.h"
#include "Layers/GameResultLayer.h"
#include "Layers/LastChanceLayer.h"
#include "Layers/Lucky7RankingLayer.h"
#include "Layers/PauseLayer.h"
#include "Layers/TimeOverLayer.h"
#include "Networks/AnytaleHTTP.h"
#include "Storages/ItemStorage.h"
#include "Storages/NeedForGameMemory.h"
#include "Storages/UserStorage.h"
#include "Structs/PlayTimeProgressSprite.h"
#include "Structs/TimeGoldCoinSprite.h"
#include "Structs/TouchScoreSprite.h"
#include "Utilities/ATUtil.h"

const float MATRIX_LEFT_MARGIN = 2.;
const float MATRIX_BOTTOM_MARGIN = 145.;

// TAGS
const int TAG_GAME_SCORE_SPRITE = 10000;
const int TAG_GAME_LOADING_LAYER = 11001;

// LAYERS
const int ZORDER_PULL_SCREEN = 110000;
const int LAYER_MENU = 100000;
const int LAYER_MENU_BUTTON = 90000;
const int LAYER_GAME_MESSAGE = 80000;
const int LAYER_TITLE = 60000;
const int LAYER_TOUCH_SCORE = 55000;
const int LAYER_COINSET = 50000;
const int LAYER_PROGRESSBAR = 50000;
const int LAYER_TOP_BAR_CONTENTS = 40000;
const int LAYER_TOP_BAR = 30000;
const int LAYER_GAUGE = 20000;
const int LAYER_TOP_BAR_BG = 15000;
const int LAYER_BG = 10000;

USING_NS_CC;

#pragma mark -
#pragma mark Scene() & Init()

CCScene *GameScene::scene() {
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();

    // enable Touch
    layer->setTouchEnabled(true);

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init() {
    //////////////////////////////
    // 1. super init first
    if (!CCLayer::init()) {
        return false;
    }
    // Ready Coin Animation
    //    GameLoadingLayer *gameLoadingLayer  = GameLoadingLayer::create();
    //    this->addChild(gameLoadingLayer, LAYER_GAME_MESSAGE);

    // GameLoadingLayer called / NABUZA_LASTCHANCE_NOTIFICATION
    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        this, callfuncO_selector(GameScene::resume), "RESUME_NOTIFICATION",
        NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        this, callfuncO_selector(GameScene::restart), "RESTART_NOTIFICATION",
        NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        this, callfuncO_selector(GameScene::quit), "QUIT_NOTIFICATION", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        this, callfuncO_selector(GameScene::timeGoldGaugeMaxNotification),
        "TIME_GOLD_GAUGE_MAX_NOTIFICATION", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        this, callfuncO_selector(GameScene::notiGamePlaying),
        "NABUZA_PLAYING_NOTIFICATION", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        this, callfuncO_selector(GameScene::notiGameLastChance),
        "NABUZA_LASTCHANCE_NOTIFICATION", NULL);

    // TIME_OVER_LAYER_DONE_NOTIFICATION
    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        this, callfuncO_selector(GameScene::notiTimeOverDone),
        "TIME_OVER_LAYER_DONE_NOTIFICATION", NULL);
    // NABUZA_END_GAMERESULT_NOTIFICATION
    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        this, callfuncO_selector(GameScene::notiEndGameResult),
        "NABUZA_END_GAMERESULT_NOTIFICATION", NULL);
    // NABUZA_END_LUCKY7RANKING_NOTIFICATION
    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        this, callfuncO_selector(GameScene::notiEndLucky7Ranking),
        "NABUZA_END_LUCKY7RANKING_NOTIFICATION", NULL);
    // NABUZA_END_GAMEEVENT_NOTIFICATION
    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        this, callfuncO_selector(GameScene::notiEndGameEvent),
        "NABUZA_END_GAMEEVENT_NOTIFICATION", NULL);
    CCLog("Start Game");

    this->nabuzaTimeCount = 0;

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    CCSprite *playBgMidTimeSprite = CCSprite::create("play_bg_mid_time.png");
    playBgMidTimeSprite->setPosition(
        ccp(visibleSize.width / 2., 800. - 118 - 30.));
    this->addChild(playBgMidTimeSprite, LAYER_TOP_BAR);

    CCSprite *layerTopBarBg = CCSprite::create("play_bg_mid_time_block.png");
    layerTopBarBg->setPosition(ccp(142., 651.5));  // 62, 125 / 사이즈가 160 47
    this->addChild(layerTopBarBg, LAYER_TOP_BAR_BG);

    // 복주머니&용대가리
    this->timeGoldSprite = TimeGoldSprite::createWithCustom();
    this->timeGoldSprite->setPosition(ccp(2. + 31., 800. - 118 - 31));
    this->addChild(this->timeGoldSprite, LAYER_TOP_BAR_CONTENTS);

    this->gameBgLayer = GameBgLayer::create();
    this->addChild(gameBgLayer, LAYER_BG);

    this->timeGoldGaugeSprite = TimeGoldGaugeSprite::createWithCustom();
    this->timeGoldGaugeSprite->setPosition(ccp(62. + 78., 800. - 127. - 22.));
    this->addChild(this->timeGoldGaugeSprite, LAYER_GAUGE);
    this->timeNabuzaGaugeSprite = TimeNabuzaGaugeSprite::create();
    this->addChild(this->timeNabuzaGaugeSprite, LAYER_GAUGE);

    CCSprite *playBgMidSprite = CCSprite::create("play_bg_mid.png");
    playBgMidSprite->setPosition(
        ccp(visibleSize.width / 2., 800. - 108 - 332.));
    this->addChild(playBgMidSprite, LAYER_PROGRESSBAR);

    CCLabelBMFont *lbScore = CCLabelBMFont::create("0", "score.fnt");
    lbScore->setAnchorPoint(ccp(1., .5));
    lbScore->setScale(1.);
    lbScore->setPosition(ccp(480. - 5., 800. - 147.));
    this->addChild(lbScore, LAYER_TOP_BAR_CONTENTS, TAG_GAME_SCORE_SPRITE);

    CCMenuItem *btnPlayPause =
        CCMenuItemImage::create("play_btn_pause.png", "play_btn_pause.png",
                                this, menu_selector(GameScene::pauseCallback));
    btnPlayPause->setPosition(ccp(420. + 30., 770.));
    CCMenu *pauseMenu = CCMenu::create(btnPlayPause, NULL);
    pauseMenu->setPosition(CCPointZero);
    pauseMenu->setTouchPriority(0);
    this->addChild(pauseMenu, LAYER_MENU_BUTTON);

    this->coinSprites = new CCArray;

    srand(time(NULL));  // shuffle for rand()

    for (unsigned int i = 0; i < 49; i++) {
        unsigned int randomCoinNumber = GetRandomCoinNumber();
        this->addCoin(i, randomCoinNumber);
    }

    this->remainSeconds = 7;

    this->nabuzaTimeTitleLayer = NabuzaTimeTitleLayer::create();
    this->addChild(this->nabuzaTimeTitleLayer, LAYER_TITLE);

    this->needCoinCountForNabuzaTime = 9;
    this->lastChanceCount = 0;

    // 아이템
    ItemStorage *itemStorage = ItemStorage::create();
    CCArray *selectedItems = itemStorage->getItems();

    if (selectedItems->count() != 0) {
        for (unsigned int i = 0; i < selectedItems->count(); i++) {
            CCInteger *itemKey =
                dynamic_cast<CCInteger *>(selectedItems->objectAtIndex(i));
            CCLog("Item Number i : %u, itemKey : %i", i, itemKey->getValue());

            CCSprite *playItemSprite = CCSprite::create(
                "play_item.png",
                CCRect(44. * itemKey->getValue(), 0., 44., 44.));
            playItemSprite->setPosition(ccp(22. + 44. * i, 800. - 682 - 22.));
            this->addChild(playItemSprite, LAYER_PROGRESSBAR);

            switch (itemKey->getValue()) {
                case 0:  // 보너스 타임
                    this->remainSeconds += 10;
                    break;
                case 1:  // 나부자 타임
                    this->setNabuzaTimeCount(1);
                    break;
                case 2:  // 코인셋

                    break;
                case 3:  // 한번 더
                    break;
                case 4:  // 라스트 찬스 (5번)
                    this->lastChanceCount = 5;
                    break;
                case 5:  // 이지모드 - 7개 동전으로 나부자 타임에 들어감.
                    this->needCoinCountForNabuzaTime = 7;
                    break;
            }
        }
    }

    CCString *strRemainSconds =
        CCString::createWithFormat("%d", this->remainSeconds);

    this->lbRemainSeconds =
        CCLabelBMFont::create(strRemainSconds->getCString(), "play_time.fnt");
    this->lbRemainSeconds->setScale(.8);
    this->lbRemainSeconds->setPosition(ccp(240., 127.));
    this->addChild(this->lbRemainSeconds, LAYER_TITLE);

    this->setGameMode(0);  // 일반 모드(라스트챈스 모드 아님)

    this->setGameState(kGAMESTATE_SHOW_LEVEL);

    return true;
}

#pragma mark -
#pragma mark Notification Callback
// notiEndGameEvent
void GameScene::notiEndGameEvent(CCObject *obj) {
    this->setGameState(kGAMESTATE_GAMEOVER);
}

void GameScene::notiEndLucky7Ranking(CCObject *obj) {
    this->setGameState(kGAMESTATE_GAMEEVENT);
}

void GameScene::notiEndGameResult(CCObject *obj) {
    this->setGameState(kGAMESTATE_LUCKY7RANKING);
}

void GameScene::notiGamePlaying(CCObject *obj) {
    this->setGameState(kGAMESTATE_PLAYING);
}

void GameScene::notiTimeOverDone(CCObject *obj) {
    this->setGameState(kGAMESTATE_GAMERESULT);
}

void GameScene::notiGameLastChance(CCObject *obj) {
    this->setGameState(kGAMESTATE_LASTCHANCE);
}

void GameScene::go() {
}

void GameScene::timeOver() {
    stopBgGamePlay();
    this->pauseSchedulerAndActions();
    TimeOverLayer *timeOverLayer = TimeOverLayer::create();
    this->addChild(timeOverLayer, LAYER_GAME_MESSAGE);
}

void GameScene::resume(
    CCObject *obj) {  // 재시작은 아이템 선택 화면으로 나가는 것을 의미
    CCLog("RESUME");
    CCDirector::sharedDirector()->resume();
    //    this->resumeSchedulerAndActions();
}

void GameScene::restart(
    CCObject *obj) {  // 재시작은 아이템 선택 화면으로 나가는 것을 의미
    CCLog("RESTART");
    this->resume(obj);
}

void GameScene::quit(
    CCObject *obj) {  // 재시작은 아이템 선택 화면으로 나가는 것을 의미
    CCLog("QUIT");
    CCDirector::sharedDirector()->resume();
    CCDirector::sharedDirector()->replaceScene(BaseScene::scene());
}

void GameScene::nabuzaTimeFinishCallback() {
    this->nabuzaTimeCount = 0;
}

void GameScene::timeGoldGaugeMaxNotification(
    unsigned int goldKey) {  // 랜덤하게
    CCPoint randomCoinXY;
    CCObject *object;
    CoinSprite *coinSprite;
    do {
        unsigned int randomKey = GetRandomKey();
        randomCoinXY = GetCCPFromKey(randomKey);
        CCARRAY_FOREACH(this->coinSprites, object) {
            coinSprite = (CoinSprite *)object;
            if (coinSprite->key == randomKey) {
                break;
            }
        }
        if (coinSprite->number < 5) {               // 골드가 아닐 경우
            coinSprite->beTimeGoldSprite(goldKey);  // 0이면 금, 1이면 은
            break;
        }
    } while (true);

    // 애니메이션
    TimeGoldCoinSprite *timeGoldCoinSprite =
        TimeGoldCoinSprite::createWithColor(goldKey);  // 0은 금, 1은 은.
    timeGoldCoinSprite->setPosition(ccp(2. + 31., 800. - 118 - 31));
    this->addChild(timeGoldCoinSprite, LAYER_COINSET);
    timeGoldCoinSprite->move(randomCoinXY.x, randomCoinXY.y);
}

void GameScene::removeCoin(CoinSprite *obj) {
    this->removeChild(obj);
    obj->stopAllActions();
}

#pragma mark -
#pragma mark Game Sprite Managements
void GameScene::setGameScore(int score) {
    std::stringstream ss;
    std::string gameScore;

    ss << score;
    gameScore = ss.str();

    ATUtil::insert_separator(gameScore);

    // LAYER_TOP_ON_GAME, TAG_GAME_SCORE_SPRITE
    CCLabelBMFont *lbScore = dynamic_cast<CCLabelBMFont *>(
        this->getChildByTag(TAG_GAME_SCORE_SPRITE));

    lbScore->setString(gameScore.c_str());
}

void GameScene::addGameScore(int score) {
    this->gameScore += score;
    this->setGameScore(this->gameScore);
}

void GameScene::addCoin(unsigned int key, unsigned int coinNumber) {
    CoinSprite *coinSprite = CoinSprite::createWithNumber(key, coinNumber);
    coinSprite->key = key;

    coinSprite->setPosition(GetCCPFromKey(key));

    if (this->nabuzaTimeCount > 0) {
        coinSprite->setIsNabuzaTime(true, false);
    }

    this->addChild(coinSprite, LAYER_COINSET);
    this->coinSprites->addObject(coinSprite);

    coinSprite->effectSprite->setPosition(GetCCPFromKey(key));

    this->addChild(coinSprite->effectSprite, LAYER_COINSET);
    coinSprite->animationDown();
}

void GameScene::addRandomCoinAtTop(unsigned int x) {
    unsigned int randomCoinNumber = GetRandomCoinNumber();
    this->addCoin(x + 42, randomCoinNumber);
}

void GameScene::setNabuzaTimeCount(unsigned int v) {
    // 첫번째 나부자 타임
    if (v == 1) {
        for (unsigned int i = 0; i < this->coinSprites->count(); i++) {
            CoinSprite *coinSprite =
                dynamic_cast<CoinSprite *>(this->coinSprites->objectAtIndex(i));
            if (coinSprite->isValid == true) {
                coinSprite->setIsNabuzaTime(true);
            }
        }
        this->gameBgLayer->setIsNabuzaTime(true);
        this->timeGoldSprite->setIsNabuzaTime(true);
        this->timeNabuzaGaugeSprite->isNabuzaTime(true);
        this->timeGoldGaugeSprite->isNabuzaTime(true);
        playBgGameNabuzaPlay();
    }
    this->timeNabuzaGaugeSprite->isNabuzaTime(true);
    this->nabuzaTimeTitleLayer->setNabuzaTimeCount(v);

    this->nabuzaTimeCount = v;

    // 나부자 타임
    if (v != 0) {
        for (unsigned int i = 0; i < this->coinSprites->count(); i++) {
            CoinSprite *coinSprite =
                dynamic_cast<CoinSprite *>(this->coinSprites->objectAtIndex(i));
            coinSprite->runAction(
                CCSequence::create(CCMoveBy::create(.1, ccp(0., -10.)),
                                   CCMoveBy::create(.1, ccp(0., 10.)), NULL));
        }
        playSoundNabuzaTime();
        if (UserStorage::sharedUserStorage()->getIsVibrate()) {
            AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
        }
    }
    if (v == 0) {  // 나부자 타임 끝
        this->gameBgLayer->setIsNabuzaTime(false);
        this->timeGoldSprite->setIsNabuzaTime(false);
        this->timeNabuzaGaugeSprite->isNabuzaTime(false);
        this->timeGoldGaugeSprite->isNabuzaTime(false);
        playBgGamePlay();
    }
}

void GameScene::setGameMode(unsigned int mode) {
    this->gameMode = mode;

    if (mode == 1) {  // 라스트 찬스 레이어
    }
}

void GameScene::setGameState(eGameStats kGameState) {
    this->kGameState = kGameState;

    switch (kGameState) {
        case kGAMESTATE_SHOW_LEVEL: {
            GameLoadingLayer *gameLoadingLayer = GameLoadingLayer::create();
            this->addChild(gameLoadingLayer, ZORDER_PULL_SCREEN,
                           TAG_GAME_LOADING_LAYER);
            std::stringstream ss;
            ss << "&spent_jade_count="
               << NeedForGameMemory::sharedNeedForGameMemory()->getJadeCount();
            ss << "&spent_gold="
               << NeedForGameMemory::sharedNeedForGameMemory()->getCardCount();
            ss << "&last_invitation_count_updated="
               << UserStorage::sharedUserStorage()->getLastCardCountUpdated();
            //            UserStorage::sharedUserStorage()->setCardCount(UserStorage::sharedUserStorage()->getCardCount()-1);
            ss << "&invitation_count="
               << UserStorage::sharedUserStorage()->getCardCount();

            AnytaleHTTP::onHttpRequesting(
                this, callfuncND_selector(GameScene::onHttpRequestCompleted),
                "/players/start_game2", ss.str().c_str(),
                "PLAYERS_START_GAME2");
        } break;
        case kGAMESTATE_READY: {
            CCLog("kGAMESTATE_READY");
            GameLoadingLayer *gameLoadingLayer =
                (GameLoadingLayer *)this->getChildByTag(TAG_GAME_LOADING_LAYER);
            gameLoadingLayer->removeFromParentAndCleanup(true);

            GameReadyStartLayer *gameReadyStartLayer =
                GameReadyStartLayer::create();
            this->addChild(gameReadyStartLayer, ZORDER_PULL_SCREEN);
        } break;
        case kGAMESTATE_PLAYING: {
            CCLog("kGAMESTATE_PLAYING");
            CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

            this->schedule(schedule_selector(GameScene::tiktok), 1.,
                           this->remainSeconds, 0.);

            PlayTimeProgressSprite *playTimeProgressSprite =
                PlayTimeProgressSprite::createWithCustom(this->remainSeconds);
            playTimeProgressSprite->setPosition(
                ccp(visibleSize.width / 2., 130.));
            this->addChild(playTimeProgressSprite, LAYER_PROGRESSBAR);
            playTimeProgressSprite->start();

            this->timeGoldGaugeSprite->start();
            this->timeGoldSprite->startAnimation();

            playBgGamePlay();
        } break;
        case kGAMESTATE_LASTCHANCE_ALERT: {
            CCLog("kGAMESTATE_LASTCHANCE_ALERT");

            LastChanceLayer *lastChanceLayer = LastChanceLayer::create();
            this->addChild(lastChanceLayer, ZORDER_PULL_SCREEN);
        } break;
        case kGAMESTATE_LASTCHANCE: {
            //            CCDirector::sharedDirector()->resume();
            CCLog("kGAMESTATE_LASTCHANCE");
        } break;
        case kGAMESTATE_TIMEOVER: {
            CCLog("kGAMESTATE_TIMEOVER");
            TimeOverLayer *timeOverLayer = TimeOverLayer::create();
            this->addChild(timeOverLayer, ZORDER_PULL_SCREEN);
        } break;
        case kGAMESTATE_GAMERESULT: {
            GameResultLayer *gameResultLayer =
                GameResultLayer::createWithGameScore(this->gameScore);
            this->addChild(gameResultLayer, ZORDER_PULL_SCREEN);
        } break;
        case kGAMESTATE_LUCKY7RANKING: {
            Lucky7RankingLayer *lucky7RankingLayer =
                Lucky7RankingLayer::createWithGameScore(this->gameScore);
            this->addChild(lucky7RankingLayer, ZORDER_PULL_SCREEN);
        } break;
        case kGAMESTATE_GAMEEVENT: {
            eGameEventResults eventResult = kGAMEEVENTRESULT_FAILURE;
            GameEventLayer *gameEventLayer =
                GameEventLayer::createWithEventResult(eventResult);
            this->addChild(gameEventLayer, ZORDER_PULL_SCREEN);
        } break;
        case kGAMESTATE_GAMEOVER: {
            CCDirector::sharedDirector()->replaceScene(BaseScene::scene());
        } break;
    }
}

void GameScene::onHttpRequestCompleted(CCHttpClient *sender,
                                       CCHttpResponse *response) {
    Json::Value root;

    int error;
    AnytaleHTTP::validateResponse(response, root, error);

    if (error != 0) {
        CCLog("AuthStorage json parse error");
        return;
    }

    // 게임 시작을 서버에 알림
    if (strcmp(response->getHttpRequest()->getTag(), "PLAYERS_START_GAME2") ==
        0) {
        UserStorage::sharedUserStorage()->setOwnJadeCount(
            root["result"]["Player"].get("own_jade_count", 0).asInt());
        UserStorage::sharedUserStorage()->setCardCount(
            root["result"]["Player"].get("invitation_count", 0).asInt());
        UserStorage::sharedUserStorage()->setOwnGold(
            root["result"]["Player"].get("own_gold", 0).asInt());

        this->setGameState(kGAMESTATE_READY);
    }

    return;
}

#pragma mark -
#pragma mark About Time & Score

void GameScene::tiktok() {
    if (this->remainSeconds == 0) {
        if (this->lastChanceCount == 0) {
            this->setGameState(kGAMESTATE_TIMEOVER);
        } else {
            this->setGameState(kGAMESTATE_LASTCHANCE_ALERT);
        }

        return;
    }

    this->remainSeconds--;

    CCString *strRemainSconds =
        CCString::createWithFormat("%d", this->remainSeconds);
    this->lbRemainSeconds->setString(strRemainSconds->getCString());
}

unsigned int GameScene::getAddingGameScore() {
    if (this->rollingCoinCount < 2) {
        return 0;
    }

    unsigned int caculatedGameScore = 0;
    // coin score
    caculatedGameScore += this->rollingCoinCount * 50;
    caculatedGameScore *= getMultiplyConstant(this->rollingCoinCount);

    if (this->nabuzaTimeCount > 0 || this->nabuzaTimeCount < 10) {
        caculatedGameScore *= this->nabuzaTimeCount + 1;
    }

    if (this->nabuzaTimeCount > 0 ||
        this->nabuzaTimeCount > this->needCoinCountForNabuzaTime) {
        caculatedGameScore *= 10;
    }

    return caculatedGameScore;
}

#pragma mark -
#pragma mark Initialize & Reset

void GameScene::resetCoinsMatrix() {
    for (unsigned int i = 0; i < MATRIX_XY_COIN_COUNT; i++) {
        for (unsigned int j = 0; j < MATRIX_XY_COIN_COUNT; j++) {
            this->coinsMatrix[i][j] = false;
        }
    }
}

#pragma mark -
#pragma mark Touch Delegates

void GameScene::ccTouchEnded(CCTouch *touch, CCEvent *event) {
    if (this->isValidTouchBegan == false) {
        return;
    }

    this->isValidTouchBegan = false;
    CCLog("isValidTouchBegan True");

    if (this->rollingCoinCount == 1) {
        this->currentSelectingCoinSprite->setIsRolling(false);
        return;
    }

    // 처리
    unsigned int i = 0;
    do {
        CoinSprite *coinSprite =
            (CoinSprite *)this->coinSprites->objectAtIndex(i);

        // check Pang
        if (coinSprite->isRolling == true) {
            intPoint pangCoinXY = GetXYFromKey(coinSprite->key);
            coinSprite->setIsRolling(false);
            CCLog("Pang!!! : x - %d, y - %d", pangCoinXY.x, pangCoinXY.y);

            coinSprite->isValid = false;
            this->coinSprites->removeObject(coinSprite);

            if (this->rollingCoinCount < this->needCoinCountForNabuzaTime) {
                this->removeCoin(coinSprite);
            } else {
                coinSprite->runAction(CCSequence::create(
                    CCMoveTo::create(.4, this->timeGoldSprite->getPosition()),
                    CCCallFuncN::create(
                        this, callfuncN_selector(GameScene::removeCoin)),
                    NULL));
            }

            if (pangCoinXY.y == 6) {
                this->addRandomCoinAtTop(pangCoinXY.x);
            }

            unsigned int coinSpriteCount = this->coinSprites->count();

            for (unsigned int i = 0; i < coinSpriteCount; i++) {
                CoinSprite *coinSprite4Moving = dynamic_cast<CoinSprite *>(
                    this->coinSprites->objectAtIndex(i));
                intPoint enumCoinXY = GetXYFromKey(coinSprite4Moving->key);

                if (enumCoinXY.y > pangCoinXY.y &&
                    enumCoinXY.x ==
                        pangCoinXY.x) {  // 팡되는 코인 위의 것 이라면...
                    if (enumCoinXY.y ==
                        6) {  // 위에서 첫번째 줄이 떨어졌을 경우 혹은 첫번째
                              // 줄이 터졌을 경우, 첫번째 줄에 새로운 코인을
                              // 넣는다.
                        this->addRandomCoinAtTop(enumCoinXY.x);
                    }

                    coinSprite4Moving->down();  // 아래로 한칸 내린다.
                }
            }
        } else {
            i++;
        }

    } while (i < this->coinSprites->count());

    // 코인 삭제
    //    for (unsigned int i=0; i < removeCoinSprites->count(); i++) {
    //        removeCoinSprites->removeLastObject();
    //    }

    // 나부자 보이스 플래이하고
    playSoundNabuzaVoice(this->rollingCoinCount);  // 나부자 보이스
    playSoundDropCoins(this->rollingCoinCount);    // 동전소리

    // 점수 올리고
    int addGameScore = this->getAddingGameScore();
    this->addGameScore(addGameScore);

    // 터치 점수 올라가는 애니메이션
    CCPoint pt =
        CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());

    TouchScoreSprite *touchScore =
        TouchScoreSprite::createWithXY(pt.x, pt.y, addGameScore);

    if (addGameScore < 0) {
        touchScore->setColor(ccRED);
    }

    this->addChild(touchScore, LAYER_TOUCH_SCORE);
    touchScore->show();  // auto cleanup

    // 나부자 타임 올리고
    if (this->rollingCoinCount > 8) {
        this->setNabuzaTimeCount(this->nabuzaTimeCount + 1);
    } else {
        // 게이지 조정하고
        if (this->nabuzaTimeCount > 0) {
            bool isNabuzaTimeEnd =
                this->timeNabuzaGaugeSprite->addValueFromRollingCount(
                    this->rollingCoinCount);
            if (isNabuzaTimeEnd == true) {
                // 나부자타임 끝
                for (unsigned int i = 0; i < this->coinSprites->count(); i++) {
                    CoinSprite *coinSprite = dynamic_cast<CoinSprite *>(
                        this->coinSprites->objectAtIndex(i));
                    coinSprite->setIsNabuzaTime(false);
                }
                CCLog("NabuzaTime 끝");
                this->setNabuzaTimeCount(0);
            }
        } else {
            this->timeGoldGaugeSprite->addValue(this->rollingCoinCount);
        }
    }

    // 게임모드가 라스트 타임이면 1 줄이고 0이면 끝.
    if (this->kGameState == kGAMESTATE_LASTCHANCE) {
        this->lastChanceCount--;
        if (this->lastChanceCount == 0) {
            this->setGameState(kGAMESTATE_TIMEOVER);
        }
    }

    CCLog("TouchUp CoinSpriteCount : %u", this->coinSprites->count());
}

void GameScene::ccTouchMoved(CCTouch *touch, CCEvent *event) {
    if (this->isValidTouchBegan == false) {
        return;
    }

    //    CCTouch *touch  = (CCTouch*)*touches->begin();
    CCPoint pt =
        CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());

    intPoint tapXY = GetXYFromPoint(pt.x, pt.y);

    if (isValidXY(tapXY) == false) {
        return;
    }

    unsigned int kCurrentSelectingCoinSprite = GetKeyFromXY(tapXY.x, tapXY.y);

    CoinSprite *currentSelectingCoinSprite;

    for (unsigned int i = 0; i < this->coinSprites->count(); i++) {
        CoinSprite *enumCoinSprite =
            (CoinSprite *)this->coinSprites->objectAtIndex(i);
        if (enumCoinSprite->key == kCurrentSelectingCoinSprite) {
            currentSelectingCoinSprite = enumCoinSprite;
            break;
        }
    }

    if (currentSelectingCoinSprite->isRolling == true) {
        return;
    }

    if (currentSelectingCoinSprite->key ==
        this->previousSelectingCoinSprite->key) {
        return;
    }

    if (this->selectingCoinNumber != currentSelectingCoinSprite->number &&
        currentSelectingCoinSprite->number < 5) {
        return;
    }

    if (currentSelectingCoinSprite->number > 4 &&
        currentSelectingCoinSprite->mustTapCoinCount > this->rollingCoinCount) {
        return;
    }

    if (this->canRolling(tapXY) == false) {
        CCLog("Can not rolling");
        return;
    }

    // 여기부터 참
    this->coinsMatrix[tapXY.x][tapXY.y] = true;
    this->currentSelectingCoinSprite = currentSelectingCoinSprite;
    this->rollingCoinCount++;

    currentSelectingCoinSprite->setIsRolling(true);

    // 복주머니일 경우 rolling 시킨다.
    if (currentSelectingCoinSprite->number == 5) {  //  금색 골드 코인
        for (unsigned int i = 0; i < this->coinSprites->count(); i++) {
            CoinSprite *enumCoinSprite =
                (CoinSprite *)this->coinSprites->objectAtIndex(i);
            if (enumCoinSprite->number < 5) {
                if (GetYFromKey(enumCoinSprite->key) == tapXY.y) {
                    enumCoinSprite->setIsRolling(true);
                }
                if (GetXFromKey(enumCoinSprite->key) == tapXY.x) {
                    enumCoinSprite->setIsRolling(true);
                }
            }
        }
    }

    if (currentSelectingCoinSprite->number == 6) {  // 은색 골드 코인
        for (unsigned int i = 0; i < this->coinSprites->count(); i++) {
            CoinSprite *enumCoinSprite =
                (CoinSprite *)this->coinSprites->objectAtIndex(i);

            intPoint enumSpritePoint = GetXYFromKey(enumCoinSprite->key);
            if (enumCoinSprite->number < 5) {
                if ((abs(enumSpritePoint.y - tapXY.y) == 1 &&
                     abs(enumSpritePoint.x - tapXY.x) == 1) ||
                    (abs(enumSpritePoint.y - tapXY.y) == 1 &&
                     abs(enumSpritePoint.x - tapXY.x) == 0) ||
                    (abs(enumSpritePoint.y - tapXY.y) == 0 &&
                     abs(enumSpritePoint.x - tapXY.x) == 1)) {
                    enumCoinSprite->setIsRolling(true);
                }
            }
        }
    }

    // sound call

    playSoundJing(this->rollingCoinCount);

    if (this->rollingCoinCount > this->needCoinCountForNabuzaTime - 1) {
        for (unsigned int i = 0; i < this->coinSprites->count(); i++) {
            CoinSprite *enumCoinSprite =
                (CoinSprite *)this->coinSprites->objectAtIndex(i);
            if (enumCoinSprite->isRolling == true) {
                enumCoinSprite->activeNabuzaAction();
            }
        }
    }

    this->previousSelectingCoinSprite =
        this->currentSelectingCoinSprite;  // this code must be located in the
                                           // last line of ccTouchesMoved
                                           // method.
}

void GameScene::ccTouchCancelled(CCTouch *touch, CCEvent *pEvent) {
    CCLog("Cancel");
}

bool GameScene::ccTouchBegan(CCTouch *touch, CCEvent *pEvent) {
    if (this->isValidTouchBegan == true) {
        return false;
    }
    //    CCTouch *touch  = (CCTouch*)*touches->begin();
    CCPoint pt =
        CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
    intPoint tapXY = GetXYFromPoint(pt.x, pt.y);

    if (isValidXY(tapXY) == false) {
        this->isValidTouchBegan = false;
        return false;
    }

    unsigned int kCurrentSelectingCoinSprite = GetKeyFromXY(tapXY.x, tapXY.y);

    CCLog("Selecting key : %u", kCurrentSelectingCoinSprite);

    for (unsigned int i = 0; i < this->coinSprites->count(); i++) {
        CoinSprite *enumCoinSprite =
            (CoinSprite *)this->coinSprites->objectAtIndex(i);
        if (enumCoinSprite->key == kCurrentSelectingCoinSprite) {
            if (enumCoinSprite->mustTapCoinCount > 0) {
                this->isValidTouchBegan = false;
                return false;
            }
            this->previousSelectingCoinSprite =
                this->currentSelectingCoinSprite = enumCoinSprite;
            this->isValidTouchBegan = false;
            break;
        }
    }

    this->isValidTouchBegan = true;

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("CS001.mp3");
    this->rollingCoinCount = 1;

    this->currentSelectingCoinSprite->setIsRolling(true);
    this->selectingCoinNumber = this->currentSelectingCoinSprite->number;

    this->canSelecting = true;

    // set coinsMatrix
    resetCoinsMatrix();
    this->coinsMatrix[tapXY.x][tapXY.y] = true;

    return true;
}

bool GameScene::canRolling(
    intPoint currentPoint) {  // 8방향에서 rolling 되는 코인이 존재 && 그 코인이
                              // 같은 색깔

    int x;
    int y;

    for (unsigned int i = 0; i < 8; i++) {
        switch (i) {
            case 0:
                x = currentPoint.x;
                y = currentPoint.y + 1;
                break;
            case 1:
                x = currentPoint.x + 1;
                y = currentPoint.y + 1;
                break;
            case 2:
                x = currentPoint.x + 1;
                y = currentPoint.y;
                break;
            case 3:
                x = currentPoint.x + 1;
                y = currentPoint.y - 1;
                break;
            case 4:
                x = currentPoint.x;
                y = currentPoint.y - 1;
                break;
            case 5:
                x = currentPoint.x - 1;
                y = currentPoint.y - 1;
                break;
            case 6:
                x = currentPoint.x - 1;
                y = currentPoint.y;
                break;
            case 7:
                x = currentPoint.x - 1;
                y = currentPoint.y + 1;
                break;
        }
        CCLog("CurrentSelectingCoinNumber %u",
              this->currentSelectingCoinSprite->number);
        if (isValidXY(x, y) && this->coinsMatrix[x][y] == true &&
            (this->currentSelectingCoinSprite->number ==
                 this->selectingCoinNumber ||
             this->currentSelectingCoinSprite->number >
                 4)) {  // 12시 방향에서 시계방향으로 가자.
            return true;
        }
    }

    return false;
}

#pragma mark -
#pragma mark Functions

intPoint GetXYFromPoint(float x, float y) {
    intPoint point = {0, 0};

    float stdX = x - MATRIX_LEFT_MARGIN;
    float stdY = y - MATRIX_BOTTOM_MARGIN;

    point.x = (int)floor(stdX / MATRIX_CELL_WH);
    point.y = (int)floor(stdY / MATRIX_CELL_WH);

    return point;
}

unsigned int GetKeyFromXY(unsigned int x, unsigned int y) {
    return x + y * MATRIX_XY_COIN_COUNT;
}

intPoint GetXYFromKey(unsigned int key) {
    intPoint xy;
    xy.x = key % MATRIX_XY_COIN_COUNT;
    xy.y = int(key / MATRIX_XY_COIN_COUNT);
    return xy;
}

unsigned int GetRandomCoinNumber() {
    return (unsigned int)rand() % 5;
}

unsigned int GetRandomKey() {
    return (unsigned int)rand() % 49;
}

unsigned int GetXFromKey(unsigned int key) {
    return key % MATRIX_XY_COIN_COUNT;
}

unsigned int GetYFromKey(unsigned int key) {
    return int(key / MATRIX_XY_COIN_COUNT);
}

CCPoint GetCCPFromKey(unsigned int key) {
    int coordinationX = key % 7;
    int coordinationY = ceilf(key / 7);
    return ccp(coordinationX * MATRIX_CELL_WH + MATRIX_LEFT_MARGIN +
                   MATRIX_CELL_WH / 2,
               coordinationY * MATRIX_CELL_WH + MATRIX_BOTTOM_MARGIN +
                   MATRIX_CELL_WH / 2);
}

bool isValidXY(intPoint xy) {
    if (xy.x > -1 && xy.x < MATRIX_XY_COIN_COUNT && xy.y > -1 &&
        xy.y < MATRIX_XY_COIN_COUNT) {
        return true;
    }
    return false;
}

bool isValidXY(int x, int y) {
    if (x > -1 && x < MATRIX_XY_COIN_COUNT && y > -1 &&
        y < MATRIX_XY_COIN_COUNT) {
        return true;
    }
    return false;
}

bool isValidSelectingXY(intPoint previousPoint, intPoint currentPoint) {
    unsigned int previousNormalizedX = (previousPoint.x % MATRIX_XY_COIN_COUNT);
    unsigned int previousNormalizedY =
        (previousPoint.y % MATRIX_XY_COIN_COUNT);  // 0 - 6
    unsigned int currentNormalizedX = (currentPoint.x % MATRIX_XY_COIN_COUNT);
    unsigned int currentNormalizedY =
        (currentPoint.y % MATRIX_XY_COIN_COUNT);  // 0 - 6

    if (abs(previousNormalizedX - currentNormalizedX) == 1 &&
        abs(previousNormalizedY - currentNormalizedY) == 1) {
        CCLog("is valid");
        return true;
    }
    CCLog("is not valid");
    return false;
}

bool isValidSelectingXY(unsigned int kPreviousPoint,
                        unsigned int kCurrentPoint) {
    intPoint previousXY = GetXYFromKey(kPreviousPoint);
    intPoint currentXY = GetXYFromKey(kCurrentPoint);
    unsigned int previousNormalizedX = (previousXY.x % MATRIX_XY_COIN_COUNT);
    unsigned int previousNormalizedY =
        (previousXY.y % MATRIX_XY_COIN_COUNT);  // 0 - 6
    unsigned int currentNormalizedX = (currentXY.x % MATRIX_XY_COIN_COUNT);
    unsigned int currentNormalizedY =
        (currentXY.y % MATRIX_XY_COIN_COUNT);  // 0 - 6

    if (abs(previousNormalizedX - currentNormalizedX) < 2 &&
        abs(previousNormalizedY - currentNormalizedY) < 2) {
        CCLog("is valid");
        return true;
    }
    CCLog("is not valid");
    return false;
}

int getMultiplyConstant(unsigned int coinCount) {
    CCAssert(coinCount > 1, "CoinCount must over 1");

    unsigned int key = (coinCount > 19) ? 19 : coinCount - 2;
    int constants[18] = {-20, 6,  7,  8,  9,  10, 11, 13, 15,
                         17,  19, 21, 24, 27, 30, 33, 36, 40};

    return constants[key];
}

#pragma mark -
#pragma mark Sound Functions
void playSoundJing(unsigned int rollingCoinCount) {
    std::stringstream ss;
    ss << "CS0";
    if (rollingCoinCount < 10) {
        ss << "0" << rollingCoinCount;
    } else if (rollingCoinCount < 16) {
        ss << rollingCoinCount;
    } else {
        ss << "15";
    }
    ss << ".mp3";

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
        ss.str().c_str());
}

void playSoundNabuzaTime() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("JN001.mp3");
}

void playSoundNabuzaVoice(unsigned int rollingCoinCount) {
    if (rollingCoinCount < 2) {
        return;
    }

    unsigned int soundMap[] = {1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7};

    unsigned int soundMapKey;

    if (rollingCoinCount - 2 > 12) {
        soundMapKey = 12;
    } else {
        soundMapKey = rollingCoinCount - 2;
    }

    std::stringstream ss;
    ss << "GS00";

    ss << soundMap[soundMapKey];
    ss << ".mp3";

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
        ss.str().c_str());
}

void playSoundGameReady() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("GA001.mp3");
}

void playSoundGameStart() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("GA002.mp3");
}

void playSoundTimeOver() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("GA003.mp3");
}

void playSoundLastChange() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("GA004.mp3");
}

void playSoundDropCoins(unsigned int coinCount) {
    if (coinCount < 4) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
            "CD001.mp3");
        return;
    }

    if (coinCount < 9) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
            "CD002.mp3");
        return;
    }

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("CD003.mp3");
    return;
}

void playSoundBeTimeGoldSprite() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("BZ001.mp3");
    return;
}

void playBgGamePlay() {
    CCLog("Play Bg Game Play");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
        "BG004.mp3", true);
    return;
}

void playBgGameNabuzaPlay() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
        "BG003.mp3", true);
    return;
}

void stopBgGamePlay() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(
        false);
}

#pragma mark -
#pragma mark Callback Methods For Button

void GameScene::pauseCallback(CCObject *pSender) {
    CCDirector::sharedDirector()->pause();

    PauseLayer *pauseLayer = PauseLayer::create();
    this->addChild(pauseLayer, LAYER_MENU);
}

void GameScene::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
        this, 0, true);
}

GameScene::~GameScene() {
    this->coinSprites->release();
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
};