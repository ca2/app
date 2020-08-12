//
//  c_os_cross_win_user.cpp
//  c
//
//  Created by Snow Leopard User on 06/11/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "framework.h"



#ifdef _DEBUG
#undef _DEBUG
#define _DEBUG 1
#else
#define _DEBUG 0
#endif

#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>

#if _DEBUG
#undef _DEBUG
#define _DEBUG
#else
#undef _DEBUG
#endif


/*

WINBOOL set_window_pos(oswindow hwnd, oswindow hwndInsertAfter, int x, int y, int cx, int cy, UINT uFlags)
{
   
//   int   value_mask = 0;
   bool  bMove = !(uFlags & SWP_NOMOVE);
   bool  bSize = !(uFlags & SWP_NOSIZE);
   
   if(bMove && bSize)
   {
      
      RECT rect;
      
      rect.left      = x;
      rect.top       = y;
      rect.right     = rect.left + cx;
      rect.bottom    = rect.top + cy;
      
      set_nswindow_frame(hwnd, &rect, (uFlags & SWP_SHOWWINDOW));
      
   }
   else if(bSize) // bSize only
   {
      
      RECT rect;
      
      get_window_rect(hwnd, &rect);

      rect.right     = rect.left + cx;
      rect.bottom    = rect.top + cy;
      
      set_nswindow_frame(hwnd, &rect, (uFlags & SWP_SHOWWINDOW));
      
   }
   else if(bMove) // bMove only
   {
      
      move_nswindow(hwnd, x, y);
      
   }
   
    if(!(uFlags & SWP_NOZORDER))
    {
       
       iptr iInsertAfter = (iptr) hwndInsertAfter;
       
       if(iInsertAfter == zorder_top || iInsertAfter == ZORDER_TOPMOST)
       {
          
          order_front_nswindow(hwnd);
          
       }
       
    }
*/
   
   /*   if(!(uFlags & SWP_NOZORDER) && hwndInsertAfter >= 0)
    {
    value_mask |= CWSibling;
    values.sibling = hwndInsertAfter;
    values.stack_mode = Above;
    }
    
    XConfigureWindow(display, hwnd, value_mask, &values);
    
    if(uFlags & SWP_SHOWWINDOW)
    {
    XMapWindow(display, hwnd);
    }
    
    if(!(uFlags & SWP_NOZORDER) && hwndInsertAfter < 0)
    {
    if(hwndInsertAfter == zorder_top || hwndInsertAfter == ZORDER_TOPMOST)
    {
    XRaiseWindow(display, hwnd);
    }
    else if(hwndInsertAfter == ZORDER_BOTTOM)
    {
    XLowerWindow(display, hwnd);
    }
    
    }
    
    XCloseDisplay(display);*/
   
//   return 1;
   
//}

