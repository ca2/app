// Created by camilo on 2021-08-09 02:44 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/const/parallelization.h"


inline enum_synchronization_result windows_wait_result_to_synchronization_result(int iResult)
{

   if (iResult >= WAIT_ABANDONED_0 && iResult < (WAIT_ABANDONED_0 + MAXIMUM_WAIT_OBJECTS))
   {

      return (enum_synchronization_result)((int)e_synchronization_result_abandoned_base + (iResult - WAIT_ABANDONED_0));

   }
   else if (iResult == WAIT_IO_COMPLETION)
   {

      return e_synchronization_result_io_completion;

   }
   else if (iResult == WAIT_FAILED)
   {

      return e_synchronization_result_error;

   }
   else if (iResult == WAIT_TIMEOUT)
   {

      return e_synchronization_result_timed_out;

   }
   else if (iResult >= WAIT_OBJECT_0 && iResult < (WAIT_OBJECT_0 + MAXIMUM_WAIT_OBJECTS))
   {

      return (enum_synchronization_result)((int)e_synchronization_result_signaled_base + (iResult - WAIT_OBJECT_0));

   }
   else
   {

      return e_synchronization_result_error;

   }

}

#ifndef CUBE

CLASS_DECL_ACME int_bool _001DefaultDllMain(hinstance hinstance, ::u32 dwReason, void * pReserved, int iLibMainDebugBox = 0, const lib_main_int & intDelayMs = {});

#endif


#include "api.h"



