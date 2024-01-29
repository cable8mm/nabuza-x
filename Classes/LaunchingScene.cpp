#include "LaunchingScene.h"

#include "BaseScene.h"
#include "BuddyStorage.h"
#include "Layers/BuyJadeLayer.h"
#include "Layers/GameLoadingLayer.h"
#include "Networks/AnytaleHTTP.h"
#include "SimpleAudioEngine.h"
#include "Storages/AuthStorage.h"
#include "UserStorage.h"
#include "Utilities/ATUtil.h"

// For Testing
#include "GameScene.h"
#include "Layers/BuddyInfoLayer.h"
#include "Layers/CouponLayer.h"
#include "Layers/GameLoadingLayer.h"
#include "Layers/WebViewLayer.h"

#define TAG_MESSAGE_FOR_PLAYER 1000

CCScene *LaunchingScene::scene() {
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    LaunchingScene *layer = LaunchingScene::create();

    // enable Touch
    layer->setTouchEnabled(true);

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LaunchingScene::init() {
    //////////////////////////////
    // 1. super init first
    if (!CCLayer::init()) {
        return false;
    }

    this->isReady = false;

    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        this, callfuncO_selector(LaunchingScene::onHttpGetAccessTokenCompleted),
        "ACCESS_TOKEN_GET_NOTIFICATION", NULL);

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    CCSprite *bgSprite = CCSprite::create("default_bg.jpg");
    bgSprite->setPosition(ccp(visibleSize.width / 2., visibleSize.height / 2));
    this->addChild(bgSprite);

    CCSprite *titleSprite = CCSprite::create("default_logo.png");
    titleSprite->setPosition(ccp(visibleSize.width / 2, 800. - 115. - 22.5));
    this->addChild(titleSprite);

    CCTexture2D *whitelightTexture =
        CCTextureCache::sharedTextureCache()->addImage(
            "default_whitelight.png");

    CCSprite *whitelightSprite1 = CCSprite::createWithTexture(
        whitelightTexture, CCRect(0., 0., 64., 64.));
    whitelightSprite1->setPosition(ccp(364. + 32., 800. - 107. - 32.));
    this->addChild(whitelightSprite1);

    CCSprite *whitelightSprite2 = CCSprite::createWithTexture(
        whitelightTexture, CCRect(0., 0., 64., 64.));
    whitelightSprite2->setPosition(ccp(99. + 32., 800. - 101. - 32.));
    this->addChild(whitelightSprite2);

    CCSprite *whitelightSprite3 = CCSprite::createWithTexture(
        whitelightTexture, CCRect(0., 0., 64., 64.));
    whitelightSprite3->setPosition(ccp(259. + 32., 800. - 93. - 32.));
    this->addChild(whitelightSprite3);

    CCSprite *whitelightSprite4 = CCSprite::createWithTexture(
        whitelightTexture, CCRect(0., 0., 64., 64.));
    whitelightSprite4->setPosition(ccp(1. + 32., 800. - 106. - 32.));
    this->addChild(whitelightSprite4);

    CCArray *whitelightFrames = new CCArray;
    for (unsigned int i = 0; i < 3; i++) {
        CCSpriteFrame *whitelightFrame = CCSpriteFrame::createWithTexture(
            whitelightTexture, CCRect(0., 64. * i, 64., 64.));
        whitelightFrames->addObject(whitelightFrame);
    }

    CCAnimation *whitelightAnimation =
        CCAnimation::createWithSpriteFrames(whitelightFrames, .2);
    CCAnimationCache::sharedAnimationCache()->addAnimation(
        whitelightAnimation, "whitelight_animation");

    CCAnimation *whitelightAnimation1 =
        CCAnimationCache::sharedAnimationCache()->animationByName(
            "whitelight_animation");
    CCAnimation *whitelightAnimation2 =
        CCAnimationCache::sharedAnimationCache()->animationByName(
            "whitelight_animation");
    CCAnimation *whitelightAnimation3 =
        CCAnimationCache::sharedAnimationCache()->animationByName(
            "whitelight_animation");
    CCAnimation *whitelightAnimation4 =
        CCAnimationCache::sharedAnimationCache()->animationByName(
            "whitelight_animation");

    whitelightSprite1->runAction(
        CCRepeatForever::create(CCAnimate::create(whitelightAnimation1)));
    whitelightSprite2->runAction(
        CCRepeatForever::create(CCAnimate::create(whitelightAnimation2)));
    whitelightSprite3->runAction(
        CCRepeatForever::create(CCAnimate::create(whitelightAnimation3)));
    whitelightSprite4->runAction(
        CCRepeatForever::create(CCAnimate::create(whitelightAnimation4)));

    CCTexture2D *lemonlightTexture =
        CCTextureCache::sharedTextureCache()->addImage(
            "default_lemonlight.png");

    CCSprite *lemonlightSprite1 = CCSprite::createWithTexture(
        lemonlightTexture, CCRect(0., 0., 64., 64.));
    lemonlightSprite1->setPosition(ccp(408. + 32., 800. - 131. - 32.));
    this->addChild(lemonlightSprite1);

    CCSprite *lemonlightSprite2 = CCSprite::createWithTexture(
        lemonlightTexture, CCRect(0., 0., 64., 64.));
    lemonlightSprite2->setPosition(ccp(27. + 32., 800. - 131. - 32.));
    this->addChild(lemonlightSprite2);

    CCSprite *lemonlightSprite3 = CCSprite::createWithTexture(
        lemonlightTexture, CCRect(0., 0., 64., 64.));
    lemonlightSprite3->setPosition(ccp(259. + 32., 800. - 137. - 32.));
    this->addChild(lemonlightSprite3);

    CCArray *lemonlightFrames = new CCArray;
    for (unsigned int i = 0; i < 3; i++) {
        CCSpriteFrame *lemonlightFrame = CCSpriteFrame::createWithTexture(
            lemonlightTexture, CCRect(0., 64. * i, 64., 64.));
        lemonlightFrames->addObject(lemonlightFrame);
    }

    CCAnimation *lemonlightAnimation =
        CCAnimation::createWithSpriteFrames(lemonlightFrames, .2);
    CCAnimationCache::sharedAnimationCache()->addAnimation(
        lemonlightAnimation, "lemonlight_animation");

    CCAnimation *lemonlightAnimation1 =
        CCAnimationCache::sharedAnimationCache()->animationByName(
            "lemonlight_animation");
    CCAnimation *lemonlightAnimation2 =
        CCAnimationCache::sharedAnimationCache()->animationByName(
            "lemonlight_animation");
    CCAnimation *lemonlightAnimation3 =
        CCAnimationCache::sharedAnimationCache()->animationByName(
            "lemonlight_animation");

    lemonlightSprite1->runAction(
        CCRepeatForever::create(CCAnimate::create(lemonlightAnimation1)));
    lemonlightSprite2->runAction(
        CCRepeatForever::create(CCAnimate::create(lemonlightAnimation2)));
    lemonlightSprite3->runAction(
        CCRepeatForever::create(CCAnimate::create(lemonlightAnimation3)));

    this->preload();

    CCTexture2D *nabuzaTexture =
        CCTextureCache::sharedTextureCache()->addImage("default_nabuza.png");
    CCSprite *nabuzaSprite =
        CCSprite::createWithTexture(nabuzaTexture, CCRect(0., 0., 478., 468.));
    nabuzaSprite->setPosition(ccp(visibleSize.width / 2, 800. - 275. - 234.));
    this->addChild(nabuzaSprite);

    CCArray *nabuzaFrames = new CCArray;
    for (unsigned int i = 0; i < 4; i++) {
        CCSpriteFrame *nabuzaFrame = CCSpriteFrame::createWithTexture(
            nabuzaTexture, CCRect(0., 468. * i, 478., 468.));
        nabuzaFrames->addObject(nabuzaFrame);
    }

    nabuzaSprite->runAction(CCRepeatForever::create(CCAnimate::create(
        CCAnimation::createWithSpriteFrames(nabuzaFrames, .2))));
    // 아이템 선택 화면
    CCTexture2D *itemChoosedTexture =
        CCTextureCache::sharedTextureCache()->addImage("item_box_btn.png");

    CCLabelTTF *launchingMessage = CCLabelTTF::create(
        "서버에 연결 중 입니다.", "Arial Rounded MT Bold", 25);
    launchingMessage->setPosition(
        ccp(visibleSize.width / 2., visibleSize.height / 2. - 300.));
    launchingMessage->setScale(1.);
    launchingMessage->setTag(TAG_MESSAGE_FOR_PLAYER);
    this->addChild(launchingMessage);

    launchingMessage->runAction(CCRepeatForever::create(CCSequence::create(
        CCScaleTo::create(.5, 1.2), CCScaleTo::create(.5, .9), NULL)));

    // AccessToken 세팅
    AuthStorage::sharedAuthStorage()->setAccessToken();

    // GameLoadingLayer called / NABUZA_LASTCHANCE_NOTIFICATION

    return true;
}

