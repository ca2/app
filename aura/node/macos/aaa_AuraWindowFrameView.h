//
//  AuraWindowFrameView.h
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

#include "apex/node/macos/ApexWindowFrameView.h"

#define NS_ROUND_WINDOW_FRAME_PADDING 0

#include "keyboard.h"




@interface AuraWindowFrameView : ApexWindowFrameView
{
@public

   AuraWindow * m_paurawindow;
   
}

- (id)initWithFrame:(NSRect)frame andAuraWindow:(AuraWindow*)paurawindow;

@end
