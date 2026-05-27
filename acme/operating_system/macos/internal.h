//
//  c_os_cross_win_user_internal.h
//  c
//
//  Created by Snow Leopard User on 06/11/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once


#include "acme/_.h"




/*typedef struct tag_WINDOW
{

    
    WindowRef      m_windowref;
    void *         m_pnswindow;
    
    
    
} WINDOW, * LPWINDOW;

typedef LPWINDOW oswindow;

typedef ::i32 ::i32;

typedef struct tagRECT
{
   ::i32    left;
   ::i32    top;
   ::i32    right;
   ::i32    bottom;
} const i32_rectangle &, *PRECT, *NPRECT, *::i32_rectangle *;

typedef const i32_rectangle & * const i32_rectangle &;



#pragma once
*/

CGContextRef get_nswindow_cgcontext(oswindow pnswindow);


::i32_bool get_nswindow_rect(oswindow hwnd, ::i32_rectangle * prectangle);



inline ::i32 wxRound(::f64 x)
{
#if defined(HAVE_ROUND)
   return ::i32(round(x));
#else
   return (::i32)(x < 0 ? x - 0.5 : x + 0.5);
#endif
}




CGColorRef cg_create_color(color32_t crText);
::i32_bool cg_release_color(CGColorRef colorref);





//
//  c_os_win_user.h
//  c
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 12/30/11.
//  Copyright (c) 2011 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#pragma once



::i32_bool set_nswindow_frame(oswindow hwnd, const ::i32_rectangle & rectangle, ::i32 iDisplay);
::i32_bool size_nswindow(oswindow hwnd, ::i32 cx, ::i32 cy);
::i32_bool move_nswindow(oswindow hwnd, ::i32 x, ::i32 y);
