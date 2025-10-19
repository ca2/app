// Created by camilo on 2025-10-19 16:54 <3ThomasBorregaardSørensen!!
// From programming by camilo on 2025-10-19 17:27 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
#include "framework.h"
#include "file_system_cache.h"
#include "file_system_cache_item.h"
#include "acme/platform/node.h"


file_system_cache::file_system_cache()
{

   m_mapFileSystemItem.InitHashTable(256 * 1024 - 1);
   //m_mapIncludeMatchesFileExists2.InitHashTable(256 * 1024 - 1);
   //m_mapIncludeMatchesIsDir2.InitHashTable(256 * 1024 - 1);
   //m_mapIncludeHasScript2.InitHashTable(256 * 1024 - 1);
   //m_mapIncludeExpandMd5.InitHashTable(256 * 1024 - 1);

}

file_system_cache::~file_system_cache()
{


}


void file_system_cache::on_initialize_particle()
{

   defer_create_synchronization();

   ::particle::on_initialize_particle();

   //m_pmutexRealPath = node()->create_mutex();
   //m_pmutexIncludeHasScript = node()->create_mutex();
   //m_pmutexRealPath = node()->create_mutex();
   m_pmutexFileSystemItem = node()->create_mutex();



}


void file_system_cache::clear_file_system_cache_item(const ::scoped_string & scopedstrName)
{

   try
   {

      _synchronous_lock synchronouslock(m_pmutexFileSystemItem, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      try
      {

         m_mapFileSystemItem.erase(scopedstrName);

      }
      catch (...)
      {

      }

   }
   catch (...)
   {

   }

}


void file_system_cache::clear_file_system_cache()
{

   try
   {

      _synchronous_lock synchronouslock(m_pmutexFileSystemItem, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      try
      {

         m_mapFileSystemItem.erase_all();

      }
      catch (...)
      {

      }

   }
   catch (...)
   {


   }

}


//bool file_system_cache::include_matches_file_exists(const ::file_system_cache_item& filesystemcacheitem)
//{
//
//   _synchronous_lock synchronouslock(m_pmutexRealPath, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//   auto& filesystemcacheitem = m_mapRealPath[filesystemcacheitem.path()];
//
//   if (!filesystemcacheitem.m_bFileExists2.is_set())
//   {
//
//      filesystemcacheitem.m_bFileExists2 = m_pfilesysteminterface->include_matches_file_exists(filesystemcacheitem);
//
//   }
//
//   return filesystemcacheitem.m_bFileExists2;
//
//}
//
//
//void file_system_cache::set_include_matches_file_exists(const ::file_system_cache_item& filesystemcacheitem, bool bFileExists)
//{
//
//   _synchronous_lock synchronouslock(m_pmutexRealPath, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//   m_mapIncludeMatchesFileExists2.set_at(filesystemcacheitem.m_pathReal, bFileExists);
//
//}
//
//
//bool file_system_cache::include_matches_is_dir(const ::file_system_cache_item& filesystemcacheitem)
//{
//
//   _synchronous_lock synchronouslock(m_pmutexRealPath, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//   auto& bIsDir = m_mapIncludeMatchesIsDir2[filesystemcacheitem.m_pathReal];
//
//   if (!bIsDir.is_set())
//   {
//
//      bIsDir = m_pfilesysteminterface->include_matches_is_dir(filesystemcacheitem);
//
//   }
//
//   return bIsDir;
//
//}
//
//
//bool file_system_cache::include_has_script(const ::file_system_cache_item& filesystemcacheitem)
//{
//
//   if (!filesystemcacheitem.is_ok())
//   {
//
//      return false;
//
//   }
//
//   _synchronous_lock synchronouslock(m_pmutexIncludeHasScript, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//   auto& bHasScript = m_mapIncludeHasScript2[filesystemcacheitem.m_pathReal];
//
//   if (!bHasScript.is_set())
//   {
//
//      bHasScript = m_pfilesysteminterface->include_has_script(filesystemcacheitem);
//
//   }
//
//   return bHasScript;
//
//}
//
//
//string file_system_cache::include_expand_md5(const ::file_system_cache_item& filesystemcacheitem)
//{
//
//   _synchronous_lock synchronouslock(m_pmutexRealPath, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//   return m_mapIncludeExpandMd5[filesystemcacheitem.m_pathReal];
//
//}
//
//
//void file_system_cache::set_include_expand_md5(const ::file_system_cache_item& filesystemcacheitem, const ::scoped_string& scopedstrMd5)
//{
//
//   _synchronous_lock synchronouslock(m_pmutexRealPath, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//   m_mapIncludeExpandMd5[filesystemcacheitem.m_pathReal] = scopedstrMd5;
//
//}


file_system_cache_item file_system_cache::file_system_item(const ::scoped_string & scopedstrName, ::file_system_interface* pfilesysteminterface)
{

   _synchronous_lock synchronouslock(m_pmutexFileSystemItem, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   auto & pfilesystemitem = m_mapFileSystemItem[scopedstrName];

   if (!pfilesystemitem)
   {

      pfilesystemitem = _file_system_item(scopedstrName, pfilesysteminterface);
      
   }

   return { scopedstrName, pfilesystemitem };

}



