//
//  nsview.m
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 02/02/22.
//  09:10
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
//
//  RoundWindowFrameView.m
//  RoundWindow
//
//  Created by Matt Gallagher on 12/12/08.
//  Copyright 2008 Matt Gallagher. All rights reserved.
//
//  Permission is given to use this source code file without charge in any
//  project, commercial or otherwise, entirely at your risk, with the condition
//  that any redistribution (in part or whole) of source code must retain
//  this copyright and permission notice. Attribution in compiled projects is
//  appreciated but not required.
//
#include "framework.h"
#include "window_bridge.h"
#include "nswindow.h"
#include "nsimpact.h"
#include "acme/operating_system/macos/keyboard.h"
#include "acme/operating_system/winpr_input.h"
#include <Carbon/Carbon.h>


@implementation ns_nano_impact


- (id) initWithFrame: (NSRect) frame andns_nano_window: (ns_nano_window *) pnanowindow
{

   self                 = [super initWithFrame:frame];
   
   
   m_pnanowindow        = pnanowindow;
   
   m_bLShift            = false;
   m_bRShift            = false;
   m_bLControl          = false;
   m_bRControl          = false;
   m_bLAlt              = false;
   m_bRAlt              = false;
   m_bLCommand          = false;
   m_bRCommand          = false;
   
   if (self)
   {
      
      trackingArea = [[NSTrackingArea alloc] initWithRect:[self bounds]
                                                  options: (NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved | NSTrackingActiveInKeyWindow )
                                                    owner:self userInfo:nil];
      [self addTrackingArea:trackingArea];
      
   }
   
   return self;
   
}


- (NSRect) resizeRect
{
   
   const CGFloat resizeBoxSize = 16.0;
   
   const CGFloat contentViewPadding = 5.5;
   
   NSRect contentViewRect = [[self window] contentRectForFrameRect:[[self window] frame]];
   
   NSRect resizeRect = NSMakeRect(
      NSMaxX(contentViewRect) + contentViewPadding,
      NSMinY(contentViewRect) - resizeBoxSize - contentViewPadding,
      resizeBoxSize,
      resizeBoxSize);
   
   return resizeRect;
   
}


- (NSPoint) screenLocationEx: (NSEvent *) event
{
   
   NSPoint point = [event locationInWindow];
   
   if([event window] != nil)
   {
      
      CGRect rectWindow = [[event window] frame];
      
      point.x += rectWindow.origin.x;
      
      point.y += rectWindow.origin.y;
      
   }
   
   point.y = (int) [[NSScreen mainScreen] frame].size.height - point.y;

   return point;
   
}

- (void) mouseUp: (NSEvent *) event
{

   nano_window_bridge * p = m_pnanowindow->m_pwindowbridge;
   
   if(p == NULL)
   {
      
      return;
      
   }
    
   NSPoint point = [self screenLocationEx: event];
   
   int x = point.x;
   
   int y = point.y;
 
   p->on_left_button_up(x, y);
   
}


- (void) mouseMoved: (NSEvent *) event
{

   nano_window_bridge * p = m_pnanowindow->m_pwindowbridge;
   
   if(p == NULL)
   {
      
      return;
      
   }
   
   NSPoint point = [ self screenLocationEx: event ];
   
   int x = point.x;
   
   int y = point.y;
   
   p->on_mouse_move(x, y);
   
   return;
   
}


- (void) mouseDragged: (NSEvent *) event
{

   nano_window_bridge * p = m_pnanowindow->m_pwindowbridge;
   
   if(p == NULL)
   {

      return;
      
   }
   
   NSPoint point = [self screenLocationEx: event];
   
   int x = point.x;
   
   int y = point.y;

   p->on_mouse_move(x, y);
   
}


- (void) mouseDown: (NSEvent *) event
{
   
   nano_window_bridge * p = m_pnanowindow->m_pwindowbridge;
   
   if(p == NULL)
   {
      
      return;
      
   }
   
   NSPoint point = [self screenLocationEx: event];
   
   int x = point.x;
   
   int y = point.y;

   p->on_left_button_down(x, y);
   
}



- (BOOL) isFlipped
{
   
   return YES;
   
}


- (BOOL) isOpaque
{
   
   return NO;
   
}



