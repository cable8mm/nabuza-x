//
//  SaleInvitationLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 7/29/13.
//
//

#include "SaleInvitationLayer.h"
#include "AlertTitleSprite.h"
#include "ButtonSprite.h"
#include "SaleInvitationSprite.h"
#include "JadeLessAlertViewLayer.h"
#include "../Storages/UserStorage.h"
#include "../Networks/AnytaleHTTP.h"
#include "IndicationLayer.h"

#define ZORDER_JADELESSALERTVIEW_LAYER  80000
#define ZORDER_INDICATION_LAYER         999999

#define TAG_INDICATION_LAYER            999999

#define TAG_CLOSE_BUTTON_SPRITE         70001

void SaleInvitationLayer::onEnter()
{
    this->setTouchEnabled(true);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    // BG
    CCSprite *bgRankingSprite   = CCSprite::create("title_full_alert.jpg");
    bgRankingSprite->setPosition(ccp(visibleSize.width / 2., visibleSize.height / 2.));
    this->addChild(bgRankingSprite);
    
    // TITLE
    AlertTitleSprite *alertTitleSprite  = AlertTitleSprite::createWithItemKey(kGAMEALERTTITLE_BUY_CARD);
    this->addChild(alertTitleSprite);
    
    // 닫기 버튼
    ButtonSprite *closeButtonSprite = ButtonSprite::createWithItemKey(kGAMEBUTTON_CLOSE);
    closeButtonSprite->setPosition(ccp(visibleSize.width / 2., 800.-648.-44.));
    closeButtonSprite->setTag(TAG_CLOSE_BUTTON_SPRITE);
//    ButtonSprite *closeButtonSpriteTapped = ButtonSprite::createWithItemKey(kGAMEBUTTON_CLOSE);
//    closeButtonSpriteTapped->setScale(1.2);
//    closeButtonSpriteTapped->setPosition(ccp(closeButtonSprite->getPositionX()-20., closeButtonSprite->getPositionY()-6.));
//
//    CCMenuItemSprite *closeButtonItem    = CCMenuItemSprite::create(closeButtonSprite, closeButtonSpriteTapped, this, menu_selector(SaleInvitationLayer::close));
//    CCMenu *menu    = CCMenu::create(closeButtonItem, NULL);
//    menu->alignItemsHorizontally();
//    closeButtonSprite->setPosition(ccp(visibleSize.width / 2, 800.-648.-44.));
    this->addChild(closeButtonSprite);
    
    // 초대장 리스트
    SaleInvitationSprite *jade10ButtonSprite = SaleInvitationSprite::createWithItemKey(0);
    SaleInvitationSprite *jade10ButtonSpriteTapped = SaleInvitationSprite::createWithItemKeyTapped(0);
    CCMenuItemSprite *jade10ButtonItem    = CCMenuItemSprite::create(jade10ButtonSprite, jade10ButtonSpriteTapped, this, menu_selector(SaleInvitationLayer::buyInvitation));
    jade10ButtonItem->setTag(0);
    
    SaleInvitationSprite *jade55ButtonSprite = SaleInvitationSprite::createWithItemKey(1);
    SaleInvitationSprite *jade55ButtonSpriteTapped = SaleInvitationSprite::createWithItemKeyTapped(1);
    CCMenuItemSprite *jade55ButtonItem    = CCMenuItemSprite::create(jade55ButtonSprite, jade55ButtonSpriteTapped, this, menu_selector(SaleInvitationLayer::buyInvitation));
    jade55ButtonItem->setTag(1);
    
    SaleInvitationSprite *jade120ButtonSprite = SaleInvitationSprite::createWithItemKey(2);
    SaleInvitationSprite *jade120ButtonSpriteTapped = SaleInvitationSprite::createWithItemKeyTapped(2);
    CCMenuItemSprite *jade120ButtonItem    = CCMenuItemSprite::create(jade120ButtonSprite, jade120ButtonSpriteTapped, this, menu_selector(SaleInvitationLayer::buyInvitation));
    jade120ButtonItem->setTag(2);
    
    SaleInvitationSprite *jade360ButtonSprite = SaleInvitationSprite::createWithItemKey(3);
    SaleInvitationSprite *jade360ButtonSpriteTapped = SaleInvitationSprite::createWithItemKeyTapped(3);
    CCMenuItemSprite *jade360ButtonItem    = CCMenuItemSprite::create(jade360ButtonSprite, jade360ButtonSpriteTapped, this, menu_selector(SaleInvitationLayer::buyInvitation));
    jade360ButtonItem->setTag(3);
    
    SaleInvitationSprite *jade675ButtonSprite = SaleInvitationSprite::createWithItemKey(4);
    SaleInvitationSprite *jade675ButtonSpriteTapped = SaleInvitationSprite::createWithItemKeyTapped(4);
    CCMenuItemSprite *jade675ButtonItem    = CCMenuItemSprite::create(jade675ButtonSprite, jade675ButtonSpriteTapped, this, menu_selector(SaleInvitationLayer::buyInvitation));
    jade675ButtonItem->setTag(4);
    
    CCMenu *jadeMenu    = CCMenu::create(jade10ButtonItem, jade55ButtonItem, jade120ButtonItem, jade360ButtonItem, jade675ButtonItem, NULL);
    jadeMenu->alignItemsVerticallyWithPadding(0.);
    jadeMenu->setTouchPriority(0);
    jadeMenu->setPosition(ccp(visibleSize.width / 2, 800.-364.-40.));
    this->addChild(jadeMenu);
    
    CCLayerColor::onEnter();
}

