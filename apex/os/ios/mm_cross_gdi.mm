//
//  c_os_cross_win_gdi.mm
//  c
//
//  Created by Camilo Sasuke Tsumanuma on 12/22/11.
//  Copyright (c) 2011 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "_mm.h"


int GetMainWkspaceRect(LPRECT lprect);


//oswindow set_active_window(oswindow window);



//CGContextRef get_nswindow_cgcontext(oswindow oswindow)
//{
//
////    return (CGContextRef) [[oswindow->window() graphicsContext] graphicsPort];
//    
//    return 0;
//
//}


//int GetMainScreenRect(LPRECT lprect)
//{
//
//   CGRect rect = [[UIScreen mainScreen] bounds];
//
//   lprect->left        = 0;
//   lprect->top         = 0;
//   lprect->right       = rect.size.width;
//   lprect->bottom      = rect.size.height;
//   
//   return TRUE;
//   
//}


int GetMainWkspaceRect(LPRECT lprect)
{

   GetMainScreenRect(lprect);
   
   CGSize statusBarSize = [[UIApplication sharedApplication] statusBarFrame].size;
   
   int iHeight = min(statusBarSize.width, statusBarSize.height);
   
   lprect->top = iHeight;
   
   //lprect->bottom -= iHeight;
   
   return TRUE;
   
}



int GetScreenRect(LPRECT lprect, int iMonitor)
{
   return GetMainScreenRect(lprect);
}

int GetScreenCount()
{
   return 1;
}


int GetWkspaceRect(LPRECT lprect, int iMonitor)
{

   return GetMainWkspaceRect(lprect);
   
}


int GetWkspaceCount()
{
   return 1;
}



int_bool SetForegroundWindow(oswindow window)
{
  
  if(!::is_window(window))
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


//int_bool BringWindowToTop(oswindow window)
//{
//   
//   if(!::is_window(window))
//      return FALSE;
//    
//   /*
//   
//   [NSApp activateIgnoringOtherApps:YES];
//   
////   [NSApp setWindow : window->window()];
//   
//   [window->window() makeKeyAndOrderFront: NSApp];
//   
//   [window->window() orderFrontRegardless];
//     
//   */
//   
//   set_active_window(window);
//   
//   return TRUE;
//   
//}




