//
//  UserStorage.h
//  NabuzaI
//
//  Created by Lee Samgu on 6/28/13.
//
//

#ifndef __NabuzaI__UserStorage__
#define __NabuzaI__UserStorage__

#include "cocos2d.h"
USING_NS_CC;

#define REMAIN_SECONDS_FOR_CARD     70

class UserStorage : public CCObject {
private:
    std::string nickname;
    int ownJadeCount;
    int ownGold;
    int cardCount;
    unsigned int lastCardCountUpdated;
    int lastLevel;
    int highscore;
    int playerId;
    int remainSeconds;  // 서버에서 내려주는 수치, 카드 올라가는 초의 초기값으로 사용.
    
    bool isBgm;
    bool isEffect;
    bool isVibrate;
    bool isEventalarm;
    
    bool init();
    void reset();
    void setLastCardCountUpdated(unsigned int v);
    bool isFirst;
    
public:
    UserStorage();
    static UserStorage* sharedUserStorage(void);
    static UserStorage* create();
    void addCard(int cardCount);
    int getCardCount();
    void setCardCount(int v);
    void setPlayerId(int v);
    void setNickname(std::string v);
    std::string getNickname();
    void setOwnJadeCount(int v);
    void addOwnJadeCount(int v);
    CCString *getOwnJadeCount();
    unsigned int getOwnJadeCountToInt();
    unsigned int getJadeCount();
    void setOwnGold(int v);
    CCString *getOwnGold();
    int getOwnGoldCount();
//    void setInvitationCount(int v);
//    CCString *getInvitationCount();
    void setLastLevel(int v);
    CCString *getHighscore();
    int getHighscoreToInt();
    void setHighscore(int v);
    bool isCardFulled();
    void setCountDownClock();
    int getCountDownClock();
    void setRemainSeconds(int v);
    int getRemainSeconds();
    unsigned int getLastCardCountUpdated();
    unsigned int getDiffSeconds();
    
    void setIsBgm(bool v);
    void setIsEffect(bool v);
    void setIsVibrate(bool v);
    void setisEventalarm(bool v);
    bool getIsBgm();
    bool getIsEffect();
    bool getIsVibrate();
    bool getIsEventalarm();
    
    void flush();   // add 할 때만 flush() 호출. add는 아이템 한개씩 더해져서 그런 것.
};

class LevelInformation {
private:
    int key;
    int displayLevelNumber;
    std::string displayName;
    int maxNeedGoldCount;
    int levelBonus;
    int needGoldCountForNextLevel;
    void setKey(unsigned int key);
public:
    void setting(unsigned int ownGoldCount);
    static LevelInformation* sharedLevelInformation(void);
    bool init();
    LevelInformation();
    
    // Getters / Setters
    int getLevelBonus();
    int getMaxNeedGoldCount();
    int getNeedGoldCountForNextLevel();
    std::string getDisplayName();
    int getLevel();
};

#endif /* defined(__NabuzaI__UserStorage__) */
