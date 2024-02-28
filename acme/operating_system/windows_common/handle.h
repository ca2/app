// Created by camilo on 2023-03-14 05:56 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/file/exception.h"


namespace windows
{


   class CLASS_DECL_ACME handle
   {
   public:


      HANDLE m_handle;


      handle(HANDLE handle = INVALID_HANDLE_VALUE);
      ~handle();


      handle & operator = (HANDLE handle);

      void close_handle();


      operator HANDLE() const { return m_handle; }
      operator HANDLE & () { return m_handle; }


      bool nok() const { return m_handle == INVALID_HANDLE_VALUE || m_handle == NULL; }
      bool is_ok() const { return !nok(); }




   };


} // namespace windows



