//
//  BelowTapLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 8/14/13.
//
//

#include "BelowTapLayer.h"

#include "ATUtil.h"
#include "PlusMaxSprite.h"

#include "SaleInvitationLayer.h"
#include "SendingGiftLayer.h"
#include "SettingLayer.h"
#include "InviteFriendLayer.h"
#include "MessageBoxLayer.h"
#include "GameScene.h"
#include "LetterBigSprite.h"
#include "UserStorage.h"

#define TAG_BELOW_EVENT_BUTTON          11101
#define TAG_BELOW_GIFT_BUTTON           11102
#define TAG_BELOW_SETTING_BUTTON        11103
#define TAG_BELOW_INVITE_BUTTON         11104
#define TAG_BELOW_MESSAGE_BUTTON        11105
#define TAG_GAME_START_MENU             11106
#define TAG_GAME_START_SPRITE           11107

BelowTapLayer::BelowTapLayer()
: touchedSprite(NULL)
, isGameStart(false)
{}

BelowTapLayer *BelowTapLayer::createWithIsStartGame(bool v) {
    BelowTapLayer *pobLayer = new BelowTapLayer;
    pobLayer->isGameStart   = v;
    
    if (pobLayer && pobLayer->init())
    {
        pobLayer->autorelease();
        return pobLayer;
    }
    CC_SAFE_DELETE(pobLayer);
    return NULL;
}

void BelowTapLayer::onEnter()
{
    this->setTouchEnabled(true);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    /*
     골드몰은 GDD에 따라 삭제 됨.
     CCTexture2D *btnBelowGoldTexture = CCTextureCache::sharedTextureCache()->addImage("menu_gs_btn.png");
     CCSpriteFrame* btnBelowGoldFrame   = CCSpriteFrame::createWithTexture(btnBelowGoldTexture, CCRectMake(0., 0., 60., 72.));
     CCSprite *btnBelowGoldSprite   = CCSprite::createWithSpriteFrame(btnBelowGoldFrame);
     btnBelowGoldSprite->setPosition(ccp(135. + 30, ATUtil::agy(725.) - 36.));
     this->addChild(btnBelowGoldSprite, 10000);
     
     CCArray *btnBelowGoldFrames  = new CCArray;
     for (int i=0; i < 4; i++) {
     btnBelowGoldFrames->addObject(CCSpriteFrame::createWithTexture(btnBelowGoldTexture, CCRectMake(0, 72.*i, 60., 72.)));
     }
     CCAnimation* animationTableObject  = CCAnimation::createWithSpriteFrames(btnBelowGoldFrames, .2f);
     CCAnimate*  animateTableObject = CCAnimate::create(animationTableObject);
     CCRepeatForever *repeat = CCRepeatForever::create(animateTableObject);
     CCSpeed *speed  = CCSpeed::create(repeat, 1.f);
     btnBelowGoldSprite->runAction(speed);
     */
    // 시작버튼
    CCTexture2D *btnStartTexture = CCTextureCache::sharedTextureCache()->addImage("start_btn.png");
    CCSpriteFrame* btnStartFrame   = CCSpriteFrame::createWithTexture(btnStartTexture, CCRectMake(0., 0., 290., 76.));
    
    // 하단 버튼들...
    CCTexture2D *btnBelowMenusTexture = CCTextureCache::sharedTextureCache()->addImage("menu_btn.png");
    CCSpriteFrame* btnBelowMenuFrame   = CCSpriteFrame::createWithTexture(btnBelowMenusTexture, CCRectMake(0., 0., 60., 72.));
    CCSprite *btnBelowMenu1Sprite   = CCSprite::createWithSpriteFrame(btnBelowMenuFrame);
    btnBelowMenu1Sprite->setPosition(ccp(9. + 30, ATUtil::agy(725.) - 36.));
    btnBelowMenu1Sprite->setTag(TAG_BELOW_EVENT_BUTTON);
    this->addChild(btnBelowMenu1Sprite);
    
    btnBelowMenuFrame->setRect(CCRectMake(0., 72. + 1., 60., 72.));
    CCSprite *btnBelowMenu2Sprite   = CCSprite::createWithSpriteFrame(btnBelowMenuFrame);
    btnBelowMenu2Sprite->setPosition(ccp(72. + 30, ATUtil::agy(725.) - 36.));
    btnBelowMenu2Sprite->setTag(TAG_BELOW_GIFT_BUTTON);
    this->addChild(btnBelowMenu2Sprite);
//    this->addChild(btnBelowMenu2Sprite, ZORDER_BELOW_BUTTON, TAG_BELOW_GIFT_BUTTON);
    
    btnBelowMenuFrame->setRect(CCRectMake(0., 72.*2 + 1., 60., 72.));
    CCSprite *btnBelowMenu3Sprite   = CCSprite::createWithSpriteFrame(btnBelowMenuFrame);
    btnBelowMenu3Sprite->setPosition(ccp(284. + 30, ATUtil::agy(725.) - 36.));
    btnBelowMenu3Sprite->setTag(TAG_BELOW_SETTING_BUTTON);
    this->addChild(btnBelowMenu3Sprite);
//    this->addChild(btnBelowMenu3Sprite, ZORDER_BELOW_BUTTON, TAG_BELOW_SETTING_BUTTON);
    
    btnBelowMenuFrame->setRect(CCRectMake(0., 72.*3 + 1., 60., 72.));
    CCSprite *btnBelowMenu4Sprite   = CCSprite::createWithSpriteFrame(btnBelowMenuFrame);
    btnBelowMenu4Sprite->setPosition(ccp(347. + 30, ATUtil::agy(725.) - 36.));
    btnBelowMenu4Sprite->setTag(TAG_BELOW_INVITE_BUTTON);
    this->addChild(btnBelowMenu4Sprite);
//    this->addChild(btnBelowMenu4Sprite, ZORDER_BELOW_BUTTON, TAG_BELOW_INVITE_BUTTON);
    
    btnBelowMenuFrame->setRect(CCRectMake(0., 72.*4 + 1., 60., 72.));
    CCSprite *btnBelowMenu5Sprite   = CCSprite::createWithSpriteFrame(btnBelowMenuFrame);
    btnBelowMenu5Sprite->setPosition(ccp(410. + 30, ATUtil::agy(725.) - 36.));
    btnBelowMenu5Sprite->setTag(TAG_BELOW_MESSAGE_BUTTON);
    this->addChild(btnBelowMenu5Sprite);
//    this->addChild(btnBelowMenu5Sprite, ZORDER_BELOW_BUTTON, TAG_BELOW_MESSAGE_BUTTON);
    
    CCLayerColor::onEnter();
}

