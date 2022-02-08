//
//  macos_user.mm
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//


#include "_mm.h"


int get_uiwindow_rect(oswindow oswindow, LPRECT lprect);


bool uiwindow_is_visible(UIWindow * window)
{
   
   //return [window isVisible];
   return true;
   
}


bool uiwindow_is_iconic(UIWindow * window)
{
   
   return false;
   
}


int move_nswindow(oswindow hwnd, int x, int y)
{
   
//   RECT rect;
   
//   get_nswindow_rect(hwnd, &rect);
   
   CGPoint point;
   
   point.x = x;
   point.y = [[UIScreen mainScreen] applicationFrame].size.height - y;
   
//   [hwnd->window() setFrameTopLeftPoint : point];
   
   return 1;
   
   
}




void ns_redraw_window(oswindow w)
{
   
//   [w->window() display];
   
}

int ui_open_url(const char * pszUrl)
{
   
   NSString * strUrl = [NSString stringWithUTF8String:pszUrl];
   
   if(strUrl == NULL)
      return 0;
   
   NSURL * url = [NSURL URLWithString:strUrl];
   
   if(url == NULL)
   {
      
      //[strUrl release];
      
      return 0;
      
   }
   
  // [strUrl release];
   
   BOOL b = [[UIApplication sharedApplication] openURL:url];   
   
//   [url release];

   return b ? 1 : 0;

}


CGRect g_rectWorkspace;


void mm_init_workspace_rect()
{
   
   g_rectWorkspace = [[UIScreen mainScreen] bounds];
   
}


CGRect mm_get_workspace_rect()
{
   
   return g_rectWorkspace;
   
}



int_bool get_uiwindow_rect(oswindow oswindow, LPRECT lprect)
{
   
   CGRect rect = [__uiwindow(oswindow) frame];
   
   lprect->left        = rect.origin.x;
   lprect->bottom      = [[UIScreen mainScreen] bounds ].size.height - rect.origin.y;
   lprect->right       = rect.origin.x  + rect.size.width;
   lprect->top         = lprect->bottom - rect.size.height;
   
   return 1;
   
}



bool uiwindow_show_window(UIWindow * window, int iShow)
{
   
   if(iShow <= 0)
   {
   
//   printf("\nhide window");
      
//      ns_main_async(^
//      {
//         [window orderOut : nil];
//      });

      ns_main_async(^
       {
          [window setHidden: true];
       });

   }
   else if(iShow == SW_MINIMIZE)
   {
   
//   printf("\nhide window");
      
//      ns_main_async(^
//      {
//         [window miniaturize : nil];
//      });
      
      ns_main_async(^
       {
          [window setHidden: true];
       });
   }
   else if(iShow == SWP_NOACTIVATE)
   {

//      ns_main_async(^
//                    {
//                       [window orderFront : nil];
//                    });
      ns_main_async(^
      {
         [window makeKeyAndVisible];
      });

   }
   else
   {
  //    printf("\nshow window");
//
      
      ns_main_async(^
      {
         [window makeKeyAndVisible];
      });

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

      
//      [[m_nswindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE ]display];
      
   }
   
   return 1;
   
}
