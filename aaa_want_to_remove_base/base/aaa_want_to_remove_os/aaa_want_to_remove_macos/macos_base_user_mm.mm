//
//  macos_user.mm
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//

#import "macos_windowing.h"


WINBOOL get_nswindow_rect(oswindow oswindow, LPRECT lprect);
void copy(LPRECT lprectDst, const CGRect & rectSrc);


bool oswindow_data::is_window_visible()
{
   
   return [window() isVisible];
   
}


bool oswindow_data::is_iconic()
{
   
   return [window() isMiniaturized] != FALSE;
   
}


bool oswindow_data::iconify()
{
   
   [window() miniaturize : 0];
   
   return 1;
   
}


bool oswindow_data::show_window(i32 nCmdShow)
{

   if(nCmdShow == SW_HIDE)
   {
   
//   printf("\nhide window");
    
      [[m_nswindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE ]orderOut : nil];

   }
   else if(nCmdShow == SW_SHOWNOACTIVATE)
   {

      [[m_nswindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] orderFront : nil];
      
   }
   else
   {
  //    printf("\nshow window");
//
      
      
      defer_dock_application(true);
      
      nsapp_activate_ignoring_other_apps(1);
      
      //[[m_nswindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE ]showWindow: nil];

      [[m_nswindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] makeKeyAndOrderFront : nil];
      
//      [[m_nswindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE ]display];
      
   }
   
   return 1;
   
}


bool oswindow_data::client_to_screen(POINT *lppoint)
{
   RECT rect;
   get_nswindow_rect(this, &rect);
   lppoint->x += rect.left;
   lppoint->y += rect.top;
   return true;
}

bool oswindow_data::screen_to_client(POINT *lppoint)
{
   RECT rect;
   get_nswindow_rect(this, &rect);
   lppoint->x -= rect.left;
   lppoint->y -= rect.top;
   return true;
}


WINBOOL move_nswindow(oswindow hwnd, int x, int y);



WINBOOL set_nswindow_frame(oswindow hwnd, LPCRECT lpcrect, int iDisplay)
{
   
   NSRect rect;
   
   NSRect frame = [[[NSScreen screens] objectAtIndex:0] frame];
   
   rect.origin.x     = lpcrect->left;
   rect.origin.y     = frame.size.height  -     lpcrect->bottom;
   rect.size.width   = lpcrect->right     -     lpcrect->left;
   rect.size.height  = lpcrect->bottom    -     lpcrect->top;
   
      //rect.origin.x     = 500;
      //rect.origin.y     = 100;
      //rect.size.width   = 500;
      //rect.size.height  = 500;
   
//   printf("\nset nswindow frame (%f, %f)[%f, %f]", rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);

   
   
   [[hwnd->window() dd_invokeOnMainThreadAndWaitUntilDone:TRUE] setFrame : rect display : iDisplay];
   
   //move_nswindow(hwnd, lpcrect->left, lpcrect->top);
   
   return 1;
   
}



WINBOOL move_nswindow(oswindow hwnd, int x, int y)
{
   
//   RECT rect;
   
//   get_nswindow_rect(hwnd, &rect);
   
   NSPoint point;
   
   point.x = x;
   point.y = [[NSScreen mainScreen] frame].size.height - y;
   
//   printf("\nmove nswindow (%f, %f)", point.x, point.y);

   
   [[hwnd->window() dd_invokeOnMainThreadAndWaitUntilDone:TRUE]setFrameTopLeftPoint : point];
   
   return 1;
   
   
}


WINBOOL make_key_and_order_front_nswindow(oswindow hwnd)
{

//   printf("\nmake_key_and_order_front_nswindow");

   
   [[hwnd->window() dd_invokeOnMainThreadAndWaitUntilDone:TRUE] makeKeyAndOrderFront: nil];
   
   return 1;
   
   
}


WINBOOL order_front_nswindow(oswindow hwnd)
{
//   printf("\norder_front_nswindow");
   
   [[hwnd->window() dd_invokeOnMainThreadAndWaitUntilDone:TRUE] orderFront: nil];
   
   return 1;
   
   
}


//CLASS_DECL_THREAD NSAutoreleasePool * g_ns_pool = NULL;
//
//
//
//
//NSAutoreleasePool * new_ns_pool()
//{
//   
//   NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
//   
//   return pool;
//   
//}
//
//
//void release_pool(NSAutoreleasePool * pool)
//{
//   
//   [pool release];
//   
//}

void on_start_thread()
{
   
//   g_ns_pool = new_ns_pool();
   
}


void on_end_thread()
{
   
//   release_pool(g_ns_pool);
   
  // g_ns_pool = NULL;
   
}


void ns_redraw_window(oswindow w)
{
   
   [[w->window() dd_invokeOnMainThreadAndWaitUntilDone:TRUE] display];
   
}


WINBOOL get_nswindow_rect(oswindow oswindow, LPRECT lprect)
{
   
   NSRect rect = [oswindow->window() frame];
   
   lprect->left        = rect.origin.x;
   lprect->bottom      = [[NSScreen mainScreen] frame ].size.height - rect.origin.y;
   lprect->right       = rect.origin.x  + rect.size.width;
   lprect->top         = lprect->bottom - rect.size.height;
   
   return 1;
   
}




