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

typedef int int;

typedef struct tagRECT
{
   int    left;
   int    top;
   int    right;
   int    bottom;
} ::rectangle_i32, *PRECT, *NPRECT, *::rectangle_i32 *;

typedef const ::rectangle_i32 * const ::rectangle_i32 *;



#pragma once
*/

//CGContextRef get_nswindow_cgcontext(oswindow pnswindow);


int_bool get_uiwindow_rect(oswindow hwnd, ::rectangle_i32 * lprect);





int_bool set_nswindow_frame(oswindow hwnd, const ::rectangle_i32 * prectangle, int iDisplay);
int_bool move_nswindow(oswindow hwnd, int x, int y);
