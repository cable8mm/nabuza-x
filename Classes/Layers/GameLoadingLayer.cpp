//
//  GameLoadingLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 5/9/13.
//
//

#include "GameLoadingLayer.h"
#include "../Structs/CoinSprite.h"
#include "SimpleAudioEngine.h"

#include "../Networks/AnytaleHTTP.h"

#include "../Storages/NeedForGameMemory.h"
#include "../Storages/UserStorage.h"

GameLoadingLayer* GameLoadingLayer::createWithLevel(eGamePlayerLevels level) {
    GameLoadingLayer *pobLayer = new GameLoadingLayer;
    pobLayer->playerLevel   = level;
    
    if (pobLayer && pobLayer->init())
    {
        pobLayer->autorelease();
        return pobLayer;
    }
    CC_SAFE_DELETE(pobLayer);
    return NULL;
}

bool GameLoadingLayer::init()
{
    
    //////////////////////////////
    // 1. super init first
    if( !CCLayerColor::initWithColor(ccc4(0., 0., 0., 255.)) ) //RGBA
    {
        return false;
    }
    
    return true;
}

void GameLoadingLayer::onEnter()
{
    CCLog("GameLoadingLayer onEnter");

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    // 배경 상자
    CCSprite *whatAlertSprite = CCSprite::create("what_alert.png");
    whatAlertSprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(whatAlertSprite);
    
    // 입장 레벨 로딩 중 타이틀
    CCSprite *lvTitleSprite = CCSprite::create("lv_title.png");
    lvTitleSprite->setPosition(ccp(visibleSize.width / 2, 800.-198.-34.5));
    this->addChild(lvTitleSprite);
    
    // 고수방, 중수방, 초보방
    GameEnterLevelSprite *highLevelSprite   = GameEnterLevelSprite::createWithLevel(kGAMEPLAYERLEVEL_EXPERT);
    highLevelSprite->setPosition(ccp(visibleSize.width / 2, 800.-274.-61.));
    this->addChild(highLevelSprite);

    GameEnterLevelSprite *middleLevelSprite   = GameEnterLevelSprite::createWithLevel(kGAMEPLAYERLEVEL_ADVANCED);
    middleLevelSprite->setPosition(ccp(visibleSize.width / 2, 800.-382.-61.));
    this->addChild(middleLevelSprite);

    GameEnterLevelSprite *lowLevelSprite   = GameEnterLevelSprite::createWithLevel(kGAMEPLAYERLEVEL_BEGINNER);
    lowLevelSprite->setPosition(ccp(visibleSize.width / 2, 800.-483.-61.));
    this->addChild(lowLevelSprite);
    lowLevelSprite->onAnimating();
    // 고수 중수 초보 얼굴
    GameEnterLevelFaceSprite *highLevelFaceSprite  = GameEnterLevelFaceSprite::createWithLevel(kGAMEPLAYERLEVEL_EXPERT);
    highLevelFaceSprite->setPosition(ccp(29. + 32., 800.-274.-61.));
    this->addChild(highLevelFaceSprite);

    GameEnterLevelFaceSprite *middleLevelFaceSprite  = GameEnterLevelFaceSprite::createWithLevel(kGAMEPLAYERLEVEL_ADVANCED);
    middleLevelFaceSprite->setPosition(ccp(29. + 32., 800.-382.-61.));
    this->addChild(middleLevelFaceSprite);

    GameEnterLevelFaceSprite *lowLevelFaceSprite  = GameEnterLevelFaceSprite::createWithLevel(kGAMEPLAYERLEVEL_BEGINNER);
    lowLevelFaceSprite->setPosition(ccp(29. + 32., 800.-483.-61.));
    this->addChild(lowLevelFaceSprite);
    lowLevelFaceSprite->onAnimating();

    int ownGoldCount    = UserStorage::sharedUserStorage()->getOwnGoldCount();
    eGamePlayerLevels ownPlayerLevel;
    
    if (ownGoldCount <= 25000 ) {
        lowLevelSprite->onAnimating();
        lowLevelFaceSprite->onAnimating();
    } else if (ownGoldCount <= 400000) {
        middleLevelSprite->onAnimating();
        middleLevelFaceSprite->onAnimating();
    } else {
        highLevelSprite->onAnimating();
        highLevelFaceSprite->onAnimating();
    }
    
    CCLayerColor::onEnter();
}

