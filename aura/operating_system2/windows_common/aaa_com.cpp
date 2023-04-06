#include "framework.h"



bool defer_co_initialize_ex(bool bMultiThread, bool bDisableOleDDE)
{

   auto pthread = ::get_task();

   if (!pthread)
   {

      return false;

   }

   HRESULT hr = pthread->m_hresultCoInitialize;

   if (!pthread->m_bCoInitialize)
   {

      pthread->m_bCoInitialize = true;

      if (bMultiThread)
      {

         hr = ::CoInitializeEx(nullptr, COINIT_MULTITHREADED);

      }
      else
      {

         hr = ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | (bDisableOleDDE ? COINIT_DISABLE_OLE1DDE : 0));

      }

      pthread->m_hresultCoInitialize = hr;

   }

   if (FAILED(hr))
   {

      ::output_debug_string("Failed to ::CoInitializeEx(nullptr, COINIT_MULTITHREADED) at __node_pre_init");

      return false;

   }

   return true;

}




