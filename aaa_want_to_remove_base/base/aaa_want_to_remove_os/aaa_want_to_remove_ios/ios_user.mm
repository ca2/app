//
//  macos_user.mm
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//




WINBOOL get_nswindow_rect(oswindow oswindow, LPRECT lprect);
void copy(LPRECT lprectDst, const CGRect & rectSrc);


bool oswindow_data::is_window_visible()
{
   
   return 1;
   
}


bool oswindow_data::is_iconic()
{
   
//   [window() miniaturize : 0];
   
   return 0;
   
   
}


bool oswindow_data::show_window(i32 nCmdShow)
{
   
   if(nCmdShow == SW_HIDE)
   {
      
      //   printf("\nhide window");
      
//      [m_nswindow orderOut : nil];
      
   }
   else
   {
      //    printf("\nshow window");
      
  //    [m_nswindow makeKeyAndOrderFront : nil];
      
    //  [m_nswindow display];
      
   }
   
   return 1;
   
}


WINBOOL ui_SetWindowPos(oswindow hwnd, oswindow hwndInsertAfter, int x, int y, int cx, int cy, UINT uFlags)
;

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



WINBOOL set_nswindow_frame(oswindow hwnd,oswindow hwndAfter, LPCRECT lpcrect, int iDisplay)
{
   
   CGRect rect = [[UIScreen mainScreen] bounds];
   
   rect.origin.x     = lpcrect->left;
   rect.origin.y     = rect.size.height  -     lpcrect->bottom;
   rect.size.width   = lpcrect->right     -     lpcrect->left;
   rect.size.height  = lpcrect->bottom    -     lpcrect->top;
   
   //   rect.origin.x     = 500;
   //   rect.origin.y     = 400;
   //   rect.size.width   = 500;
   //   rect.size.height  = 500;
   
   //   printf("\nset nswindow frame (%f, %f)[%f, %f]", rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
   ui_SetWindowPos(hwnd, hwndAfter, rect.origin.x, rect.origin.y, rect.size.width, rect.size.height, SWP_SHOWWINDOW);
   
   
//   [hwnd->window() setFrame : rect display : iDisplay];
   
   return 1;
   
}



WINBOOL make_key_and_order_front_nswindow(oswindow hwnd)
{
   
   //   printf("\nmake_key_and_order_front_nswindow");
   
   
//   [[hwnd->window() dd_invokeOnMainThreadAndWaitUntilDone:FALSE] makeKeyAndOrderFront: nil];
   
   return 1;
   
   
}


WINBOOL order_front_nswindow(oswindow hwnd)
{
   //   printf("\norder_front_nswindow");
   
//   [[hwnd->window() dd_invokeOnMainThreadAndWaitUntilDone:FALSE] orderFront: nil];
   
   return 1;
   
   
}


WINBOOL get_nswindow_rect(oswindow oswindow, LPRECT lprect);


//bool oswindow_data::is_window_visible()
//{
//   
//   return 1;
//   
//}


//bool oswindow_data::is_iconic()
//{
//   
////   [window() miniaturize : 0];
//   
//   return 1;
//   
//   
//}


//bool oswindow_data::show_window(i32 nCmdShow)
//{
//
//   if(nCmdShow == SW_HIDE)
//   {
//
//      [m_nswindow setHidden: true];
//      
//   }
//   else
//   {
//   
//  //    [m_nswindow makeKeyAndOrderFront : nil];
//      
//      [m_nswindow setHidden: false];
//      
//   }
//   
//   return 1;
//   
//}


//bool oswindow_data::client_to_screen(POINT *lppoint)
//{
//   RECT rect;
//   get_nswindow_rect(this, &rect);
//   lppoint->x += rect.left;
//   lppoint->y += rect.top;
//   return true;
//}
//
//bool oswindow_data::screen_to_client(POINT *lppoint)
//{
//   RECT rect;
//   get_nswindow_rect(this, &rect);
//   lppoint->x -= rect.left;
//   lppoint->y -= rect.top;
//   return true;
//}



//WINBOOL set_nswindow_frame(oswindow hwnd, LPCRECT lpcrect, int iDisplay)
//{
//   
//   CGRect rect;
//   
//   CGRect frame = [[UIScreen mainScreen] applicationFrame];
//   
//   rect.origin.x     = lpcrect->left;
//   rect.origin.y     = frame.size.height  -     lpcrect->bottom;
//   rect.size.width   = lpcrect->right     -     lpcrect->left;
//   rect.size.height  = lpcrect->bottom    -     lpcrect->top;
//   
//   //   rect.origin.x     = 500;
//   //   rect.origin.y     = 400;
//   //   rect.size.width   = 500;
//   //   rect.size.height  = 500;
//   
//   
//   hwnd->window().frame = rect;
//   
//   return 1;
//   
//}
//
//
//
//WINBOOL move_nswindow(oswindow hwnd, int x, int y)
//{
//   
////   RECT rect;
//   
////   get_nswindow_rect(hwnd, &rect);
//   
//   CGPoint point;
//   
//   point.x = x;
//   point.y = [[UIScreen mainScreen] applicationFrame].size.height - y;
//   
////   [hwnd->window() setFrameTopLeftPoint : point];
//   
//   return 1;
//   
//   
//}




//void * new_ns_pool()
//{
//   
//   NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
//   
//   return pool;
//   
//}
//
//
//void release_pool(void * pool)
//{
//
//   NSAutoreleasePool * ppool =    (NSAutoreleasePool *)pool;
//   [ppool release];
//   
//}




WINBOOL get_nswindow_rect(oswindow oswindow, LPRECT lprect)
{
   
   CGRect rect = [oswindow->window() frame];
   
   lprect->left        = rect.origin.x;
   lprect->bottom      = [[UIScreen mainScreen] applicationFrame ].size.height - rect.origin.y;
   lprect->right       = rect.origin.x  + rect.size.width;
   lprect->top         = lprect->bottom - rect.size.height;
   
   return 1;
   
}







