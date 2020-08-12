#pragma once


#include "macos_oswindow.h"


//#include "macos_windowing.h"


#include "macos_window_impl.h"


//#include "macos_multithreading.h"



i32 axis_main_command_line(const char * pszParams, int argc, char *argv[]);

#ifdef cplusplus


namespace macos
{
   
   CGFloat get_system_main_menu_bar_height();
   CGFloat get_system_dock_height();
   
   
} // namespace macos




//
//  c_os_cross_win_user_internal.h
//  c
//
//  Created by Snow Leopard User on 06/11/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


/*typedef struct tag_WINDOW
 {
 
 
 WindowRef      m_windowref;
 void *         m_pnswindow;
 
 
 
 } WINDOW, * LPWINDOW;
 
 typedef LPWINDOW oswindow;
 
 typedef int LONG;
 
 typedef struct tagRECT
 {
 LONG    left;
 LONG    top;
 LONG    right;
 LONG    bottom;
 } RECT, *PRECT, NEAR *NPRECT, FAR *LPRECT;
 
 typedef const RECT FAR* LPCRECT;
 
 
 
 #pragma once
 */

CGContextRef get_nswindow_cgcontext(oswindow pnswindow);


WINBOOL get_nswindow_rect(oswindow hwnd,LPRECT lprect);


inline int wxRound(double x)
{
#if defined(HAVE_ROUND)
   return int(round(x));
#else
   return (int)(x < 0 ? x - 0.5 : x + 0.5);
#endif
}



#endif




