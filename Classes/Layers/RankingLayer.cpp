//
//  RankingLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 4/23/13.
//
//

#include "RankingLayer.h"
#include "../Utilities/ATUtil.h"

#include "CCScale9Sprite.h"
#include "CCControlButton.h"
#include "CCTableView.h"

#include "LevelIconSprite.h"
#include "AnytaleHTTP.h"
#include "InvitedIconSprite.h"
#include "IndicationLayer.h"
#include "BuddyInfoLayer.h"
#include "BuddyStorage.h"

#include "BelowTapLayer.h"
#include "CardLayer.h"
#include "TopJadeGoldLayer.h"
#include "BelowStartLayer.h"

#include "MessageBoxLayer.h"

#define RANK_TABLE_CELL_HEIGHT 80.
#define RANK_TABLE_WIDTH 400.
#define DEFAULT_FONT_NAME   "Helvetica"

USING_NS_CC;
USING_NS_CC_EXT;

#define TAG_BACKGROUND_SPRITE   500001
#define TAG_NICKNAME_LABEL      500002
#define TAG_RANK_LABEL          500004
#define TAG_LEVEL_ICON_SPRITE   500005
#define TAG_HIGHSCORE_LABEL     500006
#define TAG_MY_RANK_SPRITE      500007
#define TAG_INVITED_ICON_SPRITE      500008
#define TAG_INDICATION_LAYER    500009
#define TAG_INVITED_BUDDY_CELL  500010

#pragma mark -
#pragma mark RankingLayer Class

RankingLayer::RankingLayer()
{
    
}

// on "init" you need to initialize your instance
bool RankingLayer::init()
{
    
    //////////////////////////////
    // 1. super init first
    if( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)) ) //RGBA
    {
        return false;
    }
    this->setTouchEnabled(true);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCSprite *bgRankingSprite   = CCSprite::create("bg_board_a.png");
    bgRankingSprite->setPosition(ccp(visibleSize.width / 2., visibleSize.height / 2.));
    this->addChild(bgRankingSprite);
    
    this->btnFBLoginSprite    = CCSprite::create("btn_fblogin.png");
    this->btnFBLoginSprite->setPosition(ccp(visibleSize.width / 2., 800.-531.-31.));
//    this->addChild(this->btnFBLoginSprite);
    
    this->rankingTableView = CCTableView::create(this, CCSizeMake(400., 440.));
    this->rankingTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    this->rankingTableView->setDirection(kCCScrollViewDirectionVertical);
    this->rankingTableView->setPosition(ccp(40., 204.));
    this->rankingTableView->setDelegate(this);
    this->addChild(this->rankingTableView);

    CCSprite *boardbar   = CCSprite::create("boardbar.png");
    boardbar->setPosition(ccp(visibleSize.width / 2., ATUtil::agy(586.) - 28.));
    this->addChild(boardbar);

    BelowStartLayer *belowStartLayer    = BelowStartLayer::create();
    this->addChild(belowStartLayer);

    CardLayer *cardLayer    = CardLayer::create();
    this->addChild(cardLayer);
    
    BelowTapLayer *belowTapLayer    = BelowTapLayer::create();
    this->addChild(belowTapLayer);

    TopJadeGoldLayer *topJadeGoldLayer  = TopJadeGoldLayer::create();
    this->addChild(topJadeGoldLayer);
    
    return true;
}

void RankingLayer::onEnter()
{
    CCLayerColor::onEnter();
}

void RankingLayer::onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response) {
    Json::Value root;
    Json::Reader reader;
    
    std::vector<char>*rawData = response->getResponseData();
    std::string ss(rawData->begin(), rawData->end());
    
    bool bIsParsed  = reader.parse(ss, root, false);
    
    if(strcmp(response->getHttpRequest()->getTag(), "MESSAGES_SEND_INVITATION2") == 0) {
        CCTableViewCell *cell   = this->rankingTableView->cellAtIndex(this->sendInvitationCellIdx);
        InvitedIconSprite *invitedIconSprite    = (InvitedIconSprite *)cell->getChildByTag(TAG_INVITED_ICON_SPRITE);
        invitedIconSprite->setStat(kINVITEDICONSTATE_SENT);
        this->rankingTableView->updateCellAtIndex(this->sendInvitationCellIdx);
    }
    
    return;
}

bool RankingLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    this->tappedPoint    = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    return true;
}

void RankingLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {

//    if (this->btnFBLoginSprite->boundingBox().containsPoint(pt)) {    // 로그인
//        CCLog("Facebook Login Button Touch End");
////        if (![FBSession activeSession].isOpen) {
////            FB_Login();
////        }
//    }
    
    return;
}

void RankingLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate( this, 0, true );
}

#pragma -- CCTableViewDataSource

CCSize RankingLayer::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(RANK_TABLE_WIDTH, RANK_TABLE_CELL_HEIGHT);
}

CCTableViewCell* RankingLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell = table->dequeueCell();
    BuddyModel *buddy;
    if (idx != 10) {
        buddy = (BuddyModel*)(BuddyStorage::sharedBuddyStorage()->buddies->objectAtIndex(idx));
    }
    
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        cell->setIdx(idx);
        
        if (false) {
            CCSprite *cellBackgroundSprite = CCSprite::create("ranking_box_best.png");
            cellBackgroundSprite->setTextureRect(CCRect(0., 4.*80., 400., 80.));
            cellBackgroundSprite->setPosition(CCPointZero);
            cellBackgroundSprite->setAnchorPoint(CCPointZero);
            cellBackgroundSprite->setTag(TAG_INVITED_BUDDY_CELL);
            cell->addChild(cellBackgroundSprite);
            
            CCLabelBMFont* rankLabel    = CCLabelBMFont::create();
            rankLabel->setFntFile("font_brown_45.fnt");
            std::stringstream ss;
            ss << idx;
            CCLog("Buddy Rank : %d -> %s", idx, ss.str().c_str());
            rankLabel->setString(ss.str().c_str());
            rankLabel->setAlignment(kCCTextAlignmentCenter);
            rankLabel->setAnchorPoint(ccp(.5, .5));
            rankLabel->setPosition(ccp(50., 50.));
            rankLabel->setTag(TAG_RANK_LABEL);
            cell->addChild(rankLabel);

        } else {
        
            // 랭킹
            CCLabelBMFont* rankLabel    = CCLabelBMFont::create();
            rankLabel->setFntFile("font_brown_45.fnt");
            std::stringstream ss;
            ss << buddy->rank;
            CCLog("Buddy Rank : %d -> %s", buddy->rank, ss.str().c_str());
            rankLabel->setString(ss.str().c_str());
            rankLabel->setAlignment(kCCTextAlignmentCenter);
            rankLabel->setAnchorPoint(ccp(.5, .5));
            rankLabel->setPosition(ccp(50., 50.));
            rankLabel->setTag(TAG_RANK_LABEL);
            cell->addChild(rankLabel);
            
            // 배경
            CCSprite *cellBackgroundSprite = CCSprite::create("ranking_box_best.png");
            cellBackgroundSprite->setTextureRect(CCRect(0., 3.*80., 400., 80.));
            cellBackgroundSprite->setPosition(CCPointZero);
            cellBackgroundSprite->setAnchorPoint(CCPointZero);
            cellBackgroundSprite->setTag(TAG_BACKGROUND_SPRITE);
            cell->addChild(cellBackgroundSprite);
            
            // 닉네임
            CCLabelTTF *lbNickName = CCLabelTTF::create(buddy->nickname.c_str(), DEFAULT_FONT_NAME, 16.0);
            lbNickName->setHorizontalAlignment(kCCTextAlignmentLeft);
            lbNickName->setColor(ccBLACK);
            lbNickName->setAnchorPoint(CCPointZero);
            lbNickName->setPosition(ccp(210., 50.));
            lbNickName->setTag(TAG_NICKNAME_LABEL);
            cell->addChild(lbNickName);
            
            // 레벨아이콘
            LevelIconSprite *levelIconSprite    = LevelIconSprite::createWithGoldCount(buddy->ownGoldCount);
            levelIconSprite->setAnchorPoint(CCPointZero);
            levelIconSprite->setPosition(ccp(86., 20.));
            levelIconSprite->setTag(TAG_LEVEL_ICON_SPRITE);
            cell->addChild(levelIconSprite);
            
            // 점수
            std::stringstream ssHighscore;
            ssHighscore << buddy->highscore;
            std::string sHighscore  = ssHighscore.str().c_str();
            ATUtil::insert_separator(sHighscore);
            CCLabelTTF *highscoreSprite = CCLabelTTF::create(sHighscore.c_str(), DEFAULT_FONT_NAME, 18.0);
            highscoreSprite->setAnchorPoint(CCPointZero);
            highscoreSprite->setPosition(ccp(210., 20.));
            highscoreSprite->setColor(ccBLACK);
            highscoreSprite->setTag(TAG_HIGHSCORE_LABEL);
            cell->addChild(highscoreSprite);
            
            // 초대 아이콘
            InvitedIconSprite *invitedIconSprite    = InvitedIconSprite::create();
            invitedIconSprite->setPosition(ccp(330., 20.));
            invitedIconSprite->setAnchorPoint(CCPointZero);
            invitedIconSprite->setTag(TAG_INVITED_ICON_SPRITE);
            if (!buddy->isInvitationNotification) {
                invitedIconSprite->setVisible(false);
            }
            cell->addChild(invitedIconSprite);
        }
    }
    else
    {
        // 랭킹
        CCLabelBMFont *rankLabel   = (CCLabelBMFont *)cell->getChildByTag(TAG_RANK_LABEL);
        if (rankLabel != NULL) {
            std::stringstream ss;
            ss << buddy->rank;
            CCLog("Rank Label : %s", ss.str().c_str());
            rankLabel->setString(ss.str().c_str());
        }

        CCSprite *cellBackgroundSprite  = (CCSprite *)cell->getChildByTag(TAG_BACKGROUND_SPRITE);
        if (cellBackgroundSprite != NULL) {
            cellBackgroundSprite->setTextureRect(CCRect(0., 3.*80., 400., 80.));
        }
        
        // 닉네임
        CCLabelTTF *lbNickName = (CCLabelTTF *)cell->getChildByTag(TAG_NICKNAME_LABEL);
        if (lbNickName != NULL) {
            lbNickName->setString(buddy->nickname.c_str());
        }
        
        CCLabelTTF *highscoreSprite = (CCLabelTTF *)cell->getChildByTag(TAG_HIGHSCORE_LABEL);
        if (highscoreSprite != NULL) {
            std::stringstream ssHighscore;
            ssHighscore << buddy->highscore;
            std::string sHighscore  = ssHighscore.str().c_str();
            ATUtil::insert_separator(sHighscore);
            highscoreSprite->setString(sHighscore.c_str());
        }
        
        InvitedIconSprite *invitedIconSprite    = (InvitedIconSprite *)cell->getChildByTag(TAG_INVITED_ICON_SPRITE);
        if (invitedIconSprite != NULL) {
            if (!buddy->isInvitationNotification) {
                invitedIconSprite->setVisible(false);
            } else {
                invitedIconSprite->setVisible(true);
            }
        }
        
        CCSprite *invitedBuddyBgSprite  = (CCSprite *)cell->getChildByTag(TAG_INVITED_BUDDY_CELL);
        if (invitedBuddyBgSprite != NULL) {
            invitedBuddyBgSprite->setTextureRect(CCRect(0., 4.*80., 400., 80.));
        }
    }
    
    return cell;
}

