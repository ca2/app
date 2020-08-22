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


#include "RoundWindowController.h"

unsigned int event_key_code(NSEvent * event);


class round_window;


@interface RoundWindow : NSWindow
{
@public
   
   
   bool                    m_bNoActivate;
   round_window            * m_pwindow;
   
   
	NSView                  * childContentView;
   NSWindowController      * m_controller;
   
   
}

-(void)dealloc;

-(void)windowDidExpose;

-(void)windowWillClose;

@end