#pragma mark -
#pragma mark HttpRequest Callback

void LaunchingScene::onHttpRequestCompleted(CCHttpClient *sender,
                                            CCHttpResponse *response) {
    Json::Value root;
    Json::Reader reader;

    std::vector<char> *rawData = response->getResponseData();
    std::string ss(rawData->begin(), rawData->end());

    bool bIsParsed = reader.parse(ss, root, false);

    // 플래이어 등록 & 플래이어 정보 업데이트
    if (strcmp(response->getHttpRequest()->getTag(), "HTTP_PLAYERS_REGIST") ==
        0) {
        UserStorage::sharedUserStorage()->setNickname(
            root["result"]["player_info"]["Player"]
                .get("nickname", "")
                .asString());
        UserStorage::sharedUserStorage()->setOwnJadeCount(
            root["result"]["player_info"]["Player"]
                .get("own_jade_count", 0)
                .asInt());
        UserStorage::sharedUserStorage()->setOwnGold(
            root["result"]["player_info"]["Player"].get("own_gold", 0).asInt());
        UserStorage::sharedUserStorage()->setCardCount(
            root["result"]["player_info"]["Player"]
                .get("invitation_count", 0)
                .asInt());
        //        UserStorage::sharedUserStorage()->setRemainSeconds(root["result"]["player_info"]["Player"].get("remain_seconds",
        //        0).asInt());
        UserStorage::sharedUserStorage()->setLastLevel(
            root["result"]["player_info"]["Player"]
                .get("last_level", 0)
                .asInt());
        UserStorage::sharedUserStorage()->setPlayerId(
            root["result"]["player_info"]["Player"].get("id", 0).asInt());

        AnytaleHTTP::onHttpRequesting(
            this, callfuncND_selector(LaunchingScene::onHttpRequestCompleted),
            "/players/view2", "", "PLAYERS_VIEW2");
    }

    // 게임 시작을 서버에 알림
    if (strcmp(response->getHttpRequest()->getTag(), "PLAYERS_VIEW2") == 0) {
        // 랭킹 테이블

        const Json::Value rankings = root["result"];
        for (int index = 0; index < rankings.size(); index++) {
            BuddyModel *buddy = new BuddyModel;
            buddy->idx = rankings[index]["Player"]["id"].asInt();
            buddy->rank = rankings[index]["Player"]["rank"].asInt();
            buddy->highscore = rankings[index]["Player"]["highscore"].asInt();
            buddy->nickname = rankings[index]["Player"]["nickname"].asString();
            buddy->ownGoldCount = rankings[index]["Player"]["own_gold"].asInt();
            buddy->isMe = false;
            buddy->isInvitationNotification =
                rankings[index]["Player"]["is_invitation_notification"]
                    .asBool();
            buddy->weeklyHighscore =
                rankings[index]["Player"]["weekly_highscore"].asInt();
            buddy->ownGoldMedalCount =
                rankings[index]["Player"]["gold_medal_count"].asInt();
            buddy->ownSilverMedalCount =
                rankings[index]["Player"]["silver_medal_count"].asInt();
            buddy->ownBronzeMedalCount =
                rankings[index]["Player"]["bronze_medal_count"].asInt();
            BuddyStorage::sharedBuddyStorage()->buddies->addObject(buddy);
        }

        CCLabelTTF *launchingMessage =
            (CCLabelTTF *)this->getChildByTag(TAG_MESSAGE_FOR_PLAYER);
        launchingMessage->setString("화면을 터치해 주세요.");

        this->isReady = true;
    }

    return;
}

