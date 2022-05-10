//
//  round_window.cpp
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 6/8/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#import "_mm.h"
#import "apex/node/ios/RoundWindowApp.h"


#import "apex/os/apple/DDInvocationGrabber.h"
#import "apex/os/apple/NSObject+DDExtensions.h"


#ifdef APEX_LANGUAGE

#error "APEX_LANGUAGE?!?!?!!!???"

#endif


#ifndef __MM

#error "MM?!?!?!!!???"

#endif

UIWindow * new_round_window(round_window * pwindow, CGRect rect)
{
   
   __block UIWindow * puiwindow = nullptr;
   
   ns_main_sync(^()
   {
      
      RoundWindow * proundwindow = [RoundWindow alloc];
       
      pwindow->m_proundwindow = proundwindow;
       
      pwindow->m_proundwindow->m_pwindow = pwindow;
      
      if([pwindow->m_proundwindow initWithFrame:[[UIScreen mainScreen] bounds]])
      {
      
         puiwindow = proundwindow;
         
      }
      
   });
   
   return puiwindow;

}


void round_window::round_window_show()
{
   
//   [[m_proun dd_invokeOnMainThread] showWindow : m_proundwindow];
   
}


void round_window::round_window_redraw()
{
   
   ns_main_async(^{
      
      [m_proundwindow->m_controller->childContentView setNeedsDisplay];
      
      [m_proundwindow setNeedsDisplay];
      
   });
   
}


void round_window::round_window_redraw_sync()
{
   
   ns_main_async(^{
      
      [m_proundwindow->m_controller->childContentView setNeedsDisplay];

      [m_proundwindow setNeedsDisplay];
      
   });
   
}


void round_window::round_window_invalidate()
{
   
   ns_main_async(^{
      
      [m_proundwindow->m_controller->childContentView setNeedsDisplay];

      [m_proundwindow setNeedsDisplay];
      
   });

}


void round_window::round_window_show_keyboard(bool bShow)
{
   
   ns_main_async(^
   {

      if(bShow)
      {
         
         m_proundwindow->m_pwindow->m_bCanBecomeFirstResponder = true;
    
         [m_proundwindow->m_controller->childContentView becomeFirstResponder];
      
      }
      else
      {
         
         m_proundwindow->m_pwindow->m_bCanBecomeFirstResponder = false;
      
         if(m_proundwindow->m_controller->childContentView.isFirstResponder)
         {
      
            [m_proundwindow->m_controller->childContentView resignFirstResponder];
         
         }
      
      }
      
   });
   
}



//
//  round_window.cpp
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 6/8/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
//#import "macos_mm.h"





void round_window::round_window_set_title(const char * pszTitle)
{
   
   NSString * str = [NSString stringWithUTF8String:pszTitle];
   
   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:FALSE] setTitle: str];

   
}


void round_window::round_window_get_title(char * pszTitle, long iSize)
{
   
   NSString * str = [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:FALSE] title];

   strncpy(pszTitle, [str UTF8String], iSize);
   
}


void round_window::round_window_set_sel(long iBeg, long iEnd)
{
   
   // UITextView --> UIView
//   UITextView * pimpact = m_proundwindow->m_controller->childContentView;
//
//   UITextPosition * beg = [pimpact beginningOfDocument];
//
//   UITextPosition * selbeg = [pimpact endOfDocument];
//
//   UITextPosition * selend = selbeg;
//
//   long iLen = (long) strlen([[pimpact text] UTF8String]);
//
//   if(iBeg >= 0 && iBeg < iLen)
//   {
//
//      selbeg = [pimpact positionFromPosition: beg offset: iBeg];
//
//   }
//
//   if(iEnd >= 0 && iEnd < iLen)
//   {
//
//      selend = [pimpact positionFromPosition: beg offset: iEnd];
//
//   }
//
//   UITextRange * sel = [pimpact textRangeFromPosition: selbeg toPosition: selend];
//
//   [pimpact setSelectedTextRange: sel];
   
}


void round_window::round_window_get_sel(long & iBeg, long & iEnd)
{
   
   // UITextView --> UIView
//   UITextView * pimpact = m_proundwindow->m_controller->childContentView;
//
//   UITextPosition * beg = [pimpact beginningOfDocument];
//
//   UITextPosition * selbeg = [[pimpact selectedTextRange] start];
//
//   UITextPosition * selend = [[pimpact selectedTextRange] start];
//
//   iBeg = [pimpact offsetFromPosition: beg toPosition: selbeg];
//
//   iEnd = [pimpact offsetFromPosition: beg toPosition: selend];
   
}


void round_window::round_window_set_text(const char * pszText)
{
   
   NSString * text = [[NSString alloc] initWithUTF8String:pszText];
   
   // UITextView --> UIView
   //[m_proundwindow->m_controller->childContentView setText: text];
   
}

void round_window::round_window_get_text(char * pszText, long iSize)
{
   
   // UITextView --> UIView
//   strncpy(pszText, [[m_proundwindow->m_controller->childContentView text] UTF8String], iSize);
   
}


long round_window::round_window_get_text_length()
{
   
//   return strlen([[m_proundwindow->m_controller->childContentView text] UTF8String]);
   
   return 0;
   
}


void round_window::round_window_edit_on_set_focus(int l, int t, int r, int b, const char * pszText, long iSelBeg, long iSelEnd)
{
   
   CGRect rect;
   
   rect.origin.x = l;
   rect.origin.y = t;
   rect.size.width = r - l;
   rect.size.height = b - t;
 

   NSString * strText = [ NSString stringWithUTF8String: pszText ];

   [ m_proundwindow->m_controller onEditSetFocus: rect withText: strText withSelBeg: iSelBeg withSelEnd: iSelEnd];
   
}


void round_window::round_window_edit_on_kill_focus()
{
   
   [ m_proundwindow->m_controller onEditKillFocus ];
   
}






void round_window::round_window_destroy()
{
   
   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] close];
   
}


//void round_window::round_window_show()
//{
//   
////   [[m_proundwindow->m_controller dd_invokeOnMainThreadAndWaitUntilDone:TRUE] showWindow : m_proundwindow];
//   
//}


void round_window::round_window_hide()
{
   
//   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] orderOut : m_proundwindow];
   
}

//void round_window::round_window_order_front()
//{
//   
//   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] orderFront : m_proundwindow];
//   
//}
//
//
//void round_window::round_window_make_key_window()
//{
//   
//   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] makeKeyWindow];
//   
//}


//void round_window::round_window_make_key_window_and_order_front()
//{
//   
//   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] makeKeyAndOrderFront: m_proundwindow];
//   
//}
//
//
//void round_window::round_window_make_main_window()
//{
//   
//   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] makeMainWindow];
//   
//}
//
//
//void round_window::round_window_redraw()
//{
//   
//   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] display ];
//   
//}
//
//
//void round_window::round_window_invalidate()
//{
//   
//   //   [[m_proundwindow->m_controller dd_invokeOnMainThread] setViewsNeedDisplay : TRUE];
//   
//}

