//
//  AuraWindow.m
//  AuraWindow
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
#import "_mm.h"

int session_accepts_first_responder();

NSWindow * get_os_window_ns_window(oswindow hwnd);

CGWindowID get_os_window_window_number(oswindow oswindow)
{

      if(oswindow == NULL)
      {

return 0;

      }


      NSWindow * window = get_os_window_ns_window(oswindow);

      if(window == NULL)
      {

return 0;

      }

      return (CGWindowID)[window windowNumber];
}



@implementation AuraWindow


//
// initWithContentRect:styleMask:backing:defer:screen:
//
// Init method for the object.
//
- (id)initWithContentRect: (NSRect) contentRect styleMask: (NSUInteger) windowStyle backing:(NSBackingStoreType) bufferingType defer: (BOOL) deferCreation
{
   
   m_bNoActivate = false;
   
	self = [super initWithContentRect:contentRect styleMask:windowStyle
           
                             // | NSWindowStyleMaskMiniaturizable
           
                             backing:bufferingType defer:deferCreation];

	if(self == NULL)
      return NULL;
   

   
	[self setOpaque:NO];
   
   //	[self setOpaque:YES];

   [self setBackgroundColor:[NSColor clearColor]];
		
   //	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(mainWindowChanged:) name:NSWindowDidBecomeMainNotification object:self];
		
   //	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(mainWindowChanged:) name:NSWindowDidResignMainNotification object:self];
   
   [self setReleasedWhenClosed: NO];
   
   
   [self setAcceptsMouseMovedEvents : YES];
   
   // Thank yous: http://ios.phonesdevelopers.com/195_17967545/
   // Thank you: Author: unitom Date: 2013-07-14
   // I have a fullscreen transparent window.
   // When the user clicks on it I want the click to be sent to what's
   // underneath the window. How would I do so?
   // Best Answer
   
   // Setting IgnoresMouseEvents to YES should do the trick..
      
   // (void)setIgnoresMouseEvents:(BOOL)ignoreMouseEvents

   [self setIgnoresMouseEvents : NO];
   
   m_pwindowcontroller = [[NSWindowController alloc] initWithWindow: self];

   [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(windowDidBecomeKey:) name: NSWindowDidBecomeKeyNotification object: self];

   [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(windowDidResignKey:) name: NSWindowDidResignKeyNotification object: self];

   [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(windowDidBecomeMain:) name: NSWindowDidBecomeMainNotification object: self];
   
   [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(windowDidResignMain:) name: NSWindowDidResignMainNotification object: self];

   [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(windowDidResize:) name: NSWindowDidResizeNotification object: self];
   
   [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector (windowDidMove:) name: NSWindowDidMoveNotification object: self];

   [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(windowWillClose:) name: NSWindowWillCloseNotification object: self];

   [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(windowDidExpose:) name: NSWindowDidExposeNotification object: self];

   [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(windowDidMiniaturize:) name: NSWindowDidMiniaturizeNotification object: self];

   [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(windowDidDeminiaturize:) name: NSWindowDidDeminiaturizeNotification object: self];
   
   [self create_view];
   
   m_paurawindow->round_window_add_ref();
   
   return self;
   
}


- (void)dealloc
{
   
   auto pwindow = m_paurawindow;
   
   m_paurawindow = NULL;

   pwindow->round_window_dec_ref();
   
}

- (void)performMiniaturize:(id)sender
{
   
   //[self miniaturize: self];
   [self miniaturize:self];
   
}



//
// setContentSize:
//
// Convert from childContentView to frameView for size.
//
- (void)setContentSize:(NSSize)newSize
{
	
	[super setContentSize:newSize];
   
}


//
// mainWindowChanged:
//
// Redraw the close button when the main window status changes.
//
- (void)windowDidBecomeKey:(NSNotification *)aNotification
{

   printf("windowDidBecomeKey\n");

   m_paurawindow->round_window_did_become_key();
   
}

- (void)windowDidResignKey:(NSNotification *)aNotification
{
   
   printf("windowDidResignKey\n");
   
   //m_paurawindow->round_window_deactivate();
   
}