#pragma mark -
#pragma mark Notification Callback

// Active AccessToken을 받음.
// 후에 플래이어 등록이 진행됨.
void LaunchingScene::onHttpGetAccessTokenCompleted(CCObject *obj) {
    // 플래이어 등록.
    AnytaleHTTP::onHttpRequesting(
        this, callfuncND_selector(LaunchingScene::onHttpRequestCompleted),
        "/players/regist", "", "HTTP_PLAYERS_REGIST");
}

#pragma mark -
#pragma mark Touch Events Callback
bool LaunchingScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    return true;
}

void LaunchingScene::ccTouchEnded(CCTouch *touch, CCEvent *event) {
    if (this->isReady) {
        CCDirector::sharedDirector()->replaceScene(BaseScene::scene());
    }
}

void LaunchingScene::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
        this, 0, true);
}

LaunchingScene::~LaunchingScene() {
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
};

void LaunchingScene::preload() {
    // Image Preload
    CCTexture2D *coinTexture =
        CCTextureCache::sharedTextureCache()->addImage("coin_effect.png");

    // Coin Effect Cache
    CCTexture2D *coinEffectTexture =
        CCTextureCache::sharedTextureCache()->addImage(
            "coin_all_star_effect.png");

    CCTexture2D *timeGoldTexture =
        CCTextureCache::sharedTextureCache()->addImage("time_gold.png");

    CCArray *coinWhiteEffectFrames = new CCArray;
    CCArray *coinYellowEffectFrames = new CCArray;
    for (unsigned int i = 0; i < 3; i++) {
        CCSpriteFrame *coinWhiteEffectFrame = CCSpriteFrame::createWithTexture(
            coinEffectTexture, CCRect(156. * i, 0., 156., 156.));
        coinWhiteEffectFrames->addObject(coinWhiteEffectFrame);
        CCSpriteFrame *coinYellowEffectFrame = CCSpriteFrame::createWithTexture(
            coinEffectTexture, CCRect(156. * i, 156., 156., 156.));
        coinYellowEffectFrames->addObject(coinYellowEffectFrame);
    }

    CCAnimation *coinWhiteEffectAnimation =
        CCAnimation::createWithSpriteFrames(coinWhiteEffectFrames, .1);
    CCAnimation *coinYellowEffectAnimation =
        CCAnimation::createWithSpriteFrames(coinYellowEffectFrames, .1);

    CCAnimationCache::sharedAnimationCache()->addAnimation(
        coinWhiteEffectAnimation, "coin_white_effect_animation");
    CCAnimationCache::sharedAnimationCache()->addAnimation(
        coinYellowEffectAnimation, "coin_yellow_effect_animation");

    CCArray *timeGoldWhiteEffectFrames = new CCArray;
    CCArray *timeGoldYellowEffectFrames = new CCArray;

    for (unsigned int i = 0; i < 5; i++) {
        CCSpriteFrame *timeGoldWhiteEffectFrame =
            CCSpriteFrame::createWithTexture(timeGoldTexture,
                                             CCRect(62., 61. * i, 62., 61.));
        timeGoldWhiteEffectFrames->addObject(timeGoldWhiteEffectFrame);
        CCSpriteFrame *timeGoldYellowEffectFrame =
            CCSpriteFrame::createWithTexture(timeGoldTexture,
                                             CCRect(0., 61. * i, 62., 61.));
        timeGoldYellowEffectFrames->addObject(timeGoldYellowEffectFrame);
    }

    CCAnimation *timeGoldWhiteEffectAnimation =
        CCAnimation::createWithSpriteFrames(timeGoldWhiteEffectFrames, .08);
    CCAnimation *timeGoldYellowEffectAnimation =
        CCAnimation::createWithSpriteFrames(timeGoldYellowEffectFrames, .08);

    CCAnimationCache::sharedAnimationCache()->addAnimation(
        timeGoldWhiteEffectAnimation, "time_gold_white_effect_animation");
    CCAnimationCache::sharedAnimationCache()->addAnimation(
        timeGoldYellowEffectAnimation, "time_gold_yellow_effect_animation");

    for (unsigned int i = 0; i < 7; i++) {
        //        CCArray *coinFrames = CCArray::create();
        CCArray *coinFrames = new CCArray;
        unsigned int frameCount = (i < 5) ? 7 : 6;
        for (unsigned int j = 0; j < frameCount; j++) {
            CCSpriteFrame *coinFrame = CCSpriteFrame::createWithTexture(
                coinTexture, CCRect(MATRIX_COIN_WH * i, MATRIX_COIN_WH * j,
                                    MATRIX_COIN_WH, MATRIX_COIN_WH));
            coinFrames->addObject(coinFrame);
        }

        CCAnimation *coinAnimation = CCAnimation::createWithSpriteFrames(
            coinFrames, .08);  // 동전 회전 속도

        int n;
        char animationCacheName[17];
        n = sprintf(animationCacheName, "coin_animation_%u", i);
        CCAnimationCache::sharedAnimationCache()->addAnimation(
            coinAnimation, animationCacheName);
    }

    // NabuzaTime Animation - Coin
    for (unsigned int i = 0; i < 7; i++) {
        CCArray *nabuzaCoinFrames = new CCArray;
        for (unsigned int j = 0; j < 3; j++) {
            CCSpriteFrame *coinFrame = CCSpriteFrame::createWithTexture(
                coinTexture,
                CCRect(MATRIX_COIN_WH * i, MATRIX_COIN_WH * (j + 1),
                       MATRIX_COIN_WH, MATRIX_COIN_WH));
            nabuzaCoinFrames->addObject(coinFrame);
        }

        CCAnimation *nabuzaCoinAnimation = CCAnimation::createWithSpriteFrames(
            nabuzaCoinFrames, .04);  // 나부자 동전 회전 속도

        int n;
        char nabuzaAnimationCacheName[19];
        n = sprintf(nabuzaAnimationCacheName, "nabuza_animation_%u", i);
        CCAnimationCache::sharedAnimationCache()->addAnimation(
            nabuzaCoinAnimation, nabuzaAnimationCacheName);

        // unnabuza

        CCArray *unNabuzaCoinFrames = new CCArray;
        for (unsigned int j = 0; j < 2; j++) {
            CCSpriteFrame *coinFrame = CCSpriteFrame::createWithTexture(
                coinTexture,
                CCRect(MATRIX_COIN_WH * i, MATRIX_COIN_WH * (j + 5),
                       MATRIX_COIN_WH, MATRIX_COIN_WH));
            unNabuzaCoinFrames->addObject(coinFrame);
        }

        CCAnimation *unNabuzaCoinAnimation =
            CCAnimation::createWithSpriteFrames(nabuzaCoinFrames, .1);

        char unNabuzaAnimationCacheName[21];
        n = sprintf(unNabuzaAnimationCacheName, "unnabuza_animation_%u", i);
        CCAnimationCache::sharedAnimationCache()->addAnimation(
            unNabuzaCoinAnimation, unNabuzaAnimationCacheName);
    }

    // NabuzaTime Animation - BG
    CCTexture2D *nabuzaGameTopBgTexture =
        CCTextureCache::sharedTextureCache()->addImage("play_bg_n_top.png");
    CCArray *nabuzaGameTopBgFrames = new CCArray;
    for (unsigned int i = 0; i < 2; i++) {
        CCSpriteFrame *nabuzaGameTopBgFrame = CCSpriteFrame::createWithTexture(
            nabuzaGameTopBgTexture, CCRect(0., 118. * i, 480., 118.));
        nabuzaGameTopBgFrames->addObject(nabuzaGameTopBgFrame);
    }
    CCAnimation *nabuzaGameTopBgAnimation =
        CCAnimation::createWithSpriteFrames(nabuzaGameTopBgFrames, .1);
    CCAnimationCache::sharedAnimationCache()->addAnimation(
        nabuzaGameTopBgAnimation, "nabuza_t_bg_animation");

    CCTexture2D *nabuzaGameBottomBgTexture =
        CCTextureCache::sharedTextureCache()->addImage("play_bg_n_bottom.png");
    CCArray *nabuzaGameBottomBgFrames = new CCArray;
    for (unsigned int i = 0; i < 2; i++) {
        CCSpriteFrame *nabuzaGameBottomBgFrame =
            CCSpriteFrame::createWithTexture(nabuzaGameBottomBgTexture,
                                             CCRect(0., 118. * i, 480., 118.));
        nabuzaGameBottomBgFrames->addObject(nabuzaGameBottomBgFrame);
    }
    CCAnimation *nabuzaGameBottomBgAnimation =
        CCAnimation::createWithSpriteFrames(nabuzaGameBottomBgFrames, .1);
    CCAnimationCache::sharedAnimationCache()->addAnimation(
        nabuzaGameBottomBgAnimation, "nabuza_b_bg_animation");

    CCTexture2D *nabuzaDragonTexture =
        CCTextureCache::sharedTextureCache()->addImage(
            "play_n_time_dragon.png");
    CCArray *nabuzaDragonFrames = new CCArray;
    for (unsigned int i = 0; i < 2; i++) {
        CCSpriteFrame *nabuzaDragonFrame = CCSpriteFrame::createWithTexture(
            nabuzaDragonTexture, CCRect(246. * i, 0., 246., 469.));
        nabuzaDragonFrames->addObject(nabuzaDragonFrame);
    }
    CCAnimationCache::sharedAnimationCache()->addAnimation(
        CCAnimation::createWithSpriteFrames(nabuzaDragonFrames, .1),
        "nabuza_dragon_animation");

    CCTexture2D *timeNabuzaGaugeTexture =
        CCTextureCache::sharedTextureCache()->addImage(
            "play_n_time_rainbow.png");
    CCArray *timeNabuzaGaugeFrames = new CCArray;
    for (unsigned int i = 0; i < 6; i++) {
        CCSpriteFrame *timeNabuzaFrame = CCSpriteFrame::createWithTexture(
            timeNabuzaGaugeTexture, CCRect(0., 44. * i, 155., 43.));
        timeNabuzaGaugeFrames->addObject(timeNabuzaFrame);
    }
    CCAnimationCache::sharedAnimationCache()->addAnimation(
        CCAnimation::createWithSpriteFrames(timeNabuzaGaugeFrames, .1),
        "time_nabuza_gauge_animation");

    // 내 등수
    CCTexture2D *myRankTexture =
        CCTextureCache::sharedTextureCache()->addImage("t_me.png");
    CCArray *myRankFrames = new CCArray;
    for (unsigned int i = 0; i < 2; i++) {
        CCSpriteFrame *myRankFrame = CCSpriteFrame::createWithTexture(
            myRankTexture, CCRect(70. * i, 0., 70., 60.));
        myRankFrames->addObject(myRankFrame);
    }
    CCAnimation *myRankAnimation =
        CCAnimation::createWithSpriteFrames(myRankFrames, .5);
    CCAnimationCache::sharedAnimationCache()->addAnimation(myRankAnimation,
                                                           "my_rank_animation");

    // Sound Preload
    // Coin Effect
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "CS001.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "CS002.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "CS003.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "CS004.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "CS005.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "CS006.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "CS007.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "CS008.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "CS009.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "CS010.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "CS011.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "CS012.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "CS013.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "CS014.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "CS015.mp3");

    // Jung Effect
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "JN001.mp3");

    // Nabuza Voice
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "GS001.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "GS002.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "GS003.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "GS004.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "GS005.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "GS006.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "GS007.mp3");

    // Ready Start TimeOver LastChange
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "GA001.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "GA002.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "GA003.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "GA004.mp3");

    // Drop Coins
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "CD001.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "CD002.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "CD003.mp3");

    // TimeGold
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
        "BZ001.mp3");

    // BG
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(
        "BG001.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(
        "BG003.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(
        "BG004.mp3");

    // Coin Count For GameResult
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(
        "CU001.mp3");
}