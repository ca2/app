//
//  c_os_cross_win_user.cpp
//  c
//
//  Created by Snow Leopard User on 06/11/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "framework.h"
//#include "ios_internal.h"




int ui_MessageBoxA(const char * pszMessageParam, const char * pszHeaderParam, unsigned int uType, const char * pszDetails, ::function < void (enum_dialog_result) > function);



CLASS_DECL_ACME string message_box_result_to_string(int iResult);


void message_box_synchronous(oswindow oswindow, const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox, const char * pszDetails, const ::function < void(::enum_dialog_result) > & function)
{

   string strMessage(pszMessage); // string "absorbs" nullptr pointers into ""

   string strHeader(pszTitle); // string "absorbs" nullptr pointers into ""
   
   string strDetails(pszDetails);

   auto pevent = __new(manual_reset_event);
   
   auto eresult = (::enum_dialog_result) ui_MessageBoxA(strMessage, strHeader, emessagebox, strDetails, [function, pevent](enum_dialog_result eresult)
                                                        {
      
      function(eresult);
      
      pevent->SetEvent();
   
   });
   
   //string strResult = message_box_result_to_string(iResult);

   //function(eresult);
   
   pevent->wait();

   return ::success;
   
}





