//
//  user_notify_icon_mm_bridge.m
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 3/17/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "notify_icon_mm_bridge.h"


void user_notify_icon_mm_bridge::notify_icon_init(const char * strIconFile)
{
   
   NSString * str = [[NSString alloc] initWithCString:strIconFile encoding:NSUTF8StringEncoding];
   
   m_pnotifyicon = (__bridge_retained void *) [[[user_notify_icon alloc]dd_invokeOnMainThreadAndWaitUntilDone:TRUE] init: str bridge:this];
   
}


void user_notify_icon_mm_bridge::notify_icon_destroy()
{
   [[((__bridge user_notify_icon *) m_pnotifyicon) dd_invokeOnMainThread] close];
   //NSMenu* rootMenu = [NSApp mainMenu];
   // sender is an NSMenuItem
   //[rootMenu removeItem: menu];
   //[rootMenu removeItemAtIndex: iIndex];
   
}

