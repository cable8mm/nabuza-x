//
//  MessageBoxLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 7/4/13.
//
//

#include "MessageBoxLayer.h"

#include "AlertTitleSprite.h"
#include "AnytaleHTTP.h"
#include "ButtonSprite.h"
#include "CCTableView.h"
#include "InvitedIconSprite.h"
#include "LevelIconSprite.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define RANK_TABLE_CELL_HEIGHT 80.
#define RANK_TABLE_WIDTH 400.
#define DEFAULT_FONT_NAME "Helvetica"

#define TAG_BACKGROUND_SPRITE 500001
#define TAG_NICKNAME_LABEL 500002
#define TAG_RANK_LABEL 500004
#define TAG_LEVEL_ICON_SPRITE 500005
#define TAG_HIGHSCORE_LABEL 500006
#define TAG_MY_RANK_SPRITE 500007
#define TAG_INVITED_ICON_SPRITE 500008
#define TAG_MESSAGES_TABLEVIEW 500009

void MessageBoxLayer::onEnter() {
    this->setTouchEnabled(true);

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    // BG
    CCSprite *bgRankingSprite = CCSprite::create("title_full_alert.jpg");
    bgRankingSprite->setPosition(
        ccp(visibleSize.width / 2., visibleSize.height / 2.));
    this->addChild(bgRankingSprite);

    // TITLE
    AlertTitleSprite *alertTitleSprite =
        AlertTitleSprite::createWithItemKey(kGAMEALERTTITLE_MESSAGE_BOX);
    this->addChild(alertTitleSprite);

    AnytaleHTTP::onHttpRequesting(
        this, callfuncND_selector(MessageBoxLayer::onHttpRequestCompleted),
        "/messages/get2", "", "MESSAGES_GET2");

    CCLayerColor::onEnter();
}

