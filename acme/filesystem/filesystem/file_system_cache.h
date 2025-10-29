// Created by camilo on 2025-10-19 16:53 <3ThomasBorregaardSørensen!!
// From programming by camilo on 2025-10-19 17:28 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
#pragma once


#include "acme/filesystem/filesystem/file_system_interface.h"
#include "acme/filesystem/filesystem/file_system_cache_item.h"


class CLASS_DECL_ACME file_system_cache :
   virtual public ::particle,
   virtual public ::unique_index_domain
{
public:


   //::pointer < ::mutex >                                 m_pmutexIncludeMatches;
   //::pointer < ::mutex >                                 m_pmutexIncludeHasScript;
   //::pointer < ::mutex >                                 m_pmutexIncludeExpandMd5;

   ::pointer < ::mutex >                                    m_pmutexFileSystemItem;
   string_map_base < ::pointer < ::file_system_item > >     m_mapFileSystemItem;
   //string_map_base < ::logic::boolean >                  m_mapIncludeMatchesFileExists2;
   //string_map_base < ::logic::boolean >                  m_mapIncludeMatchesIsDir2;
   //string_map_base < ::logic::boolean >                  m_mapIncludeHasScript2;
   //string_to_string_base                                 m_mapIncludeExpandMd5;
   critical_section                                         m_criticalsectionFileSystemCacheItem;
   index_map_base < ::file_system_cache_item >              m_mapFileSystemCacheItem;

   
   file_system_cache();
   ~file_system_cache() override;


   void on_initialize_particle() override;


   ::file_system_cache_item& file_system_cache_item(const ::scoped_string& scopedstrName, const ::unique_index& uniqueindex)
   {

      critical_section_lock criticalsectionlock(&m_criticalsectionFileSystemCacheItem);

      auto& pfilesystemcacheitem = m_mapFileSystemCacheItem[uniqueindex.index()];

      if (!pfilesystemcacheitem)
      {

         criticalsectionlock.unlock();

         auto pfilesystemcacheitemNew = file_system_item(scopedstrName);

         criticalsectionlock.lock();

         pfilesystemcacheitem = pfilesystemcacheitemNew;

      }

      return pfilesystemcacheitem;

   }




   //bool file_system_file_exists(const ::file_system_cache_item& pfilesystemcacheitem) override;
   //bool file_system_is_folder(const ::file_system_cache_item& pfilesystemcacheitem) override;
   //bool file_system_has_script(const ::file_system_cache_item& pfilesystemcacheitem) override;
   //string file_system_expanded_md5(const ::file_system_cache_item& pfilesystemcacheitem) override;

   virtual ::file_system_cache_item file_system_item(
      const ::scoped_string & scopedstrName, 
      ::file_system_real_path_interface* pfilesystemrealpathinterface = nullptr,
      ::file_system_interface* pfilesysteminterface = nullptr);


   //virtual void set_include_matches_file_exists(const ::file_system_cache_item& pfilesystemcacheitem, bool bFileExists);
   //virtual void set_include_expand_md5(const ::file_system_cache_item& pfilesystemcacheitem, const ::scoped_string& scopedstrMd5);


   virtual void clear_file_system_cache_item(const ::scoped_string& scopedstrName);
   virtual void clear_file_system_cache();


};


