//
//  ItemSelectionLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 4/22/13.
//
//

#ifndef __NabuzaI__ItemSelectionLayer__
#define __NabuzaI__ItemSelectionLayer__


#include "cocos2d.h"
using namespace cocos2d;
#include "ItemChoosedSprite.h"
#include "ItemSprite.h"

class ItemSelectionLayer : public cocos2d::CCLayerColor
{
public:
    ItemSelectionLayer();
    ~ItemSelectionLayer();
    
    CCArray *itemButtonSprites;
    ItemSprite *selectedItemSprite;
    CCArray *itemChoosedSprites;
    CCArray *bgItemChoosedSprites;
    ItemChoosedSprite *selectedChoosedSprite;
    bool init();

    CREATE_FUNC(ItemSelectionLayer);
    
private:
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

    void registerWithTouchDispatcher();
    void close();
};

int GetNextItemChoosedSpriteKey(CCArray *itemChoosedSprites);

#endif /* defined(__NabuzaI__ItemSelectionLayer__) */
