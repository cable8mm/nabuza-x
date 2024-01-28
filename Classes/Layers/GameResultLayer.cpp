//
//  GameResultLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 7/2/13.
//
//

#include "GameResultLayer.h"

#include "ATUtil.h"
#include "AlertTitleSprite.h"
#include "AnytaleHTTP.h"
#include "ButtonSprite.h"
#include "SimpleAudioEngine.h"
#include "UserStorage.h"

// TAGS
#define TAG_GAME_RESULT_SCORE 100000
#define TAG_CHARACTER_SPRITE 100001

// LAYERS
#define LAYER_GAME_RESULT_SCORE 100000

GameResultLayer *GameResultLayer::createWithGameScore(int gameScore) {
    GameResultLayer *pobSprite = new GameResultLayer;

    pobSprite->gameScore = gameScore;

    if (pobSprite && pobSprite->init()) {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

bool GameResultLayer::init() {
    //////////////////////////////
    // 1. super init first
    if (!CCLayerColor::initWithColor(ccc4(0., 0., 0., 200.)))  // RGBA
    {
        return false;
    }

    return true;
}

void GameResultLayer::onEnter() {
    this->setTouchEnabled(true);

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    // BG
    CCSprite *bgRankingSprite = CCSprite::create("title_full_alert.jpg");
    bgRankingSprite->setPosition(
        ccp(visibleSize.width / 2., visibleSize.height / 2.));
    this->addChild(bgRankingSprite);

    // TITLE
    AlertTitleSprite *alertTitleSprite =
        AlertTitleSprite::createWithItemKey(kGAMEALERTTITLE_GAMERESULT);
    this->addChild(alertTitleSprite);

    // 스코어와 롤 배경
    CCTexture2D *gameResultScoreTexture =
        CCTextureCache::sharedTextureCache()->addImage("gameresult_score.png");
    CCSprite *gameResultScoreSprite = CCSprite::createWithTexture(
        gameResultScoreTexture, CCRect(0., 0., 400., 310.));
    gameResultScoreSprite->setPosition(
        ccp(visibleSize.width / 2., 800. - 264. - 155.));
    this->addChild(gameResultScoreSprite);

    // 캐릭터
    CCTexture2D *characterTexture =
        CCTextureCache::sharedTextureCache()->addImage("character.png");
    CCSprite *characterSprite = CCSprite::createWithTexture(
        characterTexture, CCRect(0., 0., 200., 250.));
    characterSprite->setPosition(ccp(120., 800. - 314. - 125.));
    characterSprite->setTag(TAG_CHARACTER_SPRITE);
    this->addChild(characterSprite);

    // 레벨 보너스
    CCString *ownGoldCount = UserStorage::sharedUserStorage()->getOwnGold();

    LevelInformation::sharedLevelInformation()->setting(
        ownGoldCount->intValue());
    std::stringstream strLabelLevelBonus;
    strLabelLevelBonus << "레벨 보너스 +";
    std::stringstream ssLevelBonus;
    ssLevelBonus << ((
        int)(LevelInformation::sharedLevelInformation()->getLevelBonus() *
             0.01 * (int)this->gameScore));
    std::string sLevelBonus = ssLevelBonus.str();
    ATUtil::insert_separator(sLevelBonus);
    strLabelLevelBonus << sLevelBonus.c_str();

    //    strLevelBonus += ATUtil::insert_separator();

    CCLabelTTF *lbGameResultLevelBonus = CCLabelTTF::create(
        strLabelLevelBonus.str().c_str(), "JejuGothic.ttf", 20);
    lbGameResultLevelBonus->setPosition(
        ccp(visibleSize.width / 2., 800. - 150. - 135.));
    lbGameResultLevelBonus->setColor(ccBLACK);
    lbGameResultLevelBonus->setHorizontalAlignment(kCCTextAlignmentCenter);
    this->addChild(lbGameResultLevelBonus);

    // 다음 레벨까지
    int needGoldCount = LevelInformation::sharedLevelInformation()
                            ->getNeedGoldCountForNextLevel();
    std::stringstream needGoldCountStream;
    needGoldCountStream << needGoldCount;
    std::string needGoldCountString = needGoldCountStream.str();
    ATUtil::insert_separator(needGoldCountString);
    std::stringstream strLabelNeedGoldCountForNextLevel;
    strLabelNeedGoldCountForNextLevel << "다음 레벨까지 ";
    strLabelNeedGoldCountForNextLevel << needGoldCountString;
    strLabelNeedGoldCountForNextLevel << "골드";

    CCLabelTTF *lbGameResultNextLevel = CCLabelTTF::create(
        strLabelNeedGoldCountForNextLevel.str().c_str(), "JejuGothic.ttf", 18);
    lbGameResultNextLevel->setPosition(ccp(426., 800. - 458.));
    lbGameResultNextLevel->setColor(ccBLACK);
    lbGameResultNextLevel->setAnchorPoint(ccp(1., .5));
    this->addChild(lbGameResultNextLevel);

    // 최고 점수
    std::string strLabelUserHighscore =
        UserStorage::sharedUserStorage()->getHighscore()->getCString();
    ATUtil::insert_separator(strLabelUserHighscore);
    std::stringstream ssLabelUserHighscore;
    ssLabelUserHighscore << "최고 점수 " << strLabelUserHighscore;

    CCLabelTTF *lbGameResultHighScore = CCLabelTTF::create(
        ssLabelUserHighscore.str().c_str(), "JejuGothic.ttf", 20);
    lbGameResultHighScore->setPosition(ccp(426., 800. - 545.));
    lbGameResultHighScore->setColor(ccBLACK);
    lbGameResultHighScore->setAnchorPoint(ccp(1., .5));
    this->addChild(lbGameResultHighScore);

    // 닫기 버튼
    ButtonSprite *closingButtonSprite =
        ButtonSprite::createWithItemKey(kGAMEBUTTON_CLOSE);
    ButtonSprite *closingButtonSpriteTapped =
        ButtonSprite::createWithItemKey(kGAMEBUTTON_CLOSE);
    closingButtonSpriteTapped->setScale(1.2);
    closingButtonSpriteTapped->setPosition(
        ccp(closingButtonSprite->getPositionX() - 20.,
            closingButtonSprite->getPositionY() - 6.));
    //    btnStartSelectedSprite->setPosition(ccp(btnStartSprite->getPositionX()-29.,
    //    btnStartSprite->getPositionY()-10.));

    CCMenuItemSprite *closeButtonItem =
        CCMenuItemSprite::create(closingButtonSprite, closingButtonSpriteTapped,
                                 this, menu_selector(GameResultLayer::close));
    CCMenu *menu = CCMenu::create(closeButtonItem, NULL);
    menu->setPosition(ccp(visibleSize.width / 2, 800. - 648. - 44.));

    this->addChild(menu);

    this->gameTickScore = 0;
    this->isPlayCoinCount = false;
    this->tickTerm = (unsigned int)(this->gameScore / 100);

    // 점수
    CCLabelBMFont *lbGameResultScore =
        CCLabelBMFont::create("0", "fontopo30brown.fnt");
    lbGameResultScore->setPosition(
        ccp(visibleSize.width / 2., 800. - 50. - 190.));
    lbGameResultScore->setScale(2.);
    lbGameResultScore->setAlignment(kCCTextAlignmentCenter);
    this->addChild(lbGameResultScore, LAYER_GAME_RESULT_SCORE,
                   TAG_GAME_RESULT_SCORE);

    std::stringstream ss;
    ss << "&highscore=" << this->gameScore;

    AnytaleHTTP::getUrlWithToken("/players/finished_game2", ss.str().c_str());

    // 플래이어 등록.
    //    AnytaleHTTP::onHttpRequesting(this,
    //    callfuncND_selector(LaunchingScene::onHttpRequestCompleted),
    //    "/players/regist", "", "HTTP_PLAYERS_REGIST");

    AnytaleHTTP::onHttpRequesting(
        this, callfuncND_selector(GameResultLayer::onHttpRequestCompleted),
        "/players/finished_game2", ss.str().c_str(), "PLAYERS_FINISHED_GAME2");

    this->setGameResultState(kGAMERESULTSTATE_READY);

    CCLayerColor::onEnter();
}

#pragma mark -
#pragma mark HttpRequest Callback

void GameResultLayer::onHttpRequestCompleted(CCHttpClient *sender,
                                             CCHttpResponse *response) {
    Json::Value root;

    int error;
    AnytaleHTTP::validateResponse(response, root, error);

    if (error != 0) {
        CCLog("AuthStorage json parse error");
        return;
    }

    // 플래이어 등록 & 플래이어 정보 업데이트
    if (strcmp(response->getHttpRequest()->getTag(),
               "PLAYERS_FINISHED_GAME2") == 0) {
        /*
         {"code":0,"message":"OK","result":{"is_regist":false}}
         OR
         {"code":0,"message":"OK","result":{"is_regist":true,"player_info":{"Player":{"nickname":"Player#32868","id":"32868"}}}}
         */

        //        bool isRegist   = root["result"].get("is_regist",
        //        false).asBool();
        CCLabelBMFont *lbGameResultScore = dynamic_cast<CCLabelBMFont *>(
            this->getChildByTag(TAG_GAME_RESULT_SCORE));

        lbGameResultScore->runAction(CCRepeatForever::create(CCSequence::create(
            CCDelayTime::create(0.03),
            CCCallFunc::create(this,
                               callfunc_selector(GameResultLayer::changeScore)),
            NULL)));
    }

    return;
}

void GameResultLayer::changeScore() {
    CCLabelBMFont *lbGameResultScore = dynamic_cast<CCLabelBMFont *>(
        this->getChildByTag(TAG_GAME_RESULT_SCORE));

    this->gameTickScore += this->tickTerm;

    if ((this->gameTickScore > this->gameScore ||
         this->gameTickScore == this->gameScore) &&
        this->kGameResultState == kGAMERESULTSTATE_ADD_COINCOUNT) {
        this->gameTickScore = this->gameScore;
        lbGameResultScore->stopAllActions();
        this->setGameResultState(kGAMERESULTSTATE_DISPLAY_GOLD);
    }

    std::stringstream newScore;
    newScore << this->gameTickScore;

    std::string s;
    s = newScore.str();

    ATUtil::insert_separator(s);

    lbGameResultScore->setString(s.c_str());

    if (this->isPlayCoinCount == false) {
        playSoundCoinCount();
        this->isPlayCoinCount = true;
    }
}

void GameResultLayer::setGameResultState(eGameResultStats kGameResultState) {
    this->kGameResultState = kGameResultState;

    switch (kGameResultState) {
        case kGAMERESULTSTATE_READY: {
            CCLog("kGAMERESULTSTATE_READY");
            CCLabelBMFont *lbGameResultScore = dynamic_cast<CCLabelBMFont *>(
                this->getChildByTag(TAG_GAME_RESULT_SCORE));

            this->setGameResultState(kGAMERESULTSTATE_ADD_COINCOUNT);

        } break;
        case kGAMERESULTSTATE_ADD_COINCOUNT: {
            CCLog("kGAMERESULTSTATE_ADD_COINCOUNT");

        } break;
        case kGAMERESULTSTATE_DISPLAY_GOLD: {
            CCLog("kGAMERESULTSTATE_DISPLAY_GOLD");
            CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

            // 추가 골드
            std::stringstream ssGameResultGoldBonus;
            ssGameResultGoldBonus << "+" << (int)(this->gameScore / 10000);
            std::string strGameResultGoldBonus = ssGameResultGoldBonus.str();
            ATUtil::insert_separator(strGameResultGoldBonus);
            CCLabelBMFont *lbGameResultGoldBonus = CCLabelBMFont::create(
                strGameResultGoldBonus.c_str(), "rst_score.fnt");
            lbGameResultGoldBonus->setPosition(ccp(334., 800. - 381. + 600.));
            lbGameResultGoldBonus->setAlignment(kCCTextAlignmentCenter);
            this->addChild(lbGameResultGoldBonus);

            lbGameResultGoldBonus->runAction(CCEaseElasticOut::create(
                CCMoveBy::create(.8, ccp(0., -600.)), .3));

            // highscore 갱신되면 테두리 나타남.
            if (true) {
                // 테두리
                CCTexture2D *gameResultTexture =
                    CCTextureCache::sharedTextureCache()->addImage(
                        "gameresult_best.png");
                CCSprite *gameResultSprite = CCSprite::createWithTexture(
                    gameResultTexture, CCRect(0., 0., 480., 551.));
                gameResultSprite->setPosition(
                    ccp(visibleSize.width / 2., 800. - 77. - 275.5));
                this->addChild(gameResultSprite);

                CCArray *frames = new CCArray;
                for (unsigned int i = 0; i < 2; i++) {
                    CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(
                        gameResultTexture, CCRect(480. * i, 0, 480., 551.));
                    frames->addObject(frame);
                }
                CCAnimation *animation =
                    CCAnimation::createWithSpriteFrames(frames, .2);
                CCAnimate *animate = CCAnimate::create(animation);
                gameResultSprite->runAction(CCRepeatForever::create(animate));

                CCSprite *characterSprite = (CCSprite *)this->getChildByTag(
                    TAG_CHARACTER_SPRITE);  // rect 200.,250.

                CCArray *characterFrames = new CCArray;
                for (unsigned int i = 0; i < 4; i++) {
                    CCSpriteFrame *characterFrame =
                        CCSpriteFrame::createWithTexture(
                            characterSprite->getTexture(),
                            CCRect(200. * (i % 2), 250. + 250. * floorf(i / 2),
                                   200., 250.));
                    characterFrames->addObject(characterFrame);
                }
                CCAnimation *characterAnimation =
                    CCAnimation::createWithSpriteFrames(characterFrames, .2);
                CCAnimate *characterAnimate =
                    CCAnimate::create(characterAnimation);
                characterSprite->runAction(
                    CCRepeatForever::create(characterAnimate));
            }
        } break;
        case kGAMERESULTSTATE_DONE: {
            CCLog("kGAMERESULTSTATE_DONE");
            CCNotificationCenter::sharedNotificationCenter()->postNotification(
                "NABUZA_END_GAMERESULT_NOTIFICATION");
            this->stopAllActions();
            this->removeFromParentAndCleanup(true);
        } break;
    }
}

void GameResultLayer::setGameScore(unsigned int v) {
    this->gameScore = v;
}

void GameResultLayer::close() {
    this->setGameResultState(kGAMERESULTSTATE_DONE);
}

void playSoundCoinCount() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
        "CU001.mp3");  // 3초임
}

bool GameResultLayer::ccTouchBegan(CCTouch *touch, CCEvent *pEvent) {
    return true;
}

void GameResultLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
        this, 0, true);
}