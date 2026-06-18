#pragma once


#include "application_common.h"


::i32 console_end(::e_status estatus)
{

   ::i32 iStatus = (::i32)estatus;

   ::i32 iError = 0;

   if (iStatus < 0)
   {

      iError = iStatus;

   }
   else if (iStatus > 1)
   {

      iError = 0;

      if (psystem->is_true("show_application_information"))
      {

         printf("return code is %d", iStatus);

      }

   }

   psystem->system_end();

   return iError;

}



