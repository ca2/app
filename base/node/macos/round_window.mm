//
//  round_window.cpp
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 6/8/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#import "_mm.h"
#import "RoundWindow.h"


NSWindow * new_round_window(round_window * pwindow, CGRect rect, unsigned int uStyle)
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
   
   pwindow->m_proundwindow = [RoundWindow alloc];
   
   pwindow->m_proundwindow->m_pwindow = pwindow;
   
   //__block RoundWindow * proundwindow;
   
   ns_main_sync(^()
   {
                   
      pwindow->m_proundwindow = [pwindow->m_proundwindow initWithContentRect : rect styleMask : uStyle backing : NSBackingStoreBuffered defer : YES];
                   
   });
   
   return  pwindow->m_proundwindow;
   
}


round_window::round_window()
{
   
   m_bDirty = false;
   
   m_bDestroying = false;
   
}


round_window::~round_window()
{
   
   m_proundwindow = nullptr;
   
}


void round_window::round_window_set_title(const char * pszTitle)
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   char *pszText = strdup(pszTitle);
   
   ns_main_async(^
                 {
   
   NSString * str = [NSString stringWithUTF8String:pszText];
   
   [m_proundwindow setTitle:str];
                    ::free((void *)pszText);
                    
                 });
   
}


void round_window::round_window_get_title(char * pszTitle, int iSize)
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_sync(^
                {
                   
                  NSString * str = [m_proundwindow title];
                  
                  strncpy(pszTitle, [str UTF8String], iSize);
                   
                });
                
   
}


void round_window::round_window_destroy()
{
   
   if(m_proundwindow == NULL)
   {
      
      return;
      
   }
   
   [[NSNotificationCenter defaultCenter] removeObserver: m_proundwindow];

   [m_proundwindow setReleasedWhenClosed: YES];
   
   m_proundwindow->m_pwindow = NULL;
   
   [m_proundwindow close];

}


void round_window::round_window_show()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
   {
      
      [m_proundwindow->m_controller showWindow : m_proundwindow];
      
      [m_proundwindow windowDidExpose];

   });
   
}


void round_window::round_window_hide()
{
   
//   if(m_bDestroying)
//   {
//      
//      return;
//      
//   }

   ns_main_async(^
              {
                 
                 if(m_proundwindow)
                 {
                 
                    [m_proundwindow orderOut : nil];
                    
                 }
                 
                 if(m_proundwindow)
                 {
                    
                    round_window_on_hide();
                    
                 }
                 
              });
   
}


void round_window::round_window_miniaturize()
{
 
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
                 {
                    
                    if([m_proundwindow styleMask] & NSWindowStyleMaskMiniaturizable)
                    {
                    
                       [m_proundwindow performMiniaturize: nil];
                       
                    }
                    else
                    {
                     
                       [m_proundwindow orderOut : nil];
                       
                       round_window_iconified();
                       
                    }
                    
                    if(m_proundwindow->m_pwindow == NULL)
                    {
                       
                       return;
                       
                    }
                    
                    //round_window_on_miniaturize();
                    
                 });
   
}



void round_window::round_window_order_front()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
              {
                 
                 [m_proundwindow orderFront : m_proundwindow];
                 
              });
   
}


void round_window::round_window_make_key_window()
{

   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
              {
                 
                 [m_proundwindow makeKeyWindow];
                 
              });
   
}


void round_window::round_window_make_key_window_and_order_front()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
              {
                 
                 [m_proundwindow makeKeyAndOrderFront: m_proundwindow];
                 
              });
   
}


void round_window::round_window_make_main_window()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
              {
                 
                 [m_proundwindow makeMainWindow];
                 
              });
   
}


void round_window::round_window_redraw()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   auto proundwindow = m_proundwindow;
   
   if(proundwindow)
   {

   ns_main_async(^
                 {
                    
                   // m_bDirty = true;
                    
                    if(proundwindow)
                    {
                    
                       [proundwindow->childContentView setNeedsDisplay:TRUE];
                       
                    }
   
                 });
      
   }
   
}


void round_window::round_window_redraw_sync()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_sync(^
                 {
                    
                    [m_proundwindow display];
                    
                 });
   
}



void round_window::round_window_set_frame(CGRect r)
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
      
      [m_proundwindow setFrame : rect display: TRUE];

   });
   
}


void round_window::round_window_invalidate()
{
  
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
   {
      
      [m_proundwindow setViewsNeedDisplay : TRUE];
      
   });
   
}


bool nsapp_activation_policy_is_regular()
{
   
   if(NSApp.activationPolicy == NSApplicationActivationPolicyRegular)
   {
      
      return true;
      
   }
   
   return false;
   
}


bool nsapp_activation_policy_is_accessory()
{
   
   if(NSApp.activationPolicy == NSApplicationActivationPolicyAccessory)
   {
      
      return true;
      
   }
   
   return false;
   
}


bool nsapp_activation_policy_is_prohibited()
{
   
   if(NSApp.activationPolicy == NSApplicationActivationPolicyProhibited)
   {
      
      return true;
      
   }
   
   return false;
   
}


void nsapp_activation_policy_regular()
{
   
   ns_main_async(^{
   
      [NSApp  setActivationPolicy:NSApplicationActivationPolicyRegular];
   
   });
   
}


void nsapp_activation_policy_accessory()
{
   ns_main_async(^{
      
      [NSApp setActivationPolicy:NSApplicationActivationPolicyAccessory];
       
   });
   
}


void nsapp_activation_policy_prohibited()
{
  
   ns_main_async(^{
   
      [NSApp setActivationPolicy:NSApplicationActivationPolicyProhibited];
   
   });
   
}


void nsapp_activate_ignoring_other_apps(int i)
{
   
   ns_main_async(^{
      
      if(i)
      {
      
         [NSApp activateIgnoringOtherApps: YES];
      
      }
      else
      {
      
         [NSApp activateIgnoringOtherApps: NO];
      
      }
                 
   });
   
}


NSWindow * get_os_window_ns_window(oswindow hwnd)
{
   
   return __nswindow(hwnd);
   
}



