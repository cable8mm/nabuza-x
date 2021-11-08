//
//  BuyJadeLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 7/5/13.
//
//

#include "BuyJadeLayer.h"
#include "AlertTitleSprite.h"
#include "ButtonSprite.h"
#include "BuyJadeButtonSprite.h"
#include "TopJadeGoldLayer.h"

#include "CouponLayer.h"

#include "IndicationLayer.h"
#include "AlertLayer.h"

#include "UserStorage.h"
#include "AnytaleHTTP.h"

//#include "store/CCStore.h"
//#include "store/CCStoreProduct.h"
//#include "store/CCStorePaymentTransaction.h"
//#include "native/CCNative.h"

#include "InAppPurchase.h"

#define JADEBUTTON_COUNT    5
#define TAG_INDICATOR_LAYER 1002

BuyJadeLayer::~BuyJadeLayer() {
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

bool BuyJadeLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayerColor::init() )
    {
        return false;
    }

    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(BuyJadeLayer::purchasingIAP), "PURCHASING_IAP_NOTIFICATION", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(BuyJadeLayer::purchasedIAP), "PURCHASED_IAP_NOTIFICATION", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(BuyJadeLayer::failedIAP), "FAILED_IAP_NOTIFICATION", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(BuyJadeLayer::restoredIAP), "RESTORED_IAP_NOTIFICATION", NULL);

    return true;
}

void BuyJadeLayer::purchasingIAP(CCObject* obj) {   // 서버에 거래 처리중
//    IndicationLayer *indicatorLayer = (IndicationLayer*)this->getChildByTag(TAG_INDICATOR_LAYER);
//    indicatorLayer->close();
}

void BuyJadeLayer::purchasedIAP(CCObject* obj) {    // 구매 완료
    int purchasedJadeCount;
    
    CCString *productIdentifier   = (CCString*)obj;
    
    CCLog("productIdentifier : %s", productIdentifier->getCString());
    
    if (productIdentifier->compare("NABUZA_PRODUCT_JADE_20") == 0) {
        purchasedJadeCount  = 20;
    }

    if (productIdentifier->compare("NABUZA_PRODUCT_JADE_80") == 0) {
        purchasedJadeCount  = 80;
    }
    
    if (productIdentifier->compare("NABUZA_PRODUCT_JADE_180") == 0) {
        purchasedJadeCount  = 180;
    }
    
    if (productIdentifier->compare("NABUZA_PRODUCT_JADE_500") == 0) {
        purchasedJadeCount  = 500;
    }
    
    if (productIdentifier->compare("NABUZA_PRODUCT_JADE_1500") == 0) {
        purchasedJadeCount  = 1500;
    }

    CCLog("PurchasedJadeCount : %d", purchasedJadeCount);

    UserStorage::sharedUserStorage()->addOwnJadeCount(purchasedJadeCount);

    std::stringstream ss;
    ss << "&product_id=" << purchasedJadeCount;
    
    AnytaleHTTP::onHttpRequesting(this, callfuncND_selector(BuyJadeLayer::onHttpRequestCompleted), "/purchasings/item2", ss.str().c_str(), "PURCHASINGS_ITEM2");
}

void BuyJadeLayer::failedIAP(CCObject* obj) {       // 거래 실패 또는 취소
    IndicationLayer *indicatorLayer = (IndicationLayer*)this->getChildByTag(TAG_INDICATOR_LAYER);
    if (indicatorLayer != NULL) {
        indicatorLayer->close();
    }
    
//    CCString *productIdentifier = (CCString *)obj;
//    
//    std::stringstream ss;
//    ss << productIdentifier->getCString() << " 이 구입되지 않았습니다.\n다시 시도해 주세요.";
//    
//    AlertLayer *alertLayer  = AlertLayer::sharedAlertLayer();
//    alertLayer->show("구입 실패", ss.str());

    AlertLayer *alertLayer  = AlertLayer::sharedAlertLayer();
    alertLayer->show("구입 실패", "구입되지 않았습니다.\n다시 시도해 주세요.");
}

