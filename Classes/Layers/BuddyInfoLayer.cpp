//
//  BuddyInfoLayer.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 8/8/13.
//
//

#include "BuddyInfoLayer.h"

#include "../Networks/AnytaleHTTP.h"
#include "../Storages/UserStorage.h"
#include "../Structs/ButtonSprite.h"
#include "../Structs/LevelMoneySprite.h"
#include "ATUtil.h"
#include "BuddyStorage.h"
#include "IndicationLayer.h"

#define TAG_BUDDY_NAME_LABEL 40000
#define TAG_BUDDY_OWN_GOLD_LABEL 40001
#define TAG_BUDDY_NEXT_LEVEL_LABEL 40002
#define TAG_BUDDY_LEVEL_BONUS_LABEL 40003
#define TAG_BUDDY_WEEKLY_HIGHLIGHT_LABEL 40004
#define TAG_BUDDY_HIGHLIGHT_LABEL 40005
#define TAG_BUDDY_BRONZE_MEDAL_LABEL 40006
#define TAG_BUDDY_SILVER_MEDAL_LABEL 40007
#define TAG_BUDDY_GOLD_MEDAL_LABEL 40008
#define TAG_BUDDY_GRADE_NAME_LABEL 40009
#define TAG_BUDDY_LEVEL_LABEL 40010
#define TAG_INDICATION_LAYER 50000

#define DEFAULT_FONT_NAME "Helvetica"

BuddyInfoLayer *BuddyInfoLayer::createWithPlayerKey(int playerKey) {
    BuddyInfoLayer *pobLayer = new BuddyInfoLayer;
    pobLayer->playerKey = playerKey;

    if (pobLayer && pobLayer->initWithColor(ccc4(0., 0., 0., 200.))) {
        pobLayer->autorelease();
        return pobLayer;
    }
    CC_SAFE_DELETE(pobLayer);
    return NULL;
}

BuddyInfoLayer *BuddyInfoLayer::createWithBuddyKey(int buddyKey) {
    BuddyInfoLayer *pobLayer = new BuddyInfoLayer;
    pobLayer->buddyModel = (BuddyModel *)BuddyStorage::sharedBuddyStorage()
                               ->buddies->objectAtIndex(buddyKey);

    if (pobLayer && pobLayer->initWithColor(ccc4(0., 0., 0., 200.))) {
        pobLayer->autorelease();
        return pobLayer;
    }
    CC_SAFE_DELETE(pobLayer);
    return NULL;
}

