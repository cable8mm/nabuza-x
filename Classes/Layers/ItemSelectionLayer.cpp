//
//  ItemSelectionLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 4/22/13.
//
//

#include "ItemSelectionLayer.h"

#include "BelowStartLayer.h"
#include "BelowTapLayer.h"
#include "CardLayer.h"
#include "ItemInfoSprite.h"
#include "NeedForGameMemory.h"
#include "TopJadeGoldLayer.h"

// TAGS
#define TAG_ITEMSELECTION_INFO_SPRITE 10000
#define TAG_BG_RANKING_SPRITE 10001

const int ITEM_CHOOSED_TOTAL_COUNT = 3;
const int ITEM_TOTAL_COUNT = 6;

#pragma mark -
#pragma mark Initialize

ItemSelectionLayer::ItemSelectionLayer() {
}

// on "init" you need to initialize your instance
bool ItemSelectionLayer::init() {
    //////////////////////////////
    // 1. super init first
    if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))  // RGBA
    {
        return false;
    }
    this->setTouchEnabled(true);

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    // messageboard.png
    CCSprite *bgRankingSprite = CCSprite::create("bg_board_a.png");
    //    CCSprite *bgRankingSprite   = CCSprite::create("messageboard.png");
    //    bgRankingSprite->setAnchorPoint(ccp(.5, 1.));
    //    bgRankingSprite->setPosition(ccp(visibleSize.width / 2., 695.));
    bgRankingSprite->setPosition(
        ccp(visibleSize.width / 2., visibleSize.height / 2.));
    bgRankingSprite->setTag(TAG_BG_RANKING_SPRITE);
    this->addChild(bgRankingSprite);
    CCLog("ItemSelectionLayer ZOrder : %d", bgRankingSprite->getZOrder());

    // 초보방
    //    CCSprite *itemLevelSprite   = CCSprite::create("item_lv.png",
    //    CCRect(0., 0., 222., 52.));   // height:52
    //    itemLevelSprite->setPosition(ccp(visibleSize.width/2, 624.));
    //    this->addChild(itemLevelSprite);

    // 아이템인포 배경
    CCSprite *itemBoardSprite = CCSprite::create("itemboard.png");
    itemBoardSprite->setPosition(
        ccp(visibleSize.width / 2, 800. - (263. + 63.5)));
    this->addChild(itemBoardSprite);

    // 아이템 인포
    ItemInfoSprite *itemInfoSprite = ItemInfoSprite::create();
    itemInfoSprite->setPosition(
        ccp(visibleSize.width / 2, 800. - (280. + 44.)));
    itemInfoSprite->setTag(TAG_ITEMSELECTION_INFO_SPRITE);
    this->addChild(itemInfoSprite);

    // 아이템 버튼들
    // #define TEXTURE_SIZE_W  132.
    // #define TEXTURE_SIZE_H  88.
    this->itemButtonSprites = new CCArray;
    for (unsigned int i = 0; i < 6; i++) {
        ItemSprite *itemSprite = ItemSprite::createWithItemKey(i);

        float itemX;
        float itemY;

        if (i < 3) {
            itemX = 39. + 132. * i + 66.;
            itemY = 800. - (405. + 44.);
        } else {
            itemX = 39. + 132. * (i - 3) + 66.;
            itemY = 800. - (509. + 44.);
        }

        itemSprite->setPosition(ccp(itemX, itemY));
        this->addChild(itemSprite);
        this->itemButtonSprites->addObject(itemSprite);
    }

    // 선택된 아이템 배경
    this->bgItemChoosedSprites = new CCArray;
    CCTexture2D *bgItemCoosedTexture =
        CCTextureCache::sharedTextureCache()->addImage(
            "item_empty_box_btn.png");
    for (unsigned int i = 0; i < 3; i++) {
        CCSprite *bgItemCoosedSprite =
            CCSprite::createWithTexture(bgItemCoosedTexture);
        bgItemCoosedSprite->setPosition(
            ccp(41. + 135. * i + 64.5, 800. - (161. + 42.5)));
        this->addChild(bgItemCoosedSprite);
        this->bgItemChoosedSprites->addObject(bgItemChoosedSprites);
    }

    // 선택된 아이템
    this->itemChoosedSprites = new CCArray;
    //    CCTexture2D *itemChoiceds =
    //    CCTextureCache::sharedTextureCache()->addImage("item_box_btn.png");
    //    for (unsigned int i = 0; i < 5; i++) {
    //        ItemChoosedSprite *itemCoosedSprite  =
    //        ItemChoosedSprite::create();
    //        itemCoosedSprite->setPosition(ccp(84.+78.*i, 561.5));
    //        this->addChild(itemCoosedSprite);
    //        this->itemChoosedSprites->addObject(itemCoosedSprite);
    //    }

    CCMenuItemImage *btnCloseItem =
        CCMenuItemImage::create("exit_btn.png", "exit_btn.png", this,
                                callfuncO_selector(ItemSelectionLayer::close));
    btnCloseItem->setPosition(ccp(455., 800. - 111.));
    CCMenu *btnClose = CCMenu::createWithItem(btnCloseItem);
    btnClose->setPosition(CCPointZero);
    this->addChild(btnClose);

    BelowStartLayer *belowStartLayer =
        BelowStartLayer::createWithIsStartGame(true);
    this->addChild(belowStartLayer);

    //    CardLayer *cardLayer    = CardLayer::create();
    //    this->addChild(cardLayer);

    //    BelowTapLayer *belowTapLayer    =
    //    BelowTapLayer::createWithIsStartGame(true);
    //    this->addChild(belowTapLayer);
    CCLog("ItemSelectionLayer ZOrder : %d", this->getZOrder());

    return true;
}

