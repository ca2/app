//
//  notification_callback.m
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sorensen on 05/01/23.
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "app.h"
#include "acme/constant/id.h"
#include "acme/operating_system/argcargv.h"

void system_id_update(platform::system * psystem, long long iUpdate, long long iPayload);

::platform::system * application_system(::platform::application * papplication);

//#import <Foundation/Foundation.h>
void ns_main_post(dispatch_block_t block);
@implementation acme_notification_callback


- (id)init
{

////   ns_main_post(^{
//      
//   [ [ NSDistributedNotificationCenter defaultCenter ] addObserver:self selector:@selector(themeChanged:) name:@"AppleInterfaceThemeChangedNotification" object: nil];
//   //});

   return self;
   
}

-(void)dealloc
{
   
   
}

-(void)themeChanged:(NSNotification *) notification
{
 
   NSLog (@"%@", notification);
   
   [self fetch_dark_mode];
   
 
}


-(void)fetch_dark_mode
{
//   
//   NSString *interfaceStyle = [NSUserDefaults.standardUserDefaults valueForKey:@"AppleInterfaceStyle"];
//   
//   int iDarkMode = [interfaceStyle isEqualToString:@"Dark"];

   int iDarkMode = 0;
   if(UIScreen.mainScreen.traitCollection.userInterfaceStyle
      == UIUserInterfaceStyleDark)
   {
      
      iDarkMode = 1;
      
   }
    
   system_id_update(application_system(m_papplication), id_get_operating_system_dark_mode_reply, iDarkMode);

}




@end

