// Created by camilo on 2025-10-19 16:53 <3ThomasBorregaardSørensen!!
// From programming by camilo on 2025-10-19 17:28 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 17:34 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 17:50 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
#pragma once


#include "acme/filesystem/filesystem/file_system_interface.h"


class CLASS_DECL_ACME file_system_composite :
   virtual public ::file_system_interface
{
public:


   ::pointer < ::file_system_interface >     m_pfilesysteminterface;


   file_system_composite();
   ~file_system_composite() override;



   //bool include_matches_file_exists(const ::file_system_cache_item& filesystemcacheitem) override;
   //bool include_matches_is_dir(const ::file_system_cache_item& filesystemcacheitem) override;
   //bool include_has_script(const ::file_system_cache_item& filesystemcacheitem) override;
   //string include_expand_md5(const ::file_system_cache_item& filesystemcacheitem) override;

   class ::file_system_cache_item file_system_item(const ::scoped_string& scopedstrName, ::file_system_interface* pfilesysteminterface = nullptr) override;


};



