// Created by camilo on 2025-12-31 01:50 <3ThomasBorregaardSorensen!!
// V0idsEmbrace@YT and lowluds@Twitch
// Mummi and bilbo in the living room
#include "framework.h"
#include "acme/_operating_system.h"
//#include <objbase.h>

bool task::_defer_co_initialize_ex(bool bMultiThread)
{

   if (!m_bCoInitialize)
   {

      return false;

   }

   if (m_bCoInitialized)
   {

      return true;

   }

   m_bCoInitialized = true;


   m_errorcodeHresultCoInitialize.m_etype = e_error_code_type_hresult;

   m_errorcodeHresultCoInitialize.m_iOsError = (::iptr)::CoInitializeEx(nullptr,COINIT_MULTITHREADED);

    if (FAILED((HRESULT)m_errorcodeHresultCoInitialize.m_iOsError))
    {

       if (m_errorcodeHresultCoInitialize.m_iOsError == 0x80010106)
       {

          return true;

       }

       informationf("Failed to ::CoInitializeEx(nullptr, COINIT_MULTITHREADED) at __node_pre_init");

       return false;

    }

    return true;

 }



