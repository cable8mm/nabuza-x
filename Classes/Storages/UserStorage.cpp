//
//  UserStorage.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 6/28/13.
//
//

#include "UserStorage.h"
#include "ATUtil.h"

const char *USER_DEFAULT_USER_STORAGE_CARD_COUNT_KEY    = "USER_STORAGE_CARD_COUNT_KEY";
const char *USER_DEFAULT_USER_STORAGE_CARD_LAST_UPDATED_KEY    = "USER_STORAGE_CARD_LAST_UPDATED_KEY";
const char *USER_DEFAULT_USER_STORAGE_IS_FIRST_KEY    = "USER_STORAGE_IS_FIRST_KEY";
const char *USER_DEFAULT_USER_STORAGE_NICKNAME_KEY    = "USER_STORAGE_NICKNAME_KEY";
const char *USER_DEFAULT_USER_STORAGE_OWN_JADE_COUNT_KEY    = "USER_STORAGE_OWN_JADE_COUNT_KEY";
const char *USER_DEFAULT_USER_STORAGE_OWN_GOLD_KEY    = "USER_STORAGE_OWN_GOLD_KEY";
const char *USER_DEFAULT_USER_STORAGE_INVITATION_COUNT_KEY    = "USER_STORAGE_INVITATION_COUNT_KEY";
const char *USER_DEFAULT_USER_STORAGE_LAST_LEVEL_KEY    = "USER_STORAGE_LAST_LEVEL_KEY";
const char *USER_DEFAULT_USER_STORAGE_HIGHSCORE_KEY    = "USER_STORAGE_HIGHSCORE_KEY";
const char *USER_DEFAULT_USER_STORAGE_COUNTDOWN_CLOCK    = "USER_STORAGE_COUNTDOWN_CLOCK";
const char *USER_DEFAULT_USER_STORAGE_SETTING_IS_BGM    = "USER_STORAGE_SETTING_IS_BGM";
const char *USER_DEFAULT_USER_STORAGE_SETTING_IS_EFFECT    = "USER_STORAGE_SETTING_IS_EFFECT";
const char *USER_DEFAULT_USER_STORAGE_SETTING_IS_VIBRATE    = "USER_STORAGE_SETTING_IS_VIBRATE";
const char *USER_DEFAULT_USER_STORAGE_SETTING_IS_EVENTALARM    = "USER_STORAGE_SETTING_IS_EVENTALARM";

static UserStorage *s_SharedUserStorage = NULL;

UserStorage::UserStorage() {
    
}

UserStorage* UserStorage::sharedUserStorage(void)
{
    if (!s_SharedUserStorage)
    {
        s_SharedUserStorage = new UserStorage();
        s_SharedUserStorage->init();
    }
    
    return s_SharedUserStorage;
}

bool UserStorage::init()
{
        this->reset();
    if (CCUserDefault::sharedUserDefault()->getBoolForKey(USER_DEFAULT_USER_STORAGE_IS_FIRST_KEY, false)) {
        this->isFirst   = true;
    } else {
        this->isFirst   = false;
    }

    this->cardCount = CCUserDefault::sharedUserDefault()->getIntegerForKey(USER_DEFAULT_USER_STORAGE_CARD_COUNT_KEY, 5);    // default 5
    
    if (this->lastCardCountUpdated == 0) {
        unsigned int currentClockCount  = GetClockCount();
        this->setLastCardCountUpdated(currentClockCount);
    }

    
    return true;
}

void UserStorage::reset() {
    CCUserDefault::sharedUserDefault()->setBoolForKey(USER_DEFAULT_USER_STORAGE_IS_FIRST_KEY, false);
    this->ownJadeCount  = CCUserDefault::sharedUserDefault()->getIntegerForKey(USER_DEFAULT_USER_STORAGE_OWN_JADE_COUNT_KEY, 7);    // default 7
    this->ownGold  = CCUserDefault::sharedUserDefault()->getIntegerForKey(USER_DEFAULT_USER_STORAGE_OWN_GOLD_KEY, 7000);    // default 7000
    
    this->lastLevel  = CCUserDefault::sharedUserDefault()->getIntegerForKey(USER_DEFAULT_USER_STORAGE_LAST_LEVEL_KEY, 0);    // default 7
    this->highscore  = CCUserDefault::sharedUserDefault()->getIntegerForKey(USER_DEFAULT_USER_STORAGE_HIGHSCORE_KEY, 0);    // default 7
    
    this->isBgm = CCUserDefault::sharedUserDefault()->getBoolForKey(USER_DEFAULT_USER_STORAGE_SETTING_IS_BGM, true);
    this->isEffect = CCUserDefault::sharedUserDefault()->getBoolForKey(USER_DEFAULT_USER_STORAGE_SETTING_IS_EFFECT, true);
    this->isVibrate = CCUserDefault::sharedUserDefault()->getBoolForKey(USER_DEFAULT_USER_STORAGE_SETTING_IS_VIBRATE, true);
    this->isEventalarm = CCUserDefault::sharedUserDefault()->getBoolForKey(USER_DEFAULT_USER_STORAGE_SETTING_IS_EVENTALARM, true);
}

