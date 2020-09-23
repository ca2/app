//
//  apex_window.cpp
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 6/8/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#import "_mm.h"
#import "ApexWindow.h"


NSWindow * new_apex_window(apex_window * papexwindow, CGRect rect, unsigned int uStyle)
{
   
   // rect.origin.x        = 0;
   
   rect.origin.y           = (int) [[NSScreen mainScreen]frame].size.height - (rect.origin.y + rect.size.height);
   
   // rect.size.width      = 0;
   // rect.size.height     = 0;
   
/* 
 
   rect.origin.x           = 100;
   rect.origin.y           = 100;
   rect.size.width         = 800;
   rect.size.height        = 500;
 
*/
   
   papexwindow->m_papexwindow = [ApexWindow alloc];
   
   papexwindow->m_papexwindow->m_papexwindow = papexwindow;
   
   //__block RoundWindow * proundwindow;
   
   ns_main_sync(^()
   {
                   
      [papexwindow->m_papexwindow initWithContentRect : rect styleMask : uStyle backing : NSBackingStoreBuffered defer : YES];
                   
   });
   
   return  papexwindow->m_papexwindow;
   
}


apex_window::apex_window()
{
   
   m_bDirty = false;
   
   m_bDestroying = false;
   
}


apex_window::~apex_window()
{
   
   m_papexwindow = nullptr;
   
}


void apex_window::round_window_set_title(const char * pszTitle)
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   char *pszText = strdup(pszTitle);
   
   ns_main_async(^
                 {
   
   NSString * str = [NSString stringWithUTF8String:pszText];
   
   [m_papexwindow setTitle:str];
                    ::free((void *)pszText);
                    
                 });
   
}


void apex_window::round_window_get_title(char * pszTitle, int iSize)
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_sync(^
                {
                   
                  NSString * str = [m_papexwindow title];
                  
                  strncpy(pszTitle, [str UTF8String], iSize);
                   
                });
                
   
}


void apex_window::round_window_destroy()
{
   
   if(m_papexwindow == NULL)
   {
      
      return;
      
   }
   
   [[NSNotificationCenter defaultCenter] removeObserver: m_papexwindow];

   [m_papexwindow setReleasedWhenClosed: YES];
   
   m_papexwindow->m_papexwindow = NULL;
   
   [m_papexwindow close];

}


void apex_window::round_window_show()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
   {
      
      [m_papexwindow->m_pwindowcontroller showWindow : m_papexwindow];
      
      [m_papexwindow windowDidExpose];

   });
   
}


void apex_window::round_window_hide()
{
   
//   if(m_bDestroying)
//   {
//      
//      return;
//      
//   }

   ns_main_async(^
              {
                 
                 if(m_papexwindow)
                 {
                 
                    [m_papexwindow orderOut : nil];
                    
                 }
                 
                 if(m_papexwindow)
                 {
                    
                    round_window_on_hide();
                    
                 }
                 
              });
   
}


void apex_window::round_window_miniaturize()
{
 
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
                 {
                    
                    if([m_papexwindow styleMask] & NSWindowStyleMaskMiniaturizable)
                    {
                    
                       [m_papexwindow performMiniaturize: nil];
                       
                    }
                    else
                    {
                     
                       [m_papexwindow orderOut : nil];
                       
                       round_window_iconified();
                       
                    }
                    
                    if(m_papexwindow->m_papexwindow == NULL)
                    {
                       
                       return;
                       
                    }
                    
                    //round_window_on_miniaturize();
                    
                 });
   
}



void apex_window::round_window_order_front()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
              {
                 
                 [m_papexwindow orderFront : m_papexwindow];
                 
              });
   
}


void apex_window::round_window_make_key_window()
{

   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
              {
                 
                 [m_papexwindow makeKeyWindow];
                 
              });
   
}


void apex_window::round_window_make_key_window_and_order_front()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
              {
                 
                 [m_papexwindow makeKeyAndOrderFront: m_papexwindow];
                 
              });
   
}


void apex_window::round_window_make_main_window()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
              {
                 
                 [m_papexwindow makeMainWindow];
                 
              });
   
}


void apex_window::round_window_redraw()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   auto proundwindow = m_papexwindow;
   
   if(proundwindow)
   {

   ns_main_async(^
                 {
                    
                   // m_bDirty = true;
                    
                    if(proundwindow)
                    {
                    
                       [proundwindow->m_pviewChildContent setNeedsDisplay:TRUE];
                       
                    }
   
                 });
      
   }
   
}


void apex_window::round_window_redraw_sync()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_sync(^
                 {
                    
                    [m_papexwindow display];
                    
                 });
   
}



void apex_window::round_window_set_frame(CGRect r)
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
   {
      
      NSRect rect;
      
      NSRect rectScreen = [[[NSScreen screens] objectAtIndex:0] frame];
      
      rect.origin.x     = r.origin.x;
      rect.origin.y     = rectScreen.size.height    -     r.origin.y - r.size.height;
      rect.size   = r.size;
      
      [m_papexwindow setFrame : rect display: TRUE];

   });
   
}


void apex_window::round_window_invalidate()
{
  
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
   {
      
      [m_papexwindow setViewsNeedDisplay : TRUE];
      
   });
   
}


//NSWindow * get_os_window_ns_window(oswindow hwnd)
//{
//   
//   return __nswindow(hwnd);
//   
//}



