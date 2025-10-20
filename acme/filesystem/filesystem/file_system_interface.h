// Created by camilo on 2025-10-19 16:53 <3ThomasBorregaardSørensen!!
// From programming by camilo on 2025-10-19 17:28 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 17:34 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
#pragma once


#include "acme/filesystem/filesystem/file_system_cache_item.h"
#include "acme/prototype/collection/int_map.h"
#include "acme/prototype/prototype/unique_index.h"


class CLASS_DECL_ACME file_system_interface :
   virtual public ::particle,
   virtual public ::unique_index_domain
{
public:


   critical_section                                m_criticalsectionFileSystemCacheItem;
   index_map_base < ::file_system_cache_item >     m_mapFileSystemCacheItem;



   file_system_interface();
   ~file_system_interface() override;


   void on_initialize_particle() override;


   virtual ::file_system_real_path_interface* get_file_system_real_path_interface();



   ::file_system_cache_item& file_system_cache_item(const ::unique_index& uniqueindex)
   {

      critical_section_lock criticalsectionlock(&m_criticalsectionFileSystemCacheItem);

      return m_mapFileSystemCacheItem[uniqueindex.index()];

   }


   virtual bool file_system_file_exists(::file_system_item * pfilesystemitem);
   virtual bool file_system_is_folder(::file_system_item* pfilesystemitem);
   virtual bool file_system_has_script(::file_system_item* pfilesystemitem);
   virtual string file_system_expanded_md5(::file_system_item* pfilesystemitem);

   virtual bool _file_system_file_exists(::file_system_item* pfilesystemitem);
   virtual bool _file_system_is_folder(::file_system_item* pfilesystemitem);
   virtual bool _file_system_has_script(::file_system_item* pfilesystemitem);
   virtual string _file_system_expanded_md5(::file_system_item* pfilesystemitem);


   virtual class ::file_system_cache_item file_system_item(const ::scoped_string& scopedstrName, ::file_system_real_path_interface* pfilesystemrealpathinterface = nullptr);

   virtual ::file::path file_system_item_path(const ::scoped_string& scopedstrName, ::file_system_real_path_interface* pfilesystemrealpathinterface = nullptr);


   virtual ::file_system_item* get_file_system_item(const ::scoped_string& scopedstr, ::file_system_real_path_interface* pfilesystemrealpathinterface = nullptr);


   //virtual ::file::path _calculate_real_path(const ::scoped_string& scopedstrName, ::file_system_interface* pfilesysteminterface = nullptr);


};




