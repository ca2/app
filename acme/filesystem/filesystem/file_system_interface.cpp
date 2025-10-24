// Created by camilo on 2025-10-19 16:53 <3ThomasBorregaardSørensen!!
// From programming by camilo on 2025-10-19 17:28 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 17:34 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
#include "framework.h"
#include "directory_system.h"
#include "file_system_interface.h"
#include "file_system.h"
#include "file_system_cache_item.h"
#include "path_system.h"
#include "acme/platform/node.h"



file_system_interface::file_system_interface()
{

}


file_system_interface::~file_system_interface()
{


}



void file_system_interface::on_initialize_particle()
{

   ::particle::on_initialize_particle();

   defer_create_synchronization();

}


::file_system_real_path_interface* file_system_interface::get_file_system_real_path_interface()
{

   return nullptr;

}


bool file_system_interface::file_system_file_exists(const ::file_system_cache_item & pfilesystemcacheitem)
{

   if (pfilesystemcacheitem.nok())
   {

      return false;

   }

   if (::is_set(pfilesystemcacheitem->m_pfilesysteminterface)
      && pfilesystemcacheitem->m_pfilesysteminterface != this)
   {

      return pfilesystemcacheitem->m_pfilesysteminterface->file_system_file_exists(pfilesystemcacheitem);

   }

   return _file_system_file_exists(pfilesystemcacheitem);

}


bool file_system_interface::_file_system_file_exists(const ::file_system_cache_item & pfilesystemcacheitem)
{

   return file_system()->_file_system_file_exists(pfilesystemcacheitem);

}


bool file_system_interface::file_system_is_folder(const ::file_system_cache_item & pfilesystemcacheitem)
{

   if (pfilesystemcacheitem.nok())
   {

      return false;

   }

   if (::is_set(pfilesystemcacheitem->m_pfilesysteminterface)
      && pfilesystemcacheitem->m_pfilesysteminterface != this)
   {

      return pfilesystemcacheitem->m_pfilesysteminterface->file_system_is_folder(pfilesystemcacheitem);

   }

   return _file_system_is_folder(pfilesystemcacheitem);

}


bool file_system_interface::_file_system_is_folder(const ::file_system_cache_item & pfilesystemcacheitem)
{

   return file_system()->_file_system_is_folder(pfilesystemcacheitem);

}


bool file_system_interface::file_system_has_script(const ::file_system_cache_item & pfilesystemcacheitem)
{

   if (pfilesystemcacheitem.nok())
   {

      throw ::exception(error_null_pointer);

   }

   if (pfilesystemcacheitem->m_bHasScript2.is_set())
   {

      return pfilesystemcacheitem->m_bHasScript2.is_set_true();

   }

   if (::is_set(pfilesystemcacheitem->m_pfilesysteminterface)
      && pfilesystemcacheitem->m_pfilesysteminterface != this)
   {

      return pfilesystemcacheitem->m_bHasScript2 = pfilesystemcacheitem->m_pfilesysteminterface->file_system_has_script(pfilesystemcacheitem);

   }

   return pfilesystemcacheitem->m_bHasScript2 = _file_system_has_script(pfilesystemcacheitem);

}


bool file_system_interface::_file_system_has_script(const ::file_system_cache_item & pfilesystemcacheitem)
{

   return file_system()->_file_system_has_script(pfilesystemcacheitem);

}


::string file_system_interface::file_system_expanded_md5(const ::file_system_cache_item & pfilesystemcacheitem)
{

   if (pfilesystemcacheitem.nok())
   {

      throw ::exception(error_null_pointer);

   }

   if (::is_set(pfilesystemcacheitem->m_pfilesysteminterface)
      && pfilesystemcacheitem->m_pfilesysteminterface != this)
   {

      return pfilesystemcacheitem->m_pfilesysteminterface->file_system_expanded_md5(pfilesystemcacheitem);

   }

   return _file_system_expanded_md5(pfilesystemcacheitem);

}


::string file_system_interface::_file_system_expanded_md5(const ::file_system_cache_item & pfilesystemcacheitem)
{

   return file_system()->_file_system_expanded_md5(pfilesystemcacheitem);

}


::file_system_cache_item file_system_interface::file_system_item(const ::scoped_string& scopedstrName, ::file_system_real_path_interface* pfilesystemrealpathinterface)
{

   auto pfilesystemcacheitem = file_system()->file_system_item(
      scopedstrName,
      ::is_set(pfilesystemrealpathinterface) ?
      pfilesystemrealpathinterface :
      get_file_system_real_path_interface());

   if (::is_null(pfilesystemcacheitem))
   {

      return { scopedstrName , nullptr};

   }

   pfilesystemcacheitem->m_pfilesysteminterface = this;

   return pfilesystemcacheitem;

}


::file::path file_system_interface::file_system_item_path(const ::scoped_string& scopedstrName, ::file_system_real_path_interface* pfilesystemrealpathinterface)
{

    auto pfilesystemitem = file_system_item(scopedstrName, pfilesystemrealpathinterface);

    if (::is_null(pfilesystemitem))
    {

       return { };

    }

    auto path = pfilesystemitem->path();

    return path;

}


class ::file_system_item* file_system_interface::get_file_system_item(const ::scoped_string& scopedstrName, ::file_system_real_path_interface* pfilesystemrealpathinterface)
{

   auto pfilesystemitem = file_system()->get_file_system_item(
      scopedstrName,
      ::is_set(pfilesystemrealpathinterface) ?
      pfilesystemrealpathinterface :
      get_file_system_real_path_interface());

   if (::is_set(pfilesystemitem))
   {

      pfilesystemitem->m_pfilesysteminterface = this;

   }

   return pfilesystemitem;

}











