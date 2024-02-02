//
//  c_os_cross_win_user.cpp
//  c
//
//  Created by Snow Leopard User on 06/11/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "framework.h"
#include "acme/parallelization/manual_reset_event.h"
//#include "ios_internal.h"


int _ui_MessageBoxA(const char * pszMessageParam, const char * pszHeaderParam, unsigned int uType, const char * pszDetails, ::function < void (enum_dialog_result) > function);


int ui_MessageBoxA(const ::scoped_string & scopedstrMessageParam, const ::scoped_string & scopedstrHeaderParam, unsigned int uType, const ::scoped_string & scopedstrDetails, ::function < void (enum_dialog_result) > function);


CLASS_DECL_ACME string message_box_result_to_string(int iResult);

void message_box_synchronous(oswindow oswindow, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails, const ::function < void(::enum_dialog_result) > & function)
{

   auto pevent = ::platform::get()->__create_new< manual_reset_event >();
   
   auto eresult = (::enum_dialog_result) ui_MessageBoxA(scopedstrMessage, scopedstrTitle, emessagebox, scopedstrDetails, [function, pevent](enum_dialog_result eresult)
                                                        {
      
      function(eresult);
      
      pevent->SetEvent();
   
   });
   
   //string strResult = message_box_result_to_string(iResult);

   //function(eresult);
   
   pevent->wait();

   return ::success;
   
}


int ui_MessageBoxA(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, unsigned int uType, const ::scoped_string & scopedstrDetails, ::function < void (enum_dialog_result) > function)
{
   
   string strMessage(scopedstrMessage);

   string strTitle(scopedstrTitle);
   
   string strDetails(scopedstrDetails);

   return _ui_MessageBoxA(strMessage, strTitle, uType, strDetails, function);
   
}



