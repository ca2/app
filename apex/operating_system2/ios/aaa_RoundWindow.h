//
//  RoundWindow.h
//  RoundWindow
//
//  Created by Matt Gallagher on 12/12/08.
//  Copyright 2008 Matt Gallagher. All rights reserved.
//
//  Permission is given to use this source code file without charge in any
//  project, commercial or otherwise, entirely at your risk, with the condition
//  that any redistribution (in part or whole) of source code must retain
//  this copyright and permission notice. Attribution in compiled projects is
//  appreciated but not required.
//
#include "apex/user/_const_key.h"


::user::enum_key event_key(UIEvent * happening);


class round_window;

@class RoundImpactController;


@interface RoundWindow : UIWindow
{
@public
   
   
    round_window           * m_pwindow;
    RoundImpactController    * m_controller;
   
}


-(void)unsafe_boot_window_has_focus : (bool *)pbool;
-(void)on_destroy;
-(void)windowDidExpose;
-(void)windowWillClose;


@end



