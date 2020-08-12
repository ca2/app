//
//  c_os_cross_win_gdi.mm
//  c
//
//  Created by Camilo Sasuke Tsumanuma on 12/22/11.
//  Copyright (c) 2011 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#import "macos_mm.h"
#import "macos_windowing.h"





oswindow SetActiveWindow(oswindow window);



CGContextRef get_nswindow_cgcontext(oswindow oswindow)
{

    return (CGContextRef) [[oswindow->window() graphicsContext] graphicsPort];

}





WINBOOL SetForegroundWindow(oswindow window)
{
   
   if(!::IsWindow(window))
      return FALSE;
   
   [[NSApp dd_invokeOnMainThreadAndWaitUntilDone:FALSE] activateIgnoringOtherApps:YES];
   
//   [NSApp setWindow : window->window()];

   [[window->window() dd_invokeOnMainThreadAndWaitUntilDone:FALSE] makeKeyWindow];

   [[window->window() dd_invokeOnMainThreadAndWaitUntilDone:FALSE] makeMainWindow];
   
   SetActiveWindow(window);
   
   return TRUE;
   
}


WINBOOL BringWindowToTop(oswindow window)
{
   
   if(!::IsWindow(window))
      return FALSE;
   
   [[window->window() dd_invokeOnMainThreadAndWaitUntilDone:FALSE] orderFront: NSApp];
   
   [[window->window() dd_invokeOnMainThreadAndWaitUntilDone:FALSE] orderFrontRegardless];
   
   return TRUE;
   
}
