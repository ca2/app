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
#include "apex_macos/keyboard.h"
#import "apex/node/operating_system/winpr_input.h"
#include <Carbon/Carbon.h>
//NSCursor * g_pcurrentNscursor = nullptr;
//#define REDRAW_HINTING
@implementation ns_nano_impact


- (id) initWithFrame: (NSRect) frame andns_nano_window: (ns_nano_window *) pnanowindow
{

   self                 = [super initWithFrame:frame];
   
   //[self setWantsLayer : YES];
   //[self setLayerContentsRedrawPolicy: NSViewLayerContentsRedrawOnSetNeedsDisplay];
   
//   appleKeyboardType    = mac_detect_keyboard_type();
   
   m_pnanowindow        = pnanowindow;
   
   m_bLShift            = false;
   m_bRShift            = false;
   m_bLControl          = false;
   m_bRControl          = false;
   m_bLAlt              = false;
   m_bRAlt              = false;
   m_bLCommand          = false;
   m_bRCommand          = false;
   if (self) {
      trackingArea = [[NSTrackingArea alloc] initWithRect:[self bounds]
                                                  options: (NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved | NSTrackingActiveInKeyWindow )
                                                    owner:self userInfo:nil];
      [self addTrackingArea:trackingArea];
   }
   return self;
   
}


//
// resizeRect
//
// Returns the bounds of the resize box.
//
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
      return;
   
   NSPoint point = [self screenLocationEx: event];
   
   int x = point.x;
   
   int y = point.y;
   
   p->on_mouse_move(x, y);
   
   return;
   
}


- (void) mouseDragged: (NSEvent *) event
{

   nano_window_bridge * p = m_pnanowindow->m_pwindowbridge;
   
   if(p == NULL)
      return;
   
   NSPoint point = [self screenLocationEx: event];
   
   int x = point.x;
   
   int y = point.y;

   p->on_mouse_move(x, y);
   
}


//
// mouseDown:
//
// Handles mouse clicks in our frame. Two actions:
//   - click in the resize box should resize the window
//   - click anywhere else will drag the window.
//

///////////////////////////////
//
//   Left click only
//
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

- (void)drawDebugRect:(NSRect)rect
{
   
   /*
    
    //   [super drawRect:rect];
    
    // return;
    
    BOOL bWindowVisible = [m_pns_nano_window isVisible];
    
    BOOL bViewHidden = [self isHidden];
    
    NSRect e = [m_pns_nano_window frame];
    
    NSRect e2 = [[NSScreen mainScreen] frame];
    
    double a = [m_pns_nano_window alphaValue];
    
    CGContextRef cgc1 = (CGContextRef) [[NSGraphicsContext currentContext] graphicsPort];
    
    COLORREF cr = argb(255, 0, 0, 0);
    
    CGContextSetBlendMode(cgc1, kCGBlendModeCopy);
    
    CGContextSetRGBFillColor(cgc1, argb_get_r_value(cr) / 255.0f, argb_get_g_value(cr) / 255.0f, argb_get_b_value(cr) / 255.0f, argb_get_a_value(cr) / 255.0f);
    
    CGContextFillRect(cgc1, rect);
    
    //   [[NSColor greenColor] set];
    
    //   NSRectFill(rect);
    
    return;
    
    */
   
   /*
    
    [[NSColor clearColor] set];
    
    NSRectFill(rect);
    
    NSBezierPath * rectPath = [NSBezierPath bezierPathWithRect : [self bounds]];
    
    NSGradient * gradient = [[NSGradient alloc] initWithColorsAndLocations : [NSColor whiteColor], (CGFloat) 0.0, [NSColor lightGrayColor], (CGFloat)1.0, nil];
    
    [gradient drawInBezierPath : rectPath angle:90];
    
    [[NSColor whiteColor] set];
    [rectPath stroke];
    
    NSRect resizeRect = [self resizeRect];
    NSBezierPath *resizePath = [NSBezierPath bezierPathWithRect:resizeRect];
    
    [[NSColor lightGrayColor] set];
    [resizePath fill];
    
    [[NSColor darkGrayColor] set];
    [resizePath stroke];
    
    
    [[NSColor blackColor] set];
    NSString *windowTitle = [[self window] title];
    NSRect titleRect = [self bounds];
    titleRect.origin.y = titleRect.size.height - (WINDOW_FRAME_PADDING - 7);
    titleRect.size.height = (WINDOW_FRAME_PADDING - 7);
    NSMutableParagraphStyle *paragraphStyle =
    [[NSMutableParagraphStyle alloc] init];
    [paragraphStyle setAlignment:NSCenterTextAlignment];
    [windowTitle
    drawWithRect:titleRect
    options:0
    attributes:[NSDictionary
    dictionaryWithObjectsAndKeys:
            paragraphStyle, NSParagraphStyleAttributeName,
            [NSFont systemFontOfSize:14], NSFontAttributeName,
    nil]];
    
    
    return; */

}

