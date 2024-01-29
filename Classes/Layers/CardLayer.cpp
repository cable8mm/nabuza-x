//
//  CardLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 6/28/13.
//
//

#include "CardLayer.h"

#include "ATUtil.h"
#include "SaleInvitationLayer.h"

#define DEFAULT_FONT_NAME "Helvetica"

#define MAX_CARD_COUNT 5

#define TAG_CARD_SPRITE_INITIAL 800
#define TAG_CARD_COUNT_BG_SPRITE 900
#define TAG_CARD_COUNT_LABEL 910
#define TAG_PLUS_SPRITE 912
#define TAG_MAX_LABEL 913

void CardLayer::onEnter() {
    this->setTouchEnabled(true);

    CCNotificationCenter::sharedNotificationCenter()->addObserver(
        this, callfuncO_selector(CardLayer::onChangedCardCount),
        "OWN_CARD_COUNT_CHANGED_NOTIFICATION", NULL);

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    CCSprite *letterBarSprite = CCSprite::create("letterbar.png");
    letterBarSprite->setPosition(
        ccp(visibleSize.width / 2, ATUtil::agy(78.) - 34.));
    this->addChild(letterBarSprite);

    CCTexture2D *leftLetterTexture =
        CCTextureCache::sharedTextureCache()->addImage("letter_c.png");
    CCTexture2D *rightLetterTexture =
        CCTextureCache::sharedTextureCache()->addImage("letter_c_r.png");

    CCSprite *leftLetterSprite = CCSprite::createWithTexture(leftLetterTexture);
    leftLetterSprite->setPosition(ccp(77. + 30., ATUtil::agy(80.) - 30.));
    this->addChild(leftLetterSprite);

    CCSprite *rightLetterSprite =
        CCSprite::createWithTexture(leftLetterTexture);
    rightLetterSprite->setPosition(ccp(342. + 30., ATUtil::agy(80.) - 30.));
    this->addChild(rightLetterSprite);

    for (unsigned int i = 0; i < 2; i++) {
        CCArray *btnletterBarFrames = new CCArray;
        for (unsigned int ii = 0; ii < 5; ii++) {
            if (i == 0) {
                btnletterBarFrames->addObject(CCSpriteFrame::createWithTexture(
                    leftLetterTexture, CCRectMake(0, 60. * ii, 60., 60.)));
            } else {
                btnletterBarFrames->addObject(CCSpriteFrame::createWithTexture(
                    rightLetterTexture, CCRectMake(0, 60. * ii, 60., 60.)));
            }
        }
        CCAnimation *animationTableObject =
            CCAnimation::createWithSpriteFrames(btnletterBarFrames, .2f);
        CCAnimate *animateTableObject = CCAnimate::create(animationTableObject);
        CCRepeatForever *repeat = CCRepeatForever::create(animateTableObject);
        CCSpeed *speed = CCSpeed::create(repeat, 1.f);

        if (i == 0) {
            leftLetterSprite->runAction(speed);
        } else {
            rightLetterSprite->runAction(speed);
        }
    }

    // 카드 5개
    for (unsigned int i = 0; i < MAX_CARD_COUNT; i++) {
        CCSprite *cardSprite = CCSprite::create("letter.png");
        cardSprite->setPosition(ccp(127. + 25. + 44. * i, 800. - 91. - 25.));
        cardSprite->setTag(TAG_CARD_SPRITE_INITIAL + i);
        cardSprite->setVisible(false);
        this->addChild(cardSprite);
    }

    // 카드 옆에 원갯수
    CCSprite *bgCardCountSprite = CCSprite::create("count.png");
    bgCardCountSprite->setPosition(ccp(355., 800. - 75. - 20.));
    bgCardCountSprite->setTag(TAG_CARD_COUNT_BG_SPRITE);
    bgCardCountSprite->setVisible(false);
    this->addChild(bgCardCountSprite);

    // 카드 갯수
    CCLabelTTF *lbCircleCardCount =
        CCLabelTTF::create("", DEFAULT_FONT_NAME, 16);
    lbCircleCardCount->setPosition(ccp(355., 800. - 75. - 20.));
    lbCircleCardCount->setAnchorPoint(ccp(.5, .5));
    lbCircleCardCount->setTag(TAG_CARD_COUNT_LABEL);
    this->addChild(lbCircleCardCount);

    // 플러스 버튼
    CCSprite *plusMaxSprite = CCSprite::create("letter_mini_btn.png");
    plusMaxSprite->setPosition(ccp(40., 800. - 80. - 30.));
    plusMaxSprite->setTag(TAG_PLUS_SPRITE);
    this->addChild(plusMaxSprite);

    // 플러스 버튼 밑의 MAX 표시(카드가 5개 이상이면 MAX가 뜨고, 4개까지 일 경우
    // 시간이 뜬다.)
    CCLabelTTF *lbRemainSeconds = CCLabelTTF::create("", DEFAULT_FONT_NAME, 18);
    lbRemainSeconds->setPosition(ccp(40., 800. - 80. - 30. - 30.));
    lbRemainSeconds->setColor(ccBLACK);
    lbRemainSeconds->setTag(TAG_MAX_LABEL);
    this->addChild(lbRemainSeconds);

    int ownCardCount = UserStorage::sharedUserStorage()->getCardCount();
    unsigned int diffSeconds =
        UserStorage::sharedUserStorage()->getDiffSeconds();
    int displayCardCount =
        ownCardCount > MAX_CARD_COUNT ? MAX_CARD_COUNT : ownCardCount;

    this->setDisplayCardCount(displayCardCount);
    CCLog("CardLayer Initial CardCount : %d", ownCardCount);

    // MAX 버튼 고고
    if (ownCardCount < 5) {
        this->countDownClock = (int)(REMAIN_SECONDS_FOR_CARD - diffSeconds);
        this->tick();
        this->schedule(schedule_selector(CardLayer::tick), 1);
    } else {
        lbRemainSeconds->setString("MAX");
    }

    CCLayerColor::onEnter();
}

