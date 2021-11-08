//
//  SettingLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 7/3/13.
//
//
#import <AudioToolbox/AudioToolbox.h>
#include "SettingLayer.h"
#include "ButtonSprite.h"
#include "AlertTitleSprite.h"
#include "../Networks/AnytaleHTTP.h"
#include "IndicationLayer.h"
#include "WebViewLayer.h"
#include "SimpleAudioEngine.h"
#include "UserStorage.h"

#define TAG_INDICATION_LAYER    10011

const char *USER_DEFAULT_SETTING_STORAGE_BGM_KEY    = "SETTING_STORAGE_BGM_KEY";
const char *USER_DEFAULT_SETTING_STORAGE_EFFECT_KEY    = "SETTING_STORAGE_EFFECT_KEY";
const char *USER_DEFAULT_SETTING_STORAGE_VIBRATION_KEY    = "SETTING_STORAGE_VIBRATION_KEY";
const char *USER_DEFAULT_SETTING_STORAGE_EVENTALARM_KEY    = "SETTING_STORAGE_EVENTALARM_KEY";

bool SettingLayer::init()
{
    //////////////////////////////
    // 1. super init first
//    if( !CCLayerColor::initWithColor(ccc4(0., 0., 0., 200.)) ) //RGBA

    if( !CCLayerColor::init()) //RGBA
    {
        return false;
    }
    
    return true;
}

