// Created by camilo on 2023-03-14 05:56 <3ThomasBorregaardSorensen!!
#include "framework.h"


#include "acme/_operating_system.h"


namespace windows
{


   handle::handle(HANDLE handle) 
   {
      
      m_handle = handle; 
   
   }


   handle::~handle()
   {

      close_handle();

   }


   handle & handle::operator = (HANDLE handle)
   {

      close_handle();

      m_handle = handle;

      return *this;

   }


   void handle::close_handle()
   {

      if (is_ok())
      {

         ::CloseHandle(m_handle);

         m_handle = INVALID_HANDLE_VALUE;

      }

   }


} // namespace windows



