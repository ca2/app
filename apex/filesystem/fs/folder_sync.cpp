// From fs/native.cpp to fs/folder_sync.cpp by camilo on 2024-04-28 00:34 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "folder_sync.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/prototype/data/listener.h"
#include "acme/prototype/string/international.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/context.h"
#include "apex/platform/node.h"


namespace fs
{


   folder_sync::folder_sync()
   {

      m_timeRestartTimeout = 40_s;

      m_timeOperationThrottlingTime = 5_s;

      m_iStableOkCount = 0;

   }


   folder_sync::~folder_sync()
   {


   }


   // optional if ls_dir is implemented
   bool folder_sync::has_subdir(const ::file::path& path)
   {

      auto pathLocal(path);

      if (!pathLocal.case_insensitive_begins_eat(m_pathProtocol))
      {

         return false;

      }

      pathLocal = local_folder_path() / pathLocal;

      return directory()->has_subdir(pathLocal);

   }


   bool folder_sync::fast_has_subdir(const ::file::path& path)
   {

      auto pathLocal(path);

      if (!pathLocal.case_insensitive_begins_eat(m_pathProtocol))
      {

         return false;

      }

      pathLocal = local_folder_path() / pathLocal;

      return directory()->fast_has_subdir(pathLocal);

   }


   bool folder_sync::enumerate(::file::listing& listing)
   {

      auto pathLocal(listing.m_pathUser);

      if (!pathLocal.case_insensitive_begins_eat(m_pathProtocol))
      {

         return false;

      }

      pathLocal = local_folder_path() / pathLocal;

      listing.m_pathFinal = pathLocal;

      return directory()->enumerate(listing);

   }


   bool folder_sync::is_link(const ::file::path& path)
   {

      //auto pathLocal(path);

      //if (!pathLocal.case_insensitive_begins_eat(m_pathProtocol))
      //{

      //   return false;

      //}

      //pathLocal = m_pathLocalFolder / pathLocal;

      //if(::fs::data::is_link(pathLocal))
      //{

      //   return true;

      //}

      //if(m_papplication->os_is_alias(path))
      //{

      //   return true;

      //}

      return false;

   }


   bool folder_sync::has_operation_error()
   {

      return false;

   }


   /*::file::listing & folder_sync::ls_relative_name(::file::listing & listing)
   {

      directory()->ls_relative_name(listing);

      return listing;

   }*/


   int folder_sync::is_dir(const ::file::path& path)
   {

      auto pathLocal(path);

      if (!pathLocal.case_insensitive_begins_eat(m_pathProtocol))
      {

         return false;

      }

      pathLocal = local_folder_path() / pathLocal;

      return directory()->is(pathLocal) ? 1 : 0;

   }


   ::file::listing& folder_sync::root_ones(::file::listing& listing)
   {

      auto pathLocal = m_pathProtocol;

      listing.m_pathUser = pathLocal;

      node()->m_papexnode->root_ones(listing);

      return listing;

   }


   //void folder_sync::get_ascendants_path(const ::file::path & pszPath,::file::path_array & stra)
   //{

   //   return file()->get_ascendants_path(pszPath, stra);

   //}


   //void folder_sync::get_ascendants_name(const ::file::path & path,::file::path_array & straParam)

   //{

   //   return file()->get_ascendants_name(pcsz, straParam);


   //}


   //string folder_sync::eat_end_level(const ::file::path & path, int iCount)
   //{

   //   string strPath(pszPath);

   //   while(iCount > 0)
   //   {

   //      strPath = directory()->name(strPath);

   //      iCount--;

   //   }

   //   return strPath;

   //}


   //string folder_sync::file_name(const ::file::path & path)
   //{

   //   return file()->name_(pszPath);

   //}


   //string folder_sync::dir_path(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstr2)
   //{

   //   return ::file::path(psz1) / ::file::path(psz2);

   //}


   void folder_sync::on_initialize_particle()
   {

      ::fs::data::on_initialize_particle();

      //m_pathLocalFolder = m_papplication->defer_process_path(m_pathProtocol);

   }


   ::file::path folder_sync::local_path(const ::file::path& path)
   {

      auto pathProcessed(path);

      if (!pathProcessed.begins_eat(m_pathProtocol))
      {

         throw ::exception(error_wrong_state);

      }

      pathProcessed = local_folder_path() / pathProcessed;

      return ::transfer(pathProcessed);

   }


   void folder_sync::folder_sync_touch_file(const ::file::path& path,
                                            const ::function<void(const ::scoped_string&)>& callbackStatus)
   {


   }


