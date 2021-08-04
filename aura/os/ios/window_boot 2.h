//
//  boot_window.h
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 6/8/13 (aura_window).
//  16 de novembro de 2013 - 29 anos e dia da instância Camilo Sasuke Tsumanuma da Minha Alma Gêmea Master (boot_window)
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#pragma once


#include "app/base/user/user/user_key_enum.h"


class boot_window
{
public:


bool m_bDirty;
   
#ifdef __OBJC__
   mm_window * m_proundwindow;
#else
   void * m_proundwindow;
#endif
   
   
   virtual void boot_window_draw(CGContextRef cgc) = 0;
   virtual void boot_window_mouse_down(double x, double y) = 0;
   virtual void boot_window_mouse_up(double x, double y) = 0;
   virtual void boot_window_mouse_moved(double x, double y) = 0;
   virtual void boot_window_mouse_dragged(double x, double y) = 0;
   virtual bool boot_window_key_down(::user::enum_key ekey, const ::string & characters) = 0;
   virtual bool boot_window_key_up(::user::enum_key ekey, const ::string & characters) = 0;
   
   
   virtual void boot_window_invalidate();
   virtual void boot_window_show();
   virtual void boot_window_redraw();
   
   virtual void boot_window_destroy();
   
   
   virtual bool boot_window_has_focus();
   
   
};


UIWindow * new_boot_window(boot_window * pwindow, CGRect rectangle_i32);
void ios_application_main();
int ios_app_run(int argc, char * argv[]);