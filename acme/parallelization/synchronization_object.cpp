// Created by camilo on 2022-10-28 14:35 <3ThomasBorregaardSorensen!!
#include "platform.h"
#include "synchronization_object.h"
#include "acme/exception/exception.h"
#include "acme/parallelization/task.h"
#include "acme/_operating_system.h"





CLASS_DECL_ACME bool _hsynchronization_wait(::hsynchronization h, const class ::time& timeWait);


//namespace acme_windows_common
//{


   synchronization_object::synchronization_object() :
      m_handle(nullptr)
   {


   }


   synchronization_object::~synchronization_object()
   {

      if (m_bOwner && m_handle != nullptr)
      {

         if (has_own_synchronization_flag())
         {

            BOOL bOk = ::CloseHandle(m_handle);

            if (!bOk)
            {

               auto errorcodeLastError = ::windows::last_error_error_code();

               ::warningf("synchronization_object::~synchronization_object : Failed to close synchronization handle (%d)", errorcodeLastError.m_iOsError);

            }

         }

         m_handle = nullptr;

      }

   }


   hsynchronization synchronization_object::get_synchronization_handle()
   {

      return m_handle;

   }


   bool synchronization_object::_wait(const class time & timeWait)
   {
   
      return _hsynchronization_wait(m_handle, timeWait);
    
   }
   

//} // namespace acme_windows_common



