//
//  ItemStorage.h
//  NabuzaI
//
//  Created by Lee Samgu on 6/12/13.
//
//

#ifndef __NabuzaI__ItemStorage__
#define __NabuzaI__ItemStorage__

#include "cocos2d.h"
USING_NS_CC;

class ItemStorage : public CCObject {
private:
    CCUserDefault* userDefault;
    bool init();

public:
    static ItemStorage* create();
    static unsigned int getItemKey(CCObject* item);
    void reset();
    void addItem(int itemKey);
    void
    flush();  // add 할 때만 flush() 호출. add는 아이템 한개씩 더해져서 그런 것.
    CCArray* getItems();
    void purgeItemStorage();
};

#endif /* defined(__NabuzaI__ItemStorage__) */
