// Created by camilo on 2021-08-09 02:44 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/constant/parallelization.h"


#include "_c.h"


inline void __throw_last_error(DWORD dwLastError)
{

   auto estatus = last_error_to_status(dwLastError);

   throw ::exception(estatus);

}


inline void __throw_last_error()
{

   auto lastError = ::GetLastError();

   __throw_last_error(lastError);

}


inline ::e_status windows_wait_result_to_status(int iResult)
{

   if (iResult >= WAIT_ABANDONED_0 && iResult < (WAIT_ABANDONED_0 + MAXIMUM_WAIT_OBJECTS))
   {

      return (::e_status)((::i64)abandoned_base + (iResult - WAIT_ABANDONED_0));

   }
   else if (iResult == WAIT_IO_COMPLETION)
   {

      return error_wait_io_completion;

   }
   else if (iResult == WAIT_FAILED)
   {

      return error_wait_failed;

   }
   else if (iResult == WAIT_TIMEOUT)
   {

      return error_wait_timeout;

   }
   else if (iResult >= WAIT_OBJECT_0 && iResult < (WAIT_OBJECT_0 + MAXIMUM_WAIT_OBJECTS))
   {

      return (::e_status)((::i64)signaled_base + (iResult - WAIT_OBJECT_0));

   }
   else
   {

      return error_failed;

   }

}

#ifndef CUBE

CLASS_DECL_ACME int_bool _001DefaultDllMain(hinstance hinstance, ::u32 dwReason, void * pReserved, int iLibMainDebugBox = 0, const lib_main_int & intDelayMs = {});

#endif


wstring CLASS_DECL_ACME windows_get_root(const wstring & wstrPath);


#include "api.h"






