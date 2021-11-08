//
//  SettingLayer.h
//  NabuzaI
//
//  Created by Lee Samgu on 7/3/13.
//
//

#ifndef __NabuzaI__SettingLayer__
#define __NabuzaI__SettingLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SwitchSprite.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SettingLayer : public cocos2d::CCLayerColor
{
public:
    CREATE_FUNC(SettingLayer);
    
private:
    SwitchSprite *bgmSwitch;
    SwitchSprite *effectSwitch;
    SwitchSprite *vibrationSwitch;
    SwitchSprite *eventalarmSwitch;
    
    bool init();
    void onEnter();
    void close();
    void openHelpView();
    void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);
    
    // Touches
    bool ccTouchBegan(CCTouch *touch, CCEvent *pEvent);
    void ccTouchCancelled(CCTouch *touch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *touch, CCEvent *event);
    
    void registerWithTouchDispatcher();
};

#endif /* defined(__NabuzaI__SettingLayer__) */