void CardLayer::setDisplayCardCount(int cardCount) {
    int visibleCardCount =
        cardCount > MAX_CARD_COUNT ? MAX_CARD_COUNT : cardCount;
    CCLog("cardCount : %d, visibleCardCount : %d", cardCount, visibleCardCount);
    // 카드
    for (unsigned int i = 0; i < MAX_CARD_COUNT; i++) {
        CCSprite *cardSprite =
            (CCSprite *)this->getChildByTag(TAG_CARD_SPRITE_INITIAL + i);
        if (visibleCardCount > i) {
            cardSprite->setVisible(true);
        } else {
            cardSprite->setVisible(false);
        }
    }

    // 카드 갯수
    CCSprite *bgCardCountSprite =
        (CCSprite *)this->getChildByTag(TAG_CARD_COUNT_BG_SPRITE);
    CCLabelTTF *lbCircleCardCount =
        (CCLabelTTF *)this->getChildByTag(TAG_CARD_COUNT_LABEL);

    if (cardCount > MAX_CARD_COUNT) {
        bgCardCountSprite->setVisible(true);

        std::stringstream ss;
        ss << cardCount - MAX_CARD_COUNT;
        lbCircleCardCount->setString(ss.str().c_str());
    } else {
        bgCardCountSprite->setVisible(false);
        lbCircleCardCount->setString("");
    }
}

void CardLayer::onChangedCardCount(CCObject *obj) {
    CCInteger *ownCardCount = (CCInteger *)obj;
    CCAssert(ownCardCount->getValue() > -1, "Card Count must over -1");

    this->setDisplayCardCount(ownCardCount->getValue());

    if (UserStorage::sharedUserStorage()->isCardFulled() == false) {
        UserStorage::sharedUserStorage()->setCountDownClock();
        this->countDownClock = REMAIN_SECONDS_FOR_CARD;  // 10분
        this->schedule(schedule_selector(CardLayer::tick), 1);
    }
}

void CardLayer::tick() {
    CCLabelTTF *lbRemainSeconds =
        (CCLabelTTF *)this->getChildByTag(TAG_MAX_LABEL);
    this->countDownClock--;
    int remainMinutes = (int)floorf(this->countDownClock / 60);
    int remainSeconds = (int)(this->countDownClock % 60);
    std::stringstream ss;
    ss << remainMinutes << ":" << remainSeconds;
    lbRemainSeconds->setString(ss.str().c_str());

    if (this->countDownClock < 1) {  // 10분이 다 지났을 때, 카드를 하나 올린다.
        UserStorage::sharedUserStorage()->addCard(1);
        if (UserStorage::sharedUserStorage()->isCardFulled()) {
            this->unschedule(schedule_selector(CardLayer::tick));
            lbRemainSeconds->setString("MAX");
        }
        this->countDownClock = REMAIN_SECONDS_FOR_CARD;
    }
}

void CardLayer::close() {
    this->removeFromParentAndCleanup(true);
}

CardLayer::~CardLayer() {
    this->unschedule(schedule_selector(CardLayer::tick));
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

bool CardLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint pt =
        CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());

    CCSprite *plusMaxSprite = (CCSprite *)this->getChildByTag(TAG_PLUS_SPRITE);
    if (plusMaxSprite->boundingBox().containsPoint(pt)) {
        plusMaxSprite->setScale(1.2);
        return true;
    }

    return false;
}

void CardLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint pt =
        CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());

    CCSprite *plusMaxSprite = (CCSprite *)this->getChildByTag(TAG_PLUS_SPRITE);
    if (plusMaxSprite->boundingBox().containsPoint(pt)) {
        plusMaxSprite->setScale(1.);
        SaleInvitationLayer *saleInvitationLayer =
            SaleInvitationLayer::create();
        this->addChild(saleInvitationLayer);
    }
}

void CardLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
        this, 0, true);
}