//
//  BelowStartLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 8/22/13.
//
//

#include "BelowStartLayer.h"

#include "ATUtil.h"
#include "AlertLayer.h"
#include "GameScene.h"
#include "ItemSelectionLayer.h"
#include "LetterBigSprite.h"
#include "NeedForGameMemory.h"
#include "UserStorage.h"

#define TAG_GAME_START_SPRITE 11107

BelowStartLayer::BelowStartLayer() : touchedSprite(NULL), isGameStart(false) {
}

BelowStartLayer *BelowStartLayer::createWithIsStartGame(bool v) {
    BelowStartLayer *pobLayer = new BelowStartLayer;
    pobLayer->isGameStart = v;

    if (pobLayer && pobLayer->init()) {
        pobLayer->autorelease();
        return pobLayer;
    }
    CC_SAFE_DELETE(pobLayer);
    return NULL;
}

void BelowStartLayer::onEnter() {
    this->setTouchEnabled(true);

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    // 시작버튼
    CCTexture2D *btnStartTexture =
        CCTextureCache::sharedTextureCache()->addImage("start_btn.png");
    CCSpriteFrame *btnStartFrame = CCSpriteFrame::createWithTexture(
        btnStartTexture, CCRectMake(0., 0., 290., 76.));

    // 시작 버튼을 메뉴로 만들어 보자. 왜? 커져야 하니까...
    CCSprite *btnStartSprite = CCSprite::createWithSpriteFrame(btnStartFrame);
    btnStartSprite->setTag(TAG_GAME_START_SPRITE);
    btnStartSprite->setPosition(
        ccp(visibleSize.width / 2, ATUtil::agy(641.) - 38.));
    this->addChild(btnStartSprite);

    CCArray *btnStartFrames = new CCArray;
    for (int i = 0; i < 6; i++) {
        btnStartFrames->addObject(CCSpriteFrame::createWithTexture(
            btnStartTexture, CCRectMake(0, 76. * i, 290., 76.)));
    }
    CCAnimation *animationBtnStart =
        CCAnimation::createWithSpriteFrames(btnStartFrames, .2f);
    CCAnimate *animateBtnStart = CCAnimate::create(animationBtnStart);
    CCRepeatForever *repeatAnimateBtnStart =
        CCRepeatForever::create(animateBtnStart);
    CCSpeed *speedAnimateBtnStart = CCSpeed::create(repeatAnimateBtnStart, 1.f);
    btnStartSprite->runAction(speedAnimateBtnStart);
    CCLog("BelowStartLayer ZOrder : %d", this->getZOrder());
    CCLayerColor::onEnter();
}

void BelowStartLayer::onStartGame() {
    if (!this->isGameStart) {
        ItemSelectionLayer *itemSelectionLayer = ItemSelectionLayer::create();
        this->addChild(itemSelectionLayer);
    } else {
        if (UserStorage::sharedUserStorage()->getJadeCount() <
            NeedForGameMemory::sharedNeedForGameMemory()->getJadeCount()) {
            AlertLayer::sharedAlertLayer()->show(
                "비취 부족", "비취가 부족합니다.\n비취를 구매해 주세요.");

            //            AlertLayer *alertLayer  =
            //            AlertLayer::createWithMessage("비취 부족", "비취가
            //            부족합니다.\n비취를 구매해 주세요.");
            //            this->addChild(alertLayer);
            //            CCMessageBox("비취가 부족합니다.\n비취를 구매해
            //            주세요.", "비취 부족");
            return;
        }

        if (UserStorage::sharedUserStorage()->getCardCount() < 1) {
            AlertLayer::sharedAlertLayer()->show("초대장 부족",
                                                 "초대장이 부족합니다.");
            //            AlertLayer *alertLayer  =
            //            AlertLayer::createWithMessage("초대장 부족", "초대장이
            //            부족합니다."); this->addChild(alertLayer);
            return;
        }

        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

        int cardCount = UserStorage::sharedUserStorage()->getCardCount() > 5
                            ? 5
                            : UserStorage::sharedUserStorage()->getCardCount();
        //        float x = cardCount * 44. + 127.+25.+44.;
        float x = visibleSize.width / 2 - 44 * 3 + 44 * cardCount;
        LetterBigSprite *letterBigSprite = LetterBigSprite::createWithPosition(
            ccp(x, 684.), callfunc_selector(BelowStartLayer::replaceGameScene));
        letterBigSprite->setAnchorPoint(ccp(.5, .5));
        this->addChild(letterBigSprite);
        letterBigSprite->runAnimation();
        UserStorage::sharedUserStorage()->addCard(-1);
    }
}

void BelowStartLayer::replaceGameScene() {
    NeedForGameMemory::sharedNeedForGameMemory()->setCardCount(1);
    CCDirector::sharedDirector()->replaceScene(GameScene::scene());
}

void BelowStartLayer::close() {
    this->removeFromParentAndCleanup(true);
}

#pragma mark -
#pragma mark Touch Delegates

bool BelowStartLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    this->touchedSprite = NULL;

    CCPoint pt =
        CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());

    CCSprite *btnStartSprite =
        (CCSprite *)this->getChildByTag(TAG_GAME_START_SPRITE);
    if (btnStartSprite->boundingBox().containsPoint(pt)) {
        this->touchedSprite = btnStartSprite;
        this->touchedSprite->setScale(1.2);
        return true;
    }

    return false;
}

void BelowStartLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint pt =
        CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());

    CCSprite *btnStartSprite =
        (CCSprite *)this->getChildByTag(TAG_GAME_START_SPRITE);
    if (btnStartSprite->boundingBox().containsPoint(pt) &&
        this->touchedSprite == btnStartSprite) {
        this->touchedSprite->setScale(1.);
        this->onStartGame();
    }

    if (this->touchedSprite != NULL) {
        this->touchedSprite->setScale(1.);
    }

    this->touchedSprite = NULL;
    return;
}

void BelowStartLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
        this, 0, true);
}