//
//  aura_window.h
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 6/8/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#pragma once


#include "apex/node/macos/apex_window.h"
//#include "app/axis/user/user/user_key_enum.h"


class aura_window :
   public apex_window
{
public:
   
   
#ifdef __OBJC__
   
   AuraWindow * m_paurawindow;
   
#else
   
   void * m_paurawindow; // cast to AuraWindow * to use it
   
#endif

//   bool                    m_bDestroying;
//   bool                    m_bDirty;
//
//   unsigned long long      m_uiLastUpdateBeg;
//   unsigned long long      m_uiLastUpdateEnd;

   
   aura_window();
   virtual ~aura_window();
   
//   virtual void round_window_add_ref() = 0;
//   virtual void round_window_dec_ref() = 0;
//
//   virtual void round_window_draw(CGContextRef cgc, CGSize sizeWindow) = 0;
//   virtual void round_window_mouse_down(int iButton, double x, double y) = 0;
//   virtual void round_window_mouse_up(int iButton, double x, double y) = 0;
//   virtual void round_window_mouse_moved(double x, double y, unsigned long ulAppleMouseButton) = 0;
//   virtual void round_window_mouse_dragged(double x, double y, unsigned long ulAppleMouseButton) = 0;
//   virtual void round_window_mouse_wheel(double deltaY, double x, double y) = 0;
//   virtual void round_window_double_click(int iButton, double x, double y) = 0;
//   virtual bool round_window_key_down(unsigned int vk, unsigned int scan, const char * pszUtf8) = 0;
//   virtual bool round_window_key_up(unsigned int vk, unsigned int scan) = 0;
//   virtual bool round_window_key_down(unsigned int uiKeyCode) = 0;
//   virtual bool round_window_key_up(unsigned int uiKeyCode) = 0;
//
//   virtual void round_window_resized(CGRect rect) = 0;
//   virtual void round_window_moved(CGPoint point) = 0;
//
//   virtual void round_window_iconified() = 0;
//   virtual void round_window_deiconified() = 0;
//
//   virtual void round_window_on_show() = 0;
//   virtual void round_window_on_hide() = 0;
//   virtual void round_window_on_miniaturize() = 0;
//
//   virtual void round_window_did_become_key() = 0;
//
//   virtual void round_window_activate() = 0;
//   virtual void round_window_deactivate() = 0;
   
   virtual void round_window_set_frame(CGRect rect)override;
   virtual void round_window_invalidate()override;
   virtual void round_window_show()override;
   virtual void round_window_hide()override;
   virtual void round_window_miniaturize()override;
   virtual void round_window_redraw()override;
   virtual void round_window_redraw_sync()override;
   
   virtual void round_window_order_front()override;
   virtual void round_window_make_key_window()override;
   virtual void round_window_make_key_window_and_order_front()override;
   virtual void round_window_make_main_window()override;
   
   virtual void round_window_set_title(const char * pszTitle)override;
   virtual void round_window_get_title(char * pszTitle, int iSize)override;
   
   virtual void round_window_destroy()override;
   
   //virtual void ns_main_async(dispatch_block_t block) = 0;
   
};


NSWindow * new_aura_window(aura_window * pwindow, CGRect rect, unsigned int uStyel);
void ns_app_close();


NSWindow * get_os_window_ns_window(oswindow hwnd);



