#ifndef __LAUNCHING_SCENE_H__
#define __LAUNCHING_SCENE_H__

#include "cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;

class LaunchingScene : public cocos2d::CCLayer {
private:
    bool isReady;
    void onHttpGetAccessTokenCompleted(CCObject *obj);

public:
    ~LaunchingScene();
    void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of
    // returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommend returning the class instance
    // pointer
    static cocos2d::CCScene *scene();
    void preload();

    // a selector callback
    void menuCloseCallback(CCObject *pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(LaunchingScene);

    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    void registerWithTouchDispatcher();
};

#endif  // __LAUNCHING_SCENE_H__
