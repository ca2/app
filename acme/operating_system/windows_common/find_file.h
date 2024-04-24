// Created by camilo on 2023-03-14 13:11 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/_operating_system.h"


namespace windows
{


   class CLASS_DECL_ACME find_file
   {
   public:


      HANDLE               m_handleFindFile;
      ::file::path         m_pathPattern;
      ::windows_path       m_windowspathPattern;
      WIN32_FIND_DATAW     m_finddata;


      find_file();
      ~find_file();


      bool find_first_file(const ::file::path & pathPattern);

      void close();

      bool find_next_file();

      
   };


} // namespace windows



