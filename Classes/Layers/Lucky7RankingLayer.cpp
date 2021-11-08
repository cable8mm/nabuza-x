//
//  Lucky7RankingLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 7/2/13.
//
//

#include "Lucky7RankingLayer.h"
#include "AlertTitleSprite.h"
#include "ButtonSprite.h"
#include "CCTableView.h"
#include "AnytaleHTTP.h"

#include "MyRankSprite.h"
#include "LevelIconSprite.h"
#include "ATUtil.h"

#include "TopJadeGoldLayer.h"

#define RANK_TABLE_CELL_HEIGHT 80.
#define RANK_TABLE_WIDTH 400.
#define DEFAULT_FONT_NAME   "Helvetica"

Lucky7RankingLayer* Lucky7RankingLayer::createWithGameScore(int gameScore) {
    Lucky7RankingLayer *pobSprite = new Lucky7RankingLayer;
    
    pobSprite->gameScore  = gameScore;
    
    if (pobSprite && pobSprite->init())
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void Lucky7RankingLayer::onEnter()
{
    this->setTouchEnabled(true);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    // BG
    CCSprite *bgRankingSprite   = CCSprite::create("title_full_alert.jpg");
    bgRankingSprite->setPosition(ccp(visibleSize.width / 2., visibleSize.height / 2.));
    this->addChild(bgRankingSprite);
    
    // TITLE
    AlertTitleSprite *alertTitleSprite  = AlertTitleSprite::createWithItemKey(kGAMEALERTTITLE_TOURNAMENT_RESULT);
    this->addChild(alertTitleSprite);
    
    //
    TopJadeGoldLayer *topJadeGoldLayer  = TopJadeGoldLayer::create();
    topJadeGoldLayer->setCanPushJadeButton(false);
    topJadeGoldLayer->setCanPushGoldButton(false);
    this->addChild(topJadeGoldLayer);
    
    std::stringstream ss;
    ss  << "&highscore=" << this->gameScore;
    
    AnytaleHTTP::onHttpRequesting(this, callfuncND_selector(Lucky7RankingLayer::onHttpRequestCompleted), "/seven_tournament_volunteers/submit2", ss.str().c_str(), "SEVEN_TOURNAMENT_VOLUNTEERS_SUBMIT2");
    
    CCLayerColor::onEnter();
}

//Json::Value root;
//
//int error;
//AnytaleHTTP::validateResponse(response, root, error);
//
//if (error != 0) {
//    CCLog("AuthStorage json parse error");
//    return;
//}

// 게임 시작을 서버에 알림
//if(strcmp(response->getHttpRequest()->getTag(), "PLAYERS_START_GAME2") == 0) {

void Lucky7RankingLayer::onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response) {
    Json::Value root;
    Json::Reader reader;
    
    std::vector<char>*rawData = response->getResponseData();
    std::string ss(rawData->begin(), rawData->end());
    
    bool bIsParsed  = reader.parse(ss, root, false);
    
//    int error;
//    AnytaleHTTP::validateResponse(response, root, error);
//    
//    if (error != 0) {
//        CCLog("AuthStorage json parse error");
//        return;
//    }
    
    // 게임 시작을 서버에 알림
    if(strcmp(response->getHttpRequest()->getTag(), "SEVEN_TOURNAMENT_VOLUNTEERS_SUBMIT2") == 0) {
        /*
         
         {"code":0,"message":"OK","result":{"ranking_infos":{"ranking":1,"reward_jade_count":1,"reward_gold_count":0},"player":{"own_jade_count":33,"own_gold_count":7639},"rankings":[{"SevenTournamentVolunteer":{"id":172731,"player_id":32868,"nickname":"Player#32868","own_gold":6997,"highscore":1232123,"created":"2013-07-24 15:43:07"}},{"SevenTournamentVolunteer":{"id":172719,"player_id":32709,"nickname":"\uc544\ub4e4\ub09c\ud2f0\ub098","own_gold":1408,"highscore":709971,"created":"2013-07-16 18:25:43"}},{"SevenTournamentVolunteer":{"id":172716,"player_id":32863,"nickname":"\uc5c6\uc74c","own_gold":0,"highscore":962524,"created":"2013-07-16 18:22:21"}},{"SevenTournamentVolunteer":{"id":172708,"player_id":32862,"nickname":"\uc591\ubbf8","own_gold":12457,"highscore":527670,"created":"2013-07-16 18:15:13"}},{"SevenTournamentVolunteer":{"id":172583,"player_id":32797,"nickname":"\ub098\uc911\uc5d0","own_gold":17652,"highscore":218170,"created":"2013-07-16 17:25:08"}},{"SevenTournamentVolunteer":{"id":172560,"player_id":32846,"nickname":"\ubc15\uc0ac\uc544\ub4e4","own_gold":23242,"highscore":621600,"created":"2013-07-16 17:05:58"}}]}}
         */
        //        int code = root.get("code", 0).asInt();
        
        // 랭킹 테이블
        
        this->sevenTournamentVolunteers = new CCArray;

        const Json::Value myRanking = root["result"]["ranking_infos"];
        this->myRanking = myRanking.get("ranking", 1).asInt();
        
        const Json::Value rankings  = root["result"]["rankings"];
        for (int index=0; index < rankings.size(); index++) {
            SevenTournamentVolunteerModel *sevenTournamentVolunteer = new SevenTournamentVolunteerModel;
            sevenTournamentVolunteer->rank    = rankings[index]["SevenTournamentVolunteer"]["rank"].asInt();
            sevenTournamentVolunteer->highscore = rankings[index]["SevenTournamentVolunteer"]["highscore"].asInt();
            sevenTournamentVolunteer->nickname = rankings[index]["SevenTournamentVolunteer"]["nickname"].asString();
            sevenTournamentVolunteer->ownGoldCount = rankings[index]["SevenTournamentVolunteer"]["own_gold"].asInt();
            sevenTournamentVolunteer->isMe = rankings[index]["SevenTournamentVolunteer"]["isMe"].asBool();
            this->sevenTournamentVolunteers->addObject(sevenTournamentVolunteer);
        }

        CCTableView *rankingTableView = CCTableView::create(this, CCSizeMake(400., 395.));
        rankingTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        rankingTableView->setDirection(kCCScrollViewDirectionVertical);
        rankingTableView->setPosition(ccp(40., 199.));
        rankingTableView->setDelegate(this);
        this->addChild(rankingTableView);
        
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        // 닫기 버튼
        ButtonSprite *checkPrizeButtonSprite = ButtonSprite::createWithItemKey(kGAMEBUTTON_CONFIRM_REWARD);
        ButtonSprite *checkPrizeButtonSpriteTapped = ButtonSprite::createWithItemKey(kGAMEBUTTON_CONFIRM_REWARD);
        checkPrizeButtonSpriteTapped->setScale(1.2);
        checkPrizeButtonSpriteTapped->setPosition(ccp(checkPrizeButtonSprite->getPositionX()-20., checkPrizeButtonSprite->getPositionY()-6.));
        
        CCMenuItemSprite *closeButtonItem    = CCMenuItemSprite::create(checkPrizeButtonSprite, checkPrizeButtonSpriteTapped, this, menu_selector(Lucky7RankingLayer::close));
        CCMenu *menu    = CCMenu::create(closeButtonItem, NULL);
        menu->setPosition(ccp(visibleSize.width / 2, 800.-648.-44.));
        this->addChild(menu);
    }
    
    return;
}

