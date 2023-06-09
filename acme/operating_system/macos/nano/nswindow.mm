//
//  nswindow.m
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 01/02/22.
//  23:25
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include <Foundation/Foundation.h>
#include <AppKit/AppKit.h>
#include <Carbon/Carbon.h>
#include "nswindow.h"
#include "window_bridge.h"
#include "nsimpact.h"
#include "app.h"

bool ns_app_is_running();
void ns_main_async(dispatch_block_t block);

void ns_main_sync(dispatch_block_t block);

 
@implementation ns_nano_window : NSWindow


// rectangle.origin.x = left of rectangle
// rectangle.origin.y = bottom of rectangle
// origin of screen is at the bottom of screen
// top of rectangle is bigger numerically than the bottom
// and grows bigger from bottom as farther from bottom of screen.


-(instancetype) init: (NSRect) rectangle
{
   
   self = [ super
      initWithContentRect : rectangle
      styleMask : 0
      backing : NSBackingStoreBuffered
      defer : YES ];
   
   if(!self)
   {
      
      return nil;
      
   }
   
   [ self setOpaque : NO ];
   
   [ self setBackgroundColor: [ NSColor clearColor ] ];
      
   [ self setReleasedWhenClosed : NO ];
   
   [ self setAcceptsMouseMovedEvents : YES ];
   
   [ self setLevel : NSNormalWindowLevel ];
   
   [ self setIgnoresMouseEvents : NO ];
   
   macos_app * papp = (macos_app *) [ [ NSApplication sharedApplication ] delegate ];
   
   m_pwindowcontroller = [ papp addWindow: self ];

   [ [ NSNotificationCenter defaultCenter ] addObserver: self selector: @selector(windowDidMove:) name: NSWindowDidMoveNotification object: self];

   [ [ NSNotificationCenter defaultCenter ] addObserver: self selector: @selector(windowDidResize:) name: NSWindowDidResizeNotification object: self];

   [ self create_impact ];
   
   return self;
   
}


- (void)windowDidMove:(NSNotification *)notification
{
   
   NSRect rectFrame = [ self frame ];
   
   int x = rectFrame.origin.x;
   
   int y = (int) [[NSScreen mainScreen] frame].size.height - rectFrame.origin.y - rectFrame.size.height;
   
   int w = rectFrame.size.width;
   
   int h = rectFrame.size.height;
   
   m_pwindowbridge->on_layout(x, y, w, h);
   
}



- (void)windowDidResize:(NSNotification *)notification
{
   
   NSRect rectFrame = [ self frame ];
   
   int x = rectFrame.origin.x;
   
   int y = (int) [[NSScreen mainScreen] frame].size.height - rectFrame.origin.y - rectFrame.size.height;
   
   int w = rectFrame.size.width;
   
   int h = rectFrame.size.height;
   
   m_pwindowbridge->on_layout(x, y, w, h);
   
}


- (BOOL) canBecomeKeyWindow
{
   
   return YES;
   
}


- (BOOL) canBecomeMainWindow
{
   
   return YES;
   
}


- (BOOL) acceptsFirstResponder
{
   
   return YES;
   
}


- (BOOL) becomeFirstResponder
{
   
   return YES;
   
}


- (BOOL) resignFirstResponder
{
   
   return YES;
   
}


- (void)create_impact
{

   NSRect bounds = [ self frame ];
   
   bounds.origin = NSZeroPoint;

   ns_nano_impact * pimpact = [ [ ns_nano_impact alloc ] initWithFrame: bounds andns_nano_window: self ];
   
   m_pimpactChild = pimpact;
   
   [ super setContentView: pimpact ];
   
   [ pimpact setFrame: bounds ];
   
   [ pimpact setAutoresizingMask: 0 ];
   
}


@end
 

nano_window_bridge::nano_window_bridge()
{
   
   m_bRunningAppMainLoop = false;
   m_pnsnanowindow = nullptr;
   
}


nano_window_bridge::~nano_window_bridge()
{
   
     
}


void nano_window_bridge::create_ns_nano_window(CGRect cgrect)
{
   
   ns_main_sync(^()
   {
   
      m_pnsnanowindow = (__bridge_retained CFTypeRef) [ [ ns_nano_window alloc ] init: cgrect ];
   
      auto pnsnanowindow = (__bridge ns_nano_window *) m_pnsnanowindow;
   
      pnsnanowindow->m_pwindowbridge = this;
      
   });
   
}


void nano_window_bridge::display()
{
   
   ns_main_async(^()
   {
      
      auto pnanowindow =  (__bridge ns_nano_window *) m_pnsnanowindow;
      
      id appName = [ [ NSProcessInfo processInfo ] processName ];

      if (![ NSApp mainMenu ])
      {
         
         [ NSApplication sharedApplication ];
         
         [ NSApp setActivationPolicy:NSApplicationActivationPolicyRegular ];

         id menubar = [ NSMenu new ];
         id appMenuItem = [ NSMenuItem new ];
         [ menubar addItem : appMenuItem ];
         
         id appMenu = [ NSMenu new ] ;
         id quitTitle = [ @"Quit " stringByAppendingString : appName];
         id quitMenuItem = [ [ NSMenuItem alloc ] initWithTitle : quitTitle action: @selector(terminate:) keyEquivalent: @"q" ];
         [ appMenu addItem : quitMenuItem ];
         [ appMenuItem setSubmenu : appMenu ];
         
         [ NSApp setMainMenu : menubar ];
         
      }
      
      [ pnanowindow setTitle : appName];
      
      if(_is_top_most())
      {
         
         [ pnanowindow setLevel: NSPopUpMenuWindowLevel ];
         
      }
      else if(_is_popup_window())
      {
         
         [ pnanowindow setLevel: NSModalPanelWindowLevel ];
         
      }

      [ pnanowindow display];
      [ pnanowindow makeKeyAndOrderFront : nil ];
      [ pnanowindow makeFirstResponder : nil ];
      [ NSApp activateIgnoringOtherApps : YES ];
      //[ [ pnanowindow windowController ] showWindow:nil ];
      //[ NSApp runModalForWindow : pnanowindow ];
   
   });
   
   
}


