//
//  c_window.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 01/02/22.
//  23:26
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


#ifdef __OBJC__

@class ns_nano_window;

#endif

namespace macos
{
class nano_window;

}


class nano_window_bridge :
   virtual public ::element
{
public:

   
   ::macos::nano_window * m_pwindow;
   
#ifdef __OBJC__
   
   CFTypeRef  m_pnsnanowindow;
   
#else
   
   void * m_pvoidNsNanoWindow;
   
#endif
   
   nano_window_bridge();
   ~nano_window_bridge() override;
   
   void create_ns_nano_window(CGRect cgrect);
   
   void do_modal();
   
   virtual void on_left_button_up(int x, int y);

   virtual void on_left_button_down(int x, int y);

   virtual void on_right_button_up(int x, int y);

   virtual void on_right_button_down(int x, int y);

   virtual void on_mouse_move(int x, int y);
   
   virtual void on_char(int iChar);
   
   virtual void _on_draw_frame(CGContextRef cg, CGSize sizeFrame);
   
   virtual void redraw();

   virtual void stop();
   
   virtual void move_to(int x, int y);

   virtual void on_layout(int x, int y, int w, int h);
   
   
};



