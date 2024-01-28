//
//  BuyGoldLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 8/14/13.
//
//

#include "BuyGoldLayer.h"

#include "AlertTitleSprite.h"
#include "AnytaleHTTP.h"
#include "ButtonSprite.h"
#include "BuyGoldButtonSprite.h"
#include "IndicationLayer.h"
#include "JadeLessAlertViewLayer.h"
#include "TopJadeGoldLayer.h"
#include "UserStorage.h"

#define TAG_BUYGOLDBUTTON10_SPRITE 1
#define TAG_BUYGOLDBUTTON50_SPRITE 2
#define TAG_BUYGOLDBUTTON100_SPRITE 3
#define TAG_BUYGOLDBUTTON300_SPRITE 4
#define TAG_BUYGOLDBUTTON500_SPRITE 5

#define TAG_INDICATION_LAYER 1000

#define GOLDBUTTON_COUNT 5

void BuyGoldLayer::onEnter() {
    this->setTouchEnabled(true);

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    // BG
    CCSprite *bgRankingSprite = CCSprite::create("title_full_alert.jpg");
    bgRankingSprite->setPosition(
        ccp(visibleSize.width / 2., visibleSize.height / 2.));
    this->addChild(bgRankingSprite);

    // TITLE
    AlertTitleSprite *alertTitleSprite =
        AlertTitleSprite::createWithItemKey(kGAMEALERTTITLE_BUY_GOLD);
    this->addChild(alertTitleSprite);

    // 닫기 버튼
    ButtonSprite *closeButtonSprite =
        ButtonSprite::createWithItemKey(kGAMEBUTTON_CLOSE);
    ButtonSprite *closeButtonSpriteTapped =
        ButtonSprite::createWithItemKey(kGAMEBUTTON_CLOSE);
    closeButtonSpriteTapped->setScale(1.2);
    closeButtonSpriteTapped->setPosition(
        ccp(closeButtonSprite->getPositionX() - 20.,
            closeButtonSprite->getPositionY() - 6.));

    CCMenuItemSprite *closeButtonItem =
        CCMenuItemSprite::create(closeButtonSprite, closeButtonSpriteTapped,
                                 this, menu_selector(BuyGoldLayer::close));
    CCMenu *menu = CCMenu::create(closeButtonItem, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(ccp(visibleSize.width / 2, 800. - 648. - 44.));
    this->addChild(menu);

    // 비취 리스트
    CCArray *goldButtons = new CCArray;

    for (unsigned int i = 0; i < GOLDBUTTON_COUNT; i++) {
        BuyGoldButtonSprite *goldButtonSprite =
            BuyGoldButtonSprite::createWithItemKey(i);
        BuyGoldButtonSprite *goldButtonSpriteTapped =
            BuyGoldButtonSprite::createWithItemKeyTapped(i);
        CCMenuItemSprite *goldButtonItem = CCMenuItemSprite::create(
            goldButtonSprite, goldButtonSpriteTapped, this,
            menu_selector(BuyGoldLayer::onBuyGoldButtonTapped));
        goldButtonItem->setTag(i);
        goldButtons->addObject(goldButtonItem);
    }

    CCMenu *goldMenu = CCMenu::createWithArray(goldButtons);
    goldMenu->alignItemsVerticallyWithPadding(0.);
    goldMenu->setPosition(ccp(visibleSize.width / 2, 800. - 364. - 40.));
    this->addChild(goldMenu);

    TopJadeGoldLayer *topJadeGoldLayer = TopJadeGoldLayer::create();
    topJadeGoldLayer->setCanPushGoldButton(false);
    this->addChild(topJadeGoldLayer);

    CCLayerColor::onEnter();
}

void BuyGoldLayer::close() {
    this->removeFromParentAndCleanup(true);
}

void BuyGoldLayer::onBuyGoldButtonTapped(CCObject *object) {
    CCMenu *goldMenu = (CCMenu *)object;

    int needJadeCountKey = goldMenu->getTag();

    CCLog("button tag : %d", needJadeCountKey);
    CCAssert(needJadeCountKey >= 0 && needJadeCountKey < GOLDBUTTON_COUNT,
             "not validate tag value");

    int needJadeCounts[] = {10, 50, 100, 300, 500};
    int buyedGoldCounts[] = {2000, 11000, 24000, 80000, 16000};

    if (UserStorage::sharedUserStorage()->getJadeCount() <
        needJadeCounts[needJadeCountKey]) {
        JadeLessAlertViewLayer *jadeLessAlertViewLayer =
            JadeLessAlertViewLayer::createWithKey(kJADELESSKEY_NOT_GOLD);
        this->addChild(jadeLessAlertViewLayer);
        return;
    }

    std::stringstream ss;
    ss << "&spend_count=" << needJadeCounts[needJadeCountKey];
    ss << "&buyed_count=" << buyedGoldCounts[needJadeCountKey];

    AnytaleHTTP::onHttpRequesting(
        this, callfuncND_selector(BuyGoldLayer::onHttpRequestCompleted),
        "/spent_jades/buy_gold2", ss.str().c_str(), "SPENT_JADES_BUY_GOLD2");
    IndicationLayer *indicationLayer = IndicationLayer::create();
    indicationLayer->setTag(TAG_INDICATION_LAYER);
    this->addChild(indicationLayer);
}

void BuyGoldLayer::onHttpRequestCompleted(CCHttpClient *sender,
                                          CCHttpResponse *response) {
    Json::Value root;

    int error;
    AnytaleHTTP::validateResponse(response, root, error);

    if (error != 0) {
        CCLog("AuthStorage json parse error");
        return;
    }

    // 게임 시작을 서버에 알림
    if (strcmp(response->getHttpRequest()->getTag(), "SPENT_JADES_BUY_GOLD2") ==
        0) {
        IndicationLayer *indicationLayer =
            (IndicationLayer *)this->getChildByTag(TAG_INDICATION_LAYER);
        indicationLayer->close();
        /*
         {"code":0,"message":"OK","result":[]}
         */
        //        int code = root.get("code", 0).asInt();
        int playerId = root["result"]["Player"].get("id", 0).asInt();

        if (playerId != 0) {
            int ownJadeCount =
                root["result"]["Player"].get("own_jade_count", 0).asInt();
            int ownGold = root["result"]["Player"].get("own_gold", 0).asInt();

            UserStorage::sharedUserStorage()->setOwnJadeCount(ownJadeCount);
            UserStorage::sharedUserStorage()->setOwnGold(ownGold);
        }
    }

    return;
}

bool BuyGoldLayer::ccTouchBegan(CCTouch *touch, CCEvent *pEvent) {
    return true;
}

void BuyGoldLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
        this, 0, true);
}