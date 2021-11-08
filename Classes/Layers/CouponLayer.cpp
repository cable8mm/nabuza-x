//
//  CouponLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 8/13/13.
//
//

#include "CouponLayer.h"
#include "AlertTitleSprite.h"
#include "ButtonSprite.h"
#include "BuyJadeButtonSprite.h"
#include "AlertLayer.h"

#include "AnytaleHTTP.h"
#include "TopJadeGoldLayer.h"
#include "IndicationLayer.h"

#include "../Storages/UserStorage.h"

#define KEYPAD_POSITION_X   370.
#define NUMBER_LABEL_LEFT   100.
#define KEYPAD_KEY_WIDTH    127.
#define KEYPAD_KEY_HEIGHT   70.

#define TAG_DISPLAY_NUMBER_INITIAL  1000
#define TAG_KEYPAD_SPRITE   2000
#define TAG_INDICATION_LAYER    2100

void CouponLayer::onEnter()
{
    this->setTouchEnabled(true);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    // BG
    CCSprite *bgRankingSprite   = CCSprite::create("coupon_box.png");
    bgRankingSprite->setPosition(ccp(visibleSize.width / 2., visibleSize.height / 2.));
    this->addChild(bgRankingSprite);
    
    // x 아이콘
    CCMenuItemImage *btnCloseItem   = CCMenuItemImage::create("exit_btn.png", "exit_btn.png", this, callfuncO_selector(CouponLayer::close));
    btnCloseItem->setPosition(ccp(455., 800.-111.));
    CCMenu *btnClose    = CCMenu::createWithItem(btnCloseItem);
    btnClose->setPosition(CCPointZero);
    btnClose->setTouchPriority(0);
    this->addChild(btnClose);
    
    // 키패드
    CCSprite *keypadSprite  = CCSprite::create("coupon_keypad.png");
    keypadSprite->setPosition(ccp(visibleSize.width / 2., KEYPAD_POSITION_X));
    keypadSprite->setTag(TAG_KEYPAD_SPRITE);
    this->addChild(keypadSprite);
    
    // 숫자
    for (unsigned int i=0; i < 4; i++) {
        CCLabelTTF *displayNumber  = CCLabelTTF::create("", "Arial", 24.);
        displayNumber->setColor(ccBLACK);
        displayNumber->setTag(TAG_DISPLAY_NUMBER_INITIAL + i);
        displayNumber->setPosition(ccp(NUMBER_LABEL_LEFT + i * 95., KEYPAD_POSITION_X + 200.));
        this->addChild(displayNumber);
    }
    
    // 등록 버튼
    ButtonSprite *couponButtonSprite = ButtonSprite::createWithItemKey(kGAMEBUTTON_COUPON_REGIST);
    ButtonSprite *couponButtonSpriteTapped = ButtonSprite::createWithItemKey(kGAMEBUTTON_COUPON_REGIST);
    couponButtonSpriteTapped->setScale(1.2);
    couponButtonSpriteTapped->setPosition(ccp(couponButtonSprite->getPositionX()-20., couponButtonSprite->getPositionY()-6.));
    
    CCMenuItemSprite *couponButtonItem    = CCMenuItemSprite::create(couponButtonSprite, couponButtonSpriteTapped, this, menu_selector(CouponLayer::registerCoupon));
    
    CCMenu *menu    = CCMenu::create(couponButtonItem, NULL);
//    menu->setTouchPriority(0);
    menu->alignItemsHorizontally();
    menu->setPosition(ccp(visibleSize.width / 2, 800.-648.-44.));
    this->addChild(menu);
    
    TopJadeGoldLayer *topJadeGoldLayer  = TopJadeGoldLayer::create();
    this->addChild(topJadeGoldLayer);

    CCLayerColor::onEnter();
}

void CouponLayer::registerCoupon() {
    if (this->couponNumber.str().length() != 16) {
        AlertLayer::sharedAlertLayer()->show("쿠폰 적용 실패", "쿠폰 번호가 유효하지 않습니다.\n다시 확인해주세요.");

//        AlertLayer *alertLayer  = AlertLayer::createWithMessage("쿠폰 적용 실패", "쿠폰 번호가 유효하지 않습니다.\n다시 확인해주세요.");
//        this->addChild(alertLayer);
        return;
    }
    
    std::stringstream ss;
    ss << "&serial=" << this->couponNumber.str();
    
    AnytaleHTTP::onHttpRequesting(this, callfuncND_selector(CouponLayer::onHttpRequestCompleted), "/coupons/using2", ss.str().c_str(), "COUPONS_USING2");
    
    IndicationLayer *indicationLayer = IndicationLayer::create();
    indicationLayer->setTag(TAG_INDICATION_LAYER);
    this->addChild(indicationLayer);
}

