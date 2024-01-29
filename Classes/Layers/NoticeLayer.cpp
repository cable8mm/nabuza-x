//
//  NoticeLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 8/1/13.
//
//

#include "NoticeLayer.h"

#include "../Structs/ButtonSprite.h"
#include "AnytaleHTTP.h"

#define ZORDER_ALERTVIEW_SPRITE 999999
#define TAG_ALERTVIEW_SPRITE 999999

bool NoticeLayer::init() {
    //////////////////////////////
    // 1. super init first
    if (!CCLayerColor::initWithColor(ccc4(0., 0., 0., 200.)))  // RGBA
    {
        return false;
    }

    return true;
}

void NoticeLayer::onEnter() {
    CCLog("NoticeLayer width : %f, height: %f", this->getContentSize().width,
          this->getContentSize().height);
    this->setTouchEnabled(true);
    AnytaleHTTP::onHttpRequesting(
        this, callfuncND_selector(NoticeLayer::onHttpRequestCompleted),
        "/notices/last2", "", "NOTICES_LAST2");

    CCLayerColor::onEnter();
}

void NoticeLayer::onHttpRequestCompleted(CCHttpClient *sender,
                                         CCHttpResponse *response) {
    Json::Value root;
    Json::Reader reader;

    std::vector<char> *rawData = response->getResponseData();
    std::string ss(rawData->begin(), rawData->end());

    bool bIsParsed = reader.parse(ss, root, false);

    // 게임 시작을 서버에 알림
    if (strcmp(response->getHttpRequest()->getTag(), "NOTICES_LAST2") == 0) {
        this->notices = new CCArray;

        const Json::Value notices = root["result"];
        for (int index = 0; index < notices.size(); index++) {
            NoticeModel *notice = new NoticeModel;
            notice->idx = notices[index]["Notice"]["id"].asInt();
            notice->contents = notices[index]["Notice"]["contents"].asString();
            this->notices->addObject(notice);
            CCLog("id : %d", notice->idx);
            CCLog("contents : %s", notice->contents.c_str());
        }

        if (this->notices->count() != 0) {
            CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

            // 공지사항 레이어
            /////////////////////
            // SCROLL VIEW + LAYER

            //            CCLayer *scrollContainerLayer = CCLayer::create();
            //            scrollContainerLayer->setAnchorPoint( CCPointZero );
            //
            //            CCSprite *alertView =
            //            CCSprite::create("what_alert.png");
            //            alertView->setAnchorPoint(ccp(.5, .5));
            //            alertView->setPosition(ccp(visibleSize.width/2,
            //            visibleSize.height/2)); // 콘텐트의 절대 좌표가
            //            들어감. scrollContainerLayer->addChild(alertView);
            //            scrollContainerLayer->setPosition(CCPointZero);
            //            scrollContainerLayer->setContentSize(CCSizeMake(visibleSize.width,
            //            visibleSize.height * .7));
            //
            //            CCScrollView *scrollView =
            //            CCScrollView::create(CCSizeMake(480., 400.),
            //            scrollContainerLayer);
            //            scrollView->setAnchorPoint(CCPointZero);
            //            scrollView->setPosition( CCPointZero );
            //            scrollView->setContentOffset(ccp(0.f, 0.f), false);
            //            scrollView->setDirection(
            //            kCCScrollViewDirectionVertical );
            //            scrollView->setDelegate(this);
            //            this->addChild( scrollView );

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
                menu_selector(NoticeLayer::viewContents));
            CCMenu *menu = CCMenu::create(closeButtonItem, NULL);
            menu->alignItemsHorizontally();
            menu->setPosition(ccp(visibleSize.width / 2, 800. - 648. - 44.));
            this->addChild(menu, 99999999);

            this->currentNoticeIdx = 0;
            this->viewContents();
        } else {
            this->close();
        }
    }

    return;
}

void NoticeLayer::viewContents() {
    CCLog("viewContents");
    if (this->notices->count() == this->currentNoticeIdx + 1) {
        this->close();
        return;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    NoticeModel *notice =
        (NoticeModel *)this->notices->objectAtIndex(this->currentNoticeIdx++);
    CCLabelTTF *lbNabuzaInfomation =
        CCLabelTTF::create(notice->contents.c_str(), "JejuGothic", 20.);
    lbNabuzaInfomation->setHorizontalAlignment(kCCTextAlignmentCenter);
    lbNabuzaInfomation->setPosition(
        ccp(visibleSize.width / 2, visibleSize.height / 2));
    lbNabuzaInfomation->setAnchorPoint(ccp(.5, .5));
    lbNabuzaInfomation->setColor(ccBLACK);

    //    CCSprite *alertView = (CCSprite
    //    *)this->getChildByTag(TAG_ALERTVIEW_SPRITE);
    //    alertView->addChild(lbNabuzaInfomation, ZORDER_ALERTVIEW_SPRITE+1);
}

#pragma-- CCScrollViewDelegate
void NoticeLayer::scrollViewDidScroll(CCScrollView *view) {
}

void NoticeLayer::scrollViewDidZoom(CCScrollView *view) {
}

void NoticeLayer::close() {
    this->removeFromParentAndCleanup(true);
}

bool NoticeLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    return true;
}

void NoticeLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
        this, -999, true);
}