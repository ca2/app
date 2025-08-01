//
//  macos_MessageBoxA.cpp
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 13/09/14.
//  from http://blog.jorgearimany.com/2010/05/messagebox-from-windows-to-mac.html
//  El blog de Jorge Arimany Espanhaque

#include "framework.h"


int _os_message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox)
{

   //convert the strings from char* to CFStringRef
   CFStringRef title_ref   = CFStringCreateWithCString(kCFAllocatorDefault, pszTitle, kCFStringEncodingUTF8);
   CFStringRef message_ref  = CFStringCreateWithCString(kCFAllocatorDefault, pszMessage, kCFStringEncodingUTF8);

   CFOptionFlags result;  //result code from the message box

   unsigned int uiType = (int) emessagebox & MB_TYPEMASK;

   string strButton1;
   string strButton2;
   string strButton3;

   switch(uiType)
   {
   case MB_OKCANCEL:
      strButton1 = "OK";
      strButton2 = "Cancel";
      break;
   case MB_ABORTRETRYIGNORE:
      strButton1 = "Abort";
      strButton2 = "Retry";
      strButton3 = "Ignore";
      break;
   case MB_YESNOCANCEL:
      strButton1 = "Yes";
      strButton2 = "No";
      strButton3 = "Cancel";
      break;
   case MB_YESNO:
      strButton1 = "Yes";
      strButton2 = "No";
      break;
   case MB_RETRYCANCEL:
      strButton1 = "Retry";
      strButton2 = "Cancel";
      break;
   case MB_CANCELTRYCONTINUE:
      strButton1 = "Cancel";
      strButton2 = "Try";
      strButton3 = "Continue";
      break;
   default:
      strButton1 = "OK";
      break;
   }

   CFStringRef button1_ref = nullptr;
   CFStringRef button2_ref = nullptr;
   CFStringRef button3_ref = nullptr;

   if(strButton1.has_character() || strButton1.case_insensitive_order("ok") != 0)
      button1_ref = CFStringCreateWithCString(kCFAllocatorDefault, strButton1, kCFStringEncodingUTF8);
   if(strButton2.has_character())
      button2_ref = CFStringCreateWithCString(kCFAllocatorDefault, strButton2, kCFStringEncodingUTF8);
   if(strButton3.has_character())
      button3_ref = CFStringCreateWithCString(kCFAllocatorDefault, strButton3, kCFStringEncodingUTF8);


   //launch the message box
   CFUserNotificationDisplayAlert(
   0, // no timeout
   kCFUserNotificationNoteAlertLevel, //change it depending message_type flags ( MB_ICONASTERISK.... etc.)
   nullptr, //icon url, use default, you can change it depending message_type flags
   nullptr, //not used
   nullptr, //localization of strings
   title_ref, //header text
   message_ref, //message text
   button1_ref, //default "ok" text in button
   button2_ref, //alternate button title
   button3_ref, //other button title, null--> no other button
   &result //response flags
   );

   if(button1_ref != nullptr)
      CFRelease(button1_ref);
   if(button2_ref != nullptr)
      CFRelease(button1_ref);
   if(button3_ref != nullptr)
      CFRelease(button1_ref);

   //Clean up the strings
   if(title_ref)
   {

      CFRelease(title_ref);

   }

   if(message_ref != nullptr)
   {

      CFRelease( message_ref );

   }


   switch(uiType)
   {
   case MB_OKCANCEL:
      if( result == kCFUserNotificationDefaultResponse)
         return e_dialog_result_ok;
      else if( result == kCFUserNotificationAlternateResponse)
         return e_dialog_result_cancel;
      break;
   case MB_ABORTRETRYIGNORE:
      if( result == kCFUserNotificationDefaultResponse)
         return IDABORT;
      else if(result == kCFUserNotificationAlternateResponse)
         return IDRETRY;
      else if(result == kCFUserNotificationOtherResponse)
         return IDIGNORE;
      break;
   case MB_YESNOCANCEL:
      if( result == kCFUserNotificationDefaultResponse)
         return e_dialog_result_yes;
      else if(result == kCFUserNotificationAlternateResponse)
         return e_dialog_result_no;
      else if(result == kCFUserNotificationOtherResponse)
         return e_dialog_result_cancel;
      break;
   case MB_YESNO:
      if( result == kCFUserNotificationDefaultResponse)
         return e_dialog_result_yes;
      else if(result == kCFUserNotificationAlternateResponse)
         return e_dialog_result_no;
      break;
   case MB_RETRYCANCEL:
      if( result == kCFUserNotificationDefaultResponse)
         return IDRETRY;
      else if(result == kCFUserNotificationAlternateResponse)
         return e_dialog_result_cancel;
      break;
   case MB_CANCELTRYCONTINUE:
      if( result == kCFUserNotificationDefaultResponse)
         return e_dialog_result_cancel;
      else if(result == kCFUserNotificationAlternateResponse)
         return IDTRYAGAIN;
      else if(result == kCFUserNotificationOtherResponse)
         return IDCONTINUE;
      break;
   default:
      if( result == kCFUserNotificationDefaultResponse)
         return e_dialog_result_ok;
      break;
   }


   return e_dialog_result_cancel;


}


CLASS_DECL_APEX string message_box_result_to_string(int iResult);


void message_box_synchronous(oswindow window, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, ::future future)
{
   
   
   int iResult = _os_message_box(scopedstrMessage, pszTitle, emessagebox);
   
   string strResult = message_box_result_to_string(iResult);

   future.send(strResult);
   
   return ::success;
   
}
