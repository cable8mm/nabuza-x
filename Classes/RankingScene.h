//
//  RankingScene.h
//  NabuzaI
//
//  Created by Lee Samgu on 4/22/13.
//
//

#ifndef __NabuzaI__RankingScene__
#define __NabuzaI__RankingScene__

#include "cocos2d.h"
#include "RankingLayer.h"
#include "ItemSelectionLayer.h"

USING_NS_CC;
using namespace cocos2d;

class RankingScene : public cocos2d::CCLayer
{
private:
    RankingLayer *rankingLayer;
    ItemSelectionLayer *itemSelectionLayer;
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(RankingScene);
    void onBuyJadeLayer();
    void ccTouchesBegan(CCSet* touches, CCEvent* event);
    void ccTouchesEnded(CCSet* touches, CCEvent* event);
};


#endif /* defined(__NabuzaI__RankingScene__) */
