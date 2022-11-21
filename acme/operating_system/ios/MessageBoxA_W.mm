//
//  MessageBoxA_W.m
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 09/07/15.
//
//
#include "framework.h"
//#include "acme/primitive/primitive/function.h"

int ui_MessageBoxA(const char * pszMessageParam, const char * pszHeaderParam, unsigned int uType, const char * pszDetails, ::function < void (enum_dialog_result) > function)
{
   
   NSString * strMessage = [NSString stringWithUTF8String:pszMessageParam];

   NSString * strHeader = [NSString stringWithUTF8String:pszHeaderParam];
   
   
   const char * strButton1 = NULL;
   const char * strButton2 = NULL;
   const char * strButton3 = NULL;
   
   switch(uType)
   {
      case e_message_box_ok_cancel:
         strButton1 = "OK";
         strButton2 = "Cancel";
         break;
      case e_message_box_abort_retry_ignore:
         strButton1 = "Abort";
         strButton2 = "Retry";
         strButton3 = "Ignore";
         break;
      case e_message_box_yes_no_cancel:
         strButton1 = "Yes";
         strButton2 = "No";
         strButton3 = "Cancel";
         break;
      case e_message_box_yes_no:
         strButton1 = "Yes";
         strButton2 = "No";
         break;
      case e_message_box_retry_cancel:
         strButton1 = "Retry";
         strButton2 = "Cancel";
         break;
      case e_message_box_cancel_try_continue:
         strButton1 = "Cancel";
         strButton2 = "Try";
         strButton3 = "Continue";
         break;
      default:
         strButton1 = "OK";
         break;
   }

   NSString * str1 = NULL;
   NSString * str2 = NULL;
   NSString * str3 = NULL;
   
   if(strButton1 != NULL)
   {
      
      str1 = [NSString stringWithUTF8String:strButton1];
      
   }
   
   if(strButton2 != NULL)
   {
      
      str2 = [NSString stringWithUTF8String:strButton2];
      
   }
   
   if(strButton3 != NULL)
   {
      
      str3 = [NSString stringWithUTF8String:strButton3];
      
   }
   
   
   __block    dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
   
   UIAlertController* alert = [UIAlertController alertControllerWithTitle:strHeader
                                                               message:strMessage
                                                        preferredStyle:UIAlertControllerStyleAlert];
   
   __block BOOL b1 = FALSE;
   __block    BOOL b2 = FALSE;
   __block    BOOL b3 = FALSE;
   
   UIAlertAction * a1 = NULL;
   UIAlertAction * a2 = NULL;
   UIAlertAction * a3 = NULL;
   
   if(strButton1 != NULL)
   {
   
      a1 = [UIAlertAction actionWithTitle:str1 style:UIAlertActionStyleDefault
                                  handler:^(UIAlertAction * action)
            {
         
         b1 = TRUE;
         enum_dialog_result eresult = e_dialog_result_cancel;
             switch(uType)
             {
                case e_message_box_ok_cancel:
                       eresult= e_dialog_result_ok;
                   break;
                case e_message_box_abort_retry_ignore:
                       eresult= e_dialog_result_abort;
                   break;
                case e_message_box_yes_no_cancel:
                       eresult= e_dialog_result_yes;
                   break;
                case e_message_box_yes_no:
                       eresult= e_dialog_result_yes;
                   break;
                case e_message_box_retry_cancel:
                       eresult= e_dialog_result_retry;
                   break;
                case e_message_box_cancel_try_continue:
                       eresult= e_dialog_result_cancel;
                   break;
                default:
                       eresult= e_dialog_result_ok;
                   break;
             }

         function(eresult);
         
      }];

      [alert addAction:a1];
      
   }
   
   
   if(strButton2 != NULL)
   {
      
      a2 = [UIAlertAction actionWithTitle:str2 style:UIAlertActionStyleDefault
                                  handler:^(UIAlertAction * action) {
         b2 = TRUE;

         enum_dialog_result eresult = e_dialog_result_cancel;
             switch(uType)
             {
                case e_message_box_ok_cancel:
                       eresult= e_dialog_result_cancel;
                   break;
                case e_message_box_abort_retry_ignore:
                       eresult= e_dialog_result_retry;
                   break;
                case e_message_box_yes_no_cancel:
                       eresult= e_dialog_result_no;
                   break;
                case e_message_box_yes_no:
                       eresult= e_dialog_result_no;
                   break;
                case e_message_box_retry_cancel:
                       eresult= e_dialog_result_cancel;
                   break;
                case e_message_box_cancel_try_continue:
                       eresult= e_dialog_result_try_again;
                   break;
                default:
                   break;
             }

         function(eresult);
      }];
      
      [alert addAction:a2];
      
   }
   
   if(strButton3 != NULL)
   {
      
      a3 = [UIAlertAction actionWithTitle:str3 style:UIAlertActionStyleDefault
                                  handler:^(UIAlertAction * action) {
         
         b3 = TRUE;
         
         enum_dialog_result eresult = e_dialog_result_cancel;

             switch(uType)
             {
                case e_message_box_ok_cancel:
                   break;
                case e_message_box_abort_retry_ignore:
                       eresult= e_dialog_result_ignore;
                   break;
                case e_message_box_yes_no_cancel:
                       eresult= e_dialog_result_cancel;
                   break;
                case e_message_box_yes_no:
                   break;
                case e_message_box_retry_cancel:
                   break;
                case e_message_box_cancel_try_continue:
                       eresult= e_dialog_result_continue;
                   break;
                default:
                   break;
             }

         function(eresult);
      }];
      
      [alert addAction:a3];
      
   }
   
//   Get the current keyWindow:
   
   UIWindow *window = [UIApplication sharedApplication].keyWindow;
   
  // Get its rootViewController:
    
   ns_main_async(^{

      UIViewController *rootViewController = window.rootViewController;
[rootViewController presentViewController:alert animated:YES completion:^{
//    enum_dialog_result eresult =e_dialog_result_ok;
//    switch(uType)
//    {
//       case e_message_box_ok_cancel:
//          if(b1)
//              eresult= e_dialog_result_ok;
//          else if(b2)
//              eresult= e_dialog_result_cancel;
//          break;
//       case e_message_box_abort_retry_ignore:
//          if(b1)
//              eresult= e_dialog_result_abort;
//          else if(b2)
//              eresult= e_dialog_result_retry;
//          else if(b3)
//              eresult= e_dialog_result_ignore;
//          break;
//       case e_message_box_yes_no_cancel:
//          if(b1)
//              eresult= e_dialog_result_yes;
//          else if(b2)
//              eresult= e_dialog_result_no;
//          else if(b3)
//              eresult= e_dialog_result_cancel;
//          break;
//       case e_message_box_yes_no:
//          if(b1)
//              eresult= e_dialog_result_yes;
//          else if(b2)
//              eresult= e_dialog_result_no;
//          break;
//       case e_message_box_retry_cancel:
//          if(b1)
//              eresult= e_dialog_result_retry;
//          else if(b2)
//              eresult= e_dialog_result_cancel;
//          break;
//       case e_message_box_cancel_try_continue:
//          if(b1)
//              eresult= e_dialog_result_cancel;
//          else if(b2)
//              eresult= e_dialog_result_try_again;
//          else if(b3)
//              eresult= e_dialog_result_continue;
//          break;
//       default:
//          if(b1)
//              eresult= e_dialog_result_ok;
//          break;
//    }
//
//
//    function(eresult);
//
    
    
}];
      
   });


}

