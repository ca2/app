//
//  AuraWindow.h
//  AuraWindow
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

#include "apex/node/macos/ApexWindow.h"

#include "AuraWindowController.h"

unsigned int event_key_code(NSEvent * event);


class aura_window;


@interface AuraWindow : ApexWindow
{
@public
   
   
   aura_window *        m_paurawindow;
   
   
   
   
}

-(void)dealloc;

-(void)windowDidExpose;

-(void)windowWillClose;

@end
