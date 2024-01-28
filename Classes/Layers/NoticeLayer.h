//
//  NoticeLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 8/1/13.
//
//

#ifndef __NabuzaI__NoticeLayer__
#define __NabuzaI__NoticeLayer__

#include "cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;

class NoticeLayer : public cocos2d::CCLayerColor, public CCScrollViewDelegate {
private:
    int currentNoticeIdx;
    CCArray *notices;
    bool init();
    void viewContents();
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void registerWithTouchDispatcher();

#pragma-- CCScrollViewDelegate

    void scrollViewDidScroll(CCScrollView *view);
    void scrollViewDidZoom(CCScrollView *view);

public:
    CREATE_FUNC(NoticeLayer);
    void onEnter();
    void close();
    void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);
};

class NoticeModel : public cocos2d::CCObject {
public:
    int idx;
    std::string contents;
};

#endif /* defined(__NabuzaI__NoticeLayer__) */
