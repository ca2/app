        //
//  macos_user.mm
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//

#include "_mm.h"
//#include "apex/node/macos/RoundWindowApp.h"



void copy(LPRECT lprectDst, const CGRect & rectSrc);


namespace macos
{

   CGFloat get_system_main_menu_bar_height()
   {
      return [[[NSApplication sharedApplication] mainMenu] menuBarHeight];
   }

   CGFloat get_system_dock_height()
   {
      return [[[NSApplication sharedApplication] mainMenu] menuBarHeight];
   }



} // namespace macos


namespace user
{


   bool is_dark_mode()
   {
      
      if (@available(macOS 10.9, *)) {
         NSAppearance *appearance = NSAppearance.currentAppearance;
         
         if (@available(*, macOS 10.14))
         {
            
            return appearance.name == NSAppearanceNameDarkAqua;
            
         }
         else
         {
            
            return false;
            
         }
      } else {
         return false;
      }
      return false;
      
   }


} // namespace user

CGRect g_rectWorkspace;


void mm_init_workspace_rect()
{
   
   g_rectWorkspace = [[NSScreen mainScreen] frame];
   
}


CGRect mm_get_workspace_rect()
{
   
   return g_rectWorkspace;
   
}


int GetMainScreenRect(RECT * prect)
{
   
   auto rect = [[NSScreen mainScreen] frame];
   
   window_copy(prect, &rect);
   
   return 0;
   
}


int GetScreenRect(RECT * prect, int iMonitor)
{
   
   if([NSScreen screens] == nil)
   {
      
      return -1;
      
   }
   
   if(iMonitor >= [NSScreen screens].count)
   {
      
      return -1;
      
   }
   
   try
   {
      
      auto rect = [[[NSScreen screens] objectAtIndex: iMonitor] frame];
      
      window_copy(prect, &rect);
      
   }
   catch (...)
   {
      
      return -1;
      
   }
                   
   
   
   return iMonitor;
   
}


int GetScreenCount()
{
   
   return (int) [[NSScreen screens] count];
   
}


int GetWkspaceRect(RECT * prect, int iMonitor)
{
   
   auto rect = [[[NSScreen screens] objectAtIndex:iMonitor ] visibleFrame];
   
   window_copy(prect, &rect);
   
   return iMonitor;
   
}


int GetWkspaceCount()
{
   
   return (int) [[NSScreen screens] count];
   
}




void ns_app_run()
{
   
   [NSApp run];
   
}







oswindow set_active_window(oswindow window);


//
//CGContextRef get_nswindow_cgcontext(oswindow oswindow)
//{
//
//   return (CGContextRef) [[__nswindow(oswindow) graphicsContext] graphicsPort];
//
//}
//

//WINBOOL SetForegroundWindow(oswindow window)
//{
//
//   if(!::is_window(window))
//      return FALSE;
//
//   ns_main_async(^{
//
//      [NSApp activateIgnoringOtherApps:YES];
//
//      [__nswindow(window) makeKeyWindow];
//
//      [__nswindow(window) makeMainWindow];
//
//      set_active_window(window);
//
//   });
//
//   return TRUE;
//
//}

//
//WINBOOL BringWindowToTop(oswindow window)
//{
//
//   if(!::is_window(window))
//      return FALSE;
//
//   [[__nswindow(window) dd_invokeOnMainThreadAndWaitUntilDone:FALSE] orderFront: NSApp];
//
//   [[__nswindow(window) dd_invokeOnMainThreadAndWaitUntilDone:FALSE] orderFrontRegardless];
//
//   return TRUE;
//
//}
//



//const char * mm_keyboard_input_source()
//{
//   
//   TISInputSourceRef source = TISCopyCurrentKeyboardInputSource();
//   NSString *s = (__bridge NSString *)(TISGetInputSourceProperty(source, kTISPropertyInputSourceID));
//   
//   if(s == nil)
//      return strdup("");
//   
//   return strdup([s UTF8String]);
//}
//








bool nswindow_is_visible(NSWindow * window)
{
   
   return [window isVisible];
   
}


bool nswindow_is_iconic(NSWindow * window)
{
   
   return [window isMiniaturized] != FALSE;
   
}


bool nswindow_iconify(NSWindow * window)
{
   
   [window miniaturize : 0];
   
   return 1;
   
}

bool is_visible(e_display);

//bool nswindow_show_window(NSWindow * window, int iShow)
//{
//   
//   if(iShow <= 0)
//   {
//   
////   printf("\nhide window");
//      
//      ns_main_async(^
//      {
//         [window orderOut : nil];
//      });
//
//   }
//   else if(iShow == SW_MINIMIZE)
//   {
//   
////   printf("\nhide window");
//      
//      ns_main_async(^
//      {
//         [window miniaturize : nil];
//      });
//
//   }
//   else if(iShow == SWP_NOACTIVATE)
//   {
//
//      ns_main_async(^
//                    {
//                       [window orderFront : nil];
//                    });
//
//   }
//   else
//   {
//  //    printf("\nshow window");
////
//      
//      
//      defer_dock_application(true);
//      
//      nsapp_activate_ignoring_other_apps(1);
//      
//      //[[m_nswindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE ]showWindow: nil];
//
//      ns_main_async(^
//                    {
//                       [window makeKeyAndOrderFront : nil];
//                    });
//
//      
////      [[m_nswindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE ]display];
//      
//   }
//   
//   return 1;
//   
//}


