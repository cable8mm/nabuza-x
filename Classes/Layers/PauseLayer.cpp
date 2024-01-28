//
//  PauseLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 5/6/13.
//
//

#include "PauseLayer.h"

PauseLayer::PauseLayer() {
}

// on "init" you need to initialize your instance
bool PauseLayer::init() {
    //////////////////////////////
    // 1. super init first
    if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 200)))  // RGBA
    {
        return false;
    }

    this->setTouchEnabled(true);

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    CCSprite *tabSprite = CCSprite::create("alert_pause.png");
    tabSprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(tabSprite);

    CCSprite *resumeSprite =
        CCSprite::create("pause_btn.png", CCRect(0., 0., 300., 80.));
    CCMenuItem *btnResume =
        CCMenuItemSprite::create(resumeSprite, resumeSprite, this,
                                 menu_selector(PauseLayer::resumeCallback));
    btnResume->setPosition(
        ccp(visibleSize.width / 2, visibleSize.height / 2 + 25.));
    CCSprite *quitSprite =
        CCSprite::create("pause_btn.png", CCRect(0., 80., 300., 80.));
    CCMenuItem *btnQuit = CCMenuItemSprite::create(
        quitSprite, quitSprite, this, menu_selector(PauseLayer::quitCallback));
    btnQuit->setPosition(
        ccp(visibleSize.width / 2, visibleSize.height / 2 - 40.));
    CCSprite *restartSprite =
        CCSprite::create("pause_btn.png", CCRect(0., 160., 300., 80.));
    CCMenuItem *btnRestart =
        CCMenuItemSprite::create(restartSprite, restartSprite, this,
                                 menu_selector(PauseLayer::restartCallback));
    btnRestart->setPosition(
        ccp(visibleSize.width / 2, visibleSize.height / 2 - 105.));

    CCMenu *pauseMenu = CCMenu::create(btnResume, btnQuit, btnRestart, NULL);
    pauseMenu->setPosition(CCPointZero);
    this->addChild(pauseMenu, 200000);

    return true;
}

#pragma mark -
#pragma mark Callback Methods For Button

void PauseLayer::resumeCallback(CCObject *pSender) {
    CCNotificationCenter::sharedNotificationCenter()->postNotification(
        "RESUME_NOTIFICATION");

    this->removeFromParentAndCleanup(true);
}

void PauseLayer::quitCallback(CCObject *pSender) {
    CCNotificationCenter::sharedNotificationCenter()->postNotification(
        "QUIT_NOTIFICATION");

    this->removeFromParentAndCleanup(true);
}

void PauseLayer::restartCallback(CCObject *pSender) {
    CCNotificationCenter::sharedNotificationCenter()->postNotification(
        "RESTART_NOTIFICATION");
    this->removeFromParentAndCleanup(true);
}

#pragma mark -
#pragma mark Touch Delegates

PauseLayer::~PauseLayer() {
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

bool PauseLayer::ccTouchBegan(CCTouch *touch, CCEvent *pEvent) {
    return true;
}

void PauseLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
        this, 0, true);
}