void BelowTapLayer::close() {
    this->removeFromParentAndCleanup(true);
}

#pragma mark -
#pragma mark Touch Delegates

bool BelowTapLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    this->touchedSprite = NULL;
    
    CCPoint pt    = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    CCSprite *belowEventButtonSprite    = (CCSprite *)this->getChildByTag(TAG_BELOW_EVENT_BUTTON);
    if (belowEventButtonSprite->boundingBox().containsPoint(pt)) {
        //        AnytaleHTTP::onHttpRequesting(this, callfuncND_selector(BaseRankingLayer::onHttpRequestCompleted), "/events/get", "", "EVENTS_GET");
        this->touchedSprite   = belowEventButtonSprite;
        this->touchedSprite->setScale(1.2);
        return true;
    }
    
    CCSprite *belowGiftButtonSprite    = (CCSprite *)this->getChildByTag(TAG_BELOW_GIFT_BUTTON);
    if (belowGiftButtonSprite->boundingBox().containsPoint(pt)) {
        this->touchedSprite   = belowGiftButtonSprite;
        this->touchedSprite->setScale(1.2);
        return true;
    }
    
    CCSprite *belowSettingButtonSprite    = (CCSprite *)this->getChildByTag(TAG_BELOW_SETTING_BUTTON);
    if (belowSettingButtonSprite->boundingBox().containsPoint(pt)) {
        this->touchedSprite   = belowSettingButtonSprite;
        this->touchedSprite->setScale(1.2);
        return true;
    }
    
    CCSprite *belowInviteButtonSprite    = (CCSprite *)this->getChildByTag(TAG_BELOW_INVITE_BUTTON);
    if (belowInviteButtonSprite->boundingBox().containsPoint(pt)) {
        this->touchedSprite   = belowInviteButtonSprite;
        this->touchedSprite->setScale(1.2);
        return true;
    }
    
    CCSprite *belowMessageButtonSprite    = (CCSprite *)this->getChildByTag(TAG_BELOW_MESSAGE_BUTTON);
    if (belowMessageButtonSprite->boundingBox().containsPoint(pt)) {
        this->touchedSprite   = belowMessageButtonSprite;
        this->touchedSprite->setScale(1.2);
        return true;
    }
    
    CCLog("BelowTapLayer return false");
    
    return false;
}

void BelowTapLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint pt    = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    if (this->touchedSprite != NULL) {
        this->touchedSprite->setScale(1.);
    }
    
    // 하단 버튼
    CCSprite *belowEventButtonSprite    = (CCSprite *)this->getChildByTag(TAG_BELOW_EVENT_BUTTON);
    if (belowEventButtonSprite->boundingBox().containsPoint(pt) && this->touchedSprite == belowEventButtonSprite) {
//        AnytaleHTTP::onHttpRequesting(this, callfuncND_selector(BaseRankingLayer::onHttpRequestCompleted), "/events/get", "", "EVENTS_GET");
        return;
    }
    
    CCSprite *belowGiftButtonSprite    = (CCSprite *)this->getChildByTag(TAG_BELOW_GIFT_BUTTON);
    if (belowGiftButtonSprite->boundingBox().containsPoint(pt) && this->touchedSprite == belowGiftButtonSprite) {
        SendingGiftLayer *sendingGiftLayer  = SendingGiftLayer::create();
        this->addChild(sendingGiftLayer);
        return;
    }
    
    CCSprite *belowSettingButtonSprite    = (CCSprite *)this->getChildByTag(TAG_BELOW_SETTING_BUTTON);
    if (belowSettingButtonSprite->boundingBox().containsPoint(pt) && this->touchedSprite == belowSettingButtonSprite) {
        SettingLayer *settingLayer  = SettingLayer::create();
        this->addChild(settingLayer);
        return;
    }
    
    CCSprite *belowInviteButtonSprite    = (CCSprite *)this->getChildByTag(TAG_BELOW_INVITE_BUTTON);
    if (belowInviteButtonSprite->boundingBox().containsPoint(pt) && this->touchedSprite == belowInviteButtonSprite) {
        InviteFriendLayer *inviteFriendLayer    = InviteFriendLayer::create();
        this->addChild(inviteFriendLayer);
        return;
    }
    
    CCSprite *belowMessageButtonSprite    = (CCSprite *)this->getChildByTag(TAG_BELOW_MESSAGE_BUTTON);
    if (belowMessageButtonSprite->boundingBox().containsPoint(pt) && this->touchedSprite == belowMessageButtonSprite) {
        MessageBoxLayer *messageBoxLayer    = MessageBoxLayer::create();
        this->addChild(messageBoxLayer);
        return;
    }
    
    this->touchedSprite = NULL;
    return;
}

void BelowTapLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate( this, 0, true );
}