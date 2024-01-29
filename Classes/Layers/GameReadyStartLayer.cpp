//
//  GameReadyStartLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 5/10/13.
//
//

#include "GameReadyStartLayer.h"

#include "SimpleAudioEngine.h"

// GameReadyStartLayer* GameReadyStartLayer::createWithCustom() {
//     GameReadyStartLayer *gameReadyStartLayer  =
//     GameReadyStartLayer::create(); gameReadyStartLayer->setColor(ccc3(0., 0.,
//     0.)); gameReadyStartLayer->setOpacity(0.); return gameReadyStartLayer;
// }

void GameReadyStartLayer::onEnter() {
    this->setTouchEnabled(true);

    CCTexture2D *playFaceTexture =
        CCTextureCache::sharedTextureCache()->addImage("play_face.png");
    CCSprite *playFaceSprite = CCSprite::createWithTexture(
        playFaceTexture, CCRect(0., 0., 184., 182.));
    playFaceSprite->setPosition(ccp(78. + 92., 800. - 377. - 91.));  // 78,377
    this->addChild(playFaceSprite, 9999999 + 99);

    CCTexture2D *playSpeechTexture =
        CCTextureCache::sharedTextureCache()->addImage("play_speech.png");
    this->playSpeechSprite = CCSprite::createWithTexture(
        playSpeechTexture, CCRect(0., 0., 235., 149.));
    playSpeechSprite->setPosition(
        ccp(203. + 117.5, 800. - 243. - 74.5));  // 78,377
    this->addChild(playSpeechSprite, 9999999 + 99);

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
        "GA001.mp3");  // Ready

    this->runAction(CCSequence::create(
        CCDelayTime::create(1.),
        CCCallFunc::create(this,
                           callfunc_selector(GameReadyStartLayer::speechStart)),
        CCDelayTime::create(.5),
        CCCallFunc::create(this, callfunc_selector(GameReadyStartLayer::close)),
        NULL));

    CCLayerColor::onEnter();
}

void GameReadyStartLayer::speechStart() {
    this->playSpeechSprite->setTextureRect(CCRect(0., 149., 235., 149.));
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
        "GA002.mp3");  // start
}

void GameReadyStartLayer::close() {
    CCNotificationCenter::sharedNotificationCenter()->postNotification(
        "NABUZA_PLAYING_NOTIFICATION");
    this->removeFromParentAndCleanup(true);
}

#pragma mark -
#pragma mark Touch Delegates

bool GameReadyStartLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    return true;
}

void GameReadyStartLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
        this, 0, true);
}