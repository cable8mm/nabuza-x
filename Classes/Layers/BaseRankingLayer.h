//
//  BaseRankingLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 5/29/13.
//
//

#ifndef __NabuzaI__BaseRankingLayer__
#define __NabuzaI__BaseRankingLayer__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

#include "../Layers/RankingLayer.h"
#include "../Layers/ItemSelectionLayer.h"
#include "../Storages/ItemStorage.h"
#include "SaleInvitationLayer.h"

class BaseRankingLayer : public cocos2d::CCLayerColor
{
public:
    BaseRankingLayer();
    ~BaseRankingLayer();
    
    virtual bool init();
    
    CREATE_FUNC(BaseRankingLayer);
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
private:
    bool isRanking;
    CCSprite *btnStartSprite;
    void registerWithTouchDispatcher();
    void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);
    CCSprite *selectedSprite;
    
    RankingLayer *rankingLayer;
    ItemSelectionLayer *itemSelectionLayer;
    SaleInvitationLayer *saleInvitationLayer;
    
    ItemStorage *itemStorage;
    
    void onStartGame(CCObject* pSender);
    void onBuyJadeLayer();
    
    // Notification Methods
    void changeToSelectItemsLayer();
    void changeToRankingLayer();
};

#endif /* defined(__NabuzaI__BaseRankingLayer__) */
