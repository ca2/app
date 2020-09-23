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
   
	self = [super initWithContentRect:contentRect styleMask:windowStyle                        backing:bufferingType defer:deferCreation];

	if(self == NULL)
   {
      
      return NULL;
      
   }
      
//	[self setOpaque:NO];
//   
//   [self setBackgroundColor:[NSColor clearColor]];
//		
//   [self setReleasedWhenClosed: NO];
//   
//   [self setAcceptsMouseMovedEvents : YES];
//   
//   // Thank yous: http://ios.phonesdevelopers.com/195_17967545/
//   // Thank you: Author: unitom Date: 2013-07-14
//   // I have a fullscreen transparent window.
//   // When the user clicks on it I want the click to be sent to what's
//   // underneath the window. How would I do so?
//   // Best Answer
//   
//   // Setting IgnoresMouseEvents to YES should do the trick..
//      
//   // (void)setIgnoresMouseEvents:(BOOL)ignoreMouseEvents
//
//   [self setIgnoresMouseEvents : NO];
//   
//   //m_pwindowcontroller = [[NSWindowController alloc] initWithWindow: self];
//
//   [self create_view];
//   
//   m_paurawindow->round_window_add_ref();
   
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


@end






WINBOOL EnableWindow(oswindow hwnd, WINBOOL bEnable)
{
   
   if(hwnd == NULL)
      return FALSE;
   
   
   
   return TRUE;
   
}