- (void)windowDidBecomeMain:(NSNotification *)aNotification
{
   
   printf("windowDidBecomeMain\n");
   
   m_paurawindow->round_window_activate();
   
}

- (void)windowDidResignMain:(NSNotification *)aNotification
{
   
   printf("windowDidResignMain\n");
   
   m_paurawindow->round_window_deactivate();
   
}

//
// setContentView:
//
// Keep our frame view as the content view and make the specified "aView"
// the child of that.
//
- (void)create_view
{

	NSRect bounds = [self frame];
	
   bounds.origin = NSZeroPoint;

	AuraWindowFrameView * pframeview = [[AuraWindowFrameView alloc] initWithFrame: bounds andAuraWindow: self];
   
   m_pviewChildContent = pframeview;
   
	[super setContentView: pframeview];
   
	[pframeview setFrame: bounds];
   
	[pframeview setAutoresizingMask: 0];
   
}


//
// contentView
//
// Returns the child of our frame view instead of our frame view.
//
- (NSView *) contentView
{
   
	return [super contentView];
   
}


//
// canBecomeKeyWindow
//
// Overrides the default to allow a borderless window to be the key window.
//
- (BOOL) canBecomeKeyWindow
{
   
   return session_accepts_first_responder();
   
}


//
// canBecomeMainWindow
//
// Overrides the default to allow a borderless window to be the main window.
//
- (BOOL) canBecomeMainWindow
{

   return session_accepts_first_responder();

}


#define WINDOW_FRAME_PADDING 0


//
// contentRectForFrameRect:
//
// Returns the rect for the content rect, taking the frame.
//
- (NSRect) contentRectForFrameRect: (NSRect) windowFrame
{

   windowFrame.origin = NSZeroPoint;
   
	return NSInsetRect(windowFrame, WINDOW_FRAME_PADDING, WINDOW_FRAME_PADDING);
   
}


//
// frameRectForContentRect:styleMask:
//
// Ensure that the window is make the appropriate amount bigger than the content.
//
+ (NSRect) frameRectForContentRect: (NSRect) windowContentRect styleMask: (NSUInteger)windowStyle
{
	
   return NSInsetRect(windowContentRect, -WINDOW_FRAME_PADDING, -WINDOW_FRAME_PADDING);
   
}


- (void)windowDidMove: (NSNotification *) notification
{
   
   
   if([self isMiniaturized])
   {
      
      return;
      
   }
   try
   {
      
      NSRect rect = [self frame];
      
      CGPoint point;
      
      point.x = rect.origin.x;
      
      point.y = [[NSScreen mainScreen] frame].size.height - (rect.origin.y + rect.size.height);
      
      m_paurawindow->round_window_moved(point);
      
   }
   catch (...)
   {
      
   }
   
}


- (void) windowDidResize: (NSNotification *) notification
{

   if([self isMiniaturized])
   {
      
      return;
      
   }
   
   try
   {
      
      NSRect rect = [self frame];
      
      rect.origin.y = [[NSScreen mainScreen] frame].size.height - (rect.origin.y + rect.size.height);
      
      m_paurawindow->round_window_resized(rect);
      
   }
   catch (...)
   {
      
   }

}


- (void) windowDidMiniaturize: (NSNotification *) notification
{
   
   try
   {
      
      m_paurawindow->round_window_iconified();
      
   }
   catch (...)
   {
      
   }
   
}


- (void) windowDidDeminiaturize: (NSNotification *) notification
{
   
   try
   {
      
      m_paurawindow->round_window_deiconified();
      
   }
   catch (...)
   {
      
   }
   
}


-(void)windowDidExpose
{
   
   try
   {
      
      if(m_paurawindow == NULL)
      {
         
         return;
         
      }
      
      m_paurawindow->round_window_on_show();

   }
   catch (...)
   {

   }
   
}


-(void)windowWillClose
{
   
   try
   {
      
      m_paurawindow->round_window_on_hide();

   }
   catch (...)
   {

   }
   
}


@end






WINBOOL EnableWindow(oswindow hwnd, WINBOOL bEnable)
{
   
   if(hwnd == NULL)
      return FALSE;
   
   
   
   return TRUE;
   
}