int UserStorage::getCardCount() {
    CCAssert(this->lastCardCountUpdated != 0, "LastCardCountUpdated must not ZERO");
    
    if (this->cardCount < 5) {
        unsigned int diffSeconds    = this->getDiffSeconds();
        int updatingCardCount   = (int)floorf(diffSeconds/REMAIN_SECONDS_FOR_CARD);
        CCLog("diffSeconds : %u, UpdatingCardCount : %d", diffSeconds, updatingCardCount);
//        CCAssert(updatingCardCount > -1 && updatingCardCount < 6, "UpdatingCardCount must between 0 - 5");
        
        if (this->cardCount + updatingCardCount > 5) {
            this->setCardCount(5);
        } else {
            this->setCardCount(this->cardCount + updatingCardCount);
        }
    }
    
    return this->cardCount;
}

unsigned int UserStorage::getDiffSeconds() {
    unsigned int currentClockCount    = GetClockCount();
    unsigned int diff   = currentClockCount - this->lastCardCountUpdated;
    unsigned int diffSeconds    = (unsigned int)(diff/1000);
    return diffSeconds;
}

void UserStorage::setCardCount(int v) {
    // SERVER 이상으로 예외 코드 삽입.
    if (v < 0) {
        v = 0;
    }
    CCAssert(v > -1, "CardCount must over 0");
    
    CCLog("SetCardCount : %d -> %d", this->cardCount, v);
    if (this->cardCount == v) {
        return;
    }

    this->cardCount = v;
    CCUserDefault::sharedUserDefault()->setIntegerForKey(USER_DEFAULT_USER_STORAGE_CARD_COUNT_KEY, this->cardCount);
    CCLog("CARD COUNT %d Saved", v);
    
    unsigned int currentClockCount  = GetClockCount();
    this->setLastCardCountUpdated(currentClockCount);
    
    CCInteger *ownCardCount = CCInteger::create(this->cardCount);
    CCNotificationCenter::sharedNotificationCenter()->postNotification("OWN_CARD_COUNT_CHANGED_NOTIFICATION", ownCardCount);
}

void UserStorage::setLastCardCountUpdated(unsigned int v) {
    if (this->lastCardCountUpdated == v) {
        return;
    }
    this->lastCardCountUpdated   = v;
    CCUserDefault::sharedUserDefault()->setIntegerForKey(USER_DEFAULT_USER_STORAGE_CARD_LAST_UPDATED_KEY, v);
}

unsigned int UserStorage::getLastCardCountUpdated() {
    return this->lastCardCountUpdated;
}

void UserStorage::addCard(int cardCount) {
    int tmpCardCount   = this->cardCount + cardCount;
    CCLog("tmpCardCount / this->cardCount / cardCount : %d, %d, %d", tmpCardCount, this->cardCount, cardCount);
    this->setCardCount(tmpCardCount);
}

bool UserStorage::isCardFulled() {
    if (this->cardCount > 4) {
        return true;
    }
    return false;
}

#pragma mark -
#pragma mark Getter / Setter

void UserStorage::setNickname(std::string v) {
    CCUserDefault::sharedUserDefault()->setStringForKey(USER_DEFAULT_USER_STORAGE_NICKNAME_KEY, v);
    this->nickname  = v;    // USER_DEFAULT_USER_STORAGE_NICK_KEY
}

std::string UserStorage::getNickname() {
    return this->nickname;
}

void UserStorage::setOwnJadeCount(int v) {
    if (this->ownJadeCount == v) {
        return;
    } 
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey(USER_DEFAULT_USER_STORAGE_OWN_JADE_COUNT_KEY, v);
    this->ownJadeCount  = v;    // USER_DEFAULT_USER_STORAGE_NICK_KEY
    
    CCInteger *ownJadeCount = CCInteger::create(v);
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification("OWN_JADE_COUNT_CHANGED_NOTIFICATION", ownJadeCount);
}