void MessageBoxLayer::onHttpRequestCompleted(CCHttpClient *sender,
                                             CCHttpResponse *response) {
    Json::Value root;
    Json::Reader reader;

    std::vector<char> *rawData = response->getResponseData();
    std::string ss(rawData->begin(), rawData->end());

    bool bIsParsed = reader.parse(ss, root, false);

    //    int validation  = ValidateResponse(response, root);    // 요기가 에러

    //    if (validation != 0) {
    //        CCLog("AuthStorage json parse error");
    //        return;
    //    }

    if (strcmp(response->getHttpRequest()->getTag(), "MESSAGES_GET2") == 0) {
        /*
         {"code":0,"message":"OK","result":[{"Message":{"id":"125","sent_player_id":"57","nickname":"\uae40\uc724\uc804","own_gold":"373503","received_player_id":"93","type":"0","is_used":"0","modified":"2013-01-18
         01:28:25","created":"2013-01-18 01:28:25"}}]}
         */
        //        int code = root.get("code", 0).asInt();

        this->messages = new CCArray;

        const Json::Value rankings = root["result"];

        CCLog("Message Count : %d", rankings.size());
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

        // 닫기 버튼

        ButtonSprite *closeButtonSprite =
            ButtonSprite::createWithItemKey(kGAMEBUTTON_CLOSE);
        ButtonSprite *closeButtonSpriteTapped =
            ButtonSprite::createWithItemKey(kGAMEBUTTON_CLOSE);
        closeButtonSpriteTapped->setScale(1.2);
        closeButtonSpriteTapped->setPosition(
            ccp(closeButtonSprite->getPositionX() - 20.,
                closeButtonSprite->getPositionY() - 6.));

        CCMenuItemSprite *closeButtonItem = CCMenuItemSprite::create(
            closeButtonSprite, closeButtonSpriteTapped, this,
            menu_selector(MessageBoxLayer::close));

        CCMenu *buttonMenu;
        if (rankings.size() != 0) {
            ButtonSprite *receiveAllButtonSprite =
                ButtonSprite::createWithItemKey(kGAMEBUTTON_RECEIVE_ALL);
            ButtonSprite *receiveAllButtonSpriteTapped =
                ButtonSprite::createWithItemKey(kGAMEBUTTON_RECEIVE_ALL);
            receiveAllButtonSpriteTapped->setScale(1.2);
            receiveAllButtonSpriteTapped->setPosition(
                ccp(receiveAllButtonSprite->getPositionX() - 20.,
                    receiveAllButtonSprite->getPositionY() - 6.));
            CCMenuItemSprite *receiveAllButtonItem = CCMenuItemSprite::create(
                receiveAllButtonSprite, receiveAllButtonSpriteTapped, this,
                menu_selector(MessageBoxLayer::close));
            buttonMenu =
                CCMenu::create(receiveAllButtonItem, closeButtonItem, NULL);
        } else {
            buttonMenu = CCMenu::create(closeButtonItem, NULL);
        }

        buttonMenu->alignItemsHorizontally();
        buttonMenu->setPosition(ccp(visibleSize.width / 2, 800. - 648. - 44.));
        this->addChild(buttonMenu);

        // 하단 메시지
        CCLabelTTF *lbNabuzaInfomation = CCLabelTTF::create(
            "주의 : 메시지함은 최대 77건까지만 보관 됩니다.", "JejuGothic", 20);
        lbNabuzaInfomation->setHorizontalAlignment(kCCTextAlignmentCenter);
        lbNabuzaInfomation->setPosition(
            ccp(visibleSize.width / 2, 800. - 698. - 40.));
        lbNabuzaInfomation->setAnchorPoint(ccp(.5, .5));
        lbNabuzaInfomation->setColor(ccWHITE);
        this->addChild(lbNabuzaInfomation);

        if (rankings.size() == 0) {
            // 캐릭터

            CCTexture2D *characterTexture =
                CCTextureCache::sharedTextureCache()->addImage(
                    "character_2.png");
            CCArray *characterFrames = new CCArray;
            for (unsigned int i = 0; i < 2; i++) {
                CCSpriteFrame *characterFrame =
                    CCSpriteFrame::createWithTexture(
                        characterTexture, CCRect(180. * i, 0, 180., 250.));
                characterFrames->addObject(characterFrame);
            }
            CCAnimation *characterAnimation =
                CCAnimation::createWithSpriteFrames(characterFrames, .1);

            CCSprite *character = CCSprite::createWithTexture(
                characterTexture, CCRect(0., 0., 180., 250.));
            character->setPosition(ccp(visibleSize.width / 2, 800. - 400.));
            this->addChild(character);

            CCLabelTTF *lbNabuzaInfomation =
                CCLabelTTF::create("신규 메시지가 없습니다.", "JejuGothic", 20);
            lbNabuzaInfomation->setHorizontalAlignment(kCCTextAlignmentCenter);
            lbNabuzaInfomation->setPosition(
                ccp(visibleSize.width / 2, 800. - 550.));
            lbNabuzaInfomation->setAnchorPoint(ccp(.5, .5));
            lbNabuzaInfomation->setColor(ccBLACK);
            this->addChild(lbNabuzaInfomation);

            character->runAction(CCSpeed::create(
                CCRepeatForever::create(CCAnimate::create(characterAnimation)),
                .5));
        } else {
            for (int index = 0; index < rankings.size(); index++) {
                MessageModel *message = new MessageModel;
                message->idx = rankings[index]["Message"]["id"].asInt();
                message->nickname =
                    rankings[index]["Message"]["nickname"].asString();
                message->ownGoldCount =
                    rankings[index]["Message"]["own_gold"].asInt();
                message->type = rankings[index]["Message"]["type"].asInt();
                message->isUsed =
                    rankings[index]["Message"]["is_used"].asBool();
                this->messages->addObject(message);
            }

            CCTableView *tableView =
                CCTableView::create(this, CCSizeMake(400., 400.));
            tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
            tableView->setDirection(kCCScrollViewDirectionVertical);
            tableView->setPosition(ccp(40., 204.));
            tableView->setDelegate(this);
            tableView->setTag(TAG_MESSAGES_TABLEVIEW);
            this->addChild(tableView);
        }
    }

    if (strcmp(response->getHttpRequest()->getTag(),
               "MESSAGES_USE_INVITATION2") == 0) {
        CCTableView *tableView =
            (CCTableView *)this->getChildByTag(TAG_MESSAGES_TABLEVIEW);
        CCTableViewCell *cell =
            tableView->cellAtIndex(this->useInvitationCellIdx);
        InvitedIconSprite *invitedIconSprite =
            (InvitedIconSprite *)cell->getChildByTag(TAG_INVITED_ICON_SPRITE);
        invitedIconSprite->setStat(kINVITEDICONSTATE_SENT);
        tableView->updateCellAtIndex(this->useInvitationCellIdx);
    }

    return;
}