void GameLoadingLayer::close() {
    this->removeFromParentAndCleanup(true);
}

const float LEVEL_IMAGE_WIDTH   = 440.;
const float LEVEL_IMAGE_HEIGHT  = 102.;

GameEnterLevelSprite* GameEnterLevelSprite::createWithLevel(eGamePlayerLevels level) {
    GameEnterLevelSprite *pobSprite = new GameEnterLevelSprite;
    
    switch (level) {
        case kGAMEPLAYERLEVEL_BEGINNER:
            pobSprite->imageName  = "lv_low_frame.png";
            break;
        case kGAMEPLAYERLEVEL_ADVANCED:
            pobSprite->imageName  = "lv_middle_frame.png";
            break;
        case kGAMEPLAYERLEVEL_EXPERT:
            pobSprite->imageName  = "lv_high_frame.png";
            break;
    }
    
    if (pobSprite && pobSprite->initWithFile(pobSprite->imageName.c_str(), CCRect(0., 0., LEVEL_IMAGE_WIDTH, LEVEL_IMAGE_HEIGHT)))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void GameEnterLevelSprite::onAnimating() {
    CCTexture2D *thisTexture  = this->getTexture();
    CCArray *thisFrames   = new CCArray;
    for (unsigned int i = 0; i < 3; i++) {
        CCSpriteFrame *thisFrame  = CCSpriteFrame::createWithTexture(thisTexture, CCRect(0, LEVEL_IMAGE_HEIGHT*i, LEVEL_IMAGE_WIDTH, LEVEL_IMAGE_HEIGHT));
        thisFrames->addObject(thisFrame);
    }
    
    CCAnimation *thisAnimation  = CCAnimation::createWithSpriteFrames(thisFrames, .2);
    CCSpeed *thisSpeed = CCSpeed::create(CCRepeatForever::create(CCAnimate::create(thisAnimation)), 1.);
    this->runAction(thisSpeed);
}

const float LEVEL_FACE_IMAGE_WIDTH   = 64.;
const float LEVEL_FACE_IMAGE_HEIGHT  = 83.;

GameEnterLevelFaceSprite* GameEnterLevelFaceSprite::createWithLevel(eGamePlayerLevels level) {
    GameEnterLevelFaceSprite *pobSprite = new GameEnterLevelFaceSprite;
    
    switch (level) {
        case kGAMEPLAYERLEVEL_BEGINNER:
            pobSprite->imageName  = "lv_low.png";
            break;
        case kGAMEPLAYERLEVEL_ADVANCED:
            pobSprite->imageName  = "lv_middle.png";
            break;
        case kGAMEPLAYERLEVEL_EXPERT:
            pobSprite->imageName  = "lv_high.png";
            break;
    }
    
    if (pobSprite && pobSprite->initWithFile(pobSprite->imageName.c_str(), CCRect(0., 0., LEVEL_FACE_IMAGE_WIDTH, LEVEL_FACE_IMAGE_HEIGHT)))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void GameEnterLevelFaceSprite::onAnimating() {
    CCTexture2D *thisTexture  = this->getTexture();
    CCArray *thisFrames   = new CCArray;
    for (unsigned int i = 0; i < 3; i++) {
        CCSpriteFrame *thisFrame  = CCSpriteFrame::createWithTexture(thisTexture, CCRect(LEVEL_FACE_IMAGE_WIDTH*i, 0, LEVEL_FACE_IMAGE_WIDTH, LEVEL_FACE_IMAGE_HEIGHT));
        thisFrames->addObject(thisFrame);
    }
    
    CCAnimation *thisAnimation  = CCAnimation::createWithSpriteFrames(thisFrames, .2);
    CCSpeed *thisSpeed = CCSpeed::create(CCRepeatForever::create(CCAnimate::create(thisAnimation)), 1.);
    this->runAction(thisSpeed);
}
