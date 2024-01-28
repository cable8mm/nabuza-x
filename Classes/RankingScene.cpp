#include "RankingScene.h"

#include "GameScene.h"
#include "Layers/BuyJadeLayer.h"
#include "Layers/ItemSelectionLayer.h"
#include "Layers/RankingLayer.h"
#include "Utilities/ATUtil.h"

USING_NS_CC;

#define ZORDER_BASERANKING_LAYER 20000

CCScene *RankingScene::scene() {
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    RankingScene *layer = RankingScene::create();

    // enable Touch
    layer->setTouchEnabled(true);

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool RankingScene::init() {
    //////////////////////////////
    // 1. super init first
    if (!CCLayer::init()) {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    // BG
    CCSprite *bgRankingSprite = CCSprite::create("bg_board_a.jpg");
    bgRankingSprite->setPosition(
        ccp(visibleSize.width / 2., visibleSize.height / 2.));
    this->addChild(bgRankingSprite);

    CCSprite *btnJewelMiniSprite = CCSprite::create("jewel_mini_btn.png");
    btnJewelMiniSprite->setPosition(ccp(7. + 78., ATUtil::agy(8.) - 30.));
    this->addChild(btnJewelMiniSprite);

    CCSprite *btnGoldSprite = CCSprite::create("gold_btn.png");
    btnGoldSprite->setPosition(ccp(238. + 112., ATUtil::agy(11.) - 30.));
    this->addChild(btnGoldSprite);

    CCSprite *letterBarSprite = CCSprite::create("letterbar.png");
    letterBarSprite->setPosition(ccp(74. + 165., ATUtil::agy(78.) - 34.));
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

    CCSprite *btnBuyInvitationSprite = CCSprite::create("letter_mini_btn.png");
    btnBuyInvitationSprite->setPosition(ccp(31. + 25., ATUtil::agy(80.) - 25.));
    this->addChild(btnBuyInvitationSprite);

    CCTexture2D *btnBelowMenusTexture =
        CCTextureCache::sharedTextureCache()->addImage("menu_btn.png");
    CCSpriteFrame *btnBelowMenuFrame = CCSpriteFrame::createWithTexture(
        btnBelowMenusTexture, CCRectMake(0., 0., 60., 72.));
    CCSprite *btnBelowMenu1Sprite =
        CCSprite::createWithSpriteFrame(btnBelowMenuFrame);
    btnBelowMenu1Sprite->setPosition(ccp(9. + 30, ATUtil::agy(725.) - 36.));
    this->addChild(btnBelowMenu1Sprite, 10000);

    btnBelowMenuFrame->setRect(CCRectMake(0., 72. + 1., 60., 72.));
    CCSprite *btnBelowMenu2Sprite =
        CCSprite::createWithSpriteFrame(btnBelowMenuFrame);
    btnBelowMenu2Sprite->setPosition(ccp(72. + 30, ATUtil::agy(725.) - 36.));
    this->addChild(btnBelowMenu2Sprite, 10000);

    btnBelowMenuFrame->setRect(CCRectMake(0., 72. * 2 + 1., 60., 72.));
    CCSprite *btnBelowMenu3Sprite =
        CCSprite::createWithSpriteFrame(btnBelowMenuFrame);
    btnBelowMenu3Sprite->setPosition(ccp(284. + 30, ATUtil::agy(725.) - 36.));
    this->addChild(btnBelowMenu3Sprite, 10000);

    btnBelowMenuFrame->setRect(CCRectMake(0., 72. * 3 + 1., 60., 72.));
    CCSprite *btnBelowMenu4Sprite =
        CCSprite::createWithSpriteFrame(btnBelowMenuFrame);
    btnBelowMenu4Sprite->setPosition(ccp(347. + 30, ATUtil::agy(725.) - 36.));
    this->addChild(btnBelowMenu4Sprite, 10000);

    btnBelowMenuFrame->setRect(CCRectMake(0., 72. * 4 + 1., 60., 72.));
    CCSprite *btnBelowMenu5Sprite =
        CCSprite::createWithSpriteFrame(btnBelowMenuFrame);
    btnBelowMenu5Sprite->setPosition(ccp(410. + 30, ATUtil::agy(725.) - 36.));
    this->addChild(btnBelowMenu5Sprite, 10000);

    CCTexture2D *btnBelowGoldTexture =
        CCTextureCache::sharedTextureCache()->addImage("menu_gs_btn.png");
    CCSpriteFrame *btnBelowGoldFrame = CCSpriteFrame::createWithTexture(
        btnBelowGoldTexture, CCRectMake(0., 0., 60., 72.));
    CCSprite *btnBelowGoldSprite =
        CCSprite::createWithSpriteFrame(btnBelowGoldFrame);
    btnBelowGoldSprite->setPosition(ccp(135. + 30, ATUtil::agy(725.) - 36.));
    this->addChild(btnBelowGoldSprite, 10000);

    CCArray *btnBelowGoldFrames = new CCArray;
    for (int i = 0; i < 4; i++) {
        btnBelowGoldFrames->addObject(CCSpriteFrame::createWithTexture(
            btnBelowGoldTexture, CCRectMake(0, 72. * i, 60., 72.)));
    }
    CCAnimation *animationTableObject =
        CCAnimation::createWithSpriteFrames(btnBelowGoldFrames, .2f);
    CCAnimate *animateTableObject = CCAnimate::create(animationTableObject);
    CCRepeatForever *repeat = CCRepeatForever::create(animateTableObject);
    CCSpeed *speed = CCSpeed::create(repeat, 1.f);
    btnBelowGoldSprite->runAction(speed);

    // 시작버튼
    CCTexture2D *btnStartTexture =
        CCTextureCache::sharedTextureCache()->addImage("start_btn.png");
    CCSpriteFrame *btnStartFrame = CCSpriteFrame::createWithTexture(
        btnStartTexture, CCRectMake(0., 0., 290., 76.));
    CCSprite *btnStartSprite = CCSprite::createWithSpriteFrame(btnStartFrame);
    btnStartSprite->setPosition(ccp(96. + 145, ATUtil::agy(641.) - 38.));
    this->addChild(btnStartSprite, 10000);

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

    // Floating RankingLayer
    this->rankingLayer = RankingLayer::create();
    this->addChild(rankingLayer, 100000);

    return true;
}

void RankingScene::onBuyJadeLayer() {
    BuyJadeLayer *buyJadeLayer = BuyJadeLayer::create();
    this->addChild(buyJadeLayer, 999999);
}

void RankingScene::ccTouchesBegan(CCSet *touches, CCEvent *event) {
}

void RankingScene::ccTouchesEnded(CCSet *touches, CCEvent *event) {
    CCLog("Click!!!");
    if (true) {
        this->itemSelectionLayer = ItemSelectionLayer::create();
        this->addChild(itemSelectionLayer, 100000);
    } else {
        CCDirector::sharedDirector()->replaceScene(GameScene::scene());
    }
    return;
}

void RankingScene::menuCloseCallback(CCObject *pSender) {
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