//- (void) updateLayer
//{
//
//
//}


//
// drawRect:
//
// Draws the frame of the window.
//

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

//printf("\nacceptsFirstMouse\n");
   
   if(![NSApp isActive])
   {
      
      //[NSApp ];
      
   }
   
   if(![m_pnanowindow isKeyWindow])
   {
      
      [m_pnanowindow makeKeyWindow];
      
   }
   
//   if(![m_pns_nano_window isMainWindow])
//   {
//
//      [m_pns_nano_window makeMainWindow];
//
//   }
//
//   if([[NSApp orderedWindows] firstObject] != m_pns_nano_window)
//   {
//
//      [m_pns_nano_window orderFront:self];
//
//   }

   return YES;
   
}


- (BOOL) mouseDownCanMoveWindow
{

   return NO;

}

//
//// from RoundWindow.mm
//
///*- (BOOL) acceptsFirstResponder
//{
//   if(m_bNoActivate)
//      return NO;
//   else
//      return YES;
//}*/
//
//- (BOOL) becomeFirstResponder
//{
//   return YES;
//}
////   if(m_bNoActivate)
//  //    return NO;
//  // else
//  // {
//
//      //      m_pns_nano_window->macos_window_on_become_first_responder();
//
//    //  return YES;
//
//  // }
////}
//
////- (BOOL) resignFirstResponder
////{
////   return YES;
////   //if(m_bNoActivate)
////     // return YES;
////   //else
////  //    return YES;
////
////}
//

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
   
   //unichar keyChar;
   
   keyCode = [event keyCode];
   
   
//   char sz[1024];
//   char szFormat[1024];
//
//   strcpy(sz, "");
//   ansi_concatenate(sz, "\n");
//   ansi_concatenate(sz, "\n");
//   ansi_concatenate(sz, "-----------------------------------------------------------------------------\n");
//   sprintf(szFormat, "RoundWindowFrameView::keyDown : %s\n", [characters UTF8String]);
//   ansi_concatenate(sz, szFormat);
//   ansi_concatenate(sz, "-----------------------------------------------------------------------------\n");
//   ansi_concatenate(sz, "\n");
//   ansi_concatenate(sz, "\n");
//
//   printf("%s", sz);
   
//   if ([characters length] > 0)
//   {
//
//      keyChar = [characters characterAtIndex:0];
//
//      keyCode = fixKeyCode(keyCode, keyChar, appleKeyboardType);
//
//   }
   
   //vkcode = GetVirtualKeyCodeFromKeycode(keyCode + 8, KEYCODE_TYPE_APPLE);
   
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

   //int iUni = utf8_to_uc32(pszUtf8);
   
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
   
   //unichar keyChar;
   
   NSString * characters;
   
   nano_window_bridge * p = m_pnanowindow->m_pwindowbridge;
   
   if(p == NULL)
   {
      
      return;
      
   }
   
   keyCode = [event keyCode];
   
   characters = [event charactersIgnoringModifiers];
   
//   char sz[1024];
//   char szFormat[1024];
//
//   strcpy(sz, "");
//   ansi_concatenate(sz, "\n");
//   ansi_concatenate(sz, "\n");
//   ansi_concatenate(sz, "-----------------------------------------------------------------------------\n");
//   sprintf(szFormat, "RoundWindowFrameView::keyUp : %s\n", [characters UTF8String]);
//   ansi_concatenate(sz, szFormat);
//   ansi_concatenate(sz, "-----------------------------------------------------------------------------\n");
//   ansi_concatenate(sz, "\n");
//   ansi_concatenate(sz, "\n");
//
//   printf("%s", sz);
   
