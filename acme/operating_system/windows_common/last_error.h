// Created by camilo on 2023-07-06 09:11 <3ThomasBorregaardSorensen!!
#pragma once


namespace windows
{


   class CLASS_DECL_ACME last_error
   {
   public:


      unsigned int        m_uLastError;


      last_error(unsigned int uLastError = 0) : m_uLastError(uLastError){}
      last_error(const last_error & lasterror) : m_uLastError(lasterror.m_uLastError){}
      
      last_error & operator = (unsigned int uLastError) {m_uLastError = uLastError; return *this;}
      bool operator == (const last_error & lasterror) const {return m_uLastError == lasterror.m_uLastError; }
      bool operator == (unsigned int uLastError) const {return m_uLastError == uLastError; }

   };


   CLASS_DECL_ACME ::windows::last_error get_last_error();

   [[ noreturn ]] CLASS_DECL_ACME void throw_last_error_exception(const last_error & lasterror);

   [[ noreturn ]] CLASS_DECL_ACME void throw_last_error_exception();


}



