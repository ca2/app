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

   bool m_bRunningAppMainLoop;
   ::macos::nano_window *     m_pwindow;
   CFTypeRef                  m_pnsnanowindow;
   
   
   nano_window_bridge();
   ~nano_window_bridge() override;
   
   void create_ns_nano_window(CGRect cgrect);
   
   void display();
   
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
   
   
   virtual void _run_modal_loop();
   
};



