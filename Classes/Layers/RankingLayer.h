//
//  RankingLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 4/23/13.
//
//

#ifndef __NabuzaI__RankingLayer__
#define __NabuzaI__RankingLayer__

//#import <UIKit/UIKit.h>

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class RankingLayer : public cocos2d::CCLayerColor, public CCTableViewDataSource, public CCTableViewDelegate, public CCScrollViewDelegate
{
public:
    RankingLayer();
    
    virtual bool init();
    void menuResumeCallback(CCObject* pSender);
    void menuRestartCallback(CCObject* pSender);
    void menuGotoMenuCallback(CCObject* pSender);
    
    CREATE_FUNC(RankingLayer);
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
#pragma -- CCTableViewDataSource
    
    virtual CCSize cellSizeForTable(CCTableView *table);
    
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
    virtual bool hasFixedCellSize();
    
    virtual CCSize cellSizeForIndex(CCTableView *table, unsigned int idx);
    
#pragma -- CCTableViewDelegate
    
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    
#pragma -- CCScrollViewDelegate
    
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view);
    
private:
    CCArray *buddies;
    CCSprite *btnStartSprite;
    void registerWithTouchDispatcher();
    CCSprite *selectedSprite;
    CCSprite *btnFBLoginSprite;
    CCPoint tappedPoint;
    int sendInvitationCellIdx;
    CCTableView *rankingTableView;
    void onEnter();
    void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);
    
};

//class BuddyModel : public cocos2d::CCObject {
//public:
//    int idx;
//    int rank;
//    int ownGoldCount;
//    std::string nickname;
//    int highscore;
//    bool isMe;
//    bool isInvitationNotification;
//};

#endif /* defined(__NabuzaI__RankingLayer__) */
