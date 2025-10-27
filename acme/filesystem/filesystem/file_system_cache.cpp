// Created by camilo on 2025-10-19 16:54 <3ThomasBorregaardSørensen!!
// From programming by camilo on 2025-10-19 17:27 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
#include "framework.h"
#include "file_system_cache.h"
#include "file_system_cache_item.h"
#include "acme/platform/node.h"


file_system_cache::file_system_cache()
{


   m_mapFileSystemCacheItem.InitHashTable(256 * 1024 - 1);



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


//bool file_system_cache::file_system_file_exists(const ::file_system_cache_item& pfilesystemcacheitem)
//{
//
//   _synchronous_lock synchronouslock(m_pmutexRealPath, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//   auto& pfilesystemcacheitem = m_mapRealPath[pfilesystemcacheitem.path()];
//
//   if (!pfilesystemcacheitem.m_bFileExists2.is_set())
//   {
//
//      pfilesystemcacheitem.m_bFileExists2 = m_pfilesysteminterface->file_system_file_exists(pfilesystemcacheitem);
//
//   }
//
//   return pfilesystemcacheitem.m_bFileExists2;
//
//}
//
//
//void file_system_cache::set_include_matches_file_exists(const ::file_system_cache_item& pfilesystemcacheitem, bool bFileExists)
//{
//
//   _synchronous_lock synchronouslock(m_pmutexRealPath, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//   m_mapIncludeMatchesFileExists2.set_at(pfilesystemcacheitem.m_pathReal, bFileExists);
//
//}
//
//
//bool file_system_cache::file_system_is_folder(const ::file_system_cache_item& pfilesystemcacheitem)
//{
//
//   _synchronous_lock synchronouslock(m_pmutexRealPath, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//   auto& bIsDir = m_mapIncludeMatchesIsDir2[pfilesystemcacheitem.m_pathReal];
//
//   if (!bIsDir.is_set())
//   {
//
//      bIsDir = m_pfilesysteminterface->file_system_is_folder(pfilesystemcacheitem);
//
//   }
//
//   return bIsDir;
//
//}
//
//
//bool file_system_cache::file_system_has_script(const ::file_system_cache_item& pfilesystemcacheitem)
//{
//
//   if (!pfilesystemcacheitem.is_ok())
//   {
//
//      return false;
//
//   }
//
//   _synchronous_lock synchronouslock(m_pmutexIncludeHasScript, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//   auto& bHasScript = m_mapIncludeHasScript2[pfilesystemcacheitem.m_pathReal];
//
//   if (!bHasScript.is_set())
//   {
//
//      bHasScript = m_pfilesysteminterface->file_system_has_script(pfilesystemcacheitem);
//
//   }
//
//   return bHasScript;
//
//}
//
//
//string file_system_cache::file_system_expanded_md5(const ::file_system_cache_item& pfilesystemcacheitem)
//{
//
//   _synchronous_lock synchronouslock(m_pmutexRealPath, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//   return m_mapIncludeExpandMd5[pfilesystemcacheitem.m_pathReal];
//
//}
//
//
//void file_system_cache::set_include_expand_md5(const ::file_system_cache_item& pfilesystemcacheitem, const ::scoped_string& scopedstrMd5)
//{
//
//   _synchronous_lock synchronouslock(m_pmutexRealPath, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//   m_mapIncludeExpandMd5[pfilesystemcacheitem.m_pathReal] = scopedstrMd5;
//
//}


file_system_cache_item file_system_cache::file_system_item(
   const ::scoped_string & scopedstrName, 
   ::file_system_real_path_interface* pfilesystemrealpathinterface,
   ::file_system_interface* pfilesysteminterface)
{

   _synchronous_lock synchronouslock(m_pmutexFileSystemItem, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   auto & pfilesystemitem = m_mapFileSystemItem[scopedstrName];

   if (pfilesystemitem.m_estatus != success_already_set)
   {

      synchronouslock.unlock();

      auto pfilesystemitemNew = pfilesysteminterface->file_system_item(scopedstrName, pfilesystemrealpathinterface);

      synchronouslock._lock();

      pfilesystemitem = pfilesystemitemNew;

      pfilesystemitem.m_estatus = success_already_set;
      
   }

   return { scopedstrName, pfilesystemitem };

}



