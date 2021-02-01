//
//  c_os_cross_win_user_internal.h
//  c
//
//  Created by Snow Leopard User on 06/11/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once


#include "apex/_.h"




/*typedef struct tag_WINDOW
{

    
    WindowRef      m_windowref;
    void *         m_pnswindow;
    
    
    
} WINDOW, * LPWINDOW;

typedef LPWINDOW oswindow;

typedef int ::i32;

typedef struct tagRECT
{
   ::i32    left;
   ::i32    top;
   ::i32    right;
   ::i32    bottom;
} const rectangle_i32 &, *PRECT, *NPRECT, *RECTANGLE_I32 *;

typedef const rectangle_i32 & * const rectangle_i32 &;



#pragma once
*/

CGContextRef get_nswindow_cgcontext(oswindow pnswindow);


int_bool get_nswindow_rect(oswindow hwnd, RECTANGLE_I32 * prectangle);



inline int wxRound(double x)
{
#if defined(HAVE_ROUND)
   return int(round(x));
#else
   return (int)(x < 0 ? x - 0.5 : x + 0.5);
#endif
}




CGColorRef cg_create_color(color32_t crText);
int_bool cg_release_color(CGColorRef colorref);





//
//  c_os_win_user.h
//  c
//
//  Created by Camilo Sasuke Tsumanuma on 12/30/11.
//  Copyright (c) 2011 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#pragma once



int_bool set_nswindow_frame(oswindow hwnd, const ::rectangle_i32 & rectangle, int iDisplay);
int_bool move_nswindow(oswindow hwnd, int x, int y);