#define WINDOW_FRAME_PADDING 32

#define REDRAW_HINTING
#undef REDRAW_HINTING

- (void) drawRect: (NSRect) rect
{

   nano_window_bridge * p = m_pnanowindow->m_pwindowbridge;
   
   if(p == NULL)
   {
      
      return;
      
   }
   
   CGContextRef cgc = (CGContextRef) [[NSGraphicsContext currentContext] graphicsPort];

#ifdef REDRAW_HINTING
   
   {
      
      CGContextSetBlendMode(cgc, kCGBlendModeCopy);
      
      CGContextSetRGBFillColor(cgc, 255 / 255.0f, 200 / 255.0f, 0 / 255.0f, 155 / 255.0f);
      
      auto rectArtifact1 = rect;
      
      rectArtifact1.size.width /= 4;
      
      rectArtifact1.size.height /= 4;
      
      CGContextFillRect(cgc, rectArtifact1);
      
   }
   
#endif
   
   auto rectFrame = [self frame];
   
   p->_on_draw_frame(cgc, rectFrame.size);
   
#ifdef REDRAW_HINTING
   
   {
   
      CGContextSetBlendMode(cgc, kCGBlendModeCopy);

      CGContextSetRGBFillColor(cgc, 255 / 255.0f, 255 / 255.0f, 255 / 255.0f, 155 / 255.0f);
      
      auto rectArtifact2 = rect;
      
      rectArtifact2.size.width /= 4;
      
      rectArtifact2.size.height /= 4;
      
      rectArtifact2.origin.x = rect.size.width - rectArtifact2.size.width;
      
      rectArtifact2.origin.y = rect.size.height - rectArtifact2.size.height;

      CGContextFillRect(cgc, rectArtifact2);
      
   }
   
#endif
   
}


- (BOOL)acceptsFirstResponder
{

   return TRUE;

}


- (BOOL) acceptsFirstMouse:(NSEvent *)theEvent
{
   
   if(![NSApp isActive])
   {
      
   }
   
   if(![m_pnanowindow isKeyWindow])
   {
      
      [m_pnanowindow makeKeyWindow];
      
   }
   
   return YES;
   
}


- (BOOL) mouseDownCanMoveWindow
{

   return NO;

}

#define DO_FLAG(m_f, p, now, key) \
if(m_f) \
{ \
if(!now) \
{ \
p->macos_window_key_up(key); \
m_f = false; \
} \
} \
else \
{ \
if(now) \
{ \
p->macos_window_key_down(key); \
m_f = true; \
} \
}


- (void)keyDown:(NSEvent *)event
{

   nano_window_bridge * p = m_pnanowindow->m_pwindowbridge;
     
   if(p == NULL)
   {
      
      return;
      
   }
   
   if(event.isARepeat)
   {
      
      return;
      
   }
   
   DWORD keyCode;
   
   DWORD keyFlags = 0;
   
   DWORD vkcode;
   
   DWORD scancode;
   
   keyCode = [event keyCode];
   
   vkcode = keyCode;
      
   scancode = GetVirtualScanCodeFromVirtualKeyCode(vkcode, 4);

   keyFlags |= (scancode & KBDEXT) ? KBDEXT : 0;
   
   char * pszUtf8 = nullptr;
   
   if(!apple_is_action_key(keyCode) && !(kbdModFlags &(NSControlKeyMask | NSCommandKeyMask|NSAlternateKeyMask)))
   {
   
      if([[event characters] length ] > 0)
      {
      
         pszUtf8 = strdup([[event characters] UTF8String]);
      
      }
      else if(keyCode == kVK_Space)
      {
       
         pszUtf8=strdup(" ");
         
      }
      
   }
   else if(keyCode == kVK_Tab)
   {
    
      pszUtf8 = strdup("\t");
      
   }
   else if(keyCode == kVK_Return)
   {
    
      pszUtf8 = strdup("\r");
      
   }
   
   if(pszUtf8)
   {

      int iUni = *pszUtf8;
      
      p->on_char(iUni);
      
      free(pszUtf8);
      
   }
   
}


