// Created by camilo on 2025-10-19 16:53 <3ThomasBorregaardSørensen!!
// From programming by camilo on 2025-10-19 17:28 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 17:34 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 17:52 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
#include "framework.h"
#include "file_system_composite.h"
#include "file_system_cache_item.h"


file_system_composite::file_system_composite()
{

}


file_system_composite::~file_system_composite()
{


}



//bool file_system_composite::include_matches_file_exists(const ::file_system_cache_item& filesystemcacheitem)
//{
//
//   return m_pfilesysteminterface->include_matches_file_exists(filesystemcacheitem);
//
//}
//
//
//
//bool file_system_composite::include_matches_is_dir(const ::file_system_cache_item& filesystemcacheitem)
//{
//
//   return m_pfilesysteminterface->include_matches_is_dir(filesystemcacheitem);
//
//}
//
//
//bool file_system_composite::include_has_script(const ::file_system_cache_item& filesystemcacheitem)
//{
//
//   return m_pfilesysteminterface->include_has_script(filesystemcacheitem);
//
//}
//
//
//string file_system_composite::include_expand_md5(const ::file_system_cache_item& filesystemcacheitem)
//{
//
//   return m_pfilesysteminterface->include_expand_md5(filesystemcacheitem);
//
//}
//


::file_system_cache_item file_system_composite::file_system_item(const ::scoped_string & scopedstrName, ::file_system_interface* pfilesysteminterface)
{

   return m_pfilesysteminterface->file_system_item(scopedstrName, pfilesysteminterface);

}


