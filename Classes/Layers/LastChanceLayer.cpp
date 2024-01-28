//
//  LastChanceLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 6/28/13.
//
//

#include "LastChanceLayer.h"

#include "SimpleAudioEngine.h"

bool LastChanceLayer::init() {
    //////////////////////////////
    // 1. super init first
    if (!CCLayerColor::initWithColor(ccc4(0., 0., 0., 200.)))  // RGBA
    {
        return false;
    }

    return true;
}

void LastChanceLayer::onEnter() {
    CCTexture2D *playFaceTexture =
        CCTextureCache::sharedTextureCache()->addImage("play_face.png");
    CCSprite *playFaceSprite = CCSprite::createWithTexture(
        playFaceTexture, CCRect(0., 0., 184., 182.));
    playFaceSprite->setPosition(ccp(78. + 92., 800. - 377. - 91.));  // 78,377
    this->addChild(playFaceSprite, 9999999 + 99);

    CCTexture2D *playSpeechTexture =
        CCTextureCache::sharedTextureCache()->addImage("play_speech.png");
    this->playSpeechSprite = CCSprite::createWithTexture(
        playSpeechTexture, CCRect(0., 447., 235., 149.));
    playSpeechSprite->setPosition(
        ccp(203. + 117.5, 800. - 243. - 74.5));  // 78,377
    this->addChild(playSpeechSprite, 9999999 + 99);

    this->runAction(CCSequence::create(
        CCDelayTime::create(.5),
        CCCallFunc::create(this,
                           callfunc_selector(LastChanceLayer::speechStart)),
        CCDelayTime::create(1.5),
        CCCallFunc::create(this, callfunc_selector(LastChanceLayer::close)),
        NULL));

    CCLayerColor::onEnter();
}

void LastChanceLayer::speechStart() {
    // this->schedule(SEL_SCHEDULE selector, float interval, <#unsigned int
    // repeat#>, <#float delay#>)
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
        "GA004.mp3");  // start
}

void LastChanceLayer::close() {
    CCNotificationCenter::sharedNotificationCenter()->postNotification(
        "NABUZA_LASTCHANCE_NOTIFICATION");

    this->removeFromParentAndCleanup(true);
}