void BuddyInfoLayer::onEnter() {
    this->setTouchEnabled(true);
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    LevelInformation *levelInformation =
        LevelInformation::sharedLevelInformation();
    levelInformation->setting(this->buddyModel->ownGoldCount);

    // 박스
    CCSprite *bgBoxSprite = CCSprite::create("title_alert.png");
    bgBoxSprite->setPosition(
        ccp(visibleSize.width / 2, visibleSize.height / 2 + 25.));
    this->addChild(bgBoxSprite);

    // BG user_info.png
    CCSprite *bgUserInfoSprite = CCSprite::create("user_info.png");
    bgUserInfoSprite->setPosition(ccp(visibleSize.width / 2, 403.));
    this->addChild(bgUserInfoSprite);

    // BG 돈다발
    LevelMoneySprite *bgMoneySprite =
        LevelMoneySprite::createWithGoldCount(this->buddyModel->ownGoldCount);
    bgMoneySprite->setPosition(ccp(404., 800. - 508));
    this->addChild(bgMoneySprite);

    // 이름
    CCLabelTTF *nameLabel = CCLabelTTF::create(
        this->buddyModel->nickname.c_str(), DEFAULT_FONT_NAME, 30.);
    nameLabel->setPosition(ccp(visibleSize.width / 2, 800. - 161.));
    nameLabel->setColor(ccBLACK);
    nameLabel->setHorizontalAlignment(kCCTextAlignmentCenter);
    nameLabel->setTag(TAG_BUDDY_NAME_LABEL);
    this->addChild(nameLabel);

    // 직책
    CCLabelTTF *gradeLabel = CCLabelTTF::create(
        levelInformation->getDisplayName().c_str(), DEFAULT_FONT_NAME, 35);
    gradeLabel->setColor(ccBLACK);
    gradeLabel->setAnchorPoint(CCPointZero);
    gradeLabel->setPosition(ccp(77., 800. - 255.));
    gradeLabel->setTag(TAG_BUDDY_GRADE_NAME_LABEL);
    this->addChild(gradeLabel);

    // 레벨 LV
    CCSprite *lvSprite = CCSprite::create("lv.png");
    lvSprite->setAnchorPoint(CCPointZero);
    lvSprite->setPosition(ccp(189., 800. - 255.));
    this->addChild(lvSprite);

    //    CCLabelBMFont *levelLabel   = CCLabelBMFont::create("LV",
    //    "font_56_brown.fnt"); levelLabel->setAlignment(kCCTextAlignmentRight);
    //    levelLabel->setPosition(ccp(189., 800.-242.));
    //    this->addChild(levelLabel);

    // 레벨 숫자

    int level = levelInformation->getLevel();
    CCSprite *levelSprite = CCSprite::create(
        "level_no.png",
        CCRect(level % 3 * 64., floorf(level / 3) * 40., 64., 40.));
    levelSprite->setAnchorPoint(ccp(1., 0.));
    levelSprite->setPosition(ccp(285., 800. - 255.));
    this->addChild(levelSprite);

    //    CCLabelBMFont *playerLevelLabel   = CCLabelBMFont::create("",
    //    "rst_score.fnt");
    //    playerLevelLabel->setAlignment(kCCTextAlignmentRight);
    //    playerLevelLabel->setPosition(ccp(235., 800.-237.));
    //    playerLevelLabel->setTag(TAG_BUDDY_LEVEL_LABEL);
    //    this->addChild(playerLevelLabel);

    // 보유 Gold

    std::string ownGoldCount = GetStringFromInt(this->buddyModel->ownGoldCount);
    ATUtil::insert_separator(ownGoldCount);
    CCLabelTTF *ownGoldLabel =
        CCLabelTTF::create(ownGoldCount.c_str(), DEFAULT_FONT_NAME, 20);
    ownGoldLabel->setColor(ccBLACK);
    ownGoldLabel->setPosition(ccp(312., 800. - 260.));
    ownGoldLabel->setAnchorPoint(ccp(0., .5));
    ownGoldLabel->setTag(TAG_BUDDY_OWN_GOLD_LABEL);
    this->addChild(ownGoldLabel);

    // 다음레벨까지
    std::string needGoldCount =
        GetStringFromInt(levelInformation->getNeedGoldCountForNextLevel());
    ATUtil::insert_separator(needGoldCount);
    CCLabelTTF *nextLevelLabel =
        CCLabelTTF::create(needGoldCount.c_str(), DEFAULT_FONT_NAME, 20);
    nextLevelLabel->setColor(ccBLACK);
    nextLevelLabel->setPosition(ccp(312., 800. - 315.));
    nextLevelLabel->setAnchorPoint(ccp(0., .5));
    nextLevelLabel->setTag(TAG_BUDDY_NEXT_LEVEL_LABEL);
    this->addChild(nextLevelLabel);

    // 레벨 보너스까지
    std::string levelBonus =
        GetStringFromInt(levelInformation->getLevelBonus());
    ATUtil::insert_separator(levelBonus);
    CCLabelTTF *levelBonusLabel =
        CCLabelTTF::create(levelBonus.c_str(), DEFAULT_FONT_NAME, 20);
    levelBonusLabel->setColor(ccBLACK);
    levelBonusLabel->setPosition(ccp(312., 800. - 360.));
    levelBonusLabel->setAnchorPoint(ccp(0., .5));
    levelBonusLabel->setTag(TAG_BUDDY_LEVEL_BONUS_LABEL);
    this->addChild(levelBonusLabel);

    // 금주 최고 점수
    std::string weeklyHighscore =
        GetStringFromInt(this->buddyModel->weeklyHighscore);
    ATUtil::insert_separator(weeklyHighscore);
    CCLabelTTF *thisWeekHighScoreLabel =
        CCLabelTTF::create(weeklyHighscore.c_str(), DEFAULT_FONT_NAME, 20);
    thisWeekHighScoreLabel->setColor(ccBLACK);
    thisWeekHighScoreLabel->setPosition(ccp(312., 800. - 411.));
    thisWeekHighScoreLabel->setAnchorPoint(ccp(0., .5));
    thisWeekHighScoreLabel->setTag(TAG_BUDDY_WEEKLY_HIGHLIGHT_LABEL);
    this->addChild(thisWeekHighScoreLabel);

    // 역대 최고 점수
    std::string highscore = GetStringFromInt(this->buddyModel->highscore);
    ATUtil::insert_separator(highscore);
    CCLabelTTF *highScoreLabel =
        CCLabelTTF::create(highscore.c_str(), DEFAULT_FONT_NAME, 20);
    highScoreLabel->setColor(ccBLACK);
    highScoreLabel->setPosition(ccp(312., 800. - 461.));
    highScoreLabel->setAnchorPoint(ccp(0., .5));
    highScoreLabel->setTag(TAG_BUDDY_HIGHLIGHT_LABEL);
    this->addChild(highScoreLabel);

    // 메달 갯수
    std::string goldMedalCount =
        GetStringFromInt(this->buddyModel->ownGoldMedalCount);
    CCLabelBMFont *goldMedalLabel =
        CCLabelBMFont::create(goldMedalCount.c_str(), "font_brown_45.fnt");
    goldMedalLabel->setAlignment(kCCTextAlignmentCenter);
    goldMedalLabel->setPosition(ccp(117., 261.));
    goldMedalLabel->setAnchorPoint(ccp(.5, .5));
    goldMedalLabel->setTag(TAG_BUDDY_GOLD_MEDAL_LABEL);
    this->addChild(goldMedalLabel);

    std::string silverMedalCount =
        GetStringFromInt(this->buddyModel->ownSilverMedalCount);
    CCLabelBMFont *silverMedalLabel =
        CCLabelBMFont::create(silverMedalCount.c_str(), "font_brown_45.fnt");
    silverMedalLabel->setAlignment(kCCTextAlignmentCenter);
    silverMedalLabel->setPosition(ccp(182., 261.));
    silverMedalLabel->setAnchorPoint(ccp(.5, .5));
    silverMedalLabel->setTag(TAG_BUDDY_SILVER_MEDAL_LABEL);
    this->addChild(silverMedalLabel);

    std::string bronzeMedalCount =
        GetStringFromInt(this->buddyModel->ownBronzeMedalCount);
    CCLabelBMFont *bronzeMedalLabel =
        CCLabelBMFont::create(bronzeMedalCount.c_str(), "font_brown_45.fnt");
    bronzeMedalLabel->setAlignment(kCCTextAlignmentCenter);
    bronzeMedalLabel->setPosition(ccp(247., 261.));
    bronzeMedalLabel->setAnchorPoint(ccp(.5, .5));
    bronzeMedalLabel->setTag(TAG_BUDDY_BRONZE_MEDAL_LABEL);
    this->addChild(bronzeMedalLabel);

    CCMenuItemImage *btnCloseItem =
        CCMenuItemImage::create("exit_btn.png", "exit_btn.png", this,
                                callfuncO_selector(BuddyInfoLayer::close));
    btnCloseItem->setPosition(ccp(455., 800. - 111.));
    CCMenu *btnClose = CCMenu::createWithItem(btnCloseItem);
    btnClose->setPosition(CCPointZero);
    btnClose->setTouchPriority(0);
    this->addChild(btnClose);

    CCLayerColor::onEnter();
}

