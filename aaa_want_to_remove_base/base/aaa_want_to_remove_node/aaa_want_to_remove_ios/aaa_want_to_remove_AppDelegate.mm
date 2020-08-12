//
//  AppDelegate.mm
//  app
//
//  Created by Camilo Sasuke Tsumanuma on 12/05/14.
//  Copyright (c) 2014 Camilo Sasuke Tsumanuma. All rights reserved.
//

//
//  AppDelegate.mm
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 05/05/14.
//  Copyright (c) 2014 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#import "AppDelegate.h"

plane_system * new_system(const char * pszId);

UIWindow * init_part_2ex(plane_system * psystem, CGRect rect);

void system_begin_main(plane_system * psystem);

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
   
//   [application _setApplicationIsOpaque : NO];
  
   NSString *ca2_command_line = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"ca2_command_line"];
   
   m_psystem = new_system([ca2_command_line UTF8String]);
   
   CGRect rect =[[UIScreen mainScreen] bounds];
   
   rect.origin.y = 0;
   
   self.window = init_part_2ex(m_psystem, rect);

   self.window.backgroundColor = [UIColor whiteColor];
   
   self.window.opaque = NO;
   
   [self.window makeKeyAndVisible];
   
//   system_begin_main(m_psystem);
   
   return YES;
   
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
