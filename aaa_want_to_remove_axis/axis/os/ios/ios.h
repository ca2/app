#pragma once


//#include "ios_ns_exception.h"


//#include "ios_multithreading.h"


#include "ios_base_internal.h"



/*#ifdef cplusplus

template < class T >
class thread_pointer
{
public:
    
    
    const char * name;
    
    thread_pointer(const char * pszName)
    {
        name = pszName;
    }
    
    
    operator T *()
    {
        
        return (T *) get_thread_ptr(name);
        
    }
    
    T * operator ->()
    {
        return operator T *();
    }
    
    thread_pointer & operator = (T * pt)
    {
        
        set_thread_ptr(name, point);
        
        return *this;
        
    }
    
};


template < class T >
class thread_var
{
public:
    
    const char * name;
    
    thread_var(const char * pszName)
    {
        name = pszName;
    }
    
    
    operator T ()
    {
        
        return (T) get_thread_int(name);
        
    }
    
    thread_var & operator = (T t)
    {
        
        set_thread_int(name, t);
        
        return *this;
        
    }
    
    
};


#endif



*/

#include "ios_window_impl.h"

#ifdef __OBJC__

#import "ios_m.h"

#endif


#pragma once


//#include "macos_oswindow.h"


//#include "macos_windowing.h"


//#include "macos_window_impl.h"


//#include "macos_multithreading.h"


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


CGColorRef cg_create_color(COLORREF crText);
WINBOOL cg_release_color(CGColorRef colorref);





//
//  c_os_win_user.h
//  c
//
//  Created by Camilo Sasuke Tsumanuma on 12/30/11.
//  Copyright (c) 2011 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//




WINBOOL set_nswindow_frame(oswindow hwnd, oswindow hwndInsertAfter,LPCRECT prect,int iDisplay);
WINBOOL move_nswindow(oswindow hwnd,int x,int y);
WINBOOL make_key_and_order_front_nswindow(oswindow hwnd);
WINBOOL order_front_nswindow(oswindow hwnd);










#endif