void BuddyInfoLayer::onHttpRequestCompleted(CCHttpClient *sender,
                                            CCHttpResponse *response) {
    Json::Value root;
    Json::Reader reader;

    std::vector<char> *rawData = response->getResponseData();
    std::string ss(rawData->begin(), rawData->end());

    bool bIsParsed = reader.parse(ss, root, false);

    // 게임 시작을 서버에 알림
    if (strcmp(response->getHttpRequest()->getTag(), "PLAYERS_GET_BUDDY") ==
        0) {
        LevelInformation *levelInformation =
            LevelInformation::sharedLevelInformation();
        levelInformation->setting(
            root["result"]["Player"].get("own_gold", 0).asInt());

        //        int getLevelBonus();
        //        int getMaxNeedGoldCount();
        //        int getNeedGoldCountForNextLevel();

        std::string ss;

        ss = root["result"]["Player"].get("nickname", 0).asString();
        CCLabelTTF *nicknameLabel =
            (CCLabelTTF *)this->getChildByTag(TAG_BUDDY_NAME_LABEL);
        nicknameLabel->setString(ss.c_str());

        CCLabelTTF *gradeLabel =
            (CCLabelTTF *)this->getChildByTag(TAG_BUDDY_GRADE_NAME_LABEL);
        gradeLabel->setString(levelInformation->getDisplayName().c_str());

        ss = GetStringFromInt(
            root["result"]["Player"].get("highscore", 0).asInt());
        CCLabelTTF *highscoreLabel =
            (CCLabelTTF *)this->getChildByTag(TAG_BUDDY_HIGHLIGHT_LABEL);
        highscoreLabel->setString(ss.c_str());

        ss = GetStringFromInt(
            root["result"]["Player"].get("own_gold", 0).asInt());
        CCLabelTTF *ownGoldLabel =
            (CCLabelTTF *)this->getChildByTag(TAG_BUDDY_OWN_GOLD_LABEL);
        ownGoldLabel->setString(ss.c_str());

        ss = GetStringFromInt(levelInformation->getLevelBonus());
        CCLabelTTF *levelBonusLabel =
            (CCLabelTTF *)this->getChildByTag(TAG_BUDDY_LEVEL_BONUS_LABEL);
        levelBonusLabel->setString(ss.c_str());

        ss = GetStringFromInt(levelInformation->getNeedGoldCountForNextLevel());
        CCLabelTTF *nextLevelLabel =
            (CCLabelTTF *)this->getChildByTag(TAG_BUDDY_NEXT_LEVEL_LABEL);
        nextLevelLabel->setString(ss.c_str());

        ss = GetStringFromInt(
            root["result"]["Player"].get("gold_medal_count", 0).asInt());
        CCLabelBMFont *goldMedalCountLabel =
            (CCLabelBMFont *)this->getChildByTag(TAG_BUDDY_GOLD_MEDAL_LABEL);
        goldMedalCountLabel->setString(ss.c_str());

        ss = GetStringFromInt(
            root["result"]["Player"].get("silver_medal_count", 0).asInt());
        CCLabelBMFont *silverMedalCountLabel =
            (CCLabelBMFont *)this->getChildByTag(TAG_BUDDY_SILVER_MEDAL_LABEL);
        silverMedalCountLabel->setString(ss.c_str());

        ss = GetStringFromInt(
            root["result"]["Player"].get("bronze_medal_count", 0).asInt());
        CCLabelBMFont *bronzeMedalCountLabel =
            (CCLabelBMFont *)this->getChildByTag(TAG_BUDDY_BRONZE_MEDAL_LABEL);
        bronzeMedalCountLabel->setString(ss.c_str());

        ss = GetStringFromInt(
            root["result"]["Player"].get("weekly_highscore", 0).asInt());
        CCLabelTTF *weeklyHighscoreLabel =
            (CCLabelTTF *)this->getChildByTag(TAG_BUDDY_WEEKLY_HIGHLIGHT_LABEL);
        weeklyHighscoreLabel->setString(ss.c_str());

        //        ss = GetStringFromInt(levelInformation->getLevel());
        //        CCLabelBMFont *levelLabel  = (CCLabelBMFont
        //        *)this->getChildByTag(TAG_BUDDY_LEVEL_LABEL);
        //        levelLabel->setString(ss.c_str());

        //        IndicationLayer *indicationLayer    = (IndicationLayer
        //        *)this->getChildByTag(TAG_INDICATION_LAYER);
        //        indicationLayer->removeFromParentAndCleanup(true);
    }

    return;
}

bool BuddyInfoLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    return true;
}

void BuddyInfoLayer::close() {
    this->removeFromParentAndCleanup(true);
}

void BuddyInfoLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
        this, 0, true);
}

std::string GetStringFromInt(int v) {
    std::stringstream ss;
    ss << v;
    return ss.str();
}