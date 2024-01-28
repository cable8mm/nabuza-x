//
//  Lucky7RankingLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/2/13.
//
//

#ifndef __NabuzaI__Lucky7RankingLayer__
#define __NabuzaI__Lucky7RankingLayer__

#include "MyRankSprite.h"
#include "cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Lucky7RankingLayer : public cocos2d::CCLayerColor,
                           public CCTableViewDataSource,
                           public CCTableViewDelegate,
                           public CCScrollViewDelegate {
public:
    //    CREATE_FUNC(Lucky7RankingLayer);
    static Lucky7RankingLayer *createWithGameScore(int gameScore);
#pragma-- CCTableViewDataSource

    virtual CCSize cellSizeForTable(CCTableView *table);

    virtual CCTableViewCell *tableCellAtIndex(CCTableView *table,
                                              unsigned int idx);

    virtual unsigned int numberOfCellsInTableView(CCTableView *table);

    virtual bool hasFixedCellSize();

    virtual CCSize cellSizeForIndex(CCTableView *table, unsigned int idx);

#pragma-- CCTableViewDelegate

    virtual void tableCellTouched(CCTableView *table, CCTableViewCell *cell);

#pragma-- CCScrollViewDelegate

    virtual void scrollViewDidScroll(CCScrollView *view);
    virtual void scrollViewDidZoom(CCScrollView *view);

private:
    int myRanking;
    int gameScore;
    CCSprite *playSpeechSprite;
    CCArray *sevenTournamentVolunteers;

    void onEnter();
    void close();
    void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);
    bool ccTouchBegan(CCTouch *touch, CCEvent *pEvent);
    void registerWithTouchDispatcher();
};

class SevenTournamentVolunteerModel : public cocos2d::CCObject {
public:
    int rank;
    int ownGoldCount;
    std::string nickname;
    int highscore;
    bool isMe;
};

#endif /* defined(__NabuzaI__Lucky7RankingLayer__) */
