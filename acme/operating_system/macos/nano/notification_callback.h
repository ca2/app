//
//  notification_callback.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sorensen on 05/01/23.
//  Copyright (c) 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


#include <Cocoa/Cocoa.h>


@interface nano_notification_callback : NSObject
{
@public

   void *               m_pApplication;
   
}

-(void)themeChanged:(NSNotification *) notification;
-(void)fetch_dark_mode;

@end
