#pragma once


#include "apex/prototype/collection/collection_file_path_map.h"


namespace file
{


   namespace dir
   {


      class CLASS_DECL_APEX is_dir
      {
      public:

         bool           m_bIsDir;
         class ::time m_timeLastCheck;
         unsigned int       m_dwError;


      };


      class CLASS_DECL_APEX is_dir_map :
         virtual public file_path_map < is_dir >
      {
      public:


         ::pointer < ::mutex >                m_pmutex;
         class ::time m_timeTimeout;


         is_dir_map(::particle * pparticle);


         bool find(const ::file::path & strPath, bool &bIsDir, unsigned int & dwLastError);
         bool find(const ::file::path & strPath, bool &bIsDir, unsigned int & dwLastError, int iLast);
         void set(const ::file::path & strPath, bool bIsDir, unsigned int dwLastError);


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

         dir_system_heap(::particle * pparticle) :
            m_isdirmap(pparticle)
         {


         }

      };


   } // namespace dir


} // namespace file



