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
} ::int_rectangle, *PRECT, *NPRECT, *::int_rectangle *;

typedef const ::int_rectangle * const ::int_rectangle *;



#pragma once
*/

//CGContextRef get_nswindow_cgcontext(oswindow pnswindow);


int_bool get_uiwindow_rect(oswindow hwnd, ::int_rectangle * lprect);





int_bool set_nswindow_frame(oswindow hwnd, const ::int_rectangle * prectangle, int iDisplay);
int_bool move_nswindow(oswindow hwnd, int x, int y);
