//
//  SendingGiftLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/5/13.
//
//

#ifndef __NabuzaI__SendingGiftLayer__
#define __NabuzaI__SendingGiftLayer__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SendingGiftLayer : public cocos2d::CCLayerColor, public CCTableViewDataSource, public CCTableViewDelegate, public CCScrollViewDelegate
{
public:
    CREATE_FUNC(SendingGiftLayer);
#pragma -- CCTableViewDataSource
    
    CCSize cellSizeForTable(CCTableView *table);
    
    CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    
    unsigned int numberOfCellsInTableView(CCTableView *table);
    
    bool hasFixedCellSize();
    
    CCSize cellSizeForIndex(CCTableView *table, unsigned int idx);
    
#pragma -- CCTableViewDelegate
    
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    
#pragma -- CCScrollViewDelegate
    
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view);
    
private:
    CCArray *buddies;
    CCPoint tappedPoint;
    int useGiftCellIdx;
    
    void onEnter();
    void speechStart();
    void close();
    
    // Touches
    bool ccTouchBegan(CCTouch *touch, CCEvent *pEvent);
    void ccTouchCancelled(CCTouch *touch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *touch, CCEvent *event);
    void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);
    void registerWithTouchDispatcher();
};

class GiftBuddyModel : public cocos2d::CCObject {
public:
    int idx;
    std::string nickname;
    int ownGoldCount;
    int type;
    bool isUsed;
};


#endif /* defined(__NabuzaI__SendingGiftLayer__) */
