//
//  AlertViewLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 7/30/13.
//
//

#include "JadeLessAlertViewLayer.h"
#include "ButtonSprite.h"

JadeLessAlertViewLayer* JadeLessAlertViewLayer::createWithKey(eJadeLessKeys key) {
    JadeLessAlertViewLayer *pobSprite = new JadeLessAlertViewLayer;

    pobSprite->key  = key;
    if (pobSprite && pobSprite->initWithColor(ccc4(0., 0., 0., 200.)))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void JadeLessAlertViewLayer::onEnter() {
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCSprite *whatAlertSprite = CCSprite::create("what_alert.png");
    whatAlertSprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(whatAlertSprite);
    
    CCSprite *jadeLessSprite    = CCSprite::create("jewel_less.png", CCRect(0., 264.*this->key, 350., 264.));
    jadeLessSprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(jadeLessSprite);
    
    // 닫기 버튼
    ButtonSprite *noButtonSprite = ButtonSprite::createWithItemKey(kGAMEBUTTON_NO);
    ButtonSprite *noButtonSpriteTapped = ButtonSprite::createWithItemKey(kGAMEBUTTON_NO);
    noButtonSpriteTapped->setScale(1.2);
    noButtonSpriteTapped->setPosition(ccp(noButtonSprite->getPositionX()-20., noButtonSprite->getPositionY()-6.));
    
    ButtonSprite *yesButtonSprite = ButtonSprite::createWithItemKey(kGAMEBUTTON_YES);
    ButtonSprite *yesButtonSpriteTapped = ButtonSprite::createWithItemKey(kGAMEBUTTON_YES);
    yesButtonSpriteTapped->setScale(1.2);
    yesButtonSpriteTapped->setPosition(ccp(yesButtonSprite->getPositionX()-20., yesButtonSprite->getPositionY()-6.));
    
    CCMenuItemSprite *noButtonItem    = CCMenuItemSprite::create(noButtonSprite, noButtonSpriteTapped, this, menu_selector(JadeLessAlertViewLayer::no));
    CCMenuItemSprite *yesButtonItem    = CCMenuItemSprite::create(yesButtonSprite, yesButtonSpriteTapped, this, menu_selector(JadeLessAlertViewLayer::yes));
    CCMenu *buttonMenu    = CCMenu::create(noButtonItem, yesButtonItem, NULL);
    buttonMenu->alignItemsHorizontally();
    buttonMenu->setPosition(ccp(visibleSize.width / 2, 800.-648.-44.));
    this->addChild(buttonMenu);
    
    //    this->setPosition(ccp(visibleSize.width / 2, 800.-138.-25.));
    CCLayerColor::onEnter();
}

void JadeLessAlertViewLayer::yes() {
    CCNotificationCenter::sharedNotificationCenter()->postNotification("ON_BUY_JADE_LAYER_NOTIFICATION");
    this->removeFromParentAndCleanup(true);
}

void JadeLessAlertViewLayer::no() {
    this->removeFromParentAndCleanup(true);
}