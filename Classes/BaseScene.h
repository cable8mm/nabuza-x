//
//  BaseScene.h
//  NabuzaI
//
//  Created by Lee Samgu on 5/27/13.
//
//

#ifndef __NabuzaI__BaseScene__
#define __NabuzaI__BaseScene__

#include "cocos2d.h"
#include "CCScale9Sprite.h"
#include "CCControlButton.h"

USING_NS_CC;
USING_NS_CC_EXT;

class BaseScene : public cocos2d::CCLayer
{
private:
    bool init();
    void onEnter();
public:
    ~BaseScene();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(BaseScene);
};

void playBgm();

#endif /* defined(__NabuzaI__BaseScene__) */
