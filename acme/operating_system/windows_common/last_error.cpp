//
// Created by camilo on 2026-04-27 16:22 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
//
#include "framework.h"
#include "last_error.h"
#include "acme/_operating_system.h"


namespace windows
{


   CLASS_DECL_ACME last_error get_last_error()
   {

      ::windows::last_error lasterror(::GetLastError());

      return lasterror;

   }

   

      ::string last_error::get_error_description() const { ::string strError;

            LPVOID lpMsgBuf;
            DWORD dwFormatFlags =
               FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
            FormatMessageW(dwFormatFlags, nullptr, m_uLastError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                           (LPWSTR)&lpMsgBuf, 0, nullptr);
            strError = (LPCWSTR)lpMsgBuf;
            LocalFree(lpMsgBuf);
         return strError;

   }

      ::e_status last_error::as_estatus() const
      {

         if (m_uLastError == ERROR_CANCELLED)
         {
            return error_cancelled;
         }
         else if (m_uLastError == ERROR_SUCCESS)
         {
            return ::success;
         }
         else
         {
            return error_failed;
         }

   }

}



