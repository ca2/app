// Created by camilo on 2022-10-21 23:41 <3ThomasBorregaardSorensen!!
#pragma once


class CLASS_DECL_ACME sync_io_error
{
   public:


   int   m_iGenerateBefore;
   int   m_iErrorBefore;
   int * m_piError;


   sync_io_error(int * piError = nullptr)
   {
      m_iGenerateBefore = get_generate_sync_io_error();
      m_iErrorBefore = get_sync_io_error();
      set_sync_io_error(0);
      set_generate_sync_io_error(1);
      m_piError = piError;
   }

   ~sync_io_error()
   {
      if (m_piError != nullptr)
      {
         *m_piError = get_sync_io_error();
      }
      set_generate_sync_io_error(m_iGenerateBefore);
      set_sync_io_error(m_iErrorBefore);
   }

   bool none() const { return get_sync_io_error() == 0; }


   operator bool() const { return get_sync_io_error() != 0; }

};


