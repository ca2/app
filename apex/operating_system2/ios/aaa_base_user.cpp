//
//  c_os_cross_win_user.cpp
//  c
//
//  Created by Snow Leopard User on 06/11/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "framework.h"
//#include "ios_internal.h"




int ui_MessageBoxA(void * oswindow, const ::scoped_string & scopedstrMessageParam, const ::scoped_string & scopedstrHeaderParam, unsigned int uType );



CLASS_DECL_APEX string message_box_result_to_string(int iResult);


void message_box_synchronous(oswindow oswindow, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, ::callback callback )
{

   string strMessage(pszMessage); // string "absorbs" nullptr pointers into ""

   string strHeader(pszTitle); // string "absorbs" nullptr pointers into ""

   int iResult = ui_MessageBoxA((void *) oswindow, strMessage, strHeader, emessagebox);
   
   string strResult = message_box_result_to_string(iResult);

   callback.receive_response(strResult);

   return ::success;
   
}





