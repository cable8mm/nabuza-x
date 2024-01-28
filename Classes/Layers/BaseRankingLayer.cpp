//
//  BaseRankingLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 5/29/13.
//
//

#include "BaseRankingLayer.h"

#include "../GameScene.h"
#include "../Storages/NeedForGameMemory.h"
#include "../Structs/PlusMaxSprite.h"
#include "../Utilities/ATUtil.h"
#include "AnytaleHTTP.h"
#include "BelowTapLayer.h"
#include "BuyJadeLayer.h"
#include "CCControlButton.h"
#include "CCScale9Sprite.h"
#include "CardLayer.h"
#include "InviteFriendLayer.h"
#include "MessageBoxLayer.h"
#include "SendingGiftLayer.h"
#include "SettingLayer.h"
#include "WebViewLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define TAG_PLUSMAX_SPRITE 5000

#define ZORDER_BELOW_LAYER 30000
#define ZORDER_CARD_ON_LETTERBAR_LAYER 21000
#define ZORDER_PLUSMAX_SPRITE 20100
#define ZORDER_LETTERBAR_SPRITE 20100
#define ZORDER_ITEM_SELECTION_LAYER 11000
#define ZORDER_RANKING_LAYER 11000
#define ZORDER_BELOW_BUTTON 11100
#define ZORDER_START_BUTTON 11100
#define ZORDER_SALE_INVITATION_LAYER 12000
#define ZORDER_BUY_JADE_LAYER 12000

#define TAG_BELOW_EVENT_BUTTON 11101
#define TAG_BELOW_GIFT_BUTTON 11102
#define TAG_BELOW_SETTING_BUTTON 11103
#define TAG_BELOW_INVITE_BUTTON 11104
#define TAG_BELOW_MESSAGE_BUTTON 11105

BaseRankingLayer::BaseRankingLayer() : isRanking(true) {
}

// on "init" you need to initialize your instance
bool BaseRankingLayer::init() {
    //////////////////////////////
    // 1. super init first
    if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))  // RGBA
    {
        return false;
    }

    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        this, callfuncO_selector(BaseRankingLayer::changeToSelectItemsLayer),
        "NABUZA_SELECT_ITEMS_NOTIFICATION", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        this, callfuncO_selector(BaseRankingLayer::changeToRankingLayer),
        "NABUZA_RANKING_NOTIFICATION", NULL);
    //    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
    //    callfuncO_selector(BaseRankingLayer::onBuyJadeLayer),
    //    "ON_BUY_JADE_LAYER_NOTIFICATION", NULL);

    this->setTouchEnabled(true);

    // Floating RankingLayer
    this->rankingLayer = RankingLayer::create();
    this->addChild(rankingLayer, ZORDER_RANKING_LAYER);

    //    this->itemStorage   = ItemStorage::create();
    //    this->itemStorage->reset();

    BelowTapLayer *belowTapLayer = BelowTapLayer::create();
    this->addChild(belowTapLayer, ZORDER_CARD_ON_LETTERBAR_LAYER);

    CardLayer *cardLayer = CardLayer::create();
    this->addChild(cardLayer, ZORDER_CARD_ON_LETTERBAR_LAYER);

    return true;
}

void BaseRankingLayer::onBuyJadeLayer() {
    BuyJadeLayer *buyJadeLayer = BuyJadeLayer::create();
    this->addChild(buyJadeLayer, ZORDER_BUY_JADE_LAYER);
}

void BaseRankingLayer::onStartGame(CCObject *pSender) {
    ItemSelectionLayer *itemSelectionLayer = ItemSelectionLayer::create();
    this->addChild(itemSelectionLayer, ZORDER_CARD_ON_LETTERBAR_LAYER - 1);
    //    CCLog("onStartGame!!!");
    //    if (this->isRanking == true) {
    //        this->rankingLayer->setVisible(false);
    //        this->rankingLayer->setTouchEnabled(false);
    //        this->itemSelectionLayer->setVisible(true);
    //        this->itemSelectionLayer->setTouchEnabled(true);
    //        this->isRanking = false;
    //    } else {
    //        // 게임 시작!
    //        NeedForGameMemory::sharedNeedForGameMemory()->reset();
    //
    //        for (unsigned int i=0; i <
    //        this->itemSelectionLayer->itemChoosedSprites->count(); i++) {
    //            ItemChoosedSprite *itemChoosedSprite    =
    //            dynamic_cast<ItemChoosedSprite*>(this->itemSelectionLayer->itemChoosedSprites->objectAtIndex(i));
    //            int itemKey    = itemChoosedSprite->getItemKey();
    //            this->itemStorage->addItem(itemKey);
    //
    //            NeedForGameMemory::sharedNeedForGameMemory()->addJadeCount(itemChoosedSprite->needJadeCount);
    //        }
    //
    //        this->itemStorage->flush();
    //
    //        CCDirector::sharedDirector()->replaceScene(GameScene::scene());
    //    }
}

