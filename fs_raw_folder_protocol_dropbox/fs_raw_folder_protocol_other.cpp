// Created by camilo on 2024-07-03 03:09 ILoveYouThomasBorregaardSorensen!!
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



   void folder::on_initialize_particle()
   {

      ::fs::raw_folder::on_initialize_particle();

   }

   
   ::file::path folder::_base_folder_path()
   {

      return m_pathDropbox;

   }


   //::file::path folder::calculate_raw_folder_base_path()
   //{

   //   calculate_installed();

   //   return m_pathDropbox;

   //}


   void folder::calculate_installed()
   {

         m_bInstalled = false;

         m_pathDropbox.empty();

         m_bCalculatedInstalled = true;

         __check_refdbg

         ::file::path pathNetworkPayload = dropbox_info_network_payload();

         __check_refdbg

         if (!file()->exists(pathNetworkPayload))
         {

            if (::system()->is_desktop_system())
            {

               auto pathUserConfig = directory_system()->userconfig();

               auto pathTxt = pathUserConfig / "dropbox.txt";

               if (file()->exists(pathTxt))
               {

                  string strPath = file()->safe_get_string(pathTxt);

                  strPath.trim();

                  if (strPath.has_character() && directory()->is(strPath))
                  {

                     m_pathDropbox = strPath;

                     m_bInstalled = true;

                  }

               }

            }
            else
            {

               m_pathDropbox.empty();

            }

         }
         else
         {

            __check_refdbg

            string strNetworkPayload = file()->as_string(pathNetworkPayload);

            __check_refdbg

            {

               ::property_set set;

               __check_refdbg

               set.parse_network_payload(strNetworkPayload);

               __check_refdbg

                  m_pathDropbox = set["personal"]["path"];

            }

            __check_refdbg

            if (directory()->is(m_pathDropbox))
            {

               m_bInstalled = true;

            }

            __check_refdbg

         }

         __check_refdbg

         m_bCalculatedInstalled = true;


   }


   //::string folder::_dropbox(const ::scoped_string & scopedstr,
   //                               const ::function<void(const ::scoped_string&)> & callbackStatus)
   //{

   //   ::string str;

   //   int iTry = 0;

   //   while (true)
   //   {

   //      while (true)
   //      {

   //         defer_throttle_operation();

   //         auto pathFolder = local_folder_path();

   //         pathFolder.trim();

   //         if (pathFolder.has_character() && directory_system()->is(pathFolder))
   //         {

   //            iTry = 0;

   //            break;

   //         }

   //         node()->calculate_dropbox_installed();

   //         if (callbackStatus)
   //         {

   //            callbackStatus("Waiting for Dropbox folder " + pathFolder + " creation...");

   //         }

   //         iTry++;

   //         if (iTry > 8)
   //         {

   //            m_iLastExitCode = -1;

   //            m_iStableOkCount = 0;

   //            return {};

   //         }

   //      }

   //      directory_system()->change_current(local_folder_path());

   //      ::file::path pathHomeFolder = directory_system()->home();

   //      ::file::path pathDropboxBin = pathHomeFolder / "bin/dropbox";

   //      ::string strDropboxCommand(pathDropboxBin);

   //      str.empty();

   //      ::string strCommand;

   //      strCommand = strDropboxCommand + " " + scopedstr;

   //      m_iLastExitCode = node()->get_posix_shell_command_output(str, strCommand);

   //      if (m_iLastExitCode == 0)
   //      {

   //         m_iStableOkCount++;

   //      }
   //      else
   //      {

   //         m_iStableOkCount = 0;

   //         iTry++;

   //         if (iTry > 5)
   //         {

   //            callbackStatus(strCommand + " has failed too many times.");

   //            return {};

   //         }

   //         if (callbackStatus)
   //         {

   //            callbackStatus(strCommand + " has failed.");

   //         }

   //      }

   //      auto strError(str);

   //      strError.trim();

   //      ::string_array straError;

   //      straError.add_lines(strError);

   //      straError.erase_empty();

   //      if (straError.size() == 1)
   //      {

   //         if (strError.case_insensitive_contains("isn't running"))
   //         {

   //            if (callbackStatus)
   //            {

   //               callbackStatus("Dropbox daemon isn't running... Trying to start it...");

   //            }

   //            defer_start_daemon(callbackStatus);

   //            m_iStableOkCount = 0;

   //            if (m_iLastExitCode == 0)
   //            {

   //               m_iLastExitCode = -1;

   //            }

   //            iTry = 0;

   //         }
   //         else if (strError.case_insensitive_contains("respond"))
   //         {

   //            if (callbackStatus)
   //            {

   //               callbackStatus("Dropbox daemon isn't responding...");

   //            }

   //            m_iStableOkCount = 0;

   //            if (m_iLastExitCode == 0)
   //            {

   //               m_iLastExitCode = -1;

   //            }

   //            iTry = 0;

   //         }
   //         else
   //         {

   //            break;

   //         }

   //      }
   //      else
   //      {

   //         break;

   //      }

   //   }

   //   return str;

   //}


   //::string_array folder::_dropbox_lines(const ::scoped_string & scopedstr, const ::function < void(const ::scoped_string&) >& callbackStatus)
   //{

   //   auto str = _dropbox(scopedstr, callbackStatus);

   //   if(m_iLastExitCode != 0)
   //   {

   //      return {};

   //   }

   //   ::string_array stra;

   //   stra.add_lines(str);

   //   stra.trim();

   //   stra.erase_empty();

   //   return ::transfer(stra);

   //}