   bool folder_sync::check_files(
      const ::file::path& pathSourceFolderParam,
      const ::string_array& straSource,
      const ::function<void(const ::scoped_string&)>& callbackStatus)
   {

      auto pathSourceFolder(pathSourceFolderParam);

      if (!pathSourceFolder.case_insensitive_begins_eat(m_pathProtocol))
      {

         return false;

      }

      pathSourceFolder = local_folder_path() / pathSourceFolder;

      bool bOk = false;

      while (true)
      {

         bOk = true;

         for (auto& strSource : straSource)
         {

            ::file::path pathSource;

            pathSource = pathSourceFolder / strSource;

            if (callbackStatus)
            {

               ::string strMessage;

               strMessage.formatf("Checking file %s", pathSource.c_str());

               callbackStatus(strMessage);

            }

            folder_sync_touch_file(pathSource, callbackStatus);

            if (!file_system()->exists(pathSource))
            {

               if (callbackStatus)
               {

                  callbackStatus(pathSource + " doesn't exist");

               }

               preempt(1_s);

               bOk = false;

               break;

            }

         }

         if (bOk)
         {

            break;

         }

      }

      preempt(5_s);

      return bOk;

   }


   void folder_sync::copy_files_out(
      const ::file::path& pathTargetFolder,
      const ::file::path& pathSourceFolderParam,
      const ::string_array& straSource,
      const ::function<void(const ::scoped_string&)>& callbackStatus)
   {

      auto pathSourceFolder(pathSourceFolderParam);

      if (!pathSourceFolder.case_insensitive_begins_eat(m_pathProtocol))
      {

         return;

      }

      pathSourceFolder = local_folder_path() / pathSourceFolder;

      while (true)
      {

         bool bOk = true;

         for (auto& strSource : straSource)
         {

            ::file::path pathSource;

            pathSource = pathSourceFolder / strSource;

            if (!file_system()->exists(pathSource))
            {

               if (callbackStatus)
               {

                  callbackStatus(pathSource + " doesn't exist");

               }

               bOk = false;

               break;

            }

            ::file::path pathTarget;

            pathTarget = pathTargetFolder / strSource;

            try
            {

               file_system()->copy(pathTarget, pathSource, true);

            }
            catch (...)
            {

               if (callbackStatus)
               {

                  callbackStatus("Failed to copy from" + pathSource + " to " + pathTarget);

               }

               bOk = false;

               break;

            }

            if (!file_system()->exists(pathTarget))
            {

               if (callbackStatus)
               {

                  callbackStatus(pathTarget + " doesn't exist");

               }

               bOk = false;

               break;

            }

         }

         if (bOk)
         {

            break;

         }

         preempt(1_s);

      }

   }


   ::string folder_sync::non__empty__file_as_string(const ::payload& payloadFile,
                                                    const ::function<void(const ::scoped_string&)>& callbackStatus)
   {

      auto pathLocal(payloadFile.as_file_path());

      if (!pathLocal.case_insensitive_begins_eat(m_pathProtocol))
      {

         throw ::exception(error_wrong_state);

      }

      pathLocal = local_folder_path() / pathLocal;

      if (callbackStatus)
      {

         callbackStatus(
            //"Checking for "+pathSourceFile.name() + " at "+pathSourceFile.folder() + "... (index.txt should exist to continue installation with code...)");
            "Checking for " + pathLocal.name() + " at " + pathLocal.folder() + "...");

      }

      while (true)
      {

         if (file_system()->exists(pathLocal))
         {

            break;

         }

         preempt(1_s);

      }

      if (callbackStatus)
      {

         callbackStatus("Checking if " + pathLocal.name() + " is up-to-date and present...");

      }

      directory_system()->change_current(pathLocal.folder());

      ::string strFile;

      while (true)
      {

         strFile = file_system()->as_string(pathLocal);

         auto strTrimmed = strFile.trimmed();

         if (strTrimmed.has_char())
         {

            break;

         }

         preempt(1_s);

      }

      return strFile;

   }


   void folder_sync::wait_folder_contains_files(const ::file::path& pathTargetFolder, const ::string_array& straName,
                                                int iMinimumSize,
                                                const ::function<void(const ::scoped_string&)>& callbackStatus)
   {

      if (callbackStatus)
      {

         callbackStatus(
            //"Checking for "+pathSourceFile.name() + " at "+pathSourceFile.folder() + "... (index.txt should exist to continue installation with code...)");
            "Checking for files at " + pathTargetFolder + "...");

      }

      while (true)
      {

         if (file_system()->exists(pathTargetFolder))
         {

            break;

         }

         preempt(1_s);

      }

      if (callbackStatus)
      {

         callbackStatus("Checking if " + pathTargetFolder + " has all files...");

      }

      ::string_array lines;

      lines = straName;

      directory_system()->change_current(pathTargetFolder);

      while (true)
      {

         preempt(1_s);

         bool bOk = true;

         for (auto& line : lines)
         {

            auto pathFile = pathTargetFolder / line;

            if (!file_system()->exists(pathFile))
            {

               bOk = false;

               break;

            }

            if (iMinimumSize > 0)
            {

               if (file_system()->get_size(pathFile) < iMinimumSize)
               {

                  bOk = false;

                  break;

               }

            }

         }

         if (bOk)
         {

            break;

         }

      }

   }