void UserStorage::addOwnJadeCount(int v) {
    int newOwnJadeCount    = this->ownJadeCount + v;
    this->setOwnJadeCount(newOwnJadeCount);
}

CCString *UserStorage::getOwnJadeCount() {
    return CCString::createWithFormat("%d", this->ownJadeCount);
}

unsigned int UserStorage::getOwnJadeCountToInt() {
    return this->ownJadeCount;
}

unsigned int UserStorage::getJadeCount() {
    return this->ownJadeCount;
}

void UserStorage::setOwnGold(int v) {
    CCUserDefault::sharedUserDefault()->setIntegerForKey(USER_DEFAULT_USER_STORAGE_OWN_GOLD_KEY, v);
    this->ownGold  = v;    // USER_DEFAULT_USER_STORAGE_NICK_KEY

    CCInteger *ownGoldCount = CCInteger::create(v);
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification("OWN_GOLD_COUNT_CHANGED_NOTIFICATION", ownGoldCount);
}

CCString *UserStorage::getOwnGold() {
    return CCString::createWithFormat("%d", this->ownGold);
}

int UserStorage::getOwnGoldCount() {
    return this->ownGold;
}

void UserStorage::setLastLevel(int v) {
    CCUserDefault::sharedUserDefault()->setIntegerForKey(USER_DEFAULT_USER_STORAGE_LAST_LEVEL_KEY, v);
    this->lastLevel  = v;    // USER_DEFAULT_USER_STORAGE_NICK_KEY
}

CCString *UserStorage::getHighscore() {
    return CCString::createWithFormat("%d", this->highscore);
}

int UserStorage::getHighscoreToInt() {
    return this->highscore;
}

void UserStorage::setHighscore(int v) {
    CCUserDefault::sharedUserDefault()->setIntegerForKey(USER_DEFAULT_USER_STORAGE_HIGHSCORE_KEY, v);
    this->highscore  = v;
}

void UserStorage::setPlayerId(int v) {
    this->playerId  = v;
}

void UserStorage::setRemainSeconds(int v) {
    this->remainSeconds = v;
}

int UserStorage::getRemainSeconds() {
    return this->remainSeconds;
}

void UserStorage::flush() {
    CCUserDefault::sharedUserDefault()->flush();
}

void UserStorage::setCountDownClock() {
    CCUserDefault::sharedUserDefault()->setIntegerForKey(USER_DEFAULT_USER_STORAGE_COUNTDOWN_CLOCK, GetClockCount());
}

int UserStorage::getCountDownClock() {
    return CCUserDefault::sharedUserDefault()->getIntegerForKey(USER_DEFAULT_USER_STORAGE_COUNTDOWN_CLOCK, 0);
}

void UserStorage::setIsBgm(bool v) {
    if (this->isBgm == v) {
        return;
    }
    this->isBgm = v;
    CCUserDefault::sharedUserDefault()->setBoolForKey(USER_DEFAULT_USER_STORAGE_SETTING_IS_BGM, v);
}

void UserStorage::setIsEffect(bool v) {
    if (this->isEffect == v) {
        return;
    }
    this->isEffect = v;
    CCUserDefault::sharedUserDefault()->setBoolForKey(USER_DEFAULT_USER_STORAGE_SETTING_IS_EFFECT, v);
}

void UserStorage::setIsVibrate(bool v)  {
    if (this->isVibrate == v) {
        return;
    }
    this->isVibrate = v;
    CCUserDefault::sharedUserDefault()->setBoolForKey(USER_DEFAULT_USER_STORAGE_SETTING_IS_VIBRATE, v);
}

void UserStorage::setisEventalarm(bool v)  {
    if (this->isEventalarm == v) {
        return;
    }
    this->isEventalarm = v;
    CCUserDefault::sharedUserDefault()->setBoolForKey(USER_DEFAULT_USER_STORAGE_SETTING_IS_EVENTALARM, v);    
}

bool UserStorage::getIsBgm() {
    return this->isBgm;
}

bool UserStorage::getIsEffect() {
    return this->isEffect;
}

bool UserStorage::getIsVibrate() {
    return this->isVibrate;
}

bool UserStorage::getIsEventalarm() {
    return this->isEventalarm;
}

static LevelInformation *s_SharedLevelInformation = NULL;

LevelInformation::LevelInformation() {}