void MessageBoxLayer::close() {
    this->removeFromParentAndCleanup(true);
}

#pragma mark -
#pragma mark Touch Delegates

bool MessageBoxLayer::ccTouchBegan(CCTouch *touch, CCEvent *pEvent) {
    this->tappedPoint =
        CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());

    return true;
}

void MessageBoxLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
        this, 0, true);
}

#pragma-- CCTableViewDataSource

CCSize MessageBoxLayer::cellSizeForTable(CCTableView *table) {
    return CCSizeMake(RANK_TABLE_WIDTH, RANK_TABLE_CELL_HEIGHT);
}

CCTableViewCell *MessageBoxLayer::tableCellAtIndex(CCTableView *table,
                                                   unsigned int idx) {
    MessageModel *message =
        (MessageModel *)(this->messages->objectAtIndex(idx));

    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();

        // 배경
        CCSprite *cellBackgroundSprite =
            CCSprite::create("ranking_box_best.png");
        cellBackgroundSprite->setTextureRect(CCRect(0., 3. * 80., 400., 80.));
        cellBackgroundSprite->setPosition(CCPointZero);
        cellBackgroundSprite->setAnchorPoint(CCPointZero);
        cellBackgroundSprite->setTag(TAG_BACKGROUND_SPRITE);
        cell->addChild(cellBackgroundSprite);

        // 레벨아이콘
        LevelIconSprite *levelIconSprite =
            LevelIconSprite::createWithGoldCount(message->ownGoldCount);
        levelIconSprite->setAnchorPoint(CCPointZero);
        levelIconSprite->setPosition(ccp(26., 20.));
        levelIconSprite->setTag(TAG_LEVEL_ICON_SPRITE);
        cell->addChild(levelIconSprite);

        // 닉네임
        std::stringstream ssNickname;
        ssNickname << message->nickname.c_str()
                   << " 님이\n초대장을 보냈습니다.";
        CCLabelTTF *lbNickName = CCLabelTTF::create(ssNickname.str().c_str(),
                                                    DEFAULT_FONT_NAME, 18.0);
        lbNickName->setHorizontalAlignment(kCCTextAlignmentLeft);
        lbNickName->setColor(ccBLACK);
        lbNickName->setAnchorPoint(CCPointZero);
        lbNickName->setPosition(ccp(140., 24.));
        lbNickName->setTag(TAG_NICKNAME_LABEL);
        cell->addChild(lbNickName);

        // 초대 아이콘
        InvitedIconSprite *invitedIconSprite = InvitedIconSprite::create();
        invitedIconSprite->setPosition(ccp(330., 20.));
        invitedIconSprite->setAnchorPoint(CCPointZero);
        invitedIconSprite->setTag(TAG_INVITED_ICON_SPRITE);
        //        if (!message->isInvitationNotification) {
        //            invitedIconSprite->setVisible(false);
        //        }
        cell->addChild(invitedIconSprite);
    } else {
    }

    return cell;
}

unsigned int MessageBoxLayer::numberOfCellsInTableView(CCTableView *table) {
    return this->messages->count();
}

bool MessageBoxLayer::hasFixedCellSize() {
    return false;
}

CCSize MessageBoxLayer::cellSizeForIndex(CCTableView *table, unsigned int idx) {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if (idx == 0) {
        return CCSizeMake(winSize.width, 160);
    }
    return CCSizeMake(winSize.width, 60);
}

#pragma-- CCTableViewDelegate

void MessageBoxLayer::tableCellTouched(CCTableView *table,
                                       CCTableViewCell *cell) {
    CCLOG("cell touched at index: %i", cell->getIdx());
    MessageModel *message =
        (MessageModel *)(this->messages->objectAtIndex(cell->getIdx()));

    if (this->tappedPoint.x > 370 && this->tappedPoint.x < 440) {
        std::stringstream ss;
        ss << "&id=" << message->idx;
        AnytaleHTTP::onHttpRequesting(
            this, callfuncND_selector(MessageBoxLayer::onHttpRequestCompleted),
            "/messages/use_invitation2", ss.str().c_str(),
            "MESSAGES_USE_INVITATION2");

        this->useInvitationCellIdx = cell->getIdx();
    } else {
    }
}

#pragma-- CCScrollViewDelegate
void MessageBoxLayer::scrollViewDidScroll(CCScrollView *view) {
}

void MessageBoxLayer::scrollViewDidZoom(CCScrollView *view) {
}