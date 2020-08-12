//
//  c_os_cross_win_gdi.mm
//  c
//
//  Created by Camilo Sasuke Tsumanuma on 12/22/11.
//  Copyright (c) 2011 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "ios_mm.h"


oswindow set_active_window(oswindow window);



CGContextRef get_nswindow_cgcontext(oswindow oswindow)
{

//    return (CGContextRef) [[oswindow->window() graphicsContext] graphicsPort];
    
    return 0;

}




WINBOOL SetForegroundWindow(oswindow window)
{
   
   if(!::IsWindow(window))
      return FALSE;
   
    /*
     
   [NSApp activateIgnoringOtherApps:YES];
   
//   [NSApp setWindow : window->window()];

   [window->window() makeKeyAndOrderFront: NSApp];
   
   [window->window() orderFrontRegardless];
     
     */
   
   set_active_window(window);
   
   return TRUE;
   
}


WINBOOL BringWindowToTop(oswindow window)
{
   
   if(!::IsWindow(window))
      return FALSE;
    
    /*
   
   [NSApp activateIgnoringOtherApps:YES];
   
//   [NSApp setWindow : window->window()];
   
   [window->window() makeKeyAndOrderFront: NSApp];
   
   [window->window() orderFrontRegardless];
     
     */
   
   set_active_window(window);
   
   return TRUE;
   
}


WINBOOL set_nswindow_frame(oswindow hwnd, LPCRECT lpcrect, int iDisplay)
{
   
   CGRect rect;
   
   CGRect frame = [[UIScreen mainScreen] applicationFrame];
   
   rect.origin.x     = lpcrect->left;
   rect.origin.y     = frame.size.height  -     lpcrect->bottom;
   rect.size.width   = lpcrect->right     -     lpcrect->left;
   rect.size.height  = lpcrect->bottom    -     lpcrect->top;
   
   //   rect.origin.x     = 500;
   //   rect.origin.y     = 400;
   //   rect.size.width   = 500;
   //   rect.size.height  = 500;
   
   
   hwnd->window().frame = rect;
   
   return 1;
   
}
