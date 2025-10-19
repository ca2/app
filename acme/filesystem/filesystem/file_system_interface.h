// Created by camilo on 2025-10-19 16:53 <3ThomasBorregaardSørensen!!
// From programming by camilo on 2025-10-19 17:28 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 17:34 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
#pragma once


#include "acme/filesystem/filesystem/file_system_cache_item.h"


class CLASS_DECL_ACME file_system_interface :
   virtual public ::particle
{
public:



   file_system_interface();
   ~file_system_interface() override;



   //virtual bool include_matches_file_exists(const ::file_system_cache_item& filesystemcacheitem);
   //virtual bool include_matches_is_dir(const ::file_system_cache_item& filesystemcacheitem);
   //virtual bool include_has_script(const ::file_system_cache_item& filesystemcacheitem);
   //virtual string include_expand_md5(const ::file_system_cache_item& filesystemcacheitem);


   virtual class ::file_system_cache_item file_system_item(const ::scoped_string& scopedstrName, ::file_system_interface* pfilesysteminterface = nullptr);
   virtual class ::file_system_item * _file_system_item(const ::scoped_string& scopedstrName, ::file_system_interface * pfilesysteminterface = nullptr);


   virtual ::file::path get_real_path(const ::scoped_string& scopedstr);

};



