//
//  SendingGiftLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 7/5/13.
//
//

#include "SendingGiftLayer.h"
#include "AlertTitleSprite.h"
#include "ButtonSprite.h"

#include "LevelIconSprite.h"

#include "AnytaleHTTP.h"
#include "UserStorage.h"
#include "JadeLessAlertViewLayer.h"

#define RANK_TABLE_CELL_HEIGHT 80.
#define RANK_TABLE_WIDTH 400.
#define DEFAULT_FONT_NAME   "Helvetica"

#define TAG_BACKGROUND_SPRITE   500001
#define TAG_NICKNAME_LABEL      500002
#define TAG_RANK_LABEL          500004
#define TAG_LEVEL_ICON_SPRITE   500005
#define TAG_HIGHSCORE_LABEL     500006
#define TAG_MY_RANK_SPRITE      500007
#define TAG_INVITED_ICON_SPRITE      500008
#define TAG_MESSAGES_TABLEVIEW           500009

void SendingGiftLayer::onEnter()
{
    this->setTouchEnabled(true);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    // BG
    CCSprite *bgRankingSprite   = CCSprite::create("title_full_alert.jpg");
    bgRankingSprite->setPosition(ccp(visibleSize.width / 2., visibleSize.height / 2.));
    this->addChild(bgRankingSprite);
    
    // TITLE
    AlertTitleSprite *alertTitleSprite  = AlertTitleSprite::createWithItemKey(kGAMEALERTTITLE_SENDING_GIFT);
    this->addChild(alertTitleSprite);
    
    // 닫기 버튼
    ButtonSprite *closeButtonSprite = ButtonSprite::createWithItemKey(kGAMEBUTTON_CLOSE);
    ButtonSprite *closeButtonSpriteTapped = ButtonSprite::createWithItemKey(kGAMEBUTTON_CLOSE);
    closeButtonSpriteTapped->setScale(1.2);
    closeButtonSpriteTapped->setPosition(ccp(closeButtonSprite->getPositionX()-20., closeButtonSprite->getPositionY()-6.));
    
    CCMenuItemSprite *closeButtonItem    = CCMenuItemSprite::create(closeButtonSprite, closeButtonSpriteTapped, this, menu_selector(SendingGiftLayer::close));
    CCMenu *menu    = CCMenu::create(closeButtonItem, NULL);
    menu->setPosition(ccp(visibleSize.width / 2, 800.-648.-44.));
    this->addChild(menu);
    
    AnytaleHTTP::onHttpRequesting(this, callfuncND_selector(SendingGiftLayer::onHttpRequestCompleted), "/players/view2", "", "PLAYERS_VIEW2");
    
    CCLayerColor::onEnter();
}

