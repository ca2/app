//
//  c_os_cross_win_user_internal.h
//  c
//
//  Created by Snow Leopard User on 06/11/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once






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
} RECTANGLE_I32, *PRECT, *NPRECT, *LPRECT32;

typedef const RECTANGLE_I32 * const RECTANGLE_I32 *;



#pragma once
*/

//CGContextRef get_nswindow_cgcontext(oswindow pnswindow);


int_bool get_uiwindow_rect(oswindow hwnd, LPRECT32 lprect);





int_bool set_nswindow_frame(oswindow hwnd, const RECTANGLE_I32 * prectangle, int iDisplay);
int_bool size_nswindow(oswindow hwnd, int cx, int cy);
int_bool move_nswindow(oswindow hwnd, int x, int y);
