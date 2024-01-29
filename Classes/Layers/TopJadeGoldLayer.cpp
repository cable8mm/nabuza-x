//
//  TopJadeGoldLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 8/14/13.
//
//

#include "TopJadeGoldLayer.h"

#include "ATUtil.h"
#include "BuyGoldLayer.h"
#include "BuyJadeLayer.h"
#include "CCControlButton.h"
#include "CCScale9Sprite.h"
#include "UserStorage.h"

#define ZORDER_TOP_JADE_BUTTON 50200
#define ZORDER_TOP_GOLD_BUTTON 50200
#define ZORDER_BASE_RANKING_LAYER 20000
#define ZORDER_BASE_BG 10100
#define ZORDER_BUY_JADE_LAYER 100000
#define ZORDER_BUY_GOLD_LAYER 100000

#define TAG_TOP_JADE_BUTTON 50200
#define TAG_TOP_JADE_LABEL 50201
#define TAG_TOP_GOLD_BUTTON 50300
#define TAG_TOP_GOLD_LABEL 50301

#define DEFAULT_FONT_NAME "Helvetica"

TopJadeGoldLayer::TopJadeGoldLayer()
    : canGoldButton(true), canJadeButton(true) {
}

bool TopJadeGoldLayer::init() {
    //////////////////////////////
    // 1. super init first
    if (!CCLayerColor::init())  // RGBA
    {
        return false;
    }

    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        this, callfuncO_selector(TopJadeGoldLayer::onBuyJadeLayer),
        "ON_BUY_JADE_LAYER_NOTIFICATION", NULL);
    // OWN_JADE_COUNT_CHANGED_NOTIFICATION
    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        this, callfuncO_selector(TopJadeGoldLayer::onChangedJadeCount),
        "OWN_JADE_COUNT_CHANGED_NOTIFICATION", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        this, callfuncO_selector(TopJadeGoldLayer::onChangedGoldCount),
        "OWN_GOLD_COUNT_CHANGED_NOTIFICATION", NULL);

    this->setTouchEnabled(true);

    return true;
}

void TopJadeGoldLayer::onEnter() {
    // 비취 배경+버튼
    CCSprite *bgJewelSprite = CCSprite::create("jewel_mini_btn.png");
    bgJewelSprite->setAnchorPoint(ccp(.5, .5));
    bgJewelSprite->setPosition(ccp(7. + 78., ATUtil::agy(8.) - 30.));
    bgJewelSprite->setTag(TAG_TOP_JADE_BUTTON);
    this->addChild(bgJewelSprite);

    std::string s1 =
        UserStorage::sharedUserStorage()->getOwnJadeCount()->getCString();
    ATUtil::insert_separator(s1);
    CCLabelTTF *jewelSpriteLabel =
        CCLabelTTF::create(s1.c_str(), DEFAULT_FONT_NAME, 18);
    jewelSpriteLabel->setTag(TAG_TOP_JADE_LABEL);
    jewelSpriteLabel->setAnchorPoint(ccp(.5, .5));
    jewelSpriteLabel->setPosition(ccp(85., 33.));
    bgJewelSprite->addChild(jewelSpriteLabel);

    //    CCScale9Sprite *btnJewelSprite  =
    //    CCScale9Sprite::create("jewel_mini_btn.png");
    //    btnJewelSprite->setCapInsets(CCRect(61., 20., 53., 22.));
    //    std::string s1   =
    //    UserStorage::sharedUserStorage()->getOwnJadeCount()->getCString();
    //    ATUtil::insert_separator(s1);
    //    CCLabelTTF *numberJewelLabel    = CCLabelTTF::create(s1.c_str(),
    //    DEFAULT_FONT_NAME, 20);
    //
    //    CCControlButton *numberJewelButton  =
    //    CCControlButton::create(numberJewelLabel, btnJewelSprite);
    //    numberJewelButton->setPreferredSize(CCSize(156., 60.));
    //    numberJewelButton->setPosition(ccp(7. + 78., ATUtil::agy(8.) - 30.));
    //    this->addChild(numberJewelButton, ZORDER_TOP_JADE_BUTTON,
    //    TAG_TOP_JADE_BUTTON);

    // 골드 배경+버튼
    CCSprite *bgGoldSprite = CCSprite::create("gold_btn.png");
    bgGoldSprite->setAnchorPoint(ccp(.5, .5));
    bgGoldSprite->setPosition(ccp(238. + 112., ATUtil::agy(11.) - 30.));
    bgGoldSprite->setTag(TAG_TOP_GOLD_BUTTON);
    this->addChild(bgGoldSprite);

    std::string s2 =
        UserStorage::sharedUserStorage()->getOwnGold()->getCString();
    ATUtil::insert_separator(s2);
    CCLabelTTF *goldSpriteLabel =
        CCLabelTTF::create(s2.c_str(), DEFAULT_FONT_NAME, 18);
    goldSpriteLabel->setTag(TAG_TOP_GOLD_LABEL);
    goldSpriteLabel->setAnchorPoint(ccp(.5, .5));
    goldSpriteLabel->setPosition(ccp(120., 33.));
    bgGoldSprite->addChild(goldSpriteLabel);

    //    CCScale9Sprite * btnGoldSprite  =
    //    CCScale9Sprite::create("gold_btn.png");
    //    btnGoldSprite->setCapInsets(CCRect(63., 20., 121., 22.));
    //    std::string s2   =
    //    UserStorage::sharedUserStorage()->getOwnJadeCount()->getCString();
    //    ATUtil::insert_separator(s2);
    //    CCLabelTTF *numberGoldLabel    = CCLabelTTF::create(s2.c_str(),
    //    DEFAULT_FONT_NAME, 20);
    //
    //    CCControlButton *numberGoldButton  =
    //    CCControlButton::create(numberGoldLabel, btnGoldSprite);
    //    numberGoldButton->setPreferredSize(CCSize(224., 60.));
    //    numberGoldButton->setPosition(ccp(238. + 112., ATUtil::agy(11.)
    //    - 30.)); this->addChild(numberGoldButton, ZORDER_TOP_GOLD_BUTTON,
    //    TAG_TOP_GOLD_BUTTON);

    CCLayerColor::onEnter();
}

