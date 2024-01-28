//
//  InviteFriendLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 7/4/13.
//
//

#include "InviteFriendLayer.h"

#include "AlertTitleSprite.h"
#include "AnytaleHTTP.h"
#include "ButtonSprite.h"
#include "SMSLayer.h"
#include "UserStorage.h"

void InviteFriendLayer::onEnter() {
    this->setTouchEnabled(true);

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    // BG
    CCSprite *bgRankingSprite = CCSprite::create("title_full_alert.jpg");
    bgRankingSprite->setPosition(
        ccp(visibleSize.width / 2., visibleSize.height / 2.));
    this->addChild(bgRankingSprite);

    // TITLE
    AlertTitleSprite *alertTitleSprite =
        AlertTitleSprite::createWithItemKey(kGAMEALERTTITLE_INVITING_FRIEND);
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
                                 this, menu_selector(InviteFriendLayer::close));
    CCMenu *menu = CCMenu::create(closeButtonItem, NULL);
    menu->setPosition(ccp(visibleSize.width / 2, 800. - 648. - 44.));
    this->addChild(menu);

    // 메시지 배경
    CCSprite *bgInvitationSprite = CCSprite::create("invitation_box.png");
    bgInvitationSprite->setPosition(
        ccp(visibleSize.width / 2, 800. - 210. - 84.5));
    this->addChild(bgInvitationSprite);

    // 초대 버튼 SMS / KAKAO TALK
    CCSprite *smsButtonSprite = CCSprite::create("invitation_btn.png");
    CCSprite *smsButtonSelectedSprite = CCSprite::create("invitation_btn.png");
    smsButtonSelectedSprite->setScale(1.2);
    smsButtonSelectedSprite->setPosition(
        ccp(smsButtonSprite->getPositionX() - 16.,
            smsButtonSprite->getPositionY() - 16.));

    CCSprite *kakaoButtonSprite = CCSprite::create("invitation_kakao_btn.png");
    CCSprite *kakaoButtonSelectedSprite =
        CCSprite::create("invitation_kakao_btn.png");
    kakaoButtonSelectedSprite->setScale(1.2);
    kakaoButtonSelectedSprite->setPosition(
        ccp(kakaoButtonSprite->getPositionX() - 16.,
            kakaoButtonSprite->getPositionY() - 16.));

    CCMenuItemSprite *smsButtonItem =
        CCMenuItemSprite::create(smsButtonSprite, smsButtonSelectedSprite, this,
                                 menu_selector(InviteFriendLayer::sms));
    CCMenuItemSprite *kakaoButtonItem = CCMenuItemSprite::create(
        kakaoButtonSprite, kakaoButtonSelectedSprite, this,
        menu_selector(InviteFriendLayer::kakaotalk));
    CCMenu *invitationMenu =
        CCMenu::create(smsButtonItem, kakaoButtonItem, NULL);
    invitationMenu->alignItemsHorizontallyWithPadding(40.);
    invitationMenu->setPosition(ccp(visibleSize.width / 2, 800. - 396. - 101.));
    this->addChild(invitationMenu);

    // 메시지
    AnytaleHTTP::onHttpRequesting(
        this, callfuncND_selector(InviteFriendLayer::onHttpRequestCompleted),
        "/invitation_messages/get", "", "INVITATION_MESSAGES_GET");

    CCLayerColor::onEnter();
}

void InviteFriendLayer::onHttpRequestCompleted(CCHttpClient *sender,
                                               CCHttpResponse *response) {
    Json::Value root;

    int error;
    AnytaleHTTP::validateResponse(response, root, error);

    if (error != 0) {
        CCLog("AuthStorage json parse error");
        return;
    }

    // 게임 시작을 서버에 알림
    if (strcmp(response->getHttpRequest()->getTag(),
               "INVITATION_MESSAGES_GET") == 0) {
        /*
         {"code":0,"message":"OK","result":[]}
         */
        this->kakaotalkMessage = root["result"]["InvitationMessage"]
                                     .get("kakaotalk_message", "")
                                     .asString();
        this->smsMessage = root["result"]["InvitationMessage"]
                               .get("sms_message", "")
                               .asString();

        std::string replacedString = "%nickname%";
        std::string replacingString =
            UserStorage::sharedUserStorage()->getNickname();

        //  치환
        for (std::string::size_type position = 0;
             (position = this->kakaotalkMessage.find(
                  replacedString, position)) != std::string::npos;
             ++position)
            this->kakaotalkMessage.replace(position, replacedString.size(),
                                           replacingString);

        for (std::string::size_type position = 0;
             (position = this->smsMessage.find(replacedString, position)) !=
             std::string::npos;
             ++position)
            this->smsMessage.replace(position, replacedString.size(),
                                     replacingString);

        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

        CCLabelTTF *lbNabuzaInfomation = CCLabelTTF::create(
            this->kakaotalkMessage.c_str(), "JejuGothic", 16);
        lbNabuzaInfomation->setHorizontalAlignment(kCCTextAlignmentCenter);
        lbNabuzaInfomation->setPosition(
            ccp(visibleSize.width / 2, 800. - 257. - 35.));
        lbNabuzaInfomation->setAnchorPoint(ccp(.5, .5));
        lbNabuzaInfomation->setColor(ccBLACK);
        this->addChild(lbNabuzaInfomation);

        //        int code = root.get("code", 0).asInt();
        //        int remainJadeCount =
        //        root["result"]["Player"].get("own_jade_count", 0).asInt(); int
        //        remainCardCount =
        //        root["result"]["Player"].get("invitation_count", 0).asInt();
        //        int remainGoldCount = root["result"]["Player"].get("own_gold",
        //        0).asInt();
    }

    return;
}

void InviteFriendLayer::sms() {
    SMSLayer *smsLayer = SMSLayer::createWithMessage(this->smsMessage.c_str());
    this->addChild(smsLayer);
}

void InviteFriendLayer::kakaotalk() {
}

void InviteFriendLayer::close() {
    this->removeFromParentAndCleanup(true);
}

#pragma mark -
#pragma mark Touch Delegates

void InviteFriendLayer::ccTouchEnded(CCTouch *touch, CCEvent *event) {
    CCPoint pt =
        CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
}

void InviteFriendLayer::ccTouchCancelled(CCTouch *touch, CCEvent *pEvent) {
    CCLog("Cancel");
}

bool InviteFriendLayer::ccTouchBegan(CCTouch *touch, CCEvent *pEvent) {
    return true;
}

void InviteFriendLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
        this, 0, true);
}
