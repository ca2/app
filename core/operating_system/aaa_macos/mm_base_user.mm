//
//  macos_user.mm
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//
#import "_mm.h"


int_bool get_nswindow_rect(oswindow oswindow, LPRECT lprect);
void copy(LPRECT lprectDst, const CGRect & rectSrc);




int_bool move_nswindow(oswindow hwnd, int x, int y);


int_bool set_nswindow_frame(oswindow hwnd, LPCRECT lpcrect, int iDisplay)
{
   
   RECT r(*lpcrect);
   
   ns_main_async(^
              {
      
                 NSRect rect;
                 
                 NSRect rectScreen = [[[NSScreen screens] objectAtIndex:0] frame];
                 
                 rect.origin.x     = r.left;
                 rect.origin.y     = rectScreen.size.height    -     r.bottom;
                 rect.size.width   = r.right                   -     r.left;
                 rect.size.height  = r.bottom                  -     r.top;
                 
                 [__nswindow(hwnd)  setFrame : rect display : iDisplay];
                 
                 
      
              });
   
   return 1;
   
}


int_bool move_nswindow(oswindow hwnd, int x, int y)
{
   
   ns_main_async(^
              {
                        
                 NSPoint point;
                 
                 NSRect rectScreen = [[[NSScreen screens] objectAtIndex:0] frame];
                 
                 point.x = x;
                 
                 point.y = rectScreen.size.height - y;
                 
                 [__nswindow(hwnd)  setFrameTopLeftPoint : point];
      
              });
   
   return 1;
   
}


int_bool make_key_and_order_front_nswindow(oswindow hwnd)
{

//   printf("\nmake_key_and_order_front_nswindow");

   ns_main_async(^
   {
                        
      [__nswindow(hwnd)  makeKeyAndOrderFront: nil];
      
   });
   
   return 1;
   
}


int_bool order_front_nswindow(oswindow hwnd)
{

   //   printf("\norder_front_nswindow");
   
   ns_main_async(^
              {
                        
                 [__nswindow(hwnd)  orderFrontRegardless];
                 
              });
   
   return 1;
   
}


int_bool nswindow_set_level_main_menu(oswindow hwnd)
{
   
   ns_main_async(^
                 {
                    
                    [__nswindow(hwnd)  setLevel: NSMainMenuWindowLevel];
                    
                 });
   
   return 1;
   
}


int_bool nswindow_set_level_floating(oswindow hwnd)
{
   
   ns_main_async(^
                 {
                    
                    [__nswindow(hwnd)  setLevel: NSFloatingWindowLevel];
                    
                 });
   
   return 1;
   
}


int_bool nswindow_set_level_normal(oswindow hwnd)
{
   
   ns_main_async(^
                 {
                    
                    if([__nswindow(hwnd)  level] !=NSNormalWindowLevel)
                    {
                    
                    [__nswindow(hwnd)  setLevel: NSNormalWindowLevel];
                       
                    }
                    
                 });
   
   return 1;
   
}


int_bool nswindow_is_level_main_menu(oswindow hwnd)
{
   
   return __nswindow(hwnd) .level == NSMainMenuWindowLevel;
   
}


int_bool nswindow_is_level_floating(oswindow hwnd)
{
   
   return __nswindow(hwnd) .level == NSFloatingWindowLevel;
   
}