WINBOOL SetWindowPos(oswindow hwnd, oswindow hwndInsertAfter, int x, int y, int cx, int cy, UINT uFlags)
{
   
   //   int   value_mask = 0;
   bool  bMove = !(uFlags & SWP_NOMOVE);
   bool  bSize = !(uFlags & SWP_NOSIZE);
   
   if(bMove && bSize)
   {
      
      RECT rect;
      
      rect.left      = x;
      rect.top       = y;
      rect.right     = rect.left + cx;
      rect.bottom    = rect.top + cy;

      hwnd->m_bNsWindowRect = false;
      
      set_nswindow_frame(hwnd, &rect, (uFlags & SWP_SHOWWINDOW) != 0);
      
   }
   else if(bSize) // bSize only
   {
      
      RECT rect;
      
      get_window_rect(hwnd, &rect);
      
      rect.right     = rect.left + cx;
      rect.bottom    = rect.top + cy;

      hwnd->m_bNsWindowRect = false;
      
      set_nswindow_frame(hwnd, &rect, (uFlags & SWP_SHOWWINDOW) != 0);
      
   }
   else if(bMove) // bMove only
   {
      
//      RECT rect;
//      
//      get_window_rect(hwnd, &rect);
//      
//      cx = rect.right - rect.left;
//      cy = rect.bottom - rect.top;
//      
//      rect.left      = x;
//      rect.top       = y;
//      rect.right     = rect.left + cx;
//      rect.bottom    = rect.top + cy;
//      
//      set_nswindow_frame(hwnd, &rect, (uFlags & SWP_SHOWWINDOW) != 0);

      hwnd->m_bNsWindowRect = false;

      move_nswindow(hwnd, x, y);
      
   }
   
   if(!(uFlags & SWP_NOZORDER))
   {
      
      iptr iInsertAfter = (iptr) hwndInsertAfter;
      
      if(iInsertAfter == zorder_top || iInsertAfter == ZORDER_TOPMOST)
      {
         
         order_front_nswindow(hwnd);
         
      }
      
   }
   
//   [[hwnd->window() dd_invokeOnMainThreadAndWaitUntilDone:TRUE] display];
   
   
   
   /*   if(!(uFlags & SWP_NOZORDER) && hwndInsertAfter >= 0)
    {
    value_mask |= CWSibling;
    values.sibling = hwndInsertAfter;
    values.stack_mode = Above;
    }
    
    XConfigureWindow(display, hwnd, value_mask, &values);
    
    if(uFlags & SWP_SHOWWINDOW)
    {
    XMapWindow(display, hwnd);
    }
    
    if(!(uFlags & SWP_NOZORDER) && hwndInsertAfter < 0)
    {
    if(hwndInsertAfter == zorder_top || hwndInsertAfter == ZORDER_TOPMOST)
    {
    XRaiseWindow(display, hwnd);
    }
    else if(hwndInsertAfter == ZORDER_BOTTOM)
    {
    XLowerWindow(display, hwnd);
    }
    
    }
    
    XCloseDisplay(display);*/
   
   return 1;
   
}



// bool macos_set_user_wallpaper(const char * psz)
// {

//    NSArray<NSScreen *> * screenArray = [NSScreen screens];
   
//    int screenCount = [screenArray count];

//    NSString * str = [NSString stringWithUTF8String: psz];
   
//    NSString * path = str;
   
//    NSURL * url = [NSURL fileURLWithPath: path];
   
// /*   NSDictionary * options = [NSDictionary dictionaryWithObjectsAndKeys:nil, NSWorkspaceDesktopImageFillColorKey, [NSNumber numberWithBool:NO], NSWorkspaceDesktopImageAllowClippingKey, [NSNumber numberWithInteger:NSImageScaleProportionallyUpOrDown], NSWorkspaceDesktopImageScalingKey, nil]; */
//    NSDictionary * options = [NSDictionary dictionaryWithObjectsAndKeys:
//       [NSColor colorWithCalibratedRed:0.51 green:0.49 blue:0.89 alpha:1.0], NSWorkspaceDesktopImageFillColorKey,
//                              [NSNumber numberWithBool:YES], NSWorkspaceDesktopImageAllowClippingKey, [NSNumber numberWithInteger:NSImageScaleProportionallyUpOrDown], NSWorkspaceDesktopImageScalingKey, nil];
   
//    NSError * error;
   
//    bool bOk = true;
   
//    for (int i = 0; i < screenCount; i++)
//    {

//       NSScreen * screen = [screenArray objectAtIndex: i];
      
//       NSURL * u = [[NSWorkspace sharedWorkspace] desktopImageURLForScreen: screen];
      
//       error = NULL;
      
//       [[[NSWorkspace sharedWorkspace] dd_invokeOnMainThreadAndWaitUntilDone:FALSE ] setDesktopImageURL:url forScreen: screen options:options error:&error];
      
//       if(error != NULL)
//       {
         
//          bOk = false;
         
//       }
   
//    }

//    return bOk;
   
// }



// long long mm_get_user_wallpaper(char *** ppp)
// {
   
//    mmos * p = [mmos get];
   
//    [p->theLock lock];
   
//    long long ll = p->m_llWallpaper;
   
//    *ppp = (char**) malloc(sizeof(char *) * ll);
   
//    for(long long i = 0; i < ll; i++)
//    {
   
//       (*ppp)[i] = strdup(p->m_ppszWallpaper[i]);
      
//    }
   
//    [p->theLock unlock];
   
//    return ll;
                         
   
// }