void BaseRankingLayer::changeToRankingLayer() {
    //    this->rankingLayer->setVisible(true);
    //    this->rankingLayer->setTouchEnabled(true);
    //    this->itemSelectionLayer->setVisible(false);
    //    this->itemSelectionLayer->setTouchEnabled(false);
    //    this->isRanking = true;
}

void BaseRankingLayer::changeToSelectItemsLayer() {
    //    this->rankingLayer->setVisible(false);
    //    this->rankingLayer->setTouchEnabled(false);
    //    this->itemSelectionLayer->setVisible(true);
    //    this->itemSelectionLayer->setTouchEnabled(true);
    //    this->isRanking = false;
}

bool BaseRankingLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    //    CCPoint pt    =
    //    CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    //
    //    // 플러스맥스스프라이트
    //    PlusMaxSprite *plusMaxSprite    = (PlusMaxSprite
    //    *)this->getChildByTag(TAG_PLUSMAX_SPRITE); if
    //    (plusMaxSprite->boundingBox().containsPoint(pt)) {
    //        return true;
    //    }
    //
    //    // 하단 버튼
    //    CCSprite *belowEventButtonSprite    = (CCSprite
    //    *)this->getChildByTag(TAG_BELOW_EVENT_BUTTON); if
    //    (belowEventButtonSprite->boundingBox().containsPoint(pt)) {
    //        return true;
    //    }
    //
    //    CCSprite *belowGiftButtonSprite    = (CCSprite
    //    *)this->getChildByTag(TAG_BELOW_GIFT_BUTTON); if
    //    (belowGiftButtonSprite->boundingBox().containsPoint(pt)) {
    //        return true;
    //    }
    //
    //    CCSprite *belowSettingButtonSprite    = (CCSprite
    //    *)this->getChildByTag(TAG_BELOW_SETTING_BUTTON); if
    //    (belowSettingButtonSprite->boundingBox().containsPoint(pt)) {
    //        return true;
    //    }
    //
    //    CCSprite *belowInviteButtonSprite    = (CCSprite
    //    *)this->getChildByTag(TAG_BELOW_INVITE_BUTTON); if
    //    (belowInviteButtonSprite->boundingBox().containsPoint(pt)) {
    //        return true;
    //    }
    //
    ////    CCSprite *belowMessageButtonSprite    = (CCSprite
    ///*)this->getChildByTag(TAG_BELOW_MESSAGE_BUTTON); /    if
    ///(belowMessageButtonSprite->boundingBox().containsPoint(pt)) { / return
    /// true; /    }
    //
    return false;
}

void BaseRankingLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
}

void BaseRankingLayer::onHttpRequestCompleted(CCHttpClient *sender,
                                              CCHttpResponse *response) {
    Json::Value root;

    int error;
    AnytaleHTTP::validateResponse(response, root, error);

    if (error != 0) {
        CCLog("AuthStorage json parse error");
        return;
    }

    // 게임 시작을 서버에 알림
    if (strcmp(response->getHttpRequest()->getTag(), "EVENTS_GET") == 0) {
        const Json::Value events = root["result"];

        if (events.size() == 0) {
            return;
        }

        for (int index = 0; index < events.size(); index++) {
            std::string linkUrl =
                events[index]["Event"].get("link_url", "").asString();
            WebViewLayer *webViewLayer =
                WebViewLayer::createWithUrl(linkUrl.c_str());
            this->addChild(webViewLayer);
            break;
        }
    }
}

void BaseRankingLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
        this, 0, true);
}

BaseRankingLayer::~BaseRankingLayer() {
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}