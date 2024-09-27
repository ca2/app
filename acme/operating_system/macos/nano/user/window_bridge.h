//
//  c_window.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 01/02/22.
//  23:26
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


#ifdef __OBJC__

@class ns_nano_window;

#endif

namespace macos
{

namespace nano
{
class window;
}
}


#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>

namespace macos{
namespace nano{
namespace user{
class window;
}
}
}

class nano_window_bridge :
   virtual public ::particle
{
public:

   bool m_bRunningAppMainLoop;
   ::macos::nano::user::interchange *     m_pwindow;
   CFTypeRef                  m_pnsnanowindow;
   
   
   nano_window_bridge();
   ~nano_window_bridge() override;
   
   void create_ns_nano_window(CGRect cgrect);
   
   void display();
   
   void hide();
   
   virtual void on_left_button_up(int xHost, int yHost, int xAbsolute, int yAbsolute);

   virtual void on_left_button_down(int xHost, int yHost, int xAbsolute, int yAbsolute);

   virtual void on_right_button_up(int xHost, int yHost, int xAbsolute, int yAbsolute);

   virtual void on_right_button_down(int xHost, int yHost, int xAbsolute, int yAbsolute);

   virtual void on_mouse_move(int xHost, int yHost, int xAbsolute, int yAbsolute);
   
   virtual void on_char(int iChar);
   
   virtual void _on_draw_frame(CGContextRef cg, CGSize sizeFrame);
   
   virtual void redraw();

   virtual void stop();
   
   virtual void move_to(int x, int y);

   virtual void on_layout(int x, int y, int w, int h);
   
   
   virtual void _run_modal_loop();
   
   virtual bool _is_top_most() const;
   
   virtual bool _is_popup_window() const;
   
};



