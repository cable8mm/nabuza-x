//
//  AuthStorage.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 6/17/13.
//
//
// Process
// 1. appid가 저장되어 있는지 확인
// 2. 저장되어 있다면 사용. 사용 시 토큰 에러가 발생하면 각 API 마다 예외가 처리해 줌.
// 3. 저장되어 있지 않다면 서버로 부터 토큰을 가져 옴.
// http://nabuza-test.anytale.com/access_tokens/get/?consumer_key=lsg&signature=car&appid=208302830942
// consumer_key : 프로젝트마다 부여되는 키. 서버에 미리 등록되어 있어야 함.
// signature : 프로젝트마다 부여되는 사인. 서버에 미리 등록되어 있어야 함.
// appid : 보통 디바이스 아이디 혹은 앱 아이디를 말함. 앱에 대한 Unique ID.
// 4. 1-3 까지는 생성자 혹은 create에서 처리함.

#include "AuthStorage.h"
#include "../ProjectConfig.h"
#include "../Networks/AnytaleHTTP.h"

#import <UIKit/UIKit.h>

const char *AUTH_DEFAULT_STORAGE_ACCESS_TOKEN_KEY    = "AUTH_STORAGE_ACCESS_TOKEN_KEY";
const char *AUTH_DEFAULT_STORAGE_APP_ID_KEY    = "AUTH_STORAGE_APP_ID_KEY";

const char *CONSUMER_KEY    = "lsg";
const char *SIGNATURE       = "car";

static AuthStorage *s_SharedAuthStorage = NULL;

AuthStorage* AuthStorage::sharedAuthStorage(void)
{
    if (!s_SharedAuthStorage)
    {
        s_SharedAuthStorage = new AuthStorage();
        s_SharedAuthStorage->init();
    }
    
    return s_SharedAuthStorage;
}

bool AuthStorage::init()
{
    this->setAppId();
    return true;
}

void AuthStorage::onReceivingAccessToken() {
    std::ostringstream oss;
    oss << "consumer_key=" << CONSUMER_KEY << "&signature=" << SIGNATURE << "&appid=" << this->getAppId()->getCString();

    AnytaleHTTP::onHttpRequestingWithoutToken(this, callfuncND_selector(AuthStorage::onHttpRequestCompleted), "/access_tokens/get", oss.str().c_str(), "HTTP_GET_ACCESS_TOKEN");
}

void AuthStorage::onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response) {
    Json::Value root;
    int error;
    AnytaleHTTP::validateResponse(response, root, error);
    
    if (error != 0) {
        CCLog("AuthStorage json parse error");
        return;
    }
    
    // Access Token 얻기
    if(strcmp(response->getHttpRequest()->getTag(), "HTTP_GET_ACCESS_TOKEN") == 0) {
        /*
         {"code":0,"message":"OK","result":{"is_login":false}}
         OR
         {"code":0,"message":"OK","result":"51e760cc-cbe0-451d-9879-3af273443b49"}
         */
        std::string accessToken = root.get("result", "").asString();

        AuthStorage::sharedAuthStorage()->setAccessToken(accessToken);
        
        CCLog("DONE_HTTP_GET_ACCESS_TOKEN : %s", accessToken.c_str());
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification("ACCESS_TOKEN_GET_NOTIFICATION");
    }
    
    return;
}

void AuthStorage::setAccessToken() {
    this->accessToken   = CCUserDefault::sharedUserDefault()->getStringForKey(AUTH_DEFAULT_STORAGE_ACCESS_TOKEN_KEY, "");
    
    CCLog("AuthStorage::setAccessToken : %s | END", this->accessToken.c_str());
    
    if (this->accessToken.empty()) {
        this->onReceivingAccessToken();
    } else {
        CCNotificationCenter::sharedNotificationCenter()->postNotification("ACCESS_TOKEN_GET_NOTIFICATION");
    }
}

void AuthStorage::setAccessToken(std::string accessToken) {
    CCUserDefault::sharedUserDefault()->setStringForKey(AUTH_DEFAULT_STORAGE_ACCESS_TOKEN_KEY, accessToken);
    this->accessToken   = accessToken;
    CCNotificationCenter::sharedNotificationCenter()->postNotification("ACCESS_TOKEN_GET_NOTIFICATION");
}

void AuthStorage::didSetAccessToken() {
    
}

CCString *AuthStorage::getAccessToken() {
    return CCString::create(this->accessToken);
}

void AuthStorage::setAppId() {
    this->appId = CCUserDefault::sharedUserDefault()->getStringForKey(AUTH_DEFAULT_STORAGE_APP_ID_KEY);
    
    if (this->appId == "") {
        this->appId = GenerateAppId();
        CCUserDefault::sharedUserDefault()->setStringForKey(AUTH_DEFAULT_STORAGE_APP_ID_KEY, this->appId);
    }
}

CCString *AuthStorage::getAppId() {
    // for test
//    this->appId = "51e509ad-fccc-4f9c-804c-781c73443b49";
    return CCString::create(this->appId);
}

#pragma mark -
#pragma mark Functions

std::string GenerateAppId() {
    CFUUIDRef   uuid;
    CFStringRef uuidStr;
    std::string appId;

    uuid   = CFUUIDCreate(NULL);
    assert(uuid != NULL);
    
    uuidStr = CFUUIDCreateString(NULL, uuid);
    assert(uuidStr != NULL);
    
    appId   = [(NSString *)uuidStr UTF8String];
    
    CFRelease(uuidStr);
    CFRelease(uuid);
    
    return appId;
}