// Created by camilo on 2025-10-19 16:54 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "file_system_cache.h"
#include "real_path.h"
#include "acme/platform/node.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"


namespace programming
{


   file_system_cache::file_system_cache()
   {


      m_mapIncludeMatchesFileExists2.InitHashTable(256 * 1024 - 1);
      m_mapIncludeMatchesIsDir2.InitHashTable(256 * 1024 - 1);
      m_mapIncludeHasScript2.InitHashTable(256 * 1024 - 1);
      m_mapIncludeExpandMd5.InitHashTable(256 * 1024 - 1);

   }

   file_system_cache::~file_system_cache()
   {

      
   }


   void file_system_cache::on_initialize_particle()
   {

      defer_create_synchronization();

      ::particle::on_initialize_particle();

      m_pmutexIncludeMatches = node()->create_mutex();
      m_pmutexIncludeHasScript = node()->create_mutex();
      m_pmutexIncludeExpandMd5 = node()->create_mutex();



   }


   void file_system_cache::clear_include_matches(::file::path path)
   {

      try
      {

         _synchronous_lock synchronouslock(m_pmutexIncludeMatches, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         try
         {

            m_mapIncludeMatchesFileExists2.erase(path);

         }
         catch (...)
         {

         }

         try
         {

            m_mapIncludeMatchesIsDir2.erase(path);

         }
         catch (...)
         {

         }

      }
      catch (...)
      {

      }

      try
      {

         _synchronous_lock synchronouslock(m_pmutexIncludeExpandMd5, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         m_mapIncludeExpandMd5.erase(path);

      }
      catch (...)
      {

      }

   }


   void file_system_cache::clear_include_matches()
   {

      try
      {

         _synchronous_lock synchronouslock(m_pmutexIncludeMatches, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         try
         {

            m_mapIncludeMatchesFileExists2.erase_all();

         }
         catch (...)
         {

         }

         try
         {

            m_mapIncludeMatchesIsDir2.erase_all();

         }
         catch (...)
         {

         }

      }
      catch (...)
      {

      }

      try
      {

         _synchronous_lock synchronouslock(m_pmutexIncludeExpandMd5, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         m_mapIncludeExpandMd5.erase_all();

      }
      catch (...)
      {

      }


   }


   bool file_system_cache::include_matches_file_exists(const programming::real_path& realpath)
   {

      _synchronous_lock synchronouslock(m_pmutexIncludeMatches, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto& bExists = m_mapIncludeMatchesFileExists2[realpath.m_pathReal];

      if (!bExists.is_set())
      {

         bExists = file_system()->__exists(realpath.m_pathReal);

      }

      return bExists;

   }


   void file_system_cache::set_include_matches_file_exists(const programming::real_path& realpath, bool bFileExists)
   {

      _synchronous_lock synchronouslock(m_pmutexIncludeMatches, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      m_mapIncludeMatchesFileExists2.set_at(realpath.m_pathReal, bFileExists);

   }


   bool file_system_cache::include_matches_is_dir(const programming::real_path& realpath)
   {

      _synchronous_lock synchronouslock(m_pmutexIncludeMatches, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto& bIsDir = m_mapIncludeMatchesIsDir2[realpath.m_pathReal];

      if (!bIsDir.is_set())
      {

         bIsDir = directory_system()->__is(realpath.m_pathReal);

      }

      return bIsDir;

   }


   bool file_system_cache::include_has_script(const programming::real_path& realpath)
   {

      if (!realpath.is_ok())
      {

         return false;

      }

      _synchronous_lock synchronouslock(m_pmutexIncludeHasScript, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto& bHasScript = m_mapIncludeHasScript2[realpath.m_pathReal];

      if (!bHasScript.is_set())
      {

         bHasScript = file_system()->__safe_find_string(realpath.m_pathReal, "<?") >= 0;

      }

      return bHasScript;

   }


   string file_system_cache::include_expand_md5(const programming::real_path& realpath)
   {

      _synchronous_lock synchronouslock(m_pmutexIncludeExpandMd5, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      return m_mapIncludeExpandMd5[realpath.m_pathReal];

   }


   void file_system_cache::set_include_expand_md5(const programming::real_path& realpath, const ::scoped_string& scopedstrMd5)
   {

      _synchronous_lock synchronouslock(m_pmutexIncludeExpandMd5, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      m_mapIncludeExpandMd5[realpath.m_pathReal] = scopedstrMd5;

   }


} // namespace programming


