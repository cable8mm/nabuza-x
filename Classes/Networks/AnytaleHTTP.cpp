//
//  AnytaleHTTP.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 6/18/13.
//
//

#include "AnytaleHTTP.h"

#include "../ProjectConfig.h"
#include "../Storages/AuthStorage.h"

// 토근과 함께 URL 생성
std::string AnytaleHTTP::getUrlWithToken(std::string localUrl,
                                         std::string param) {
    //    CCString *fullUrl   =
    //    CCString::createWithFormat("%s",HTTP_SERVER_URL);

    std::string fullUrl;
    fullUrl.erase();
    fullUrl += HTTP_SERVER_URL;
    fullUrl += localUrl;
    fullUrl += "/?type=json&token=";
    fullUrl += AuthStorage::sharedAuthStorage()->getAccessToken()->getCString();
    fullUrl += param;

    return fullUrl;
}

// 토큰 없이 URL 생성
std::string AnytaleHTTP::getUrl(std::string localUrl, std::string param) {
    std::string fullUrl;
    fullUrl.erase();
    fullUrl += HTTP_SERVER_URL;
    fullUrl += localUrl;
    fullUrl += "/?type=json&";
    fullUrl += param;
    CCLog("AnytaleHTTP::getUrl : %s", fullUrl.c_str());
    return fullUrl;
}

void AnytaleHTTP::onHttpRequesting(CCObject* pTarget, SEL_CallFuncND pSelector,
                                   std::string url, std::string param,
                                   std::string tag) {
    std::ostringstream oss;
    std::string fullUrl = AnytaleHTTP::getUrlWithToken(url, param);

    CCLog("Server Request(getUrlWithToken) Full URL : %s", fullUrl.c_str());

    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl(fullUrl.c_str());
    request->setRequestType(CCHttpRequest::kHttpDelete);
    request->setResponseCallback(pTarget, (SEL_HttpResponse)pSelector);
    request->setTag(tag.c_str());
    CCHttpClient::getInstance()->send(request);
    request->release();
}

void AnytaleHTTP::onHttpRequestingWithoutToken(CCObject* pTarget,
                                               SEL_CallFuncND pSelector,
                                               std::string url,
                                               std::string param,
                                               std::string tag) {
    std::ostringstream oss;
    std::string fullUrl = AnytaleHTTP::getUrl(url, param);
    CCLog("AnytaleHTTP::getUrl(url, param) : %s", url.c_str());

    CCLog("Server Request(getUrl) Full URL : %s", fullUrl.c_str());

    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl(fullUrl.c_str());
    request->setRequestType(CCHttpRequest::kHttpDelete);
    request->setResponseCallback(pTarget, (SEL_HttpResponse)pSelector);
    request->setTag(tag.c_str());
    CCHttpClient::getInstance()->send(request);
    request->release();
}

// int AnytaleHTTP::validateResponse(CCHttpResponse *response, Json::Value
// &root) {
//     Json::Reader reader;
//
////    CCDictionary *result;
//
//    if (!response)
//    {
//        return -1;
//    }
//
//    CCLog("Launching Scene Test");
//
//    if (0 != strlen(response->getHttpRequest()->getTag()))
//    {
//        CCLog("%s completed", response->getHttpRequest()->getTag());
//    }
//
//    int statusCode = response->getResponseCode();
//    char statusString[64] = {};
//    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode,
//    response->getHttpRequest()->getTag());
//
//    CCLog("response code: %d", statusCode);
//
//    if (!response->isSucceed())
//    {
//        CCLog("response failed");
//        CCLog("error buffer: %s", response->getErrorBuffer());
//        return -2;
//    }
//
//    // dump data
//    std::stringstream ss;
//    std::vector<char> *buffer = response->getResponseData();
//    printf("Http Test, dump data: ");
//    for (unsigned int i = 0; i < buffer->size(); i++)
//    {
//        printf("%c", (*buffer)[i]);
//        ss << (*buffer)[i];
//    }
//    printf("\n");
//
//    bool bIsParsed  = reader.parse(ss.str(), root);
//
//    if (!bIsParsed) {
//        return -3;
//    }
//
//    return 0;
//}

void AnytaleHTTP::validateResponse(CCHttpResponse* response, Json::Value& root,
                                   int& error) {
    CCLog("AnytaleHTTP::validateResponse(CCHttpResponse *response, Json::Value "
          "&root, int &error)");
    Json::Reader reader;

    if (!response) {
        error = -1;
        return;
    }

    CCLog("Launching Scene Test");

    if (0 != strlen(response->getHttpRequest()->getTag())) {
        CCLog("%s completed", response->getHttpRequest()->getTag());
    }

    int statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode,
            response->getHttpRequest()->getTag());

    CCLog("response code: %d", statusCode);

    if (!response->isSucceed()) {
        CCLog("response failed");
        CCLog("error buffer: %s", response->getErrorBuffer());
        error = -2;
        return;
    }

    //    // dump data
    //    std::stringstream ss;
    //    std::vector<char> *buffer = response->getResponseData();
    //    printf("Http Test, dump data: ");
    //    for (unsigned int i = 0; i < buffer->size(); i++)
    //    {
    //        printf("%c", (*buffer)[i]);
    //        ss << (*buffer)[i];
    //    }
    //    printf("\n");

    std::vector<char>* rawData = response->getResponseData();
    std::string ss(rawData->begin(), rawData->end());

    bool bIsParsed = reader.parse(ss, root);

    if (!bIsParsed) {
        error = -3;
        return;
    }

    error = 0;
    return;
}

// int ValidateResponse(CCHttpResponse *response, Json::Value &root) {
//     CCLog("ValidateResponse");
//     Json::Reader reader;
//
//     //    CCDictionary *result;
//
//     if (!response)
//     {
//         return -1;
//     }
//
//     CCLog("Launching Scene Test");
//
//     if (0 != strlen(response->getHttpRequest()->getTag()))
//     {
//         CCLog("%s completed", response->getHttpRequest()->getTag());
//     }
//
//     int statusCode = response->getResponseCode();
//     char statusString[64] = {};
//     sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode,
//     response->getHttpRequest()->getTag());
//
//     CCLog("response code: %d", statusCode);
//
//     if (!response->isSucceed())
//     {
//         CCLog("response failed");
//         CCLog("error buffer: %s", response->getErrorBuffer());
//         return -2;
//     }
//
//     // dump data
////    std::stringstream ss;
////    std::vector<char> *buffer = response->getResponseData();
////    printf("Http Test, dump data: ");
////    for (unsigned int i = 0; i < buffer->size(); i++)
////    {
////        printf("%c", (*buffer)[i]);
////        ss << (*buffer)[i];
////    }
////    printf("\n");
//
//    std::vector<char>*rawData = response->getResponseData();
//    std::string ss(rawData->begin(), rawData->end());
//
//    bool bIsParsed  = reader.parse(ss, root, false);
//
//    if (!bIsParsed) {
//        return -3;
//    }
//
//    return 0;
//}
