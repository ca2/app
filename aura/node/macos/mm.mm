//
//  Keyboard.mm
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 8/19/15.
//
//
#import "_mm.h"



NSWindow * get_os_window_ns_window(oswindow hwnd);

CGWindowID get_os_window_window_number(oswindow oswindow)
{

   if(oswindow == NULL)
   {

      return 0;

   }

   NSWindow * window = get_os_window_ns_window(oswindow);

   if(window == NULL)
   {

      return 0;

   }

   
   return (CGWindowID)[window windowNumber];
   
}



NSWindow * get_os_window_ns_window(oswindow hwnd)
{
   
   return __nswindow(hwnd);
   
}
