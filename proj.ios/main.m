//
//  main.m
//  iphone
//
//  Created by Walzer on 10-11-16.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

// Under iOS and the Simulator, we can use an alternate Accelerometer interface
#import "AccelerometerSimulation.h"

#import "AppController.h"

int main(int argc, char *argv[])
{
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppController class]));
    }
}


//int main(int argc, char *argv[]) {
//    
//    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
//    int retVal = UIApplicationMain(argc, argv, nil, @"AppController");
//    [pool release];
//    return retVal;
//}
