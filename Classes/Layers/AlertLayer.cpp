//
//  AlertLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 8/13/13.
//
//

#include "AlertLayer.h"

#include "ButtonSprite.h"

#define TAG_TITLE 10
#define TAG_MESSAGE 11

static AlertLayer *s_SharedAlertLayer = NULL;

AlertLayer *AlertLayer::sharedAlertLayer(void) {
    if (!s_SharedAlertLayer) {
        s_SharedAlertLayer = new AlertLayer();
        s_SharedAlertLayer->init();
    }

    return s_SharedAlertLayer;
}

// AlertLayer* AlertLayer::createWithMessage(std::string title, std::string
// message) {
//     AlertLayer *pobLayer = new AlertLayer;
//
//     pobLayer->title = title;
//     pobLayer->message   = message;
//
//     if (pobLayer && pobLayer->initWithColor(ccc4(0., 0., 0., 200.)))
//     {
//         pobLayer->autorelease();
//         return pobLayer;
//     }
//     CC_SAFE_DELETE(pobLayer);
//     return NULL;
// }

bool AlertLayer::init() {
    if (!CCLayerColor::init()) {
        return false;
    }

    this->setColor(ccBLACK);
    this->setOpacity(200.);

    this->setVisible(false);
    this->setTouchEnabled(false);

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    // BG
    CCSprite *bgRankingSprite = CCSprite::create("alert_view_box.png");
    bgRankingSprite->setPosition(
        ccp(visibleSize.width / 2., visibleSize.height / 2.));
    this->addChild(bgRankingSprite);

    // 닫기 버튼
    ButtonSprite *closeButtonSprite =
        ButtonSprite::createWithItemKey(kGAMEBUTTON_CONFIRM);
    ButtonSprite *closeButtonSpriteTapped =
        ButtonSprite::createWithItemKey(kGAMEBUTTON_CONFIRM);
    closeButtonSpriteTapped->setScale(1.2);
    closeButtonSpriteTapped->setPosition(
        ccp(closeButtonSprite->getPositionX() - 20.,
            closeButtonSprite->getPositionY() - 6.));

    CCMenuItemSprite *closeButtonItem =
        CCMenuItemSprite::create(closeButtonSprite, closeButtonSpriteTapped,
                                 this, menu_selector(AlertLayer::close));
    CCMenu *menu = CCMenu::create(closeButtonItem, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(ccp(visibleSize.width / 2, 220.));
    this->addChild(menu);

    // 타이틀
    CCLabelTTF *titleLabel = CCLabelTTF::create("", "Helvetica", 28);
    titleLabel->setColor(ccRED);
    titleLabel->setTag(TAG_TITLE);
    titleLabel->setPosition(
        ccp(visibleSize.width / 2., visibleSize.height / 2. + 50.));
    this->addChild(titleLabel);

    // 메시지
    CCLabelTTF *messageLabel = CCLabelTTF::create("", "Helvetica", 20);
    messageLabel->setColor(ccRED);
    messageLabel->setTag(TAG_MESSAGE);
    messageLabel->setAnchorPoint(ccp(.5, 1.));
    messageLabel->setPosition(
        ccp(visibleSize.width / 2., visibleSize.height / 2.));
    this->addChild(messageLabel);

    return true;
}

void AlertLayer::show(std::string title, std::string message) {
    this->setTouchEnabled(true);
    CCLabelTTF *titleLabel = (CCLabelTTF *)this->getChildByTag(TAG_TITLE);
    titleLabel->setString(title.c_str());

    CCLabelTTF *messageLabel = (CCLabelTTF *)this->getChildByTag(TAG_MESSAGE);
    messageLabel->setString(message.c_str());

    this->setVisible(true);
}

void AlertLayer::close() {
    this->setVisible(false);
    this->setTouchEnabled(false);
}

bool AlertLayer::ccTouchBegan(CCTouch *touch, CCEvent *pEvent) {
    return true;
}

void AlertLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
        this, 0, true);
}