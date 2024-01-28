//
//  TimeOverLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 6/27/13.
//
//

#include "TimeOverLayer.h"

#include "SimpleAudioEngine.h"

void TimeOverLayer::onEnter() {
    this->setTouchEnabled(true);

    CCTexture2D *playFaceTexture =
        CCTextureCache::sharedTextureCache()->addImage("play_face.png");
    CCSprite *playFaceSprite = CCSprite::createWithTexture(
        playFaceTexture, CCRect(0., 182., 184., 182.));
    playFaceSprite->setPosition(ccp(78. + 92., 800. - 377. - 91.));  // 78,377
    this->addChild(playFaceSprite);

    CCTexture2D *playSpeechTexture =
        CCTextureCache::sharedTextureCache()->addImage("play_speech.png");
    CCSprite *playSpeechSprite = CCSprite::createWithTexture(
        playSpeechTexture, CCRect(0., 149. * 2, 235., 149.));
    playSpeechSprite->setPosition(
        ccp(203. + 117.5, 800. - 243. - 74.5));  // 78,377
    this->addChild(playSpeechSprite, 9999999 + 99);

    this->runAction(CCSequence::create(
        CCDelayTime::create(1.),
        CCCallFunc::create(this, callfunc_selector(TimeOverLayer::speechStart)),
        CCDelayTime::create(.5),
        CCCallFunc::create(this, callfunc_selector(TimeOverLayer::close)),
        NULL));

    CCLayerColor::onEnter();
}

void TimeOverLayer::speechStart() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
        "GA003.mp3");  // start
}

void TimeOverLayer::close() {
    CCNotificationCenter::sharedNotificationCenter()->postNotification(
        "TIME_OVER_LAYER_DONE_NOTIFICATION");
    this->removeFromParentAndCleanup(true);
}

#pragma mark -
#pragma mark Touch Delegates

bool TimeOverLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    return true;
}

void TimeOverLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
        this, 0, true);
}