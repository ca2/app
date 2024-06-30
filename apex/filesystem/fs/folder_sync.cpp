// From fs/native.cpp to fs/folder_sync.cpp by camilo on 2024-04-28 00:34 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "folder_sync.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/primitive/data/listener.h"
#include "acme/primitive/string/international.h"
#include "acme/filesystem/filesystem/dir_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/context.h"
#include "apex/platform/node.h"


namespace fs
{


   folder_sync::folder_sync()
   {

   }


   folder_sync::~folder_sync()
   {


   }


   // optional if ls_dir is implemented
   bool folder_sync::has_subdir(const ::file::path & path)
   {

      auto pathLocal(path);

      if (!pathLocal.case_insensitive_begins_eat(m_pathProtocol))
      {

         return false;

      }

      pathLocal = m_pathLocalFolder / pathLocal;

      return dir()->has_subdir(pathLocal);

   }


   bool folder_sync::fast_has_subdir(const ::file::path & path)
   {

      auto pathLocal(path);

      if (!pathLocal.case_insensitive_begins_eat(m_pathProtocol))
      {

         return false;

      }

      pathLocal = m_pathLocalFolder / pathLocal;
      
      return dir()->fast_has_subdir(pathLocal);
      
   }


   bool folder_sync::enumerate(::file::listing & listing)
   {

      auto pathLocal(listing.m_pathUser);

      if (!pathLocal.case_insensitive_begins_eat(m_pathProtocol))
      {

         return false;

      }

      pathLocal = m_pathLocalFolder / pathLocal;

      listing.m_pathFinal = pathLocal;

      return dir()->enumerate(listing);

   }


   bool folder_sync::is_link(const ::file::path & path)
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

      //if(m_pcontext->m_papexcontext->os_is_alias(path))
      //{

      //   return true;

      //}

      return false;

   }



   /*::file::listing & folder_sync::ls_relative_name(::file::listing & listing)
   {

      dir()->ls_relative_name(listing);

      return listing;

   }*/



   int folder_sync::is_dir(const ::file::path & path)
   {

      auto pathLocal(path);

      if (!pathLocal.case_insensitive_begins_eat(m_pathProtocol))
      {

         return false;

      }

      pathLocal = m_pathLocalFolder / pathLocal;

      return dir()->is(pathLocal) ? 1 : 0;

   }


   ::file::listing & folder_sync::root_ones(::file::listing & listing)
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


   //string folder_sync::eat_end_level(const ::file::path & path, i32 iCount)
   //{

   //   string strPath(pszPath);

   //   while(iCount > 0)
   //   {

   //      strPath = dir()->name(strPath);

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

      m_pathLocalFolder = m_pcontext->defer_process_path(m_pathProtocol);

   }


   void folder_sync::folder_sync_touch_file(const ::file::path& path)
   {


   }


   bool folder_sync::check_files(
      const ::file::path& pathSourceFolderParam,
      const ::string_array& straSource,
      const ::function < void(const ::scoped_string&) >& callbackStatus)
   {

      auto pathSourceFolder(pathSourceFolderParam);

      if (!pathSourceFolder.case_insensitive_begins_eat(m_pathProtocol))
      {

         return false;

      }

      pathSourceFolder = m_pathLocalFolder / pathSourceFolder;

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

               callbackStatus(pathSource);

            }

            folder_sync_touch_file(pathSource);

            if (!acmefile()->exists(pathSource))
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
      const ::function < void(const ::scoped_string&) >& callbackStatus)
   {

      auto pathSourceFolder(pathSourceFolderParam);

      if (!pathSourceFolder.case_insensitive_begins_eat(m_pathProtocol))
      {

         return;

      }

      pathSourceFolder = m_pathLocalFolder / pathSourceFolder;

      while (true)
      {

         bool bOk = true;

         for (auto& strSource : straSource)
         {

            ::file::path pathSource;

            pathSource = pathSourceFolder / strSource;

            if (!acmefile()->exists(pathSource))
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

               acmefile()->copy(pathTarget, pathSource, true);

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

            if (!acmefile()->exists(pathTarget))
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


   ::string folder_sync::non__empty__file_as_string(const ::payload& payloadFile, const ::function < void(const ::scoped_string&) >& callbackStatus)
   {

      auto pathLocal(payloadFile.as_file_path());

      if (!pathLocal.case_insensitive_begins_eat(m_pathProtocol))
      {

         throw ::exception(error_wrong_state);

      }

      pathLocal = m_pathLocalFolder / pathLocal;

      if (callbackStatus)
      {

         callbackStatus(
            //"Checking for "+pathSourceFile.name() + " at "+pathSourceFile.folder() + "... (index.txt should exist to continue installation with code...)");
            "Checking for " + pathLocal.name() + " at " + pathLocal.folder() + "...");

      }

      while (true)
      {

         if (acmefile()->exists(pathLocal))
         {

            break;

         }

         preempt(1_s);

      }

      if (callbackStatus)
      {

         callbackStatus("Checking if " + pathLocal.name() + " is up-to-date and present...");

      }

      acmedirectory()->change_current(pathLocal.folder());

      ::string strFile;

      while (true)
      {

         strFile = acmefile()->as_string(pathLocal);
         
         auto strTrimmed = strFile.trimmed();

         if (strTrimmed.has_char())
         {

            break;

         }

         preempt(1_s);

      }

      return strFile;

   }


   void folder_sync::wait_folder_contains_files(const ::file::path& pathTargetFolder, const ::string_array& straName, int iMinimumSize, const ::function < void(const ::scoped_string&) >& callbackStatus)
   {

      if (callbackStatus)
      {

         callbackStatus(
            //"Checking for "+pathSourceFile.name() + " at "+pathSourceFile.folder() + "... (index.txt should exist to continue installation with code...)");
            "Checking for files at " + pathTargetFolder + "...");

      }

      while (true)
      {

         if (acmefile()->exists(pathTargetFolder))
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

      acmedirectory()->change_current(pathTargetFolder);

      while (true)
      {

         preempt(1_s);

         bool bOk = true;

         for (auto& line : lines)
         {

            auto pathFile = pathTargetFolder / line;

            if(!acmefile()->exists(pathFile))
            {

               bOk = false;

               break;

            }

            if (iMinimumSize > 0)
            {

               if (acmefile()->get_size(pathFile) < iMinimumSize)
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



   bool folder_sync::file_move(const ::file::path & pszDst,const ::file::path & pszSrc)
   {

      auto pathSource(pszSrc);

      if (!pathSource.case_insensitive_begins_eat(m_pathProtocol))
      {

         return false;

      }

      pathSource = m_pathLocalFolder / pathSource;

      auto pathTarget(pszDst);

      if (!pathTarget.case_insensitive_begins_eat(m_pathProtocol))
      {

         return false;

      }

      pathTarget = m_pathLocalFolder / pathTarget;

      file()->transfer(pathTarget, pathSource);

      return true;

   }


   file_pointer folder_sync::get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* ppfileexception)
   {

      auto pathLocal(payloadFile.as_file_path());

      if (!pathLocal.case_insensitive_begins_eat(m_pathProtocol))
      {

         return nullptr;

      }

      pathLocal = m_pathLocalFolder / pathLocal;


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


   bool folder_sync::file_exists(const ::file::path & path)
   {

      auto pathLocal(path);

      if (!pathLocal.case_insensitive_begins_eat(m_pathProtocol))
      {

         return false;

      }

      pathLocal = m_pathLocalFolder / pathLocal;


      return file()->exists(pathLocal);

   }


} // namespace fs



