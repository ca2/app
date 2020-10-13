//
//  c_os_cross_win_user_internal.h
//  c
//
//  Created by Snow Leopard User on 06/11/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once



#define NEAR
#define FAR

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

//CGContextRef get_nswindow_cgcontext(oswindow pnswindow);


int_bool get_uiwindow_rect(oswindow hwnd, LPRECT lprect);





int_bool set_nswindow_frame(oswindow hwnd, LPCRECT prect, int iDisplay);
int_bool size_nswindow(oswindow hwnd, int cx, int cy);
int_bool move_nswindow(oswindow hwnd, int x, int y);