int_bool nswindow_is_level_normal(oswindow hwnd)
{
   
   return __nswindow(hwnd) .level == NSNormalWindowLevel;
   
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


//void ns_redraw_window(oswindow w)
//{
//   
//   [[w->window() dd_invokeOnMainThreadAndWaitUntilDone:TRUE] display];
//   
//}


int_bool get_nswindow_rect(oswindow oswindow, LPRECT lprect)
{
   
   NSRect rect = [__nswindow(oswindow) frame];
   
   lprect->left        = rect.origin.x;
   lprect->bottom      = [[NSScreen mainScreen] frame ].size.height - rect.origin.y;
   lprect->right       = rect.origin.x  + rect.size.width;
   lprect->top         = lprect->bottom - rect.size.height;
   
   return 1;
   
}


int cx100;
int cy100;

int_bool SetWindowPos(oswindow hwnd, oswindow hwndInsertAfter, int x, int y, int cx, int cy, UINT uFlags)
{
   
   ns_main_async([=]()
              {
   
   if(cx100 != cx || cy100 != cy)
   {
      
      cx100 = cx;
      
      cy100 = cy;
      
      // xxxlog NSLog(@"different window rect size (2)");
      
   }
   
   bool  bMove = !(uFlags & SWP_NOMOVE);

   bool  bSize = !(uFlags & SWP_NOSIZE);
   
   if(bMove && bSize)
   {
      
      RECT rect;
      
      rect.left      = x;
      rect.top       = y;
      rect.right     = rect.left + cx;
      rect.bottom    = rect.top + cy;
      
      set_nswindow_frame(hwnd, &rect, (uFlags & SWP_SHOWWINDOW) != 0);
      
   }
   else if(bSize)
   {
      
      RECT rect;
      
      window_rectangle(hwnd, &rect);
      
      rect.right     = rect.left + cx;
      rect.bottom    = rect.top + cy;
      
      set_nswindow_frame(hwnd, &rect, (uFlags & SWP_SHOWWINDOW) != 0);
      
   }
   else if(bMove)
   {
      
      move_nswindow(hwnd, x, y);
      
   }
   
   if(!(uFlags & SWP_NOZORDER))
   {
      
      if(hwndInsertAfter == HWND_TOPMOST)
      {
         
         if(nswindow_is_level_floating(hwnd))
         {
            
            order_front_nswindow(hwnd);
            
         }
         else
         {
         
            nswindow_set_level_floating(hwnd);
            
         }
         
      }
      else if(hwndInsertAfter == HWND_TOP)
      {
         
         nswindow_set_level_normal(hwnd);
         
         order_front_nswindow(hwnd);
         
      }
      
   }
      
   });
   
   return 1;
   
}

void ns_main_async(dispatch_block_t block);

bool macos_set_user_wallpaper(int iScreen, const char * psz)
{
   
   NSString * str = [NSString stringWithUTF8String: psz];
   

   
   ns_main_async(^
                 {

   NSArray<NSScreen *> * screenArray = [NSScreen screens];
   
   unsigned long screenCount = [screenArray count];
   
   if(iScreen < 0 || iScreen >= screenCount)
   {
      
      return;
      
   }

   NSString * path = str;
   
   NSURL * url = [NSURL fileURLWithPath: path];
   
/*   NSDictionary * options = [NSDictionary dictionaryWithObjectsAndKeys:nil, NSWorkspaceDesktopImageFillColorKey, [NSNumber numberWithBool:NO], NSWorkspaceDesktopImageAllowClippingKey, [NSNumber numberWithInteger:NSImageScaleProportionallyUpOrDown], NSWorkspaceDesktopImageScalingKey, nil]; */
   NSDictionary * options = [NSDictionary dictionaryWithObjectsAndKeys:
      [NSColor colorWithCalibratedRed:0.51 green:0.49 blue:0.89 alpha:1.0], NSWorkspaceDesktopImageFillColorKey,
                             [NSNumber numberWithBool:YES], NSWorkspaceDesktopImageAllowClippingKey, [NSNumber numberWithInteger:NSImageScaleProportionallyUpOrDown], NSWorkspaceDesktopImageScalingKey, nil];
   
   NSError * error;
   
   bool bOk = true;
   
      NSScreen * screen = [screenArray objectAtIndex: iScreen];
      
      NSURL * u = [[NSWorkspace sharedWorkspace] desktopImageURLForScreen: screen];
      
      error = NULL;
      
      [[[NSWorkspace sharedWorkspace] dd_invokeOnMainThreadAndWaitUntilDone:FALSE ] setDesktopImageURL:url forScreen: screen options:options error:&error];
      
      if(error != NULL)
      {
         
         bOk = false;
         
      }
                    
                 });

   return true;
   
}


long long mm_get_user_wallpaper(long long llScreen, char ** ppsz);


long long mm_get_user_wallpaper(long long llScreen, char ** ppsz)
{
   
   mmos * p = [mmos get];
   
   [p->theLock lock];
   
   long long llCount = p->m_llWallpaper;

   if(llScreen < 0 || llScreen >= llCount || p->m_ppszWallpaper == NULL)
   {

      (*ppsz) = NULL;

   }
   else
   {
   
      (*ppsz) = strdup(p->m_ppszWallpaper[llScreen]);

   }
   
   [p->theLock unlock];
   
   return llCount;
                         
   
}





