//
//  AuthStorage.h
//  NabuzaI
//
//  Created by Lee Samgu on 6/17/13.
//
//

#ifndef __NabuzaI__AuthStorage__
#define __NabuzaI__AuthStorage__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class AuthStorage : public CCObject {
private:
    std::string appId;
    
    // Login Information
    std::string accessToken;

    bool init();
    void setAppId();
    void didSetAccessToken();
    void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);
    
public:
    void onReceivingAccessToken();
//    std::string getAccessTokenFromServer();
//    std::string getAccessTokenFromServer(CCObject* pTarget, SEL_CallFuncND pSelector);
    static AuthStorage* sharedAuthStorage(void);
    void setAccessToken();
    void setAccessToken(std::string accessToken);
    CCString *getAppId();
    CCString *getAccessToken();
};

std::string GenerateAppId();

#endif /* defined(__NabuzaI__AuthStorage__) */
