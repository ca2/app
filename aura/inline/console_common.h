#pragma once


#include "application_common.h"


int console_end(::e_status estatus)
{

   int iStatus = (int)estatus;

   int iError = 0;

   if (iStatus < 0)
   {

      iError = iStatus;

   }
   else if (iStatus > 1)
   {

      iError = 0;

      if (::aura::get_system()->is_true("show_application_information"))
      {

         printf("return code is %d", iStatus);

      }

   }

   ::aura::get_system()->system_end();

   return iError;

}



