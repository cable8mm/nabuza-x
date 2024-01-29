//
//  GameEventLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 7/3/13.
//
//

#include "GameEventLayer.h"

#include "AlertTitleSprite.h"
#include "ButtonSprite.h"

GameEventLayer *GameEventLayer::createWithEventResult(eGameEventResults key) {
    GameEventLayer *pobSprite = new GameEventLayer;

    pobSprite->gameEventResult = key;

    if (pobSprite && pobSprite->init()) {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void GameEventLayer::onEnter() {
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    // BG
    CCSprite *bgRankingSprite = CCSprite::create("event123_bg.jpg");
    bgRankingSprite->setPosition(
        ccp(visibleSize.width / 2., visibleSize.height / 2.));
    this->addChild(bgRankingSprite);

    switch (this->gameEventResult) {
        case kGAMEEVENTRESULT_FAILURE: {
            // TITLE
            AlertTitleSprite *alertTitleSprite =
                AlertTitleSprite::createWithItemKey(kGAMEALERTTITLE_LOSING);
            this->addChild(alertTitleSprite);

            // 아쉽지만 당첨되지 않았어요.
            CCLabelTTF *lbMessage = CCLabelTTF::create(
                "아쉽지만 당첨되지 않았어요.\n다음 기회를 이용해 주세요.",
                "JejuGothic", 26);
            lbMessage->setPosition(ccp(visibleSize.width / 2, 800. - 260.));
            lbMessage->setAnchorPoint(ccp(.5, .5));
            lbMessage->setColor(ccBLACK);
            this->addChild(lbMessage);

            // 캐릭터
            CCTexture2D *characterTexture =
                CCTextureCache::sharedTextureCache()->addImage(
                    "character_2.png");
            CCArray *characterFrames = new CCArray;
            for (unsigned int i = 0; i < 2; i++) {
                CCSpriteFrame *characterFrame =
                    CCSpriteFrame::createWithTexture(
                        characterTexture, CCRect(180. * i, 0, 180., 250.));
                characterFrames->addObject(characterFrame);
            }
            CCAnimation *characterAnimation =
                CCAnimation::createWithSpriteFrames(characterFrames, .1);

            CCSprite *character = CCSprite::createWithTexture(
                characterTexture, CCRect(0., 0., 180., 250.));
            character->setPosition(ccp(visibleSize.width / 2, 800. - 430.));
            this->addChild(character);

            character->runAction(CCSpeed::create(
                CCRepeatForever::create(CCAnimate::create(characterAnimation)),
                .5));
        } break;
        case kGAMEEVENTRESULT_FIRST:
        case kGAMEEVENTRESULT_SECOND:
        case kGAMEEVENTRESULT_THIRD:
            // 아우라 배경
            CCTexture2D *resultBgTexture =
                CCTextureCache::sharedTextureCache()->addImage("result_bg.png");
            CCArray *resultBgFrames = new CCArray;
            for (unsigned int i = 0; i < 2; i++) {
                CCSpriteFrame *resultBgFrame = CCSpriteFrame::createWithTexture(
                    resultBgTexture, CCRect(0., 436. * i, 436., 436.));
                resultBgFrames->addObject(resultBgFrame);
            }

            CCSprite *resultBgSprite = CCSprite::createWithTexture(
                resultBgTexture, CCRect(0., 0., 436., 436.));
            resultBgSprite->setPosition(
                ccp(visibleSize.width / 2, 800. - 3. - 218.));
            this->addChild(resultBgSprite);

            resultBgSprite->runAction(CCSpeed::create(
                CCRepeatForever::create(CCAnimate::create(
                    CCAnimation::createWithSpriteFrames(resultBgFrames, .1))),
                .5));
            // 나부자 케릭터
            CCSprite *nabuzaCharacterSprite = CCSprite::create(
                "result_winner.png",
                CCRect(0., 290. * this->gameEventResult, 466., 290.));
            nabuzaCharacterSprite->setPosition(
                ccp(visibleSize.width / 2, 800. - 64. - 145.));
            this->addChild(nabuzaCharacterSprite);

            // 깃발
            CCSprite *eventFlagSprite = CCSprite::create("result_flag.png");
            eventFlagSprite->setPosition(
                ccp(visibleSize.width / 2, 800. - 288. - 63.));
            this->addChild(eventFlagSprite);

            // 썬그라스
            CCTexture2D *resultAccTexture =
                CCTextureCache::sharedTextureCache()->addImage(
                    "result_acc.png");
            CCArray *resultAccFrames = new CCArray;
            for (unsigned int i = 0; i < 4; i++) {
                CCSpriteFrame *resultAccFrame =
                    CCSpriteFrame::createWithTexture(
                        resultAccTexture, CCRect(0., 42. * i, 122., 42.));
                resultAccFrames->addObject(resultAccFrame);
            }

            CCSprite *resultAccSprite = CCSprite::createWithTexture(
                resultAccTexture, CCRect(0., 0., 122., 42.));
            resultAccSprite->setPosition(
                ccp(visibleSize.width / 2, 800. - 145. - 21.));
            this->addChild(resultAccSprite);

            resultAccSprite->runAction(CCSpeed::create(
                CCRepeatForever::create(CCAnimate::create(
                    CCAnimation::createWithSpriteFrames(resultAccFrames, .1))),
                .5));

            // 등에 당첨되셨습니다. 확인을 누르시면 를 드립니다.
            CCSprite *messageSprite =
                CCSprite::create("to_event_7_res_text2.png");
            messageSprite->setPosition(
                ccp(visibleSize.width / 2, 800. - 393. - 92.));
            this->addChild(messageSprite);

            // 등수
            CCSprite *rankingSprite = CCSprite::create(
                "to_event_7_res_123.png",
                CCRect(0., this->gameEventResult * 46., 46., 46.));
            rankingSprite->setPosition(ccp(105. + 23., 800. - 390. - 23.));
            this->addChild(rankingSprite);

            // ...를 드립니다 할 때 ...
            CCSprite *rewardSprite = CCSprite::create(
                "result_bar.png",
                CCRect(0., this->gameEventResult * 48., 240., 48.));
            rewardSprite->setPosition(ccp(88. + 120., 800. - 457. - 24.));
            this->addChild(rewardSprite);

            CCSprite *jadeGoldSprite =
                CCSprite::create("to_event_7.png", CCRect(0., 0., 48., 48));
            jadeGoldSprite->setPosition(ccp(96. + 24., 800. - 457. - 24.));
            this->addChild(jadeGoldSprite);

            // 상품 점수
            CCLabelTTF *lbRewardCount =
                CCLabelTTF::create("+1000", "JejuGothic", 22);
            lbRewardCount->setPosition(ccp(78. + 200., 800. - 457. - 24.));
            lbRewardCount->setAnchorPoint(ccp(1., .5));
            lbRewardCount->setColor(ccBLACK);
            this->addChild(lbRewardCount);

            break;
    }

    // 닫기 버튼
    ButtonSprite *closingButtonSprite =
        ButtonSprite::createWithItemKey(kGAMEBUTTON_CLOSE);
    ButtonSprite *closingButtonSpriteTapped =
        ButtonSprite::createWithItemKey(kGAMEBUTTON_CLOSE);
    closingButtonSpriteTapped->setScale(1.2);
    closingButtonSpriteTapped->setPosition(
        ccp(closingButtonSprite->getPositionX() - 20.,
            closingButtonSprite->getPositionY() - 6.));

    CCMenuItemSprite *closeButtonItem =
        CCMenuItemSprite::create(closingButtonSprite, closingButtonSpriteTapped,
                                 this, menu_selector(GameEventLayer::close));
    CCMenu *menu = CCMenu::create(closeButtonItem, NULL);
    menu->setPosition(ccp(visibleSize.width / 2, 800. - 648. - 44.));

    this->addChild(menu);

    CCLayerColor::onEnter();
}

void GameEventLayer::close() {
    CCNotificationCenter::sharedNotificationCenter()->postNotification(
        "NABUZA_END_GAMEEVENT_NOTIFICATION");
    this->removeFromParentAndCleanup(true);
}