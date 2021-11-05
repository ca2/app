//
//  c_os_cross_win_user.cpp
//  c
//
//  Created by Snow Leopard User on 06/11/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "framework.h"
//#include "ios_internal.h"




int ui_MessageBoxA(void * oswindow, const char * pszMessageParam, const char * pszHeaderParam, unsigned int uType );



CLASS_DECL_APEX string message_box_result_to_string(int iResult);


::e_status os_message_box(oswindow oswindow, const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox, ::callback callback )
{

   string strMessage(pszMessage); // string "absorbs" nullptr pointers into ""

   string strHeader(pszTitle); // string "absorbs" nullptr pointers into ""

   int iResult = ui_MessageBoxA((void *) oswindow, strMessage, strHeader, emessagebox);
   
   string strResult = message_box_result_to_string(iResult);

   callback.receive_response(strResult);

   return ::success;
   
}