//   void folder::wait_folder_contains_files(const ::file::path& pathTargetFolder, const ::string_array& straName,
//                                                int iMinimumSize,
//                                                const ::function<void(const ::scoped_string&)>& callbackStatus)
//   {
//
//      if (callbackStatus)
//      {
//
//         callbackStatus(
//            //"Checking for "+pathSourceFile.name() + " at "+pathSourceFile.folder() + "... (index.txt should exist to continue installation with code...)");
//            "Checking for files at " + pathTargetFolder + "...");
//
//      }
//
//      while (true)
//      {
//
//         if (file_system()->exists(pathTargetFolder))
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
//      if (callbackStatus)
//      {
//
//         callbackStatus("Checking if " + pathTargetFolder + " has all files...");
//
//      }
//
//      ::string_array lines;
//
//      lines = straName;
//
//      directory_system()->change_current(pathTargetFolder);
//
//      while (true)
//      {
//
//         auto lines = _dropbox_lines("filestatus", callbackStatus);
//
//         bool bOk = true;
//
//         for (auto& line : lines)
//         {
//
//            //auto pszLine = line.c_str();
//
//            auto iFind = lines.case_insensitive_find_first_begins(line + ":");
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
//            auto dropboxLine = lines[iFind];
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
//            auto pathFile = pathTargetFolder / line;
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
//            if (iMinimumSize > 0)
//            {
//
//               auto iSize = file_system()->get_size(pathFile);
//
//               if (iSize < iMinimumSize)
//               {
//
//                  bOk = false;
//
//                  break;
//
//               }
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
//   }
//
//
//   void folder::wait_up_and_running(const ::function<void(const ::scoped_string&)>& callbackStatus)
//   {
//
//      m_iStableOkCount = 0;
//
//      while (::task_get_run())
//      {
//
//         if (callbackStatus)
//         {
//
//            callbackStatus("Waiting for Dropbox service to get up and running... please wait...");
//
//         }
//
//         auto stra = sync_exclusion_list(callbackStatus);
//
//         //auto stra = _dropbox_lines("exclude list", callbackStatus);
//
//         if (m_iStableOkCount >= 5)
//         {
//
//            break;
//
//         }
//
//      }
//
//   }
//
//
//   ::file::path folder::_cloud_ensure_file_txt_is_up_to_date_and_present(
//      const ::file::path& pathCloudFile, const ::function<void(const ::scoped_string&)>& callbackStatus)
//   {
//
//      ::file::path pathHomeFolder = directory_system()->home();
//
//      auto pathSource = m_pathProtocol / pathCloudFile;
//
//      auto pathSourceFolder = pathSource.folder();
//
//      auto pathSourceLocalFolder = local_path(pathSourceFolder);
//
//      while (true)
//      {
//
//         if (callbackStatus)
//         {
//            callbackStatus("Checking for \"" + pathSourceLocalFolder +
//               "\" Cloud folder... (" + ::string(pathCloudFile.name()) +
//               " should exist to continue installation with code...)");
//         }
//
//         if(directory_system()->is(pathSourceLocalFolder))
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
//      directory_system()->change_current(pathSourceLocalFolder);
//
//      auto pathLocalSource = local_path(pathSource);
//
//      while (true)
//      {
//
//         if (callbackStatus)
//         {
//            callbackStatus("Checking for " + ::string(pathCloudFile.name()) + " at \"" + pathSourceFolder +
//               "\" Cloud folder... (" + ::string(pathCloudFile.name()) +
//               " should exist to continue installation with code...)");
//         }
//
//         if (file_system()->exists(pathLocalSource))
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
//      ::string_array lines;
//
//      lines.add(pathCloudFile.name());
//
//      while (true)
//      {
//
//         auto stra = _dropbox_lines("filestatus", callbackStatus);
//
//         bool bOk = true;
//
//         for (auto& line : lines)
//         {
//
//            auto iFind = stra.case_insensitive_find_first_begins(line + ":");
//
//            if (iFind < 0)
//            {
//               bOk = false;
//
//               break;
//            }
//
//            auto dropboxLine = stra[iFind];
//
//            if (!dropboxLine.case_insensitive_ends("up to date"))
//            {
//               bOk = false;
//
//               break;
//            }
//
//            auto pathFile = pathSourceLocalFolder / line;
//
//            if (!file_system()->exists(pathFile))
//            {
//               bOk = false;
//
//               break;
//            }
//
//            if (file_system()->as_string(pathFile).trimmed().is_empty())
//            {
//               bOk = false;
//
//               break;
//            }
//         }
//
//         if (bOk)
//         {
//            break;
//         }
//      }
//
//      return pathSource;
//   }
//
//
//   ::file::path folder::_cloud_ensure_files_in_file_txt_are_up_to_date_and_present(
//      const ::file::path& pathCloudFile, const ::scoped_string& scopedstrFileExtension,
//      int iMinimumFileSize, const ::function<void(const ::scoped_string&)>& callbackStatus)
//   {
//
//      ::string_array lines;
//
//      ::file::path pathTarget;
//
//      ::file::path pathSource;
//
//      while (true)
//      {
//
//         if (callbackStatus)
//         {
//
//            callbackStatus("Checking if all files in \""+pathCloudFile+"\" listing are up-to-date and present...");
//
//         }
//
//         lines = _cloud_get_file_txt_lines(pathCloudFile, true, &pathTarget, &pathSource);
//
//         if (lines.get_size() >= 7)
//         {
//
//            /// if file listing is empty it should contain empty lines like this
//            ///
//            ///
//            ///
//            /// (empty)
//            ///
//            ///
//            ///
//            ///
//            ///
//            ///
//
//            break;
//
//         }
//
//      }
//
//      lines.trim();
//
//      lines.erase_empty();
//
//      ::string strEnds;
//
//      strEnds = "." + scopedstrFileExtension;
//
//      //lines.erase_lines_not_ending(".ttf");
//      lines.predicate_erase([strEnds](auto& str)
//      {
//
//         return !str.case_insensitive_ends(strEnds);
//
//      });
//
//      _cloud_ensure_files_are_up_to_date_and_present(pathCloudFile.folder(), lines,
//         iMinimumFileSize, callbackStatus);
//
//      return pathTarget;
//
//   }
//
//
//   void folder::_cloud_ensure_files_are_up_to_date_and_present(
//   const ::file::path& pathFolder, const ::string_array & stra,
//   int iMinimumFileSize, const ::function<void(const ::scoped_string&)>& callbackStatus)
//   {
//
//      if(stra.is_empty())
//      {
//
//         return;
//
//      }
//
//      while (true)
//      {
//
//         if (callbackStatus)
//         {
//
//            callbackStatus("Checking if files are up-to-date and present...");
//
//         }
//
//         auto lines = _dropbox_lines("filestatus", callbackStatus);
//
//         bool bOk = true;
//
//         for (auto& str : stra)
//         {
//
//            if (callbackStatus)
//            {
//
//               callbackStatus("Checking if file \""+str+"\" is up-to-date and present...");
//
//            }
//
//            auto iFind = lines.case_insensitive_find_first_begins(str + ":");
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
//            auto dropboxLine = lines[iFind];
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
//            auto pathFile = pathFolder / str;
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
//            if (iMinimumFileSize > 0 && file_system()->get_size(pathFile) < iMinimumFileSize)
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
//   }
//
//
////   void folder::start_daemon(const ::function<void(const ::scoped_string&)>& callbackStatus)
////   {
////
////      auto pathHomeFolder = directory_system()->home();
////
////      node()->detached_command(pathHomeFolder / ".dropbox-dist/dropboxd &", {});
////
////   }
//
//
//   ::string_array folder::ls(const ::file::path& path, const ::function<void(const ::scoped_string&)>& callbackStatus)
//   {
//
//      ::string str;
//
//      if (path.is_empty())
//      {
//
//         str = _dropbox("ls", callbackStatus);
//
//      }
//      else
//      {
//
//         str = _dropbox("ls \"" + path + "\"", callbackStatus);
//
//      }
//
//      ::string_array stra;
//
//      stra.add_lines(str);
//
//      stra.trim();
//
//      stra.erase_empty();
//
//      return ::transfer(stra);
//
//   }
//
//
//   ::string_array folder::ls_folder(const ::file::path& path, const ::function<void(const ::scoped_string&)>& callbackStatus)
//   {
//
//      auto stra = ls(path, callbackStatus);
//
//      auto pathFolder = local_folder_path() / path;
//
//      stra.predicate_erase([this, &pathFolder](auto& str) { return !directory_system()->is(pathFolder / str); });
//
//      return ::transfer(stra);
//
//   }
//
//
////   void folder::sync_exclude(const string_array& straExclude, const ::function<void(const ::scoped_string&)>& callbackStatus)
////   {
////
////      ::string_array stra(straExclude);
////
////      stra.predicate_each([](auto& str) { str.double_quote(); });
////
////      auto strExclude = stra.implode(" ");
////
////      auto strExcludeOutput = _dropbox("exclude add " + strExclude, callbackStatus);
////
////   }
////
////
////   void folder::sync_reinclude(const string_array& straInclude, const ::function<void(const ::scoped_string&)>& callbackStatus)
////   {
////
////      ::string_array stra(straInclude);
////
////      stra.predicate_each([](auto& str) { str.double_quote(); });
////
////      auto strInclude = stra.implode(" ");
////
////      auto strIncludeOutput = _dropbox("exclude remove " + strInclude, callbackStatus);
////
////   }
////
////
////   string_array folder::sync_exclusion_list(const ::function<void(const ::scoped_string&)>& callbackStatus)
////   {
////
////      auto stra = _dropbox_lines("exclude list", callbackStatus);
////
////      if (stra.size() == 1 && stra.first().case_insensitive_contains("no directories"))
////      {
////
////         return {};
////
////      }
////
////      if(stra.size() >= 2 && stra.first().trimmed().case_insensitive_equals("excluded:"))
////      {
////
////         stra.erase_first();
////
////      }
////
////      return ::transfer(stra);
////
////   }
//
//
//   bool folder::_cloud_defer_check_file_txt(::file::path& pathTarget, const ::file::path& pathCloudFile,
//                                                 bool bForce, ::file::path* ppathSource,
//                                                 const ::function<void(const ::scoped_string&)>& callbackStatus)
//   {
//
//      auto pathCloudFolder = pathCloudFile.folder();
//
//      ::file::path pathSourceFolder = m_pathProtocol / pathCloudFolder;
//
//      auto pathSource = m_pathProtocol / pathCloudFile;
//
//      auto pathApp = directory_system()->home() / ".config/integration/code";
//
//      auto pathTargetFolder = pathApp / pathCloudFolder;
//
//      pathTarget = pathApp / pathCloudFile;
//
//      if (bForce || !file_system()->exists(pathTarget) || file_system()->modification_time(pathTarget).elapsed() >=
//         12_hours)
//      {
//
//         auto pathLocalSource = _cloud_ensure_file_txt_is_up_to_date_and_present(pathSource, callbackStatus);
//
//         file_system()->copy(pathTarget, pathSource, true);
//
//         if (ppathSource)
//         {
//
//            *ppathSource = pathLocalSource;
//
//         }
//
//         return true;
//
//      }
//
//      return false;
//
//   }
//
//
//   ::string_array folder::_cloud_get_file_txt_lines(const ::file::path& pathCloudFile, bool bForce,
//                                                         ::file::path* ppathTarget, ::file::path* ppathSource,
//                                                         const ::function<void(const ::scoped_string&)>& callbackStatus)
//   {
//
//      ::file::path pathTarget;
//
//      if (!_cloud_defer_check_file_txt(pathTarget, pathCloudFile, bForce, ppathSource))
//      {
//
//         return {};
//
//      }
//
//      auto lines = file_system()->lines(pathTarget);
//
//      lines.trim();
//
//      lines.erase_empty();
//
//      lines.erase_duplicates();
//
//      if (ppathTarget)
//      {
//
//         *ppathTarget = pathTarget;
//
//      }
//
//      return lines;
//
//   }
//
//
//   void folder::on_initialize_particle()
//   {
//
//      ::fs::raw_folder::on_initialize_particle();
//
//
//   }
//
//
//   bool folder::has_operation_error()
//   {
//
//      return m_iLastExitCode != 0;
//
//   }


} // namespace fs_raw_folder_protocol_dropbox