void BuyJadeLayer::restoredIAP(CCObject* obj) {     // 재구매
    IndicationLayer *indicatorLayer = (IndicationLayer*)this->getChildByTag(TAG_INDICATOR_LAYER);
    if (indicatorLayer != NULL) {
        indicatorLayer->close();
    }
}

void BuyJadeLayer::onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response) {
    Json::Value root;
    
    int error;
    AnytaleHTTP::validateResponse(response, root, error);
    
    if (error != 0) {
        CCLog("AuthStorage json parse error");
        return;
    }
    
    if(strcmp(response->getHttpRequest()->getTag(), "PURCHASINGS_ITEM2") == 0) {
        IndicationLayer *indicatorLayer = (IndicationLayer*)this->getChildByTag(TAG_INDICATOR_LAYER);
        if (indicatorLayer != NULL) {
            indicatorLayer->close();
        }
        
        AlertLayer *alertLayer  = AlertLayer::sharedAlertLayer();
        alertLayer->show("구입 완료", "성공적으로 구입되었습니다.");

    }
    
    return;
}

void BuyJadeLayer::onEnter()
{
    this->setTouchEnabled(true);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    // BG
    CCSprite *bgRankingSprite   = CCSprite::create("title_full_alert.jpg");
    bgRankingSprite->setPosition(ccp(visibleSize.width / 2., visibleSize.height / 2.));
    this->addChild(bgRankingSprite);
    
    // TITLE
    AlertTitleSprite *alertTitleSprite  = AlertTitleSprite::createWithItemKey(kGAMEALERTTITLE_BUY_JADE);
    this->addChild(alertTitleSprite);
    
    // 닫기 버튼
    ButtonSprite *couponButtonSprite = ButtonSprite::createWithItemKey(kGAMEBUTTON_COUPON_REGIST);
    ButtonSprite *couponButtonSpriteTapped = ButtonSprite::createWithItemKey(kGAMEBUTTON_COUPON_REGIST);
    couponButtonSpriteTapped->setScale(1.2);
    couponButtonSpriteTapped->setPosition(ccp(couponButtonSprite->getPositionX()-20., couponButtonSprite->getPositionY()-6.));

    CCMenuItemSprite *couponButtonItem    = CCMenuItemSprite::create(couponButtonSprite, couponButtonSpriteTapped, this, menu_selector(BuyJadeLayer::registCoupon));
    
    ButtonSprite *closeButtonSprite = ButtonSprite::createWithItemKey(kGAMEBUTTON_CLOSE);
    ButtonSprite *closeButtonSpriteTapped = ButtonSprite::createWithItemKey(kGAMEBUTTON_CLOSE);
    closeButtonSpriteTapped->setScale(1.2);
    closeButtonSpriteTapped->setPosition(ccp(closeButtonSprite->getPositionX()-20., closeButtonSprite->getPositionY()-6.));
    
    CCMenuItemSprite *closeButtonItem    = CCMenuItemSprite::create(closeButtonSprite, closeButtonSpriteTapped, this, menu_selector(BuyJadeLayer::close));
    CCMenu *menu    = CCMenu::create(couponButtonItem, closeButtonItem, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(ccp(visibleSize.width / 2, 800.-648.-44.));
    this->addChild(menu);
    
    // 비취 리스트
    CCArray *jadeButtons    = new CCArray;
    
    for (unsigned int i=0; i < JADEBUTTON_COUNT; i++) {
        BuyJadeButtonSprite *jadeButtonSprite = BuyJadeButtonSprite::createWithItemKey(i);
        BuyJadeButtonSprite *jadeButtonSpriteTapped = BuyJadeButtonSprite::createWithItemKeyTapped(i);
        CCMenuItemSprite *jadeButtonItem    = CCMenuItemSprite::create(jadeButtonSprite, jadeButtonSpriteTapped, this, menu_selector(BuyJadeLayer::onBuyJadeButtonTapped));
        jadeButtonItem->setTag(i);
        jadeButtons->addObject(jadeButtonItem);
    }
    
    CCMenu *jadeMenu    = CCMenu::createWithArray(jadeButtons);
    jadeMenu->alignItemsVerticallyWithPadding(0.);
    jadeMenu->setPosition(ccp(visibleSize.width / 2, 800.-364.-40.));
    jadeMenu->setTouchPriority(0);
    this->addChild(jadeMenu);
    
    // 하단 메시지
    CCLabelTTF *lbNabuzaInfomation    = CCLabelTTF::create("위 금액은 부가세 10%가 포함된 금액입니다.", "JejuGothic", 20);
    lbNabuzaInfomation->setHorizontalAlignment(kCCTextAlignmentCenter);
    lbNabuzaInfomation->setPosition(ccp(visibleSize.width / 2, 800.-698.-40.));
    lbNabuzaInfomation->setAnchorPoint(ccp(.5, .5));
    lbNabuzaInfomation->setColor(ccWHITE);
    this->addChild(lbNabuzaInfomation);

    TopJadeGoldLayer *topJadeGoldLayer  = TopJadeGoldLayer::create();
    topJadeGoldLayer->setCanPushJadeButton(false);
    this->addChild(topJadeGoldLayer);
    
    // 결제 가능 유무 체크
//    this->inAppPurchase    = [[InAppPurchase alloc] init];
//    if ([this->inAppPurchase canMakePayments] == NO) {
//        CCLOG("InAppPurchase CANNOT");
//    } else {
//        CCLOG("InAPpPurchase CAN");
//    }
    InAppPurchase *inAppPurchase    = [InAppPurchase sharedInstance];
    if ([inAppPurchase canMakePayments] == NO) {
        CCLOG("InAppPurchase CANNOT");
    } else {
        CCLOG("InAPpPurchase CAN");
    }
    
    CCLayerColor::onEnter();
}

void BuyJadeLayer::onBuyJadeButtonTapped(CCObject *object) {
    CCMenu *jadeMenu    = (CCMenu *)object;
    
    int needJadeCountKey   = jadeMenu->getTag();
    
    CCLog("button tag : %d", needJadeCountKey);
    CCAssert(needJadeCountKey >= 0 && needJadeCountKey < JADEBUTTON_COUNT, "not validate tag value");
    
    int needMoneyCounts[]   = {1100, 3300, 5500, 11000, 22000};
    int buyedJadeCounts[]    = {20, 80, 180, 500, 1500};
    
    IndicationLayer *indicatorLayer = IndicationLayer::create();
    indicatorLayer->setTag(TAG_INDICATOR_LAYER);
    this->addChild(indicatorLayer);
    
    InAppPurchase *inAppPurchase    = [InAppPurchase sharedInstance];
    [inAppPurchase requestProductData:needJadeCountKey];
    
//    AnytaleHTTP::onHttpRequesting(this, callfuncND_selector(BuyGoldLayer::onHttpRequestCompleted), "/spent_jades/buy_gold2", ss.str().c_str(), "SPENT_JADES_BUY_GOLD2");
//    IndicationLayer *indicationLayer    = IndicationLayer::create();
//    indicationLayer->setTag(TAG_INDICATION_LAYER);
//    this->addChild(indicationLayer);
}

void BuyJadeLayer::registCoupon() {
    CouponLayer *couponLayer    = CouponLayer::create();
    this->addChild(couponLayer);
}

void BuyJadeLayer::close() {
    this->removeFromParentAndCleanup(true);
}

bool BuyJadeLayer::ccTouchBegan(CCTouch *touch, CCEvent *pEvent) {
    return true;
}

void BuyJadeLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate( this, 0, true );
}