//   if ([characters length] > 0)
//   {
//
//      keyChar = [characters characterAtIndex:0];
//
//      keyCode = fixKeyCode(keyCode, keyChar, appleKeyboardType);
//
//   }
   
   //vkcode = GetVirtualKeyCodeFromKeycode(keyCode + 8, KEYCODE_TYPE_APPLE);
   
   vkcode = keyCode;
      
   scancode = GetVirtualScanCodeFromVirtualKeyCode(vkcode, 4);

   keyFlags |= (scancode & KBDEXT) ? KBDEXT : 0;
   
   //bool bRet = p->macos_window_key_up(vkcode, scancode);
   
   //p->macos_window_key_up(vkcode, scancode);

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
   
//   const char * pszUtf8 = nullptr;
//
//   if(event.characters && event.characters.length > 0)
//   {
//
//      pszUtf8 = [[event characters] UTF8String];
//
//   }

//   if ((modFlags & NSAlphaShiftKeyMask) && !(kbdModFlags & NSAlphaShiftKeyMask))
//      p->macos_window_key_down(vkcode, scancode, nullptr);
//   else if (!(modFlags & NSAlphaShiftKeyMask) && (kbdModFlags & NSAlphaShiftKeyMask))
//      p->macos_window_key_up(vkcode, scancode);
//   
//   if ((modFlags & NSShiftKeyMask) && !(kbdModFlags & NSShiftKeyMask))
//      p->macos_window_key_down(kVK_Shift, scancode, nullptr);
//   else if (!(modFlags & NSShiftKeyMask) && (kbdModFlags & NSShiftKeyMask))
//      p->macos_window_key_up(kVK_Shift, scancode);
//   
//   if ((modFlags & NSControlKeyMask) && !(kbdModFlags & NSControlKeyMask))
//      p->macos_window_key_down(kVK_Control, scancode, nullptr);
//   else if (!(modFlags & NSControlKeyMask) && (kbdModFlags & NSControlKeyMask))
//      p->macos_window_key_up(kVK_Control, scancode);
//   
//   if ((modFlags & NSAlternateKeyMask) && !(kbdModFlags & NSAlternateKeyMask))
//      p->macos_window_key_down(kVK_Option, scancode, nullptr);
//   else if (!(modFlags & NSAlternateKeyMask) && (kbdModFlags & NSAlternateKeyMask))
//      p->macos_window_key_up(kVK_Option, scancode);
//   
//   if ((modFlags & NSCommandKeyMask) && !(kbdModFlags & NSCommandKeyMask))
//      p->macos_window_key_down(kVK_Command, scancode, nullptr);
//   else if (!(modFlags & NSCommandKeyMask) && (kbdModFlags & NSCommandKeyMask))
//      p->macos_window_key_up(kVK_Command, scancode);
//   
//   if ((modFlags & NSNumericPadKeyMask) && !(kbdModFlags & NSNumericPadKeyMask))
//      p->macos_window_key_down(vkcode, scancode, nullptr);
//   else if (!(modFlags & NSNumericPadKeyMask) && (kbdModFlags & NSNumericPadKeyMask))
//      p->macos_window_key_up(vkcode, scancode);
//   
//   if ((modFlags & NSHelpKeyMask) && !(kbdModFlags & NSHelpKeyMask))
//      p->macos_window_key_down(vkcode, scancode, nullptr);
//   else if (!(modFlags & NSHelpKeyMask) && (kbdModFlags & NSHelpKeyMask))
//      p->macos_window_key_up(vkcode, scancode);
   
   kbdModFlags = modFlags;

   // [super flagsChanged:event];
   
}

- (void)viewWillMoveToWindow:(NSWindow *)newWindow {
   NSTrackingArea *const trackingArea = [[NSTrackingArea alloc] initWithRect:NSZeroRect options:(NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved | NSTrackingActiveAlways | NSTrackingInVisibleRect) owner:self userInfo:nil];
   [self addTrackingArea:trackingArea];
   [self.window invalidateCursorRectsForView:self];
}

//- (void)resetCursorRects {
//   [super resetCursorRects];
//   [self addCursorRect:self.bounds cursor:(__bridge NSCursor*)m_pnanowindow->m_pwindowbridge->macos_window_get_mouse_cursor()];
//}

- (void)mouseEntered:(NSEvent *)theEvent {
   [super mouseEntered:theEvent];
   //[g_pcurrentNscursor push];
}

- (void)mouseExited:(NSEvent *)theEvent {
   [super mouseExited:theEvent];
   //[g_pcurrentNscursor pop];
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