void SettingLayer::onEnter()
{
    this->setTouchEnabled(true);
    
    CCUserDefault *userDefault   = CCUserDefault::sharedUserDefault();

    // 설정 읽어 옴.
    bool isBgm    = userDefault->getBoolForKey(USER_DEFAULT_SETTING_STORAGE_BGM_KEY, true);
    bool isEffect   = userDefault->getBoolForKey(USER_DEFAULT_SETTING_STORAGE_EFFECT_KEY, true);
    bool isVibration   = userDefault->getBoolForKey(USER_DEFAULT_SETTING_STORAGE_VIBRATION_KEY, true);
    bool isEventalarm   = userDefault->getBoolForKey(USER_DEFAULT_SETTING_STORAGE_EVENTALARM_KEY, true);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    
    
    // BG // bg_board_a.png
    CCSprite *bg   = CCSprite::create("bg_board_a.png");
    bg->setPosition(ccp(visibleSize.width / 2., visibleSize.height / 2.));
    this->addChild(bg);

    CCSprite *bgRankingSprite   = CCSprite::create("set_bg.png");
    bgRankingSprite->setPosition(ccp(visibleSize.width / 2., visibleSize.height / 2.));
    this->addChild(bgRankingSprite);
    
    // BGM 스위치
    this->bgmSwitch = SwitchSprite::createWithValue(isBgm);
    bgmSwitch->setPosition(ccp(300.+65., 800.-190.-50.));
    if (!UserStorage::sharedUserStorage()->getIsBgm()) {
        this->bgmSwitch->toggle();
    }
    this->addChild(bgmSwitch);
    // EFFECT 스위치
    this->effectSwitch = SwitchSprite::createWithValue(isEffect);
    effectSwitch->setPosition(ccp(300.+65., 800.-250.-50.));
    if (!UserStorage::sharedUserStorage()->getIsEffect()) {
        this->effectSwitch->toggle();
    }
    this->addChild(effectSwitch);

    // Vibration 스위치
    this->vibrationSwitch = SwitchSprite::createWithValue(isVibration);
    vibrationSwitch->setPosition(ccp(300.+65., 800.-310.-50.));
    if (!UserStorage::sharedUserStorage()->getIsVibrate()) {
        this->vibrationSwitch->toggle();
    }
    this->addChild(vibrationSwitch);
    // Eventalarm 스위치
    this->eventalarmSwitch = SwitchSprite::createWithValue(isEventalarm);
    eventalarmSwitch->setPosition(ccp(300.+65., 800.-370.-50.));
    if (!UserStorage::sharedUserStorage()->getIsEventalarm()) {
        this->eventalarmSwitch->toggle();
    }
    this->addChild(eventalarmSwitch);
    
    // 나부자 정보
    std::stringstream nabuzaInfomation;
    nabuzaInfomation << "게임명 : 나부자 (나도 부자다)\n제작사 : (주)애니테일\n버전 정보 : 3.0\nApp ID : 928342347\n고객 문의 : nabuza@anytale.com";
    CCLabelTTF *lbNabuzaInfomation    = CCLabelTTF::create(nabuzaInfomation.str().c_str(), "JejuGothic", 20);
    lbNabuzaInfomation->setHorizontalAlignment(kCCTextAlignmentLeft);
    lbNabuzaInfomation->setPosition(ccp(66., 800.-537.-75.));
    lbNabuzaInfomation->setAnchorPoint(ccp(0., .5));
    lbNabuzaInfomation->setColor(ccBLACK);
    this->addChild(lbNabuzaInfomation);

    // 도움말 / 페이스북 로그인
    ButtonSprite *helpButtonSprite = ButtonSprite::createWithItemKey(kGAMEBUTTON_HELP);
    ButtonSprite *helpButtonSpriteTapped = ButtonSprite::createWithItemKey(kGAMEBUTTON_HELP);
    helpButtonSpriteTapped->setScale(1.2);
    helpButtonSpriteTapped->setPosition(ccp(helpButtonSprite->getPositionX()-20., helpButtonSprite->getPositionY()-6.));

    ButtonSprite *facebookLoginButtonSprite = ButtonSprite::createWithItemKey(kGAMEBUTTON_FACEBOOK_LOGIN);
    ButtonSprite *facebookLoginButtonSpriteTapped = ButtonSprite::createWithItemKey(kGAMEBUTTON_FACEBOOK_LOGIN);
    facebookLoginButtonSpriteTapped->setScale(1.2);
    facebookLoginButtonSpriteTapped->setPosition(ccp(facebookLoginButtonSprite->getPositionX()-20., facebookLoginButtonSprite->getPositionY()-6.));
    
    CCMenuItemSprite *helpButtonItem    = CCMenuItemSprite::create(helpButtonSprite, helpButtonSpriteTapped, this, menu_selector(SettingLayer::openHelpView));
    CCMenuItemSprite *facebookButtonItem    = CCMenuItemSprite::create(facebookLoginButtonSprite, facebookLoginButtonSpriteTapped, this, menu_selector(SettingLayer::close));
    CCMenu *menu    = CCMenu::create(helpButtonItem, facebookButtonItem, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(ccp(visibleSize.width / 2, 800.-698.-44.));
    this->addChild(menu);
    
    // x 버튼
    CCMenuItemImage *btnCloseItem   = CCMenuItemImage::create("exit_btn.png", "exit_btn.png", this, callfuncO_selector(SettingLayer::close));
    btnCloseItem->setPosition(ccp(460., 690.));
    CCMenu *btnClose    = CCMenu::createWithItem(btnCloseItem);
    btnClose->setPosition(CCPointZero);
    this->addChild(btnClose);

    CCLayerColor::onEnter();
}

void SettingLayer::openHelpView() {
    WebViewLayer *webViewLayer  = WebViewLayer::createWithUrl("http://gs.anytale.com/nabuza_help_1.htm");
    this->addChild(webViewLayer);
}

void SettingLayer::close() {
    this->removeFromParentAndCleanup(true);
}

#pragma mark -
#pragma mark Touch Delegates

bool SettingLayer::ccTouchBegan(CCTouch *touch, CCEvent *pEvent) {
    
    return true;
}

void SettingLayer::ccTouchEnded(CCTouch *touch, CCEvent *event) {
    CCPoint pt    = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
    CCLog("TouchEnd");
    if (this->bgmSwitch->boundingBox().containsPoint(pt)) {
        this->bgmSwitch->toggle();
        UserStorage::sharedUserStorage()->setIsBgm(this->bgmSwitch->getValue());
        if (this->bgmSwitch->getValue()) {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        } else {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        }
        return;
    }
    if (this->effectSwitch->boundingBox().containsPoint(pt)) {
        this->effectSwitch->toggle();
        if (this->effectSwitch->getValue()) {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
        } else {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
        }
        return;
    }
    if (this->vibrationSwitch->boundingBox().containsPoint(pt)) {
        this->vibrationSwitch->toggle();
        if (this->vibrationSwitch->getValue()) {
            AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
        }
        return;
    }
    if (this->eventalarmSwitch->boundingBox().containsPoint(pt)) {
        IndicationLayer *indicationLayer    = IndicationLayer::create();
        indicationLayer->setTag(TAG_INDICATION_LAYER);
        this->addChild(indicationLayer);

        int updatedEventAlarmValue = this->eventalarmSwitch->getValue()? 0 : 1;
        
        std::stringstream ss;
        ss << "&set=" << updatedEventAlarmValue;
        AnytaleHTTP::onHttpRequesting(this, callfuncND_selector(SettingLayer::onHttpRequestCompleted), "/players/set_notifications", ss.str().c_str(), "PLAYERS_SET_NOTIFICATIONS");
        return;
    }
}

void SettingLayer::ccTouchCancelled(CCTouch *touch, CCEvent *pEvent) {
    CCLog("Cancel");
}

void SettingLayer::onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response) {
    Json::Value root;
    
    int error;
    AnytaleHTTP::validateResponse(response, root, error);
    
    if (error != 0) {
        CCLog("AuthStorage json parse error");
        return;
    }
    
    // 게임 시작을 서버에 알림
    if(strcmp(response->getHttpRequest()->getTag(), "PLAYERS_SET_NOTIFICATIONS") == 0) {
        /*
         {"code":0,"message":"OK","result":[]}
         */
        //        int code = root.get("code", 0).asInt();
        
        //        int remainJadeCount = UserStorage::sharedUserStorage()->getJadeCount() - NeedForGameMemory::sharedNeedForGameMemory()->getJadeCount();
        //        int remainCardCount = UserStorage::sharedUserStorage()->getCardCount() - NeedForGameMemory::sharedNeedForGameMemory()->getCardCount();
        IndicationLayer *indicationLayer    = (IndicationLayer *)this->getChildByTag(TAG_INDICATION_LAYER);
        indicationLayer->removeFromParentAndCleanup(true);
        
        this->eventalarmSwitch->toggle();
    }
    
    return;

}

void SettingLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate( this, 0, true );
}
