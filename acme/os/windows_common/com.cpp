#include "framework.h"
#include "acme/operating_system.h"



thread_local HRESULT t_hresultCoInitialize;

thread_local bool t_bCoInitialize = false;

HRESULT defer_co_initialize_ex(bool bMultiThread, bool bDisableOleDDE)
{

   if(!t_bCoInitialize)
   {

      t_bCoInitialize = true;

      if (bMultiThread)
      {

         t_hresultCoInitialize = ::CoInitializeEx(nullptr, COINIT_MULTITHREADED);

      }
      else
      {

         t_hresultCoInitialize = ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | (bDisableOleDDE ? COINIT_DISABLE_OLE1DDE : 0));

      }

   }

   if (FAILED(t_hresultCoInitialize))
   {

      ::output_debug_string("Failed to ::CoInitializeEx(nullptr, COINIT_MULTITHREADED) at __node_pre_init");

      return t_hresultCoInitialize;

   }

   return t_hresultCoInitialize;

}




