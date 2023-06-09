//
//  nswindow.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 02/02/22.
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


class nano_window_bridge;


@interface ns_nano_window : NSWindow
{
@public
   
   nano_window_bridge *       m_pwindowbridge;
   NSView *                   m_pimpactChild;
   NSWindowController *       m_pwindowcontroller;

}
@end
 
