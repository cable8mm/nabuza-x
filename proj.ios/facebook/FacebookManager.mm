//
//  FacebookManager.m
//  NabuzaI
//
//  Created by Lee Samgu on 8/27/13.
//
//

#import "FacebookManager.h"

@implementation FacebookManager

+(id)sharedInstance
{
    static dispatch_once_t pred = 0;
    __strong static id _sharedObject = nil;
    dispatch_once(&pred, ^{
        _sharedObject = [[self alloc] init];
    });
    return _sharedObject;
}

-(BOOL)isActiveSession {
    if (FBSession.activeSession.state == FBSessionStateCreatedTokenLoaded) {
        return YES;
    } else {
        // No, display the login page.
        return NO;
    }
}

- (void)sessionStateChanged:(FBSession *)session
                      state:(FBSessionState) state
                      error:(NSError *)error
{
    switch (state) {
        case FBSessionStateOpen: {
        }
            break;
        case FBSessionStateClosed:
        case FBSessionStateClosedLoginFailed:
            break;
        default:
            break;
    }
    
    if (error) {
    }    
}

- (void)openSession
{
    [FBSession openActiveSessionWithReadPermissions:nil
                                       allowLoginUI:YES
                                  completionHandler:
     ^(FBSession *session,
       FBSessionState state, NSError *error) {
         [self sessionStateChanged:session state:state error:error];
     }];
}

@end
