//
//  AnytaleHTTP.h
//  NabuzaI
//
//  Created by Lee Samgu on 6/18/13.
//
//

#ifndef __NabuzaI__AnytaleHTTP__
#define __NabuzaI__AnytaleHTTP__

#include "cocos-ext.h"
#include "cocos2d.h"
#include "json/json.h"

USING_NS_CC;
USING_NS_CC_EXT;

class AnytaleHTTP : public cocos2d::CCObject {
private:
public:
    static std::string getUrlWithToken(std::string localUrl, std::string param);
    static std::string getUrl(std::string localUrl, std::string param);
    //    static std::string getRequestBody(std::string url);
    static void onHttpRequesting(CCObject *pTarget, SEL_CallFuncND pSelector,
                                 std::string url, std::string param,
                                 std::string tag);
    static void onHttpRequestingWithoutToken(CCObject *pTarget,
                                             SEL_CallFuncND pSelector,
                                             std::string url, std::string param,
                                             std::string tag);
    //    static CCDictionary *validateResponse(CCHttpResponse *response, int
    //    &error); static int validateResponse(CCHttpResponse *response,
    //    Json::Value &root);
    static void validateResponse(CCHttpResponse *response, Json::Value &root,
                                 int &error);
};

// int ValidateResponse(CCHttpResponse *response, Json::Value &root);

#endif /* defined(__NabuzaI__AnytaleHTTP__) */