unsigned int RankingLayer::numberOfCellsInTableView(CCTableView *table)
{
    return BuddyStorage::sharedBuddyStorage()->buddies->count();
}

bool RankingLayer::hasFixedCellSize()
{
    return false;
}

CCSize RankingLayer::cellSizeForIndex(CCTableView *table, unsigned int idx)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if (idx == 0) {
        return CCSizeMake(winSize.width, 160);
    }
    return CCSizeMake(winSize.width, 60);
}

#pragma -- CCTableViewDelegate

void RankingLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
//    CCLOG("cell touched at index: %i", cell->getIdx());
    BuddyModel *buddy = (BuddyModel*)(BuddyStorage::sharedBuddyStorage()->buddies->objectAtIndex(cell->getIdx()));
    CCLog("CCTableView ZOrder : %d", table->getZOrder());

    if (this->tappedPoint.x > 370 && this->tappedPoint.x < 440) {   // 초대
        CCLog("Invitation Tapped number %d", cell->getIdx());
        if (buddy->isInvitationNotification) {
            CCLog("Buddy can invite game to buddy");
            std::stringstream ss;
            ss << buddy->idx;
            this->sendInvitationCellIdx = cell->getIdx();
            AnytaleHTTP::onHttpRequesting(this, callfuncND_selector(RankingLayer::onHttpRequestCompleted), "/messages/send_invitation2", ss.str().c_str(), "MESSAGES_SEND_INVITATION2");
        }
    } else {    // 버디 정보 플로팅
        BuddyInfoLayer *buddyInfoLayer  = BuddyInfoLayer::createWithBuddyKey(cell->getIdx());
        this->addChild(buddyInfoLayer);
    }
}

#pragma -- CCScrollViewDelegate
void RankingLayer::scrollViewDidScroll(CCScrollView* view)
{
    
}

void RankingLayer::scrollViewDidZoom(CCScrollView* view)
{
    
}