void CouponLayer::onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response) {
    Json::Value root;
    
    int error;
    AnytaleHTTP::validateResponse(response, root, error);
    
    if (error != 0) {
        CCLog("AuthStorage json parse error");
        return;
    }
    
    // 게임 시작을 서버에 알림
    if(strcmp(response->getHttpRequest()->getTag(), "COUPONS_USING2") == 0) {
        /*
         {"code":0,"message":"OK","result":[]}
         */
        int code = root.get("code", 0).asInt();
        
        //        int remainJadeCount = UserStorage::sharedUserStorage()->getJadeCount() - NeedForGameMemory::sharedNeedForGameMemory()->getJadeCount();
        
        IndicationLayer *indicationLayer    = (IndicationLayer *)this->getChildByTag(TAG_INDICATION_LAYER);
        indicationLayer->close();
        
        if (code != 0) {
            AlertLayer::sharedAlertLayer()->show("쿠폰 적용 실패", "쿠폰 번호가 유효하지 않습니다.\n다시 확인해주세요.");

//            AlertLayer *alertLayer  = AlertLayer::createWithMessage("쿠폰 적용 실패", "쿠폰 번호가 유효하지 않습니다.\n다시 확인해주세요.");
//            this->addChild(alertLayer);
            return;
        }

        UserStorage::sharedUserStorage()->setOwnJadeCount(root["result"]["Player"].get("own_jade_count", 0).asInt());
        
        int jadeCount   = root["result"]["CouponIssue"].get("jade_count", 0).asInt();
        std::string sponsorName = root["result"]["CouponSponsor"].get("name", "").asString();
        
        std::stringstream ss;
        
        if (jadeCount != 0) {
            ss << "비취 " << jadeCount << " 개를 얻으셨습니다.";
        }
        
        ss << "\n스폰서 : " << sponsorName;
        
        CCLog("ss : %s", ss.str().c_str());
        
        AlertLayer::sharedAlertLayer()->show("쿠폰 적용", ss.str());
//        AlertLayer *alertLayer  = AlertLayer::createWithMessage("쿠폰 적용", ss.str());
//        this->addChild(alertLayer);
        return;
    }
    
    return;
}


bool CouponLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    return true;
}

void CouponLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint pt    = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    CCSprite *keypadSprite  = (CCSprite *)this->getChildByTag(TAG_KEYPAD_SPRITE);
    
    if (keypadSprite->boundingBox().containsPoint(pt)) {
        // 왼쪽 위 : 50, 510
        // 우측 아래 : 435, 255
        
        int x   = (int)floorf((pt.x - 50.) / KEYPAD_KEY_WIDTH) + 1;
        int y   = (int)floorf((510. - pt.y) / KEYPAD_KEY_HEIGHT) * 3;
        
        CCLog("Touch Point Number : %d", x+y);
        this->addCouponNumber(x+y);
    }
}

void CouponLayer::addCouponNumber(int v) {
    if (v < 11) {
        if (v == 10) { v = 0;}
        
        if (this->couponNumber.str().length() > 15) {
            return;
        }
        this->couponNumber << v;

        this->drawCouponNumber();
        return;
    }

    if (v == 11 && this->couponNumber.str().length() > 0) { // 한자 지우기
        std::string tmp   = this->couponNumber.str().erase(this->couponNumber.str().length()-1);
        this->couponNumber.str(tmp);
        this->couponNumber.seekp(this->couponNumber.str().length());
        
        this->drawCouponNumber();
        return;
    }
    
    if (v == 12) {
        this->couponNumber.str("");
        this->drawCouponNumber();
        return;
    }
}

void CouponLayer::drawCouponNumber() {
    for (unsigned int i=0; i < 4; i++) {
        CCLabelTTF *displayNumber   = (CCLabelTTF *)this->getChildByTag(TAG_DISPLAY_NUMBER_INITIAL + i);
        displayNumber->setString("");
    }

    if (this->couponNumber.str().length() == 0) {
        return;
    }
    
    int groupCount  = (int)floorf((this->couponNumber.str().length()-1) / 4); // 칸 순번은 0,1,2,3
    
    for (int i = 0; i < groupCount + 1; i++) {
        std::string subString   = this->couponNumber.str().substr(i*4, 4);
        CCLabelTTF *displayNumber   = (CCLabelTTF *)this->getChildByTag(TAG_DISPLAY_NUMBER_INITIAL + i);
        displayNumber->setString(subString.c_str());
    }
    
    CCLog("CouponNumber : %s", this->couponNumber.str().c_str());

}

void CouponLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate( this, 0, true );
}

void CouponLayer::close() {
    this->removeFromParentAndCleanup(true);
}
