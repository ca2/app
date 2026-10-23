// Created by camilo on 2023-03-14 05:56 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/file/exception.h"


namespace windows
{


   class CLASS_DECL_ACME handle
   {
   public:


      ::uptr      m_u;


      handle(::uptr u = static_cast<::uptr>(-1));
      ~handle();


      handle & operator = (::uptr u);

      void close_handle();


      operator ::uptr() const { return m_u; }
      operator ::uptr & () { return m_u; }


      bool nok() const { return m_u == static_cast<::uptr>(-1) || m_u == 0; }
      bool is_ok() const { return !nok(); }


   };


} // namespace windows



