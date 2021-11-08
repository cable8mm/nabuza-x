//
//  BaseScene.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 5/27/13.
//
//

#include "BaseScene.h"
#include "Utilities/ATUtil.h"
#include "GameScene.h"

#include "Layers/RankingLayer.h"

#include "SimpleAudioEngine.h"

#include "Storages/UserStorage.h"
#include "Layers/BuyJadeLayer.h"
#include "Layers/BuyGoldLayer.h"
#include "Layers/TopJadeGoldLayer.h"
#include "Layers/BelowTapLayer.h"
#include "Layers/NoticeLayer.h"
#include "Layers/CardLayer.h"

#include "Layers/AlertLayer.h"

#define ZORDER_TOP_JADE_BUTTON      50200
#define ZORDER_TOP_GOLD_BUTTON      50200
#define ZORDER_BASE_RANKING_LAYER   20000
#define ZORDER_BASE_BG              10100
#define ZORDER_BUY_JADE_LAYER       100000
#define ZORDER_BUY_GOLD_LAYER       100000

#define TAG_TOP_JADE_BUTTON         50200
#define TAG_TOP_GOLD_BUTTON         50201

CCScene* BaseScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    BaseScene *layer = BaseScene::create();
    
    // enable Touch
    layer->setTouchEnabled(true);
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool BaseScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    return true;
}

void BaseScene::onEnter() {
    // 공지사항
//    NoticeLayer *noticeLayer    = NoticeLayer::create();
//    this->addChild(noticeLayer, ZORDER_BUY_JADE_LAYER);
    
    playBgm();
    
    if (!UserStorage::sharedUserStorage()->getIsBgm()) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    }
    
    if (!UserStorage::sharedUserStorage()->getIsEffect()) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    }
    
    RankingLayer *rankingLayer  = RankingLayer::create();
    this->addChild(rankingLayer, 1000);
    
    AlertLayer *alertLayer  = AlertLayer::sharedAlertLayer();
    this->addChild(alertLayer, 10000);
    
    CCLayer::onEnter();
}

BaseScene::~BaseScene() {
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

void playBgm() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("BG001.mp3", true);
    return;
}
