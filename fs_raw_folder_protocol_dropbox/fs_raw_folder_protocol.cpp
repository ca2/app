// From fs/folder_sync.cpp to folder_sync.cpp by camilo on 2024-04-28 00:55 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "fs_raw_folder_protocol.h"
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


namespace fs_raw_folder_protocol_dropbox
{


   folder::folder()
   {


   }


   folder::~folder()
   {


   }

//   folder_sync::folder_sync()
//   {
//
//      m_iLastExitCode = 0;
//
//      m_pathProtocol = "dropbox://";
//
//   }
//
//
//   folder_sync::~folder_sync()
//   {
//
//
//   }
//
//
//
//
//   void folder_sync::folder_sync_touch_file(const ::file::path& pathParam, const ::function < void(const ::scoped_string&) >& callbackStatus)
//   {
//
//      auto path(pathParam);
//
//      if (!path.case_insensitive_begins_eat(m_pathProtocol)
//         && !path.case_insensitive_begins_eat(local_folder_path()))
//      {
//
//         return;
//
//      }
//
//      char buffer[1_KiB];
//
//      path = local_folder_path() / path;
//
//      for (int iTry = 0; iTry < 5; iTry++)
//      {
//
//         try
//         {
//
//            auto pfile = file()->get_file(path, ::file::e_open_read | ::file::e_open_binary);
//
//            // touch entire file
//
//            while (pfile->read(buffer, sizeof(buffer)) > 0);
//
//            break;
//
//         }
//         catch (...)
//         {
//
//            if(callbackStatus)
//            {
//
//               ::string strMessage;
//
//               strMessage.formatf("exception with %s", path.c_str());
//
//               callbackStatus(strMessage);
//
//            }
//
//         }
//
//         preempt((iTry + 1) * 5_s);
//
//      }
//
//   }
//
//
//   bool folder_sync::check_files(
//      const ::file::path& pathSourceFolder,
//      const ::string_array& straSource,
//      const ::function < void(const ::scoped_string&) >& callbackStatus)
//   {
//
//      return ::fs::folder_sync::check_files(pathSourceFolder, straSource, callbackStatus);
//
//   }
//
//
//   void folder_sync::copy_files_out(
//      const ::file::path& pathTargetFolder,
//      const ::file::path& pathSourceFolderParam,
//      const ::string_array& straSource,
//      const ::function < void(const ::scoped_string&) >& callbackStatus)
//   {
//
//      ::fs::folder_sync::copy_files_out(pathTargetFolder, pathSourceFolderParam, straSource, callbackStatus);
//
//   }
//
//
//   // optional if ls_dir is implemented
//   bool folder_sync::has_subdir(const ::file::path& path)
//   {
//
//      return ::fs::folder_sync::has_subdir(path);
//
//   }
//
//
//   bool folder_sync::fast_has_subdir(const ::file::path& path)
//   {
//
//      return ::fs::folder_sync::fast_has_subdir(path);
//
//   }
//
//
//   bool folder_sync::enumerate(::file::listing& listing)
//   {
//
//      return ::fs::folder_sync::enumerate(listing);
//
//   }
//
//
//   bool folder_sync::is_link(const ::file::path& path)
//   {
//
//      return ::fs::folder_sync::is_link(path);
//
//   }
//
//
//
//   /*::file::listing & folder_sync::ls_relative_name(::file::listing & listing)
//   {
//
//      directory()->ls_relative_name(listing);
//
//      return listing;
//
//   }*/
//
//
//
//   int folder_sync::is_dir(const ::file::path& path)
//   {
//
//      return ::fs::folder_sync::is_dir(path);
//
//   }
//
//
//   ::file::listing& folder_sync::root_ones(::file::listing& listing)
//   {
//
//      return ::fs::folder_sync::root_ones(listing);
//
//   }
//
//
//   //void folder_sync::get_ascendants_path(const ::file::path & pszPath,::file::path_array & stra)
//   //{
//
//   //   return file()->get_ascendants_path(pszPath, stra);
//
//   //}
//
//
//   //void folder_sync::get_ascendants_name(const ::file::path & path,::file::path_array & straParam)
//
//   //{
//
//   //   return file()->get_ascendants_name(pcsz, straParam);
//
//
//   //}
//
//
//   //string folder_sync::eat_end_level(const ::file::path & path, int iCount)
//   //{
//
//   //   string strPath(pszPath);
//
//   //   while(iCount > 0)
//   //   {
//
//   //      strPath = directory()->name(strPath);
//
//   //      iCount--;
//
//   //   }
//
//   //   return strPath;
//
//   //}
//
//
//   //string folder_sync::file_name(const ::file::path & path)
//   //{
//
//   //   return file()->name_(pszPath);
//
//   //}
//
//
//   //string folder_sync::dir_path(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstr2)
//   //{
//
//   //   return ::file::path(psz1) / ::file::path(psz2);
//
//   //}
//
//
//   bool folder_sync::file_move(const ::file::path& pszDst, const ::file::path& pszSrc)
//   {
//
//      return ::fs::folder_sync::file_move(pszDst, pszSrc);
//
//   }
//
//
//   file_pointer folder_sync::get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* ppfileexception)
//   {
//
//      return ::fs::folder_sync::get_file(payloadFile, eopen, ppfileexception);
//
//   }
//
//
//   bool folder_sync::file_exists(const ::file::path& path)
//   {
//
//      return ::fs::folder_sync::file_exists(path);
//
//   }
//
//
//   ::string folder_sync::non__empty__file_as_string(const ::payload& payloadFile, const ::function < void(const ::scoped_string&) >& callbackStatus)
//   {
//
//#if defined(LINUX)
//
//      auto pathLocal(payloadFile.as_file_path());
//
//      if (!pathLocal.case_insensitive_begins_eat(m_pathProtocol))
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      pathLocal = local_folder_path() / pathLocal;
//
//      ::file::path pathDropboxBin = directory_system()->home() / "bin/dropbox";
//
//      ::string strDropboxCommand(pathDropboxBin);
//
//      //::file::path pathIndex = directory_system()->home() / ".config/integration/code/___repositories/index.txt";
//
//      //auto pathSourceFolder = pathFolder / "Dropbox/box/___repositories";
//
//      //auto pathSourceIndex = pathSourceFolder / "index.txt";
//
//      if (callbackStatus)
//      {
//
//         callbackStatus(
//            //"Checking for "+pathSourceFile.name() + " at "+pathSourceFile.folder() + "... (index.txt should exist to continue installation with code...)");
//            "Checking for " + pathLocal.name() + " at " + pathLocal.folder() + "...");
//
//      }
//
//      while (true)
//      {
//
//         if (file_system()->exists(pathLocal))
//         {
//
//            break;
//
//         }
//
//         preempt(1_s);
//
//      }
//
//      if(callbackStatus)
//      {
//
//         callbackStatus("Checking if " + pathLocal.name() + " is up-to-date and present...");
//
//      }
//
//      ::string strFile;
//
//      ::string_array lines;
//
//      lines.add(pathLocal.name());
//
//      auto pathLocalFolder = pathLocal.folder();
//
//      directory_system()->change_current(pathLocalFolder);
//
//      while (true)
//      {
//
//         preempt(1_s);
//
//         ::string strLs;
//
//         int iExitCode = node()->get_posix_shell_command_output(strLs, strDropboxCommand + " dropbox filestatus");
//
//         auto pszLs = strLs.c_str();
//
//         print_line(pszLs);
//
//         ::string_array stra;
//
//         stra.add_lines(pszLs);
//
//         bool bOk = true;
//
//         for (auto& line : lines)
//         {
//
//            auto pszLine = line.c_str();
//
//            int iFind = stra.case_insensitive_find_first_begins(line + ":");
//
//            if (iFind < 0)
//            {
//
//               bOk = false;
//
//               break;
//
//            }
//
//            auto dropboxLine = stra[iFind];
//
//            if (!dropboxLine.case_insensitive_ends("up to date"))
//            {
//
//               bOk = false;
//
//               break;
//
//            }
//
//            auto pathFile = pathLocalFolder / line;
//
//            if (!file_system()->exists(pathFile))
//            {
//
//               bOk = false;
//
//               break;
//
//            }
//
//            strFile = file_system()->as_string(pathFile);
//
//            auto strTrimmed = strFile.trimmed();
//
//            if (strTrimmed.is_empty())
//            {
//
//               bOk = false;
//
//               break;
//
//            }
//
//         }
//
//         if (bOk)
//         {
//
//            break;
//
//         }
//
//      }
//
//      return strFile;
//
//#else
//
//      return ::fs::folder_sync::non__empty__file_as_string(payloadFile, callbackStatus);
//
//#endif
//
//   }
//
//   ::file::path folder::calculate_raw_folder_base_path()
//   {
//
//      return {};
//
//   }
//
//
//
//   //void node::calculate_dropbox_installed()
//   //{
//
//   //   m_bDropbox = false;
//
//   //   m_pathDropbox.empty();
//
//   //   m_bDropboxCalculated = true;
//
//   //   __check_refdbg
//
//   //   ::file::path pathNetworkPayload = file()->dropbox_info_network_payload();
//
//   //   __check_refdbg
//
//   //   if (!file()->exists(pathNetworkPayload))
//   //   {
//
//   //      if (platform()->is_desktop_system())
//   //      {
//
//   //         auto pathHome = directory()->home();
//
//   //         auto pathTxt = pathHome / "dropbox.txt";
//
//   //         if (file()->exists(pathTxt))
//   //         {
//
//   //            string strPath = file()->safe_get_string(pathTxt);
//
//   //            strPath.trim();
//
//   //            if (strPath.has_character() && directory()->is(strPath))
//   //            {
//
//   //               m_pathDropbox = strPath;
//
//   //               m_bDropbox = true;
//
//   //            }
//
//   //         }
//
//   //      }
//   //      else
//   //      {
//
//   //         m_pathDropbox.empty();
//
//   //      }
//
//   //   }
//   //   else
//   //   {
//
//   //      __check_refdbg
//
//   //      string strNetworkPayload = file()->as_string(pathNetworkPayload);
//
//   //      __check_refdbg
//
//   //      {
//
//   //         ::property_set set;
//
//   //         __check_refdbg
//
//   //         set.parse_network_payload(strNetworkPayload);
//
//   //         __check_refdbg
//
//   //         m_pathDropbox = set["personal"]["path"];
//
//   //      }
//
//   //      __check_refdbg
//
//   //      if (directory()->is(m_pathDropbox))
//   //      {
//
//   //         m_bDropbox = true;
//
//   //      }
//
//   //      __check_refdbg
//
//   //   }
//
//   //   __check_refdbg
//
//   //   m_bDropboxCalculated = true;
//
//   //}
//
//
//   ::file::path file_context::dropbox_info_network_payload()
//   {
//
//      ::file::path pathNetworkPayload;
//
//      pathNetworkPayload = directory_system()->user_appdata_local() / "Dropbox/info" NETWORK_PAYLOAD_DEFAULT_EXTENSION;
//
//      return pathNetworkPayload;
//
//   }
//
//
//   ::file::path file_context::dropbox_client()
//   {
//
//      auto pathClientFolder = directory()->dropbox_client();
//
//      if (pathClientFolder.is_empty() || !directory()->is(pathClientFolder))
//      {
//
//         return {};
//
//      }
//
//      return pathClientFolder / "Dropbox.exe";
//
//   }
//


::file::path folder::dropbox_info_network_payload()
{


#ifdef WINDOWS_DESKTOP

      ::file::path pathNetworkPayload;

   pathNetworkPayload = directory_system()->user_appdata_local() / "Dropbox/info" NETWORK_PAYLOAD_DEFAULT_EXTENSION;

      return pathNetworkPayload;

#elif defined(LINUX)


      ::file::path pathNetworkPayload;

      auto psystem = system();

      auto pacmedir = psystem->m_pdirectorysystem;

      pathNetworkPayload = pacmedir->home() / ".dropbox/info.json";

      return pathNetworkPayload;


#else


   ::file::path pathNetworkPayload;

   pathNetworkPayload = directory_system()->home() / ".dropbox/info" NETWORK_PAYLOAD_DEFAULT_EXTENSION;

   return pathNetworkPayload;

#endif

}


::string folder::protocol()
{


   return "dropbox";


}

} // namespace fs_raw_folder_protocol_dropbox



