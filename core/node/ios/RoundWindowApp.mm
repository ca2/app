//
//  AppDelegate.mm
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 05/05/14.
//  Copyright (c) 2014 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "_mm.h"
#import "RoundWindowApp.h"

void os_on_finish_launching();

i32 defer_run_system();

i32 defer_run_system(const char * pszFileName);

i32 defer_run_system(char * * psza, int c);

void system_call_update_app_activated();

plane_system * create_plane_system();

@implementation RoundWindowApp

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{

//   m_psystem = create_plane_system();
//   
//   CGRect rect = [[UIScreen mainScreen] bounds];
//
//   self.window = m_psystem->plane_system_initialize(rect);
//
//   self.window.backgroundColor = [UIColor whiteColor];
//
//   self.window.opaque = NO;
//
//   [self.window makeKeyAndVisible];
//   
//   m_psystem->plane_system_begin();
   
   //set_apex_system_as_thread();
   //MessageBox(NULL, "applicationDidFinishLaunching", "applicationDidFinishLaunching", e_message_box_ok);
   
   //defer_run_system();
   
   os_on_finish_launching();
   
   return YES;
   
}

- (UIInterfaceOrientationMask)application:(UIApplication *)application
  supportedInterfaceOrientationsForWindow:(UIWindow *)window
{
   return UIInterfaceOrientationMaskAll;
   
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end


void ns_application_main(int argc, char * argv[], const char * pszCommandLine)
{
   
   UIApplicationMain(argc, argv, nil, NSStringFromClass([RoundWindowApp class]));
   
}


