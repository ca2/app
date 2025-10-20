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


::file_system_real_path_interface* file_system_interface::get_file_system_real_path_interface()
{

   return nullptr;

}


bool file_system_interface::file_system_file_exists(::file_system_item * pfilesystemitem)
{

   if (::is_null(pfilesystemitem))
   {

      throw ::exception(error_null_pointer);

   }

   if (::is_set(pfilesystemitem->m_pfilesysteminterface)
      && pfilesystemitem->m_pfilesysteminterface != this)
   {

      return pfilesystemitem->m_pfilesysteminterface->file_system_file_exists(pfilesystemitem);

   }

   return _file_system_file_exists(pfilesystemitem);

}


bool file_system_interface::_file_system_file_exists(::file_system_item* pfilesystemitem)
{

   return false;

}


bool file_system_interface::file_system_is_folder(::file_system_item* pfilesystemitem)
{

   if (::is_null(pfilesystemitem))
   {

      throw ::exception(error_null_pointer);

   }

   if (::is_set(pfilesystemitem->m_pfilesysteminterface)
      && pfilesystemitem->m_pfilesysteminterface != this)
   {

      return pfilesystemitem->m_pfilesysteminterface->file_system_is_folder(pfilesystemitem);

   }

   return _file_system_is_folder(pfilesystemitem);

}


bool file_system_interface::_file_system_is_folder(::file_system_item* pfilesystemitem)
{

   return false;

}


bool file_system_interface::file_system_has_script(::file_system_item * pfilesystemitem)
{

   if (::is_null(pfilesystemitem))
   {

      throw ::exception(error_null_pointer);

   }

   if (::is_set(pfilesystemitem->m_pfilesysteminterface)
      && pfilesystemitem->m_pfilesysteminterface != this)
   {

      return pfilesystemitem->m_pfilesysteminterface->file_system_has_script(pfilesystemitem);

   }

   return _file_system_has_script(pfilesystemitem);

}


bool file_system_interface::_file_system_has_script(::file_system_item* pfilesystemitem)
{

   return {};

}


::string file_system_interface::file_system_expanded_md5(::file_system_item* pfilesystemitem)
{

   if (::is_null(pfilesystemitem))
   {

      throw ::exception(error_null_pointer);

   }

   if (::is_set(pfilesystemitem->m_pfilesysteminterface)
      && pfilesystemitem->m_pfilesysteminterface != this)
   {

      return pfilesystemitem->m_pfilesysteminterface->file_system_expanded_md5(pfilesystemitem);

   }

   return _file_system_expanded_md5(pfilesystemitem);

}


::string file_system_interface::_file_system_expanded_md5(::file_system_item* pfilesystemitem)
{

   return {};

}


::file_system_cache_item file_system_interface::file_system_item(const ::scoped_string& scopedstrName, ::file_system_real_path_interface* pfilesystemrealpathinterface)
{

   auto filesystemcacheitem = file_system()->file_system_item(
      scopedstrName,
      ::is_set(pfilesystemrealpathinterface) ?
      pfilesystemrealpathinterface :
      get_file_system_real_path_interface());

   filesystemcacheitem->m_pfilesysteminterface = this;

   return filesystemcacheitem;

}


class ::file_system_item* file_system_interface::get_file_system_item(const ::scoped_string& scopedstrName, ::file_system_real_path_interface* pfilesystemrealpathinterface)
{

   auto pfilesystemitem = file_system()->get_file_system_item(
      scopedstrName,
      ::is_set(pfilesystemrealpathinterface) ?
      pfilesystemrealpathinterface :
      get_file_system_real_path_interface());

   pfilesystemitem->m_pfilesysteminterface = this;

   return pfilesystemitem;

}











