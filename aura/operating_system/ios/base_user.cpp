//
//  c_os_cross_win_user.cpp
//  c
//
//  Created by Snow Leopard User on 06/11/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "framework.h"
//#include "ios_internal.h"




int ui_MessageBoxA(const ::string & pszMessageParam, const ::string & pszHeaderParam, unsigned int uType, const scoped_string & strDetails, ::function < void (enum_dialog_result) > function);



CLASS_DECL_AURA string message_box_result_to_string(int iResult);


void message_box_synchronous(oswindow oswindow, const ::string & pszMessage, const ::string & pszTitle, const ::e_message_box & emessagebox, const ::string & strDetails, ::callback callback )
{

   string strMessage(pszMessage); // string "absorbs" nullptr pointers into ""

   string strHeader(pszTitle); // string "absorbs" nullptr pointers into ""

   
   auto pevent =__pointer(manual_reset_event());
   
   int iResult = ui_MessageBoxA((void *) oswindow, strMessage, strHeader, emessagebox,
                                [callback, pevent](enum_dialog_result eresult)
                                {
      
      string strResult = message_box_result_to_string(iResult);

      callback.receive_response(strResult);

      pevent->SetEvent();

   });
   
   pevent->wait();
   
   return ::success;
   
}





