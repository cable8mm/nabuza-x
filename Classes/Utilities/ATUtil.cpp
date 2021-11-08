//
//  Util.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 4/22/13.
//
//

const float SCREEN_WIDTH    = 800.;

#include "ATUtil.h"

float ATUtil::agy(float y) {
    float result    = SCREEN_WIDTH - y;
    return result;
}

void ATUtil::insert_separator(string& s, char separator, int width)
{
    if (s.length() < 4) {
        return;
    }
    
	string::iterator i = s.end() - width;
	while (i > s.begin())
		i = s.insert(i, separator) - width;
}

// Get clock count in milliseconds
unsigned int GetClockCount()
{
#if 0   // Traditional C Programming
    struct timeval gettick;
    gettimeofday(&gettick, NULL);
    return (unsigned int)(gettick.tv_sec * 1000 + gettick.tv_usec / 1000);
#else   // Cocos2d-x
    struct cc_timeval gettick;
    CCTime::gettimeofdayCocos2d(&gettick, 0);
    return (unsigned int)(gettick.tv_sec * 1000 + gettick.tv_usec / 1000);
#endif
}