//
//  GameBgLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 5/20/13.
//
//

#include "GameBgLayer.h"

GameBgLayer::GameBgLayer(void)
:isNabuzaTime(false) {
}

// on "init" you need to initialize your instance
bool GameBgLayer::init()
{
    
    //////////////////////////////
    // 1. super init first
    if( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)) ) //RGBA
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCTexture2D *playBgTopTexture   = CCTextureCache::sharedTextureCache()->textureForKey("play_bg_n_top.png");
    this->playBgTopSprite   = CCSprite::createWithTexture(playBgTopTexture, CCRect(0.,0.,480.,118.));
    this->playBgTopSprite->setPosition(ccp(visibleSize.width / 2., 800.-59.));
    this->addChild(this->playBgTopSprite);

    CCTexture2D *playBgBottomTexture   = CCTextureCache::sharedTextureCache()->textureForKey("play_bg_n_bottom.png");
    this->playBgBottomSprite   = CCSprite::createWithTexture(playBgBottomTexture, CCRect(0.,0.,480.,118.));
    this->playBgBottomSprite->setPosition(ccp(visibleSize.width / 2., 59.));
    this->addChild(this->playBgBottomSprite);

    CCLog("GameBgLayer init()");
    return true;
}

void GameBgLayer::update() {
    CCTexture2D *playNabuzaDragonTexture   = CCTextureCache::sharedTextureCache()->textureForKey("play_n_time_dragon.png");
    CCSprite* playNabuzaDragonSprite   = CCSprite::createWithTexture(playNabuzaDragonTexture, CCRect(0.,0.,246.,469.));
    float randomX   = (float)(rand() % 300) + 50.;
    float randomY   = (float)(rand() % 50);

    playNabuzaDragonSprite->setPosition(ccp(randomX, -200. - randomY    ));
    
    playNabuzaDragonSprite->runAction(
                                      CCRepeatForever::create(CCAnimate::create(
                                                                                CCAnimationCache::sharedAnimationCache()->animationByName("nabuza_dragon_animation")
                                                                                ))
                                      );
    playNabuzaDragonSprite->runAction(CCSequence::create(
                                                         CCMoveBy::create(1., ccp(0.,1200.))
                                                         ,CCCallFuncN::create(this, callfuncN_selector(GameBgLayer::removeNabuzaSprite))
                                                         ,NULL
                                                       ));
    this->addChild(playNabuzaDragonSprite);
}

void GameBgLayer::removeNabuzaSprite(CCSprite *obj) {
    obj->stopAllActions();
    this->removeChild(obj,true);
}

void GameBgLayer::nabuzaTimeDoneCallback() {    // 회전 속도 2배
    this->setIsNabuzaTime(true);
}

void GameBgLayer::nabuzaTimeFinishCallback() {
    this->setIsNabuzaTime(false);
}

void GameBgLayer::setIsNabuzaTime(bool yorn) {
    this->isNabuzaTime  = yorn;

    if (this->isNabuzaTime == true) {
        this->runAction(CCRepeatForever::create(CCSequence::create(
                                                                   CCCallFunc::create(this, callfunc_selector(GameBgLayer::update))
                                                                   ,CCDelayTime::create(.5)
                                                                   ,NULL
                                                                   )));

        this->playBgTopSprite->runAction(
                                         CCSpeed::create(
                                                         CCRepeatForever::create(CCAnimate::create(
                                                                                                   CCAnimationCache::sharedAnimationCache()->animationByName("nabuza_b_bg_animation")
                                                                                                   ))
                                                         , .5)
                                         );
        
        this->playBgBottomSprite->runAction(
                                            CCSpeed::create(
                                                            CCRepeatForever::create(CCAnimate::create(
                                                                                                      CCAnimationCache::sharedAnimationCache()->animationByName("nabuza_b_bg_animation")
                                                                                                      ))
                                                            , .5)
                                            );
        return;
    }
    
    this->stopAllActions();
    this->playBgTopSprite->stopAllActions();
    this->playBgBottomSprite->stopAllActions();
}


GameBgLayer::~GameBgLayer()
{
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}