//
//  MessageBoxLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/4/13.
//
//

#ifndef __NabuzaI__MessageBoxLayer__
#define __NabuzaI__MessageBoxLayer__

#include "cocos-ext.h"
#include "cocos2d.h"
USING_NS_CC;
USING_NS_CC_EXT;

class MessageBoxLayer : public cocos2d::CCLayerColor,
                        public CCTableViewDataSource,
                        public CCTableViewDelegate,
                        public CCScrollViewDelegate {
public:
    CREATE_FUNC(MessageBoxLayer);
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
    CCArray *messages;
    CCPoint tappedPoint;
    int useInvitationCellIdx;
    void onEnter();
    void close();
    void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);
    // Touches
    bool ccTouchBegan(CCTouch *touch, CCEvent *pEvent);

    void registerWithTouchDispatcher();
};

class MessageModel : public cocos2d::CCObject {
public:
    int idx;
    std::string nickname;
    int ownGoldCount;
    int type;
    bool isUsed;
};

#endif /* defined(__NabuzaI__MessageBoxLayer__) */