LevelInformation* LevelInformation::sharedLevelInformation(void)
{
    if (!s_SharedLevelInformation)
    {
        s_SharedLevelInformation = new LevelInformation();
        s_SharedLevelInformation->init();
    }
    
    return s_SharedLevelInformation;
}

bool LevelInformation::init()
{
    
    return true;
}

void LevelInformation::setting(unsigned int ownGoldCount) {
    unsigned int basicGoldCounts[]    = {0, 100,500,1000,2000,3000,4000,6000,8000,10000,15000,20000,25000,35000,45000,55000,80000,105000,130000,160000,190000,220000,300000,350000,400000,500000,600000,700000,900000,1100000,1300000,2000000,2500000,3000000,4000000,5000000,999999999};
    
    if (ownGoldCount == 0) {
        this->needGoldCountForNextLevel = basicGoldCounts[1];
        this->setKey(0);
        return;
    }
    
    if (ownGoldCount > 5000000) {
        this->needGoldCountForNextLevel = 0;
        this->setKey(35);
        return;
    }
    
    for (unsigned int i=0; i< sizeof(basicGoldCounts)/sizeof(basicGoldCounts[0]) - 1;i++) {
        if (basicGoldCounts[i] < ownGoldCount && ownGoldCount <= basicGoldCounts[i+1]) {
            this->needGoldCountForNextLevel = basicGoldCounts[i+2] - ownGoldCount;
            this->setKey(i+1);
            return;
        }
    }
}

void LevelInformation::setKey(unsigned int key) {
    this->key   = key;
    this->displayLevelNumber    = this->key + 1;
    this->levelBonus    = this->key+1;
    switch (this->key) {
        case 0: // 1단계
            this->displayName   = "알바생";
            break;
        case 1:
            this->displayName   = "알바생";
            break;
        case 2:
            this->displayName   = "알바생";
            break;
        case 3:
            this->displayName   = "사원";
            break;
        case 4:
            this->displayName   = "사원";
            break;
        case 5:
            this->displayName   = "사원";
            break;
        case 6:
            this->displayName   = "주임";
            break;
        case 7:
            this->displayName   = "주임";
            break;
        case 8:
            this->displayName   = "주임";
            break;
        case 9:
            this->displayName   = "대리";
            break;
        case 10:
            this->displayName   = "대리";
            break;
        case 11:
            this->displayName   = "대리";
            break;
        case 12:
            this->displayName   = "과장";
            break;
        case 13:
            this->displayName   = "과장";
            break;
        case 14:
            this->displayName   = "과장";
            break;
        case 15:
            this->displayName   = "차장";
            break;
        case 16:
            this->displayName   = "차장";
            break;
        case 17:
            this->displayName   = "차장";
            break;
        case 18:
            this->displayName   = "부장";
            break;
        case 19:
            this->displayName   = "부장";
            break;
        case 20:
            this->displayName   = "부장";
            break;
        case 21:
            this->displayName   = "이사";
            break;
        case 22:
            this->displayName   = "이사";
            break;
        case 23:
            this->displayName   = "이사";
            break;
        case 24:
            this->displayName   = "상무";
            break;
        case 25:
            this->displayName   = "상무";
            break;
        case 26:
            this->displayName   = "상무";
            break;
        case 27:
            this->displayName   = "전무";
            break;
        case 28:
            this->displayName   = "전무";
            break;
        case 29:
            this->displayName   = "전무";
            break;
        case 30:
            this->displayName   = "사장";
            break;
        case 31:
            this->displayName   = "사장";
            break;
        case 32:
            this->displayName   = "사장";
            break;
        case 33:
            this->displayName   = "회장";
            break;
        case 34:
            this->displayName   = "회장";
            break;
        case 35:
            this->displayName   = "회장";
            break;
    }
    
    CCLog("levelBonus : %d, maxNeedGoldCount : %d, needGoldCOuntForNextLevel : %d", this->levelBonus, this->maxNeedGoldCount, this->needGoldCountForNextLevel);
}

int LevelInformation::getLevelBonus() {
    return this->levelBonus;
}

int LevelInformation::getMaxNeedGoldCount() {
    return this->maxNeedGoldCount;
}

int LevelInformation::getNeedGoldCountForNextLevel() {
    return this->needGoldCountForNextLevel;
}

std::string LevelInformation::getDisplayName() {
    return this->displayName;
}

int LevelInformation::getLevel() {
    return this->displayLevelNumber;
}