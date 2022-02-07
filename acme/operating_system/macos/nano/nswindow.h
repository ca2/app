//
//  nswindow.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 02/02/22.
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
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
 
