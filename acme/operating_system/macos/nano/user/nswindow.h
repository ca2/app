//
//  nswindow.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 02/02/22.
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


#include <Cocoa/Cocoa.h>

class nano_window_bridge;
@class ns_nano_impact;


@interface ns_nano_window : NSWindow
{
@public
   
   nano_window_bridge *       m_pnanowindowbridge;
   ns_nano_impact *           m_pnsnanoimpact;
   //NSWindowController *       m_pwindowcontroller;

}
@end
 