void SendingGiftLayer::onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response) {
    Json::Value root;
    Json::Reader reader;
    
    std::vector<char>*rawData = response->getResponseData();
    std::string ss(rawData->begin(), rawData->end());
    
    bool bIsParsed  = reader.parse(ss, root, false);
    
    //    int validation  = ValidateResponse(response, root);    // 요기가 에러
    
    //    if (validation != 0) {
    //        CCLog("AuthStorage json parse error");
    //        return;
    //    }
    
    // 게임 시작을 서버에 알림
    if(strcmp(response->getHttpRequest()->getTag(), "PLAYERS_VIEW2") == 0) {
        /*
         
         {"code":0,"message":"OK","result":{"ranking_infos":{"ranking":1,"reward_jade_count":1,"reward_gold_count":0},"player":{"own_jade_count":33,"own_gold_count":7639},"rankings":[{"SevenTournamentVolunteer":{"id":172731,"player_id":32868,"nickname":"Player#32868","own_gold":6997,"highscore":1232123,"created":"2013-07-24 15:43:07"}},{"SevenTournamentVolunteer":{"id":172719,"player_id":32709,"nickname":"\uc544\ub4e4\ub09c\ud2f0\ub098","own_gold":1408,"highscore":709971,"created":"2013-07-16 18:25:43"}},{"SevenTournamentVolunteer":{"id":172716,"player_id":32863,"nickname":"\uc5c6\uc74c","own_gold":0,"highscore":962524,"created":"2013-07-16 18:22:21"}},{"SevenTournamentVolunteer":{"id":172708,"player_id":32862,"nickname":"\uc591\ubbf8","own_gold":12457,"highscore":527670,"created":"2013-07-16 18:15:13"}},{"SevenTournamentVolunteer":{"id":172583,"player_id":32797,"nickname":"\ub098\uc911\uc5d0","own_gold":17652,"highscore":218170,"created":"2013-07-16 17:25:08"}},{"SevenTournamentVolunteer":{"id":172560,"player_id":32846,"nickname":"\ubc15\uc0ac\uc544\ub4e4","own_gold":23242,"highscore":621600,"created":"2013-07-16 17:05:58"}}]}}
         */
        //        int code = root.get("code", 0).asInt();
        
        // 랭킹 테이블
        
        this->buddies = new CCArray;
        
        const Json::Value rankings  = root["result"];
        for (int index=0; index < rankings.size(); index++) {
            GiftBuddyModel *buddy = new GiftBuddyModel;
            buddy->idx      = rankings[index]["Player"]["id"].asInt();
            buddy->nickname = rankings[index]["Player"]["nickname"].asString();
            buddy->ownGoldCount = rankings[index]["Player"]["own_gold"].asInt();
            this->buddies->addObject(buddy);
        }
        
        CCTableView *tableView = CCTableView::create(this, CCSizeMake(400., 395.));
        tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        tableView->setDirection(kCCScrollViewDirectionVertical);
        tableView->setPosition(ccp(40., 199.));
        tableView->setDelegate(this);
        this->addChild(tableView);
    }
    
    if(strcmp(response->getHttpRequest()->getTag(), "SPENT_GIFTS_SEND") == 0) {

    }
    
    return;
}


void SendingGiftLayer::speechStart() {
    //this->schedule(SEL_SCHEDULE selector, float interval, )
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("GA004.mp3");  // start
}

void SendingGiftLayer::close() {
    this->removeFromParentAndCleanup(true);
}

#pragma mark -
#pragma mark Touch Delegates

void SendingGiftLayer::ccTouchEnded(CCTouch *touch, CCEvent *event) {
    CCPoint pt    = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
}

void SendingGiftLayer::ccTouchCancelled(CCTouch *touch, CCEvent *pEvent) {
    CCLog("Cancel");
}

bool SendingGiftLayer::ccTouchBegan(CCTouch *touch, CCEvent *pEvent) {
    this->tappedPoint    = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
    
//    CCLog("CCTouchEnded Touch Location, x : %f, y : %f", this->tappedPoint.x, this->tappedPoint.y);
    
    return true;
}

void SendingGiftLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate( this, 0, true );
}

#pragma -- CCTableViewDataSource

CCSize SendingGiftLayer::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(RANK_TABLE_WIDTH, RANK_TABLE_CELL_HEIGHT);
}