void ItemSelectionLayer::close() {
    this->removeFromParentAndCleanup(true);
}

#pragma mark -
#pragma mark Touch Delegates

bool ItemSelectionLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint pt =
        CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());

    CCLog("ItemSelection x, y : %f, %f", pt.x, pt.y);

    // 아이템 버튼들 클릭했을 경우 / 하단
    for (unsigned int i = 0; i < ITEM_TOTAL_COUNT; i++) {
        ItemSprite *itemSprite = dynamic_cast<ItemSprite *>(
            this->itemButtonSprites->objectAtIndex(i));
        if (itemSprite->boundingBox().containsPoint(pt) &&
            itemSprite->getIsActive()) {
            this->selectedItemSprite = itemSprite;
            CCLog("Item Button TouchBegan %u", itemSprite->getKey());
            return true;
        }
    }

    // 아이템 선택 버튼들 클릭했을 경우 / 상단
    for (unsigned int i = 0; i < this->itemChoosedSprites->count(); i++) {
        ItemChoosedSprite *itemChoosedSprite =
            dynamic_cast<ItemChoosedSprite *>(
                this->itemChoosedSprites->objectAtIndex(i));
        if (itemChoosedSprite->boundingBox().containsPoint(pt)) {
            this->selectedChoosedSprite = itemChoosedSprite;
            return true;
        }
    }

    // 좌상 : 35, 640
    // 우하 : 460, 185
    // 스프라이트 & 레이어로 처리 불능. active 영역의 좌표를 수동으로 넣은 것임.
    if (pt.x > 35. && pt.x < 460. && pt.y > 185. && pt.y < 640.) {
        return true;
    }

    return false;
}

void ItemSelectionLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint pt =
        CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());

    // 아이템 버튼을 클릭하고 뗐을 경우
    if (this->selectedItemSprite != NULL) {
        for (unsigned int i = 0; i < this->itemButtonSprites->count(); i++) {
            ItemSprite *itemButtonSprite = dynamic_cast<ItemSprite *>(
                this->itemButtonSprites->objectAtIndex(i));
            if (itemButtonSprite->boundingBox().containsPoint(pt)) {
                CCLog("Item Button TouchEnd %u", itemButtonSprite->getKey());
                if (this->selectedItemSprite == itemButtonSprite) {
                    // 선택 아이템 추가 this->selectedItemSprite-getKey()

                    int kNextItemChoosedSprite =
                        GetNextItemChoosedSpriteKey(this->itemChoosedSprites);

                    if (kNextItemChoosedSprite < 0) {
                        break;
                    }

                    // 아이템 선택 버튼을 만들어서 배치
                    ItemChoosedSprite *itemChoosedSprite =
                        ItemChoosedSprite::createWithKeys(
                            itemButtonSprite->getKey(), kNextItemChoosedSprite);

                    CCLog("kNextItemChoosedSprite value : %i",
                          kNextItemChoosedSprite);

                    this->addChild(itemChoosedSprite);
                    itemChoosedSprite->runAnimation();
                    this->itemChoosedSprites->addObject(itemChoosedSprite);

                    // 아이템 버튼을 비활성화
                    itemButtonSprite->setIsActive(false);

                    // 필요 비취를 더함
                    NeedForGameMemory::sharedNeedForGameMemory()->addJadeCount(
                        itemButtonSprite->getNeedJadeCount());

                    ItemInfoSprite *itemInfoSprite =
                        dynamic_cast<ItemInfoSprite *>(
                            this->getChildByTag(TAG_ITEMSELECTION_INFO_SPRITE));
                    itemInfoSprite->setItemKey(kNextItemChoosedSprite);
                }
            }
        }
    }

    // 아이템 선택 버튼들을 클릭하고 뗐을 경우
    if (this->selectedChoosedSprite != NULL) {
        for (unsigned int i = 0; i < this->itemChoosedSprites->count(); i++) {
            ItemChoosedSprite *itemChoosedSprite =
                dynamic_cast<ItemChoosedSprite *>(
                    this->itemChoosedSprites->objectAtIndex(i));
            if (itemChoosedSprite->boundingBox().containsPoint(pt)) {
                if (this->selectedChoosedSprite == itemChoosedSprite) {
                    // 아이템 선택 버튼들 해제
                    CCLog("selectedChoosedSprite Item Key : %i",
                          this->selectedChoosedSprite->getItemKey());
                    ItemSprite *itemSprite = dynamic_cast<ItemSprite *>(
                        this->itemButtonSprites->objectAtIndex(
                            this->selectedChoosedSprite->getItemKey()));
                    itemSprite->setIsActive(true);

                    this->selectedChoosedSprite->removeFromParentAndCleanup(
                        true);
                    this->itemChoosedSprites->removeObject(
                        this->selectedChoosedSprite);

                    ItemInfoSprite *itemInfoSprite =
                        dynamic_cast<ItemInfoSprite *>(
                            this->getChildByTag(TAG_ITEMSELECTION_INFO_SPRITE));
                    itemInfoSprite->reset();

                    // 필요 비취를 뻄
                    NeedForGameMemory::sharedNeedForGameMemory()
                        ->minusJadeCount(itemSprite->getNeedJadeCount());

                    break;
                }
            }
        }
    }

    this->selectedItemSprite = NULL;
    this->selectedChoosedSprite = NULL;

    return;
}

void ItemSelectionLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
        this, 0, true);
}

ItemSelectionLayer::~ItemSelectionLayer() {
    this->itemButtonSprites->release();
}

#pragma mark -
#pragma mark Functions

int GetNextItemChoosedSpriteKey(CCArray *itemChoosedSprites) {
    if (itemChoosedSprites->count() == ITEM_CHOOSED_TOTAL_COUNT) {
        return -1;
    }

    if (itemChoosedSprites->count() == 0) {
        return 0;
    }

    // 현재 있는 선택 아이템 중 비어있는 넘이 있는지 체크. 있으면 그 키 값을
    // 리턴.
    bool isExistedChoosedItem = false;

    for (unsigned int i = 0; i < ITEM_CHOOSED_TOTAL_COUNT; i++) {
        for (unsigned int j = 0; j < itemChoosedSprites->count(); j++) {
            ItemChoosedSprite *itemChoosedSprite =
                dynamic_cast<ItemChoosedSprite *>(
                    itemChoosedSprites->objectAtIndex(j));
            if (itemChoosedSprite->getPositionKey() == i) {
                isExistedChoosedItem = true;
                break;
            }
        }

        if (isExistedChoosedItem == false) {
            return i;
        }

        isExistedChoosedItem = false;
    }

    return -1;
}