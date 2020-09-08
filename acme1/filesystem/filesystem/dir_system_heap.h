#pragma once


#include "acme/primitive/collection/collection_file_path_map.h"


namespace file
{


   namespace dir
   {


      class CLASS_DECL_ACME is_dir
      {
      public:

         bool           m_bIsDir;
         tick m_tickLastCheck;
         u32       m_dwError;


      };


      class CLASS_DECL_ACME is_dir_map :
         virtual public file_path_map < is_dir >
      {
      public:


         ::mutex                m_mutex;
         tick m_tickTimeout;


         is_dir_map(::generic * pobject);


         bool lookup(const ::file::path & strPath, bool &bIsDir, u32 & dwLastError);
         bool lookup(const ::file::path & strPath, bool &bIsDir, u32 & dwLastError, i32 iLast);
         void set(const ::file::path & strPath, bool bIsDir, u32 dwLastError);


      };


      class CLASS_DECL_ACME dir_system_heap
      {
      public:

         is_dir_map         m_isdirmap;


         ::file::path         m_strCa2;
         ::file::path         m_pathCa2Module;
         ::file::path         m_pathModule;
         ::file::path         m_pathProfile;
         ::file::path         m_pathUser;
         ::file::path         m_pathHome;

         dir_system_heap(::generic * pobject) :
            m_isdirmap(pobject)
         {


         }

      };


   } // namespace dir


} // namespace file



