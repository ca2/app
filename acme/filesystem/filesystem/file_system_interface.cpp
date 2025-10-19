// Created by camilo on 2025-10-19 16:53 <3ThomasBorregaardSørensen!!
// From programming by camilo on 2025-10-19 17:28 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 17:34 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
#include "framework.h"
#include "directory_system.h"
#include "file_system_interface.h"
#include "file_system.h"
#include "file_system_cache_item.h"
#include "path_system.h"


file_system_interface::file_system_interface()
{

}


file_system_interface::~file_system_interface()
{


}



//bool file_system_interface::include_matches_file_exists(const ::file_system_cache_item& filesystemcacheitem)
//{
//
//   return file_system()->__exists(filesystemcacheitem.path());
//
//}
//
//
//
//bool file_system_interface::include_matches_is_dir(const ::file_system_cache_item& filesystemcacheitem)
//{
//
//   return directory_system()->__is(filesystemcacheitem.path());
//
//}
//
//
//bool file_system_interface::include_has_script(const ::file_system_cache_item& filesystemcacheitem)
//{
//
//   return file_system()->__safe_find_string(filesystemcacheitem.path(), "<?") >= 0;
//
//}
//
//
//string file_system_interface::include_expand_md5(const ::file_system_cache_item& filesystemcacheitem)
//{
//
//   return {};
//
//}


::file_system_cache_item file_system_interface::file_system_item(const ::scoped_string& scopedstrName, ::file_system_interface* pfilesysteminterface)
{

   return {};

}


class ::file_system_item* file_system_interface::_file_system_item(const ::scoped_string& scopedstrName, ::file_system_interface* pfilesysteminterface)
{

   return nullptr;

}


::file::path file_system_interface::get_real_path(const ::scoped_string& scopedstr)
{

   return this->path_system()->real_path(scopedstr);

}



