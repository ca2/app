// Created by camilo on 2023-03-14 13:12 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "find_file.h"

#include "acme/_operating_system.h"


namespace windows
{


   find_file::find_file() :
      m_finddata{}
   {

      m_handleFindFile = INVALID_HANDLE_VALUE;

   }


   find_file::~find_file()
   {

      close();

   }


   bool find_file::find_first_file(const ::file::path & pathPattern)
   {

      m_pathPattern = pathPattern;

      auto strPathPattern = pathPattern.windows_path();

      m_windowspathPattern = strPathPattern;

      m_handleFindFile = ::FindFirstFileW(m_windowspathPattern, &m_finddata);

      if (m_handleFindFile == INVALID_HANDLE_VALUE)
      {

         return false;

      }

      return true;

   }


   void find_file::close()
   {

      if (m_handleFindFile != INVALID_HANDLE_VALUE)
      {

         ::FindClose(m_handleFindFile);

         m_handleFindFile = INVALID_HANDLE_VALUE;

      }

   }

   
   bool find_file::find_next_file()
   {

      if (!::FindNextFileW(m_handleFindFile, &m_finddata))
      {

         return false;

      }

      return true;

   }


} // namespace windows



