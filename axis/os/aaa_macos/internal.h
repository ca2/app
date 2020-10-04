//
//  c_os_cross_win_user_internal.h
//  c
//
//  Created by Snow Leopard User on 06/11/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once


#include "aura/_.h"

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
} const rect &, *PRECT, NEAR *NPRECT, FAR *RECT *;

typedef const rect & FAR* const rect &;



#pragma once
*/

CGContextRef get_nswindow_cgcontext(oswindow pnswindow);


WINBOOL get_nswindow_rect(oswindow hwnd, RECT * prect);



inline int wxRound(double x)
{
#if defined(HAVE_ROUND)
   return int(round(x));
#else
   return (int)(x < 0 ? x - 0.5 : x + 0.5);
#endif
}




CGColorRef cg_create_color(COLORREF crText);
WINBOOL cg_release_color(CGColorRef colorref);





//
//  c_os_win_user.h
//  c
//
//  Created by Camilo Sasuke Tsumanuma on 12/30/11.
//  Copyright (c) 2011 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#pragma once



WINBOOL set_nswindow_frame(oswindow hwnd, const ::rect & rect, int iDisplay);
WINBOOL move_nswindow(oswindow hwnd, int x, int y);