//int MessageBoxANative(oswindow hwnd, const char * message, const char * header, unsigned int message_type );
/*

class set_boot_native_message_box
{
public:
   
   set_boot_native_message_box()
   {

      g_messageboxa = &MessageBoxANative;
      
   }
   
} g_set_boot_native_message_box;

int MessageBoxANative(oswindow hwnd, const char * message, const char * header, unsigned int message_type )
{
   
   //convert the strings from char* to CFStringRef
   CFStringRef  header_ref  = CFStringCreateWithCString(nullptr,  header, kCFStringEncodingUTF8);
   CFStringRef message_ref  = CFStringCreateWithCString(nullptr, message, kCFStringEncodingUTF8);
   
   CFOptionFlags result;  //result code from the message box
   
   CFStringRef button1;
   CFStringRef button2;
   CFStringRef button3 = nullptr;
   CFStringRef buttonSwap;
   
   CFOptionFlags flags = 0;
   
   if((message_type & MB_ICONQUESTION) == MB_ICONQUESTION)
   {
      flags |= kCFUserNotificationStopAlertLevel;
   }
   else if((message_type & MB_ICONEXCLAMATION) == MB_ICONEXCLAMATION)
   {
      flags |= kCFUserNotificationCautionAlertLevel;
   }
   else if((message_type & MB_ICONASTERISK) == MB_ICONASTERISK)
   {
      flags |= kCFUserNotificationNoteAlertLevel;
   }
   else
   {
      flags |= kCFUserNotificationPlainAlertLevel;
   }
   
   if((message_type & MB_YESNOCANCEL) == MB_YESNOCANCEL)
   {
      button1 = CFStringCreateWithCString(nullptr,     "Yes", kCFStringEncodingUTF8);
      button2 = CFStringCreateWithCString(nullptr,      "No", kCFStringEncodingUTF8);
      button3 = CFStringCreateWithCString(nullptr,  "Cancel", kCFStringEncodingUTF8);
   }
   else if((message_type & MB_YESNO) == MB_YESNO)
   {
      button1 = CFStringCreateWithCString(nullptr,     "Yes", kCFStringEncodingUTF8);
      button2 = CFStringCreateWithCString(nullptr,      "No", kCFStringEncodingUTF8);

   }
   else if((message_type & MB_YESNO) == MB_OKCANCEL)
   {
      button1 = CFStringCreateWithCString(nullptr,      "OK", kCFStringEncodingUTF8);
      button2 = CFStringCreateWithCString(nullptr,      "Cancel", kCFStringEncodingUTF8);
      
   }
   else
   {
      button1 = nullptr;
      button2 = nullptr;
      button3 = nullptr;
   }
   
   if((message_type & MB_DEFBUTTON1) == MB_DEFBUTTON1)
   {
   }
   else if((message_type & MB_DEFBUTTON2) == MB_DEFBUTTON2)
   {
      buttonSwap     = button1;
      button1        = button2;
      button2        = buttonSwap;
   }
   else if((message_type & MB_DEFBUTTON3) == MB_DEFBUTTON3)
   {
      buttonSwap     = button1;
      button1        = button3;
      button3        = buttonSwap;
   }
   else
   {
      flags |= kCFUserNotificationNoDefaultButtonFlag;
   }
   
   //launch the message box
   CFUserNotificationDisplayAlert(
                                  0, // no timeout
                                  flags, //change it depending message_type flags ( MB_ICONASTERISK.... etc.)
                                  nullptr, //icon url, use default, you can change it depending message_type flags
                                  nullptr, //not used
                                  nullptr, //localization of strings
                                  header_ref, //header text 
                                  message_ref, //message text
                                  button1, //default "ok" text in button
                                  button2, //alternate button title
                                  button3, //other button title, nullptr--> no other button
                                  &result //response flags
                                  );
   
   //Clean up the strings
   CFRelease(header_ref    );
   CFRelease(message_ref   );
   if(button1 != nullptr)
      CFRelease(button1);
   if(button2 != nullptr)
      CFRelease(button2);
   if(button3 != nullptr)
      CFRelease(button3);
                
    int iButton = 0;

    if((message_type & MB_DEFBUTTON2) == MB_DEFBUTTON2)
    {
       if(result == kCFUserNotificationDefaultResponse)
       {
          iButton = 2;
       }
       else if(result == kCFUserNotificationAlternateResponse)
       {
          iButton = 1;
       }
       else if(result == kCFUserNotificationOtherResponse)
       {
          iButton = 3;
       }
    }
    else if((message_type & MB_DEFBUTTON3) == MB_DEFBUTTON3)
    {
       if(result == kCFUserNotificationDefaultResponse)
       {
          iButton = 3;
       }
       else if(result == kCFUserNotificationAlternateResponse)
       {
          iButton = 1;
       }
       else if(result == kCFUserNotificationOtherResponse)
       {
          iButton = 2;
       }
    }
    else
    {
       if(result == kCFUserNotificationDefaultResponse)
       {
          iButton = 1;
       }
       else if(result == kCFUserNotificationAlternateResponse)
       {
          iButton = 2;
       }
       else if(result == kCFUserNotificationOtherResponse)
       {
          iButton = 3;
       }
   }
   
   //Convert the result
   if((message_type & MB_YESNOCANCEL) == MB_YESNOCANCEL)
   {
      if(iButton == 1)
         return IDYES;
      else if(iButton == 2)
         return IDNO;
      else
         return IDCANCEL;
   }
   else if((message_type & MB_YESNO) == MB_YESNO)
   {
      if(iButton == 1)
         return IDYES;
      else
         return IDNO;
   }
   else if((message_type & MB_OKCANCEL) == MB_OKCANCEL)
   {
      if(iButton == 1)
         return IDOK;
      else
         return IDCANCEL;
   }
   else
   {
      return MB_OK;
   }
   
}
*/

WINBOOL set_need_redraw(oswindow hWnd, CONST RECT *lprcUpdate, HRGN hrgnUpdate, UINT flags)
{
   
   return TRUE;
   
}




const char * mm_keyboard_input_source();

string keyboard_input_source()
{
   __block const char * psz = nullptr;
   
   ns_main_sync(^()
                {
   psz = mm_keyboard_input_source();
                }
                );
string str =psz;
free((void *) psz);
return str;
}
