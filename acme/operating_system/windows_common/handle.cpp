// Created by camilo on 2023-03-14 05:56 <3ThomasBorregaardSorensen!!
#include "framework.h"


#include "acme/_operating_system.h"


namespace windows
{


   handle::handle(::uptr u) 
   {
      
      m_u = u; 
   
   }


   handle::~handle()
   {

      close_handle();

   }


   handle & handle::operator = (::uptr u)
   {

      close_handle();

      m_u = u;

      return *this;

   }


   void handle::close_handle()
   {

      if (is_ok())
      {

         ::CloseHandle((HANDLE) m_u);

         m_u = (::uptr) INVALID_HANDLE_VALUE;

      }

   }


} // namespace windows