CCTableViewCell* SendingGiftLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    GiftBuddyModel *buddy = (GiftBuddyModel*)(this->buddies->objectAtIndex(idx));
    
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        
        // 배경
        CCSprite *cellBackgroundSprite = CCSprite::create("ranking_box_best.png");
        cellBackgroundSprite->setTextureRect(CCRect(0., 3.*80., 400., 80.));
        cellBackgroundSprite->setPosition(CCPointZero);
		cellBackgroundSprite->setAnchorPoint(CCPointZero);
        cellBackgroundSprite->setTag(TAG_BACKGROUND_SPRITE);
        cell->addChild(cellBackgroundSprite);
        
        // 레벨아이콘
        LevelIconSprite *levelIconSprite    = LevelIconSprite::createWithGoldCount(buddy->ownGoldCount);
        levelIconSprite->setAnchorPoint(CCPointZero);
        levelIconSprite->setPosition(ccp(26., 20.));
        levelIconSprite->setTag(TAG_LEVEL_ICON_SPRITE);
        cell->addChild(levelIconSprite);
        
        // 비취
        CCSprite *jadeSprite    = CCSprite::create("jewel.png");
        jadeSprite->setAnchorPoint(CCPointZero);
        jadeSprite->setPosition(ccp(140., 20.));
        cell->addChild(jadeSprite);
        
        // 닉네임
        CCLabelTTF *lbNickName = CCLabelTTF::create(buddy->nickname.c_str(), DEFAULT_FONT_NAME, 18.0);
        lbNickName->setHorizontalAlignment(kCCTextAlignmentLeft);
        lbNickName->setColor(ccBLACK);
		lbNickName->setAnchorPoint(CCPointZero);
        lbNickName->setPosition(ccp(185., 48.));
        lbNickName->setTag(TAG_NICKNAME_LABEL);
        cell->addChild(lbNickName);
        
        // x50개 선물하기
        CCLabelTTF *lbGiftMessage = CCLabelTTF::create("x50개 선물하기", DEFAULT_FONT_NAME, 18.0);
        lbGiftMessage->setHorizontalAlignment(kCCTextAlignmentLeft);
        lbGiftMessage->setColor(ccRED);
		lbGiftMessage->setAnchorPoint(CCPointZero);
        lbGiftMessage->setPosition(ccp(185., 24.));
        lbGiftMessage->setTag(TAG_NICKNAME_LABEL);
        cell->addChild(lbGiftMessage);
        
        // 초대 아이콘
        CCSprite *giftJadeIconSprite    = CCSprite::create("jewel_send_box.png", CCRect(0., 0., 60., 60.));
        giftJadeIconSprite->setPosition(ccp(330., 20.));
        giftJadeIconSprite->setAnchorPoint(CCPointZero);
        cell->addChild(giftJadeIconSprite);
    }
    else
    {
//        CCLabelTTF *lbNickName  = (CCLabelTTF*)this->getChildByTag(TAG_NICKNAME_LABEL);
//        lbNickName->setString(buddy->nickname.c_str());
    }
    
    return cell;
}

unsigned int SendingGiftLayer::numberOfCellsInTableView(CCTableView *table)
{
    return this->buddies->count();
}

bool SendingGiftLayer::hasFixedCellSize()
{
    return false;
}

CCSize SendingGiftLayer::cellSizeForIndex(CCTableView *table, unsigned int idx)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if (idx == 0) {
        return CCSizeMake(winSize.width, 160);
    }
    return CCSizeMake(winSize.width, 60);
}

#pragma -- CCTableViewDelegate

void SendingGiftLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
    GiftBuddyModel *buddy = (GiftBuddyModel*)(this->buddies->objectAtIndex(cell->getIdx()));
    
    if (this->tappedPoint.x > 370 && this->tappedPoint.x < 440) {
        if (UserStorage::sharedUserStorage()->getOwnJadeCountToInt() < 50) {
            JadeLessAlertViewLayer *jadeLessAlertViewLayer  = JadeLessAlertViewLayer::createWithKey(kJADELESSKEY_NOT_GIFT);
            this->addChild(jadeLessAlertViewLayer);
            return;
        }
        
        std::stringstream ss;
        ss << "&received_player_id=" << buddy->idx;
        ss << "&spent_count=50";
        
        AnytaleHTTP::onHttpRequesting(this, callfuncND_selector(SendingGiftLayer::onHttpRequestCompleted), "/spent_gifts/send", ss.str().c_str(), "SPENT_GIFTS_SEND");
        
        this->useGiftCellIdx = cell->getIdx();
    } else {
        
    }
}

#pragma -- CCScrollViewDelegate
void SendingGiftLayer::scrollViewDidScroll(CCScrollView* view)
{
    
}

void SendingGiftLayer::scrollViewDidZoom(CCScrollView* view)
{
    
}