void TopJadeGoldLayer::setCanPushJadeButton(bool v) {
    this->canJadeButton = v;

    //    CCControlButton *numberJewelButton  = (CCControlButton
    //    *)this->getChildByTag(TAG_TOP_JADE_BUTTON); CCAssert(numberJewelButton
    //    != NULL, "button is must not NULL");
    //
    //    numberJewelButton->setEnabled(this->canJadeButton);
}

void TopJadeGoldLayer::setCanPushGoldButton(bool v) {
    this->canGoldButton = v;

    //    CCControlButton *numberGoldButton  = (CCControlButton
    //    *)this->getChildByTag(TAG_TOP_GOLD_BUTTON);
    //    numberGoldButton->setEnabled(this->canGoldButton);
}

void TopJadeGoldLayer::onBuyJadeLayer() {
    BuyJadeLayer *buyJadeLayer = BuyJadeLayer::create();
    this->addChild(buyJadeLayer, ZORDER_BUY_JADE_LAYER);
}

void TopJadeGoldLayer::onChangedJadeCount(CCObject *obj) {
    CCInteger *ownJadeCount = (CCInteger *)obj;
    std::stringstream ss;
    ss << ownJadeCount->getValue();
    std::string s = ss.str();
    ATUtil::insert_separator(s);
    CCSprite *jewelSprite =
        (CCSprite *)this->getChildByTag(TAG_TOP_JADE_BUTTON);
    CCLabelTTF *jewelLabel =
        (CCLabelTTF *)jewelSprite->getChildByTag(TAG_TOP_JADE_LABEL);
    jewelLabel->setString(s.c_str());
}

void TopJadeGoldLayer::onChangedGoldCount(CCObject *obj) {
    CCInteger *ownGoldCount = (CCInteger *)obj;
    std::stringstream ss;
    ss << ownGoldCount->getValue();
    std::string s = ss.str();
    ATUtil::insert_separator(s);
    CCSprite *goldSprite = (CCSprite *)this->getChildByTag(TAG_TOP_GOLD_BUTTON);
    CCLabelTTF *goldLabel =
        (CCLabelTTF *)goldSprite->getChildByTag(TAG_TOP_GOLD_LABEL);
    goldLabel->setString(s.c_str());
}

void TopJadeGoldLayer::close() {
    this->removeFromParentAndCleanup(true);
}

TopJadeGoldLayer::~TopJadeGoldLayer() {
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

#pragma mark -
#pragma mark Touch Delegates

bool TopJadeGoldLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint pt =
        CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());

    if (this->canJadeButton) {
        CCSprite *jewelSprite =
            (CCSprite *)this->getChildByTag(TAG_TOP_JADE_BUTTON);
        if (jewelSprite->boundingBox().containsPoint(pt)) {
            jewelSprite->setScale(1.2);
            return true;
        }
    }

    if (this->canGoldButton) {
        CCSprite *goldSprite =
            (CCSprite *)this->getChildByTag(TAG_TOP_GOLD_BUTTON);
        if (goldSprite->boundingBox().containsPoint(pt)) {
            goldSprite->setScale(1.2);
            return true;
        }
    }
    return false;
}

void TopJadeGoldLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint pt =
        CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());

    if (this->canJadeButton) {
        CCSprite *jewelSprite =
            (CCSprite *)this->getChildByTag(TAG_TOP_JADE_BUTTON);
        if (jewelSprite->boundingBox().containsPoint(pt)) {
            BuyJadeLayer *buyJadeLayer = BuyJadeLayer::create();
            this->addChild(buyJadeLayer, ZORDER_BUY_JADE_LAYER);
        }
    }

    if (this->canGoldButton) {
        CCSprite *goldSprite =
            (CCSprite *)this->getChildByTag(TAG_TOP_GOLD_BUTTON);
        if (goldSprite->boundingBox().containsPoint(pt)) {
            BuyGoldLayer *buyGoldLayer = BuyGoldLayer::create();
            this->addChild(buyGoldLayer, ZORDER_BUY_GOLD_LAYER);
        }
    }

    CCSprite *jewelSprite =
        (CCSprite *)this->getChildByTag(TAG_TOP_JADE_BUTTON);
    jewelSprite->setScale(1.);
    CCSprite *goldSprite = (CCSprite *)this->getChildByTag(TAG_TOP_GOLD_BUTTON);
    goldSprite->setScale(1.);
    return;
}

void TopJadeGoldLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
        this, 0, true);
}