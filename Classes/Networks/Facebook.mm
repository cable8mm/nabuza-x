//
//  Facebook.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 6/25/13.
//
//


#include "Facebook.h"
//#include <Social/Social.h>
//#include <Social/SLComposeViewController.h>


void Facebook::FB_CreateNewSession()
{
    //m_kGameState = kGAMESTATE_FRONTSCREEN_NOSOCIAL_READY;
    //return;
    
//    FBSession* session = [[FBSession alloc] init];
//    [FBSession setActiveSession: session];
}

// Attempt to open the session - perhaps tabbing over to Facebook to authorise
void Facebook::FB_Login()
{
//    NSArray *permissions = [[NSArray alloc] initWithObjects:
//                            @"email",
//                            nil];
//    
//    // Attempt to open the session. If the session is not open, show the user the Facebook login UX
//    [FBSession openActiveSessionWithReadPermissions:permissions allowLoginUI:true completionHandler:^(FBSession *session,
//                                                                                                      FBSessionState status,
//                                                                                                      NSError *error)
//     {
//     // Did something go wrong during login? I.e. did the user cancel?
//     if (status == FBSessionStateClosedLoginFailed || status == FBSessionStateCreatedOpening) {
//     
//        // If so, just send them round the loop again
//        [[FBSession activeSession] closeAndClearTokenInformation];
//        [FBSession setActiveSession:nil];
//        FB_CreateNewSession();
//     }
//     else
//     {
//     // Update our game now we've logged in
//        if (m_kGameState == kGAMESTATE_FRONTSCREEN_LOGGEDOUT) {
//        UpdateView(true);
//        }
//     }
//     
//     }];
}