void nano_window_bridge::redraw()
{
   
   auto pnanowindow =  (__bridge ns_nano_window *) m_pnsnanowindow;

   [ pnanowindow->m_pimpactChild setNeedsDisplay:YES];
   
}


void nano_window_bridge::stop()
{
   
   auto pnanowindow =  (__bridge ns_nano_window *) m_pnsnanowindow;

   if(!ns_app_is_running())
   {
      
      if(m_bRunningAppMainLoop)
      {
         
         [ NSApp stop : nil ];
         
         m_bRunningAppMainLoop = false;
         
      }
      
   }
//)
   
   //[NSApp stopModal];
   
   [ pnanowindow close ];
   
}


void nano_window_bridge::move_to(int x, int y)
{
   
   auto pnanowindow =  (__bridge ns_nano_window *) m_pnsnanowindow;
   
   NSPoint point;
   
   point.x = x;
   
   point.y = y;
   
   NSRect frame = [ pnanowindow frame ];
   
   int w = frame.size.width;
   
   int h = frame.size.height;
   
   point.y = (int) [[NSScreen mainScreen] frame].size.height - point.y - h;

   [ pnanowindow setFrameOrigin:point ];
   
}


bool apple_is_action_key(int i)
{
   
   if(i==kVK_Return       ) return true;
   if(i==kVK_Tab          ) return true;
   //if(i==kVK_Space      ) return true;
   if(i==kVK_Delete       ) return true;
   if(i==kVK_Escape       ) return true;
   if(i==kVK_Command      ) return true;
   if(i==kVK_Shift        ) return true;
   if(i==kVK_CapsLock     ) return true;
   if(i==kVK_Option       ) return true;
   if(i==kVK_Control      ) return true;
   if(i==kVK_RightShift   ) return true;
   if(i==kVK_RightOption  ) return true;
   if(i==kVK_RightControl ) return true;
   if(i==kVK_Function     ) return true;
   if(i==kVK_F17          ) return true;
   if(i==kVK_VolumeUp     ) return true;
   if(i==kVK_VolumeDown   ) return true;
   if(i==kVK_Mute         ) return true;
   if(i==kVK_F18          ) return true;
   if(i==kVK_F19          ) return true;
   if(i==kVK_F20          ) return true;
   if(i==kVK_F5           ) return true;
   if(i==kVK_F6           ) return true;
   if(i==kVK_F7           ) return true;
   if(i==kVK_F3           ) return true;
   if(i==kVK_F8           ) return true;
   if(i==kVK_F9           ) return true;
   if(i==kVK_F11          ) return true;
   if(i==kVK_F13          ) return true;
   if(i==kVK_F16          ) return true;
   if(i==kVK_F14          ) return true;
   if(i==kVK_F10          ) return true;
   if(i==kVK_F12          ) return true;
   if(i==kVK_F15          ) return true;
   if(i==kVK_Help         ) return true;
   if(i==kVK_Home         ) return true;
   if(i==kVK_PageUp       ) return true;
   if(i==kVK_ForwardDelete) return true;
   if(i==kVK_F4           ) return true;
   if(i==kVK_End          ) return true;
   if(i==kVK_F2           ) return true;
   if(i==kVK_PageDown     ) return true;
   if(i==kVK_F1           ) return true;
   if(i==kVK_LeftArrow    ) return true;
   if(i==kVK_RightArrow   ) return true;
   if(i==kVK_DownArrow    ) return true;
   if(i==kVK_UpArrow      ) return true;

   return false;
   
}


void ns_screen_copy(CGRect & rect, const ::RECTANGLE_I32 & rectangle)
{
   
   NSScreen * pscreenMain = [ NSScreen mainScreen ];
   
   NSRect nsrectFrame = [ pscreenMain frame];
   
   rect.origin.x = rectangle.left;
   
   rect.origin.y = nsrectFrame.size.height - rectangle.bottom;
   
   rect.size.width = rectangle.right - rectangle.left;
   
   rect.size.height = rectangle.bottom - rectangle.top;
   
}


void ns_screen_copy(::RECTANGLE_I32 & rectangle, CGRect & rect)
{
   
   NSScreen * pscreenMain = [ NSScreen mainScreen ];
   
   NSRect nsrectFrame = [ pscreenMain frame];
   
   rectangle.left = rect.origin.x;
   
   rectangle.bottom = nsrectFrame.size.height - rect.origin.y;
   
   rectangle.right = rectangle.left + rect.size.width;
   
   rectangle.top = rectangle.bottom - rect.size.height;
   
}



void nano_window_bridge::_run_modal_loop()
{
   m_bRunningAppMainLoop = true;
//[ NSApp run ];
   
   if(!ns_app_is_running())
   {
      [ NSApp runModalForWindow : (__bridge ns_nano_window *)m_pnsnanowindow ];
      
   }
      
}
