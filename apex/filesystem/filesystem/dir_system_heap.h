#pragma once


#include "apex/primitive/collection/collection_file_path_map.h"


namespace file
{


   namespace dir
   {


      class CLASS_DECL_APEX is_dir
      {
      public:

         bool           m_bIsDir;
         ::duration m_durationLastCheck;
         u32       m_dwError;


      };


      class CLASS_DECL_APEX is_dir_map :
         virtual public file_path_map < is_dir >
      {
      public:


         ::mutex                m_mutex;
         ::duration m_durationTimeout;


         is_dir_map(::object * pobject);


         bool lookup(const ::file::path & strPath, bool &bIsDir, u32 & dwLastError);
         bool lookup(const ::file::path & strPath, bool &bIsDir, u32 & dwLastError, i32 iLast);
         void set(const ::file::path & strPath, bool bIsDir, u32 dwLastError);


      };


      class CLASS_DECL_APEX dir_system_heap
      {
      public:

         is_dir_map         m_isdirmap;


         //::file::path         m_strCa2;
         //::file::path         m_pathCa2Module;
         ::file::path         m_pathModule;
         ::file::path         m_pathProfile;
         ::file::path         m_pathUser;
         ::file::path         m_pathHome;

         dir_system_heap(::object * pobject) :
            m_isdirmap(pobject)
         {


         }

      };


   } // namespace dir


} // namespace file



