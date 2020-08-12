//
//  macos_user.mm
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//
#include "app/aura/_policy/aura_c.h"

WINBOOL get_nswindow_rect(oswindow oswindow, LPRECT lprect);


//bool oswindow_data::is_window_visible()
//{
//   
//   return 1;
//   
//}
//
//
//bool oswindow_data::is_iconic()
//{
//   
////   [window() miniaturize : 0];
//   
//   return 1;
//   
//   
//}
//
//
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
//
//
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
//
//

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
//
//
//
//
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
//
//
//
//
//void ns_redraw_window(oswindow w)
//{
//   
////   [w->window() display];
//   
//}
//
//
//WINBOOL get_nswindow_rect(oswindow oswindow, LPRECT lprect)
//{
//   
//   CGRect rect = [oswindow->window() frame];
//   
//   lprect->left        = rect.origin.x;
//   lprect->bottom      = [[UIScreen mainScreen] applicationFrame ].size.height - rect.origin.y;
//   lprect->right       = rect.origin.x  + rect.size.width;
//   lprect->top         = lprect->bottom - rect.size.height;
//   
//   return 1;
//   
//}
//
//


// https://stackoverflow.com/questions/6167557/get-string-from-nspasteboard
//you need to use the following method with stringForType with key NSPasteboardTypeString to read the string value from clipboard.
char * mm_clipboard_get_plain_text()
{
   
   UIPasteboard *pasteboard = [UIPasteboard generalPasteboard];

   NSString * strPasteboard = pasteboard.string;

   return ns_string(strPasteboard);
   
}

//https://stackoverflow.com/questions/3655038/how-to-copy-textfield-to-osx-clipboard
//On OSX
void mm_clipboard_set_plain_text(const char * psz)
{
   
   UIPasteboard * pasteboard = [UIPasteboard generalPasteboard];
   
   NSString * strPasteboard = [NSString stringWithUTF8String: psz];
   
   pasteboard.string = strPasteboard;
   
}


