// Created by camilo on 2021-08-12 02:25 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/string/string.h"


namespace file_lock
{


   class CLASS_DECL_ACME file_lock
   {
   public:


      int         m_iFileDescriptor;
      ::string    m_strName;
      ::string    m_strPath;


      file_lock();
      file_lock(const char * pszName);
      ~file_lock();


      bool set_name(const char * pszName);


      bool is_active();
      bool lock();
      bool unlock();


      bool create_file();
      bool close_file();


      static string _get_file_name(const char * lpszName);


   };


} // namespace file_lock



