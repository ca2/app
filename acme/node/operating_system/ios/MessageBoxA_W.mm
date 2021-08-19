//
//  MessageBoxA_W.m
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 09/07/15.
//
//


int ui_MessageBoxA(void * oswindow, const char * pszMessageParam, const char * pszHeaderParam, unsigned int uType )
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
                                  handler:^(UIAlertAction * action) {  b1 = TRUE;}];

      [alert addAction:a1];
      
   }
   
   
   if(strButton2 != NULL)
   {
      
      a2 = [UIAlertAction actionWithTitle:str2 style:UIAlertActionStyleDefault
                                  handler:^(UIAlertAction * action) { b2 = TRUE;}];
      
      [alert addAction:a2];
      
   }
   
   if(strButton3 != NULL)
   {
      
      a3 = [UIAlertAction actionWithTitle:str3 style:UIAlertActionStyleDefault
                                  handler:^(UIAlertAction * action) { b3 = TRUE;}];
      
      [alert addAction:a3];
      
   }
   
//   Get the current keyWindow:
   
   UIWindow *window = [UIApplication sharedApplication].keyWindow;
   
  // Get its rootViewController:
   
   UIViewController *rootViewController = window.rootViewController;
[rootViewController presentViewController:alert animated:YES completion:^{
   dispatch_semaphore_signal(semaphore);
}];

dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
//dispatch_release(semaphore);
   
   switch(uType)
   {
      case MB_OKCANCEL:
         if(b1)
            return IDOK;
         else if(b2)
            return IDCANCEL;
         break;
      case MB_ABORTRETRYIGNORE:
         if(b1)
            return IDABORT;
         else if(b2)
            return IDRETRY;
         else if(b3)
            return IDIGNORE;
         break;
      case MB_YESNOCANCEL:
         if(b1)
            return IDYES;
         else if(b2)
            return IDNO;
         else if(b3)
            return IDCANCEL;
         break;
      case MB_YESNO:
         if(b1)
            return IDYES;
         else if(b2)
            return IDNO;
         break;
      case MB_RETRYCANCEL:
         if(b1)
            return IDRETRY;
         else if(b2)
            return IDCANCEL;
         break;
      case MB_CANCELTRYCONTINUE:
         if(b1)
            return IDCANCEL;
         else if(b2)
            return IDTRYAGAIN;
         else if(b3)
            return IDCONTINUE;
         break;
      default:
         if(b1)
            return IDOK;
         break;
   }
   
   
   return IDCANCEL;

}