void SaleInvitationLayer::buyInvitation(CCObject *pSender) {
    int invitationProducts[5][2]    = { // {초대장, 비취 갯수}
        {5,5},
        {12,10},
        {25,20},
        {55,40},
        {150,100}
    };
    
    CCMenuItem* pMenuItem = (CCMenuItem *)(pSender);
    int tag = (int)pMenuItem->getTag();
    
    CCLog("MenuItem tag : %d", tag);
    if (invitationProducts[tag][1] > UserStorage::sharedUserStorage()->getJadeCount()) {
        JadeLessAlertViewLayer *jadeLessAlertViewLayer  = JadeLessAlertViewLayer::createWithKey(kJADELESSKEY_NOT_GOLD);
        this->addChild(jadeLessAlertViewLayer, ZORDER_JADELESSALERTVIEW_LAYER);
        return;
    }
    
    std::stringstream ss;
    ss << "&spend_count=" << invitationProducts[tag][1];
    ss << "&buyed_count=" << invitationProducts[tag][0];
    
    AnytaleHTTP::onHttpRequesting(this, callfuncND_selector(SaleInvitationLayer::onHttpRequestCompleted), "/spent_jades/buy_invitation2", ss.str().c_str(), "SPENT_JADES_BUY_INVITATION2");
    IndicationLayer *indicationLayer    = IndicationLayer::create();
    this->addChild(indicationLayer, ZORDER_INDICATION_LAYER, TAG_INDICATION_LAYER);
}


void SaleInvitationLayer::close() {
    this->removeFromParentAndCleanup(true);
}

void SaleInvitationLayer::onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response) {
    Json::Value root;
    
    int error;
    AnytaleHTTP::validateResponse(response, root, error);
    
    if (error != 0) {
        CCLog("AuthStorage json parse error");
        return;
    }
    
    // 게임 시작을 서버에 알림
    if(strcmp(response->getHttpRequest()->getTag(), "SPENT_JADES_BUY_INVITATION2") == 0) {
        /*
         {"code":0,"message":"OK","result":[]}
         */
        //        int code = root.get("code", 0).asInt();
        
        int ownJadeCount    = root["result"]["Player"].get("own_jade_count", 0).asInt();
        int buyedCount  = root["result"]["SpentJade"].get("buyed_count", 0).asInt();
        
        UserStorage::sharedUserStorage()->setOwnJadeCount(ownJadeCount);
        UserStorage::sharedUserStorage()->addCard(buyedCount);
        IndicationLayer *indicationLayer    = (IndicationLayer *)this->getChildByTag(TAG_INDICATION_LAYER);
        indicationLayer->close();
    }
    
    return;
}

bool SaleInvitationLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint pt    = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    CCSprite *closeButtonSprite    = (CCSprite *)this->getChildByTag(TAG_CLOSE_BUTTON_SPRITE);
    if (closeButtonSprite->boundingBox().containsPoint(pt)) {
        this->touchedSprite   = closeButtonSprite;
        this->touchedSprite->setScale(1.2);
        return true;
    }
    
    return false;
}

void SaleInvitationLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint pt    = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    CCSprite *btnStartSprite    = (CCSprite *)this->getChildByTag(TAG_CLOSE_BUTTON_SPRITE);
    if (btnStartSprite->boundingBox().containsPoint(pt) && this->touchedSprite == btnStartSprite) {
        this->close();
    }
    
    if (this->touchedSprite != NULL) {
        this->touchedSprite->setScale(1.);
    }
    
    this->touchedSprite = NULL;
    return;
}

void SaleInvitationLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate( this, 0, true );
}