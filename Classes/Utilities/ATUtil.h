//
//  Util.h
//  NabuzaI
//
//  Created by Lee Samgu on 4/22/13.
//
//

#ifndef __NabuzaI__Util__
#define __NabuzaI__Util__

#include "cocos2d.h"

USING_NS_CC;

#include <string>
using std::string;

class ATUtil {
public:
    static float agy(float y);
    static void insert_separator(
        string& s, char separator = ',',
        int width = 3);  // http://kldp.org/node/38269#comment-125583
};

unsigned int GetClockCount();

#endif /* defined(__NabuzaI__Util__) */
