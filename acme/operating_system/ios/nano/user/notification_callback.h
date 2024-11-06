//
//  notification_callback.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sorensen on 05/01/23.
//  Copyright (c) 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


#include <UIKit/UIKit.h>



@interface acme_notification_callback : NSObject
{
@public

   ::platform::application *               m_papplication;
   
}

-(void)themeChanged:(NSNotification *) notification;
-(void)fetch_dark_mode;

@end
