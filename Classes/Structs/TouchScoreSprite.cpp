//
//  TouchScoreSprite.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 5/8/13.
//
//

#include "TouchScoreSprite.h"

TouchScoreSprite* TouchScoreSprite::createWithXY(float x, float y, int addGameScore, int multiplyConstant, int nabuzaTimeConstant)
{
    TouchScoreSprite *pobSprite = new TouchScoreSprite;
    pobSprite->setPosition(ccp(x, y));
    
    std::stringstream ss;
    
    ss << addGameScore;
    
    if (multiplyConstant != 0) {
        ss << "\n" << multiplyConstant;
    }
    
    if (nabuzaTimeConstant != 0) {
        ss << " " << nabuzaTimeConstant;
    }
    
    if (pobSprite && pobSprite->initWithString(ss.str().c_str(), "touch_score.fnt"))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void TouchScoreSprite::show() {
    this->runAction( CCSequence::create(
                                        CCMoveBy::create(1., ccp(0., 50.))
                                        ,CCDelayTime::create(.2)
                                        ,CCCallFunc::create(this, callfunc_selector(TouchScoreSprite::removeCallback))
                                        ,NULL) );
}

void TouchScoreSprite::removeCallback()
{
    this->removeFromParentAndCleanup(true);
}