- (void)keyUp:(NSEvent *)event
{
   
   DWORD keyCode;
   
   DWORD keyFlags = 0;
   
   DWORD vkcode;
   
   DWORD scancode;
   
   NSString * characters;
   
   nano_window_bridge * p = m_pnanowindow->m_pwindowbridge;
   
   if(p == NULL)
   {
      
      return;
      
   }
   
   keyCode = [event keyCode];
   
   characters = [event charactersIgnoringModifiers];

   vkcode = keyCode;

   scancode = GetVirtualScanCodeFromVirtualKeyCode(vkcode, 4);

   keyFlags |= (scancode & KBDEXT) ? KBDEXT : 0;
   
}


- (void)flagsChanged:(NSEvent *)event
{

   nano_window_bridge * p = m_pnanowindow->m_pwindowbridge;
   
   if(p == NULL)
   {
      
      printf("flags_changed(0)\n");
      
      [super flagsChanged:event];
      
      return;
      
   }
   
   int key;
   
   DWORD keyFlags = 0;
   
   DWORD vkcode;
   
   DWORD scancode;
   
   DWORD modFlags;
   
   key = [event keyCode] + 8;
   
   modFlags = [event modifierFlags] & NSDeviceIndependentModifierFlagsMask;
   
   vkcode = GetVirtualKeyCodeFromKeycode(key, KEYCODE_TYPE_APPLE);
   
   scancode = GetVirtualScanCodeFromVirtualKeyCode(vkcode, 4);
   
   keyFlags |= (scancode & KBDEXT) ? KBDEXT : 0;
   
   scancode &= 0xFF;
   
   vkcode &= 0xFF;
   
#if 0
   
   if (modFlags & NSAlphaShiftKeyMask)
      printf("NSAlphaShiftKeyMask");
   
   if (modFlags & NSShiftKeyMask)
      printf("NSShiftKeyMask");
   
   if (modFlags & NSControlKeyMask)
      printf("NSControlKeyMask");
   
   if (modFlags & NSAlternateKeyMask)
      printf("NSAlternateKeyMask");
   
   if (modFlags & NSCommandKeyMask)
      printf("NSCommandKeyMask");
   
   if (modFlags & NSNumericPadKeyMask)
      printf("NSNumericPadKeyMask");
   
   if (modFlags & NSHelpKeyMask)
      printf("NSHelpKeyMask");
   
#endif
   
   kbdModFlags = modFlags;

}


- (void)viewWillMoveToWindow:(NSWindow *)newWindow
{
   
   NSTrackingArea *const trackingArea = [[NSTrackingArea alloc] initWithRect:NSZeroRect options:(NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved | NSTrackingActiveAlways | NSTrackingInVisibleRect) owner:self userInfo:nil];
   
   [self addTrackingArea:trackingArea];
   
   [self.window invalidateCursorRectsForView:self];
   
}


- (void)mouseEntered:(NSEvent *)theEvent
{

   [super mouseEntered:theEvent];

}


- (void)mouseExited:(NSEvent *)theEvent
{

   [super mouseExited:theEvent];

}


@end


unsigned int event_num_pad_key_code(NSEvent * event)
{

   NSString * arrow = [event charactersIgnoringModifiers];
   
   if([arrow length] == 1)
   {
      
      unichar key = [arrow characterAtIndex:0];
      
      if(key == NSLeftArrowFunctionKey)
      {
         
         return VK_LEFT; //::user::key_left;
         
      }
      else if(key == NSRightArrowFunctionKey)
      {
         
         return VK_RIGHT; //::user::key_right;
         
      }
      else if(key == NSUpArrowFunctionKey)
      {
         
         return VK_UP; // ::user::key_up;
         
      }
      else if(key == NSDownArrowFunctionKey)
      {
         
         return VK_DOWN; // ::user::key_down;
         
      }
      else if(key >= L'0' && key <= L'9')
      {
         
         //return 3000 + key - L'0';
         
         return 0;
         
      }
      
   }
   
   return 0;

}


unsigned int event_key_code(NSEvent * event)
{

   unsigned int uiModifierFlags = (unsigned int) [event modifierFlags];

   if(uiModifierFlags & NSNumericPadKeyMask)
   {

      return event_num_pad_key_code(event);
   
   }
   
   unsigned int uiKeyCode = [event keyCode];
 
   return uiKeyCode;
   
}



