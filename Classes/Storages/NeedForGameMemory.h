//
//  NeedForGameMemory.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/18/13.
//
//

#ifndef __NabuzaI__NeedForGameMemory__
#define __NabuzaI__NeedForGameMemory__

#include "cocos2d.h"
USING_NS_CC;

class NeedForGameMemory : public CCObject {
private:
    bool init();
    unsigned int jadeCount;
    int cardCount;
    
public:
    NeedForGameMemory();
    static NeedForGameMemory* sharedNeedForGameMemory(void);
    void reset();
    void addJadeCount(unsigned int v);
    void minusJadeCount(unsigned int v);
// Getters / Setters
    void setJadeCount(unsigned int v);
    unsigned int getJadeCount();
    void setCardCount(int v);
    unsigned int getCardCount();
};


#endif /* defined(__NabuzaI__NeedForGameMemory__) */
