//
//  Facebook.h
//  NabuzaI
//
//  Created by Lee Samgu on 6/25/13.
//
//

#ifndef __NabuzaI__Facebook__
#define __NabuzaI__Facebook__

#import <FacebookSDK/FacebookSDK.h>
#import <UIKit/UIKit.h>

// Standard Types
typedef char i8;
typedef unsigned char u8;
typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;
typedef signed long long i64;
typedef unsigned long long u64;

// Fixed Point
typedef signed long fx64;
typedef signed int fx32;
typedef signed short fx16;

static const u64 kuFBAppID = 425937460847689;

class Facebook {
private:
public:
    void FB_CreateNewSession();
    void FB_Login();
};

#endif /* defined(__NabuzaI__Facebook__) */