   ::file::path folder_sync::local_folder_path()
   {

      if (m_pathLocalFolder2.is_empty())
      {

         m_pathLocalFolder2 = m_papplication->defer_process_path(m_pathProtocol);

         if (m_pathLocalFolder2.contains("://"))
         {

            m_pathLocalFolder2.empty();

         }

      }

      return m_pathLocalFolder2;

   }


   void folder_sync::defer_start_daemon(const ::function<void(const ::scoped_string&)>& callbackStatus)
   {

      if (m_timeLastStart.elapsed() > m_timeRestartTimeout)
      {

         start_daemon(callbackStatus);

         m_timeLastStart.Now();

      }

   }


   void folder_sync::defer_throttle_operation()
   {

      auto elapsed = m_timeLastOperation.elapsed();

      auto remaining = m_timeOperationThrottlingTime - elapsed;

      if (remaining.m_iSecond > 0)
      {

         preempt(remaining);

      }

      m_timeLastOperation.Now();

   }


   string_array folder_sync::ls(const file::path& pathCloud, const ::function<void(const ::scoped_string&)>& callbackStatus)
   {
      return {};
   }


   string_array folder_sync::ls_folder(const file::path& pathCloud, const ::function<void(const ::scoped_string&)>& callbackStatus)
   {
      return {};
   }


   void folder_sync::sync_exclude(const string_array& stra, const ::function<void(const ::scoped_string&)>& callbackStatus)
   {


   }


   void folder_sync::sync_reinclude(const string_array& stra, const ::function<void(const ::scoped_string&)>& callbackStatus)
   {

   }


   string_array folder_sync::sync_exclusion_list(const ::function<void(const ::scoped_string&)>& callbackStatus)
   {
      return {};
   }


   void folder_sync::start_daemon(const ::function<void(const ::scoped_string&)>& callbackStatus)
   {
   }


   bool folder_sync::file_move(const ::file::path& pszDst, const ::file::path& pszSrc)
   {

      auto pathSource(pszSrc);

      if (!pathSource.case_insensitive_begins_eat(m_pathProtocol))
      {

         return false;

      }

      pathSource = local_folder_path() / pathSource;

      auto pathTarget(pszDst);

      if (!pathTarget.case_insensitive_begins_eat(m_pathProtocol))
      {

         return false;

      }

      pathTarget = local_folder_path() / pathTarget;

      file()->transfer(pathTarget, pathSource);

      return true;

   }


   file_pointer folder_sync::get_file(const ::payload& payloadFile, ::file::e_open eopen,
                                      ::pointer<::file::exception>* ppfileexception)
   {

      auto pathLocal(payloadFile.as_file_path());

      if (!pathLocal.case_insensitive_begins_eat(m_pathProtocol))
      {

         return nullptr;

      }

      pathLocal = local_folder_path() / pathLocal;

      file_pointer pfile;

      //if (eopen & ::file::e_open_text)
      //{

      //   pfile = __create_new<::stdio_file>();

      //}
      //else
      //{

      __construct(pfile);

      //      }

      //auto result =
      pfile->open(pathLocal, eopen);

      //if(!result)
      //{

      //   return result;

      //}

      return pfile;

   }


   bool folder_sync::file_exists(const ::file::path& path)
   {

      auto pathLocal(path);

      if (!pathLocal.case_insensitive_begins_eat(m_pathProtocol))
      {

         return false;

      }

      pathLocal = local_folder_path() / pathLocal;

      return file()->exists(pathLocal);

   }


   void folder_sync::wait_up_and_running(const ::function<void(const ::scoped_string&)>& callbackStatus)
   {


   }


   bool folder_sync::_cloud_defer_check_file_txt(::file::path& pathTarget, const ::file::path& pathCloudFile,
                                                 bool bForce, ::file::path* ppathSource,
                                                 const ::function<void(const ::scoped_string&)>& callbackStatus)
   {

      return false;

   }


   ::string_array folder_sync::_cloud_get_file_txt_lines(const ::file::path& pathCloudFile, bool bForce,
                                                         ::file::path* ppathTarget, ::file::path* ppathSource,
                                                         const ::function<void(const ::scoped_string&)>& callbackStatus)
   {

      return {};

   }


   ::file::path folder_sync::_cloud_ensure_file_txt_is_up_to_date_and_present(
      const ::file::path& pathCloudFile, const ::function<void(const ::scoped_string&)>& callbackStatus)
   {

      return {};

   }


   ::file::path folder_sync::_cloud_ensure_files_in_file_txt_are_up_to_date_and_present(
      const ::file::path& pathCloudFile, const ::scoped_string& scopedstrFileExtension,
      int iMinimumFileSize, const ::function<void(const ::scoped_string&)>& callbackStatus)
   {

      return {};

   }


   void folder_sync::_cloud_ensure_files_are_up_to_date_and_present(
      const ::file::path& pathFolder, const ::string_array & stra,
      int iMinimumFileSize, const ::function<void(const ::scoped_string&)>& callbackStatus)
   {


   }



} // namespace fs