void Lucky7RankingLayer::close() {
    CCInteger *rank = CCInteger::create(this->myRanking);
    CCNotificationCenter::sharedNotificationCenter()->postNotification("NABUZA_END_LUCKY7RANKING_NOTIFICATION", rank);
    this->removeFromParentAndCleanup(true);
}

#pragma -- CCTableViewDataSource

CCSize Lucky7RankingLayer::cellSizeForTable(CCTableView *table)
{
     return CCSizeMake(RANK_TABLE_WIDTH, RANK_TABLE_CELL_HEIGHT);
}

#define TAG_BACKGROUND_SPRITE   500001
#define TAG_NICKNAME_LABEL      500002
#define TAG_RANK_LABEL          500004
#define TAG_LEVEL_ICON_SPRITE   500005
#define TAG_HIGHSCORE_LABEL     500006
#define TAG_MY_RANK_SPRITE      500007


CCTableViewCell* Lucky7RankingLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    SevenTournamentVolunteerModel *sevenTournamentVolunteer = (SevenTournamentVolunteerModel*)(this->sevenTournamentVolunteers->objectAtIndex(idx));

    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        
        // 배경
        CCSprite *cellBackgroundSprite = CCSprite::create("ranking_box_best.png");
        CCLabelBMFont* rankLabel    = CCLabelBMFont::create();
        rankLabel->setFntFile("font_brown_45.fnt");
        std::stringstream ss;
        ss << sevenTournamentVolunteer->rank;
        rankLabel->setString(ss.str().c_str());
        rankLabel->setAlignment(kCCTextAlignmentCenter);
        rankLabel->setAnchorPoint(CCPointZero);
        rankLabel->setPosition(ccp(40., 16.));
        rankLabel->setTag(TAG_RANK_LABEL);
        cell->addChild(rankLabel);

        int cellBackgroundSpriteKey = sevenTournamentVolunteer->rank - 1;
        
        if (cellBackgroundSpriteKey < 3) {
            cellBackgroundSprite->setTextureRect(CCRect(0., cellBackgroundSpriteKey*80., 400., 80.));
        } else {
            cellBackgroundSprite->setTextureRect(CCRect(0., 3.*80., 400., 80.));
        }
        cellBackgroundSprite->setPosition(CCPointZero);
		cellBackgroundSprite->setAnchorPoint(CCPointZero);
        cellBackgroundSprite->setTag(TAG_BACKGROUND_SPRITE);
        cell->addChild(cellBackgroundSprite);
        
        // 닉네임
        CCLabelTTF *lbNickName = CCLabelTTF::create(sevenTournamentVolunteer->nickname.c_str(), DEFAULT_FONT_NAME, 16.0);
        lbNickName->setHorizontalAlignment(kCCTextAlignmentLeft);
        lbNickName->setColor(ccBLACK);
		lbNickName->setAnchorPoint(CCPointZero);
        lbNickName->setPosition(ccp(215., 50.));
        lbNickName->setTag(TAG_NICKNAME_LABEL);
        cell->addChild(lbNickName);
        
        LevelIconSprite *levelIconSprite    = LevelIconSprite::createWithGoldCount(sevenTournamentVolunteer->ownGoldCount);
        levelIconSprite->setAnchorPoint(CCPointZero);
        levelIconSprite->setPosition(ccp(96., 20.));
        levelIconSprite->setTag(TAG_LEVEL_ICON_SPRITE);
        cell->addChild(levelIconSprite);
        
        // 점수
        std::stringstream ssHighscore;
        ssHighscore << sevenTournamentVolunteer->highscore;
        std::string sHighscore  = ssHighscore.str().c_str();
        ATUtil::insert_separator(sHighscore);
        CCLabelTTF *highscoreSprite = CCLabelTTF::create(sHighscore.c_str(), DEFAULT_FONT_NAME, 18.0);
        highscoreSprite->setAnchorPoint(CCPointZero);
        highscoreSprite->setPosition(ccp(215., 20.));
        highscoreSprite->setColor(ccRED);
        highscoreSprite->setTag(TAG_HIGHSCORE_LABEL);
        cell->addChild(highscoreSprite);

        MyRankSprite *myRankSprite   = MyRankSprite::create();
        myRankSprite->setAnchorPoint(CCPointZero);
        myRankSprite->setPosition(ccp(320., 10.));
        myRankSprite->setTag(TAG_MY_RANK_SPRITE);
        cell->addChild(myRankSprite);

        
        if (sevenTournamentVolunteer->isMe) {
            CCLog("IS ME SPRITE TRUE");
            myRankSprite->setVisible(true);
            myRankSprite->startAnimation();
        } else {
            myRankSprite->setVisible(false);
        }
    }
    else
    {
        CCLabelBMFont *rankLabel   = (CCLabelBMFont *)cell->getChildByTag(TAG_RANK_LABEL);
        std::stringstream ss;
        ss << sevenTournamentVolunteer->rank;
        rankLabel->setString(ss.str().c_str());
        CCSprite *cellBackgroundSprite  = (CCSprite *)cell->getChildByTag(TAG_BACKGROUND_SPRITE);

        int cellBackgroundSpriteKey = sevenTournamentVolunteer->rank - 1;
        
        if (cellBackgroundSpriteKey < 3) {
            cellBackgroundSprite->setTextureRect(CCRect(0., cellBackgroundSpriteKey*80., 400., 80.));
        } else {
            cellBackgroundSprite->setTextureRect(CCRect(0., 3.*80., 400., 80.));
        }

        // 닉네임
        CCLabelTTF *lbNickName = (CCLabelTTF *)cell->getChildByTag(TAG_NICKNAME_LABEL);
        lbNickName->setString(sevenTournamentVolunteer->nickname.c_str());
        
        std::stringstream ssHighscore;
        ssHighscore << sevenTournamentVolunteer->highscore;
        std::string sHighscore  = ssHighscore.str().c_str();
        ATUtil::insert_separator(sHighscore);
        CCLabelTTF *highscoreSprite = (CCLabelTTF *)cell->getChildByTag(TAG_HIGHSCORE_LABEL);
        highscoreSprite->setString(sHighscore.c_str());

        MyRankSprite *myRankSprite  = (MyRankSprite *)cell->getChildByTag(TAG_MY_RANK_SPRITE);

        if (sevenTournamentVolunteer->isMe) {
            myRankSprite->setVisible(true);
            myRankSprite->startAnimation();
        } else {
            myRankSprite->setVisible(false);
        }
    }
    
    return cell;
}

unsigned int Lucky7RankingLayer::numberOfCellsInTableView(CCTableView *table)
{
    return this->sevenTournamentVolunteers->count();
}

bool Lucky7RankingLayer::hasFixedCellSize()
{
    return false;
}

CCSize Lucky7RankingLayer::cellSizeForIndex(CCTableView *table, unsigned int idx)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if (idx == 0) {
        return CCSizeMake(winSize.width, 160);
    }
    return CCSizeMake(winSize.width, 60);
}

#pragma -- CCTableViewDelegate

void Lucky7RankingLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
}

#pragma -- CCScrollViewDelegate
void Lucky7RankingLayer::scrollViewDidScroll(CCScrollView* view)
{
    
}
void Lucky7RankingLayer::scrollViewDidZoom(CCScrollView* view)
{
    
}

bool Lucky7RankingLayer::ccTouchBegan(CCTouch *touch, CCEvent *pEvent) {
    return true;
}

void Lucky7RankingLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate( this, 0, true );
}