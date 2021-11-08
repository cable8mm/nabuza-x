//
//  IndicationLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 7/31/13.
//
//

#include "IndicationLayer.h"

bool IndicationLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if( !CCLayerColor::initWithColor(ccc4(0., 0., 0., 200.)) ) //RGBA
    {
        return false;
    }
    
    return true;
}

void IndicationLayer::onEnter()
{
    this->setTouchEnabled(true);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCTexture2D *indicatorTexture  = CCTextureCache::sharedTextureCache()->addImage("indicator.png");
    CCSprite *indicatorSprite   = CCSprite::createWithTexture(indicatorTexture, CCRect(0.,0.,125.,125));
    indicatorSprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(indicatorSprite, 9999999+1);
    
    CCArray *indicatorFrames   = new CCArray;
    for (unsigned int i = 0; i < 3; i++) {
        CCSpriteFrame *indicatorFrame  = CCSpriteFrame::createWithTexture(indicatorTexture, CCRect(125.*i, 0., 125., 125.));
        indicatorFrames->addObject(indicatorFrame);
    }
    
    CCAnimation *indicatorAnimation  = CCAnimation::createWithSpriteFrames(indicatorFrames, .1);
    CCSpeed *indicatorSpeed = CCSpeed::create(CCRepeatForever::create(CCAnimate::create(indicatorAnimation)), 2.);
    indicatorSpeed->setTag(9);
    indicatorSprite->runAction(indicatorSpeed);
    
    CCLayerColor::onEnter();
}

bool IndicationLayer::ccTouchBegan(CCTouch *touch, CCEvent *pEvent) {
    return true;
}

void IndicationLayer::close() {
    this->removeFromParentAndCleanup(true);
}

void IndicationLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate( this, 0, true );
}