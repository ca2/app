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


   virtual ::file_system_real_path_interface* get_file_system_real_path_interface();


   virtual bool file_system_file_exists(::file_system_item * pfilesystemitem);
   virtual bool file_system_is_folder(::file_system_item* pfilesystemitem);
   virtual bool file_system_has_script(::file_system_item* pfilesystemitem);
   virtual string file_system_expanded_md5(::file_system_item* pfilesystemitem);

   virtual bool _file_system_file_exists(::file_system_item* pfilesystemitem);
   virtual bool _file_system_is_folder(::file_system_item* pfilesystemitem);
   virtual bool _file_system_has_script(::file_system_item* pfilesystemitem);
   virtual string _file_system_expanded_md5(::file_system_item* pfilesystemitem);


   virtual class ::file_system_cache_item file_system_item(const ::scoped_string& scopedstrName, ::file_system_real_path_interface* pfilesystemrealpathinterface = nullptr);


   virtual ::file_system_item* get_file_system_item(const ::scoped_string& scopedstr, ::file_system_real_path_interface* pfilesystemrealpathinterface = nullptr);


   //virtual ::file::path _calculate_real_path(const ::scoped_string& scopedstrName, ::file_system_interface* pfilesysteminterface = nullptr);


};




