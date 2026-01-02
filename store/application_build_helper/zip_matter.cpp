//
// Created by camilo on 06/03/23.
//
#include "framework.h"
////#include "acme/exception/exception.h"
#include "application_build_helper.h"
#include "acme/filesystem/file/folder.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/listing.h"
//#include "acme/filesystem/filesystem/file_context.h"
#include "acme/operating_system/process.h"
#include "acme/platform/application.h"
#include "acme/platform/ini.h"
#include "acme/platform/node.h"
#include "acme/prototype/string/str.h"
#include "acme/platform/system.h"
#ifdef WINDOWS_DESTKOP
#include <direct.h>
#endif
#include "application_build_helper.h"


namespace application_build_helper
{


   void application_build_helper::zip_matter()
   {

      //printf("zip_matter");

      ::file::path pathZip = m_pathFolder / "_matter.zip";

      ::file::path pathMatter = m_pathFolder / "matter.txt";

      //::file::path pathMatterZipList = m_pathFolder + "/_matter-zip-list_base.txt";

      //auto estatus = file_system()->ensure_exists(pathMatter);

      file_system()->ensure_exists(pathMatter);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      auto strInput = file_system()->as_string(pathMatter);

      /*if(!strInput)
      {

         return strInput;

      }*/

      string strZip = pathZip;

      strZip.find_replace("\\", "/");

      string_array_base stra;

      stra.add_lines(strInput, false);

      ::file::path pathOutput = m_pathFolder - 2;

      directory_system()->change_current(pathOutput);

      if (acmeapplication()->m_bVerbose)
      {

         printf("current directory: %s\n", pathOutput.c_str());

      }

      {

         auto pwriter = file_system()->get_file(pathZip,
            ::file::e_open_defer_create_directory
            | ::file::e_open_binary 
            | ::file::e_open_write 
            | ::file::e_open_create);

         auto pfactoryFolderZip = acmesystem()->factory("folder", "zip");

         ::pointer < ::folder > pfolder;

         pfactoryFolderZip->øconstruct(this, pfolder);

         pfolder->open_for_writing(pwriter);
         //bool bFirst = true;

         ::file::path pathZipExe;

#ifdef WINDOWS

         //pathZipExe = (m_pathFolder - 3) / "operating_system/tool-windows/bin/zip";

         pathZipExe = "\"C:/operating_system/tool-windows/bin/zip.exe\"";

#else

         pathZipExe = "zip";

#endif

         //int iAdding = 0;

         //int iDeleting = 0;

         //int iExitCode = 0;

//         auto functionTrace = [&](enum_trace_level etracelevel, const ::scoped_string& str)
//         {
//
//            auto trimmed = str().trim();
//
//            if (trimmed.case_insensitive_begins("adding:"))
//            {
//
//               iAdding++;
//
//            }
//            else if (trimmed.case_insensitive_begins("deleting:"))
//            {
//
//               iDeleting++;
//
//            }
//
//            if (acmeapplication()->m_bVerbose)
//            {
//
//               std_inline_log()(etracelevel, str);
//
//            }
//
//         };

         string strZipExe = pathZipExe;

         string strFolders;

         ::file::path_array_base patha;

         ::file_pointer preader;

         for (auto& strLine : stra)
         {

            strLine.trim();

            if (acmeapplication()->m_bVerbose)
            {

               printf("zip_matter line: %s\n", strLine.c_str());

            }

            if (strLine.contains(">>>>>"))
            {

               throw ::exception(error_parsing, "revision marks in \"" + pathMatter + "\"");

            }

            if (strLine.has_character())
            {

               string_array_base straMatter;

               straMatter.explode("/", strLine);

               if (straMatter.get_size() == 2)
               {

                  ::string strFolder = straMatter[0] + "/_matter/" + straMatter[1];

                  string_array_base straOutput;

                  ::file::listing_base listing;

                  auto pathFolder = pathOutput / strFolder;

                  listing.set_file_listing(pathFolder, ::e_depth_recursively);

                  directory_system()->enumerate(listing);

                  for (auto& p : listing)
                  {

                     auto pathItem = p;

                     if(pathItem.contains("Thomas"))
                     {

                        //printf("%s", pathItem.c_str());

                     }

                     pathItem.case_insensitive_begins_eat(pathOutput);

                     pathItem.trim_left("/");

                     if(acmeapplication()->m_bVerbose)
                     {

                        printf("%s\n", pathItem.c_str());

                     }

                     if (patha.add_unique(pathItem) >= 0)
                     {

                        if(acmeapplication()->m_bVerbose)
                        {

                           if (pathItem.case_insensitive_ends("frame.network_payload"))
                           {

                              information("test");

                           }

                        }

                        auto path = pathOutput / pathItem;

                        if (file_system()->exists(path))
                        {

                           preader = file_system()->get_file(path, ::file::e_open_read | ::file::e_open_binary);

                           pfolder->add_file(pathItem, preader);

                        }

                     }

                  }

               }

            }

         }

      }

//      file_system()->put_contents(pathMatterZipList, patha.implode("\n"));
//      //if (bFirst)
//      {
//
//         auto strCurrentDirectory = directory_system()->current();
//
//         ::string strCommandLine = strZipExe + " -r \"" + strZip + "\" -@";
//
//         if(acmeapplication()->m_bVerbose)
//         {
//
//            printf("command line : %s\n", strCommandLine.c_str());
//
//         }
//
//         iExitCode = acmenode()->command_system(strCommandLine, patha.implode("\n"), functionTrace);
//
//      }



#ifdef WINDOWS_DESKTOP

      _wchdir(wstring("C:\\"));

#else

//      {
//
//         ::file::path pathHome = getenv("HOME");
//
//         directory_system()->change_current(pathHome);
//
//      }

#endif

      ///iExitCode = acmenode()->command_system(strZipExe + " -r \"" + pathZip + "\" sensitive/sensitive/api/*", functionTrace);

//      if(iAdding > 0 || iDeleting > 0)
//      {
//
//         ::string_array_base straStatus;
//
//         if (iAdding > 0) straStatus.append_format("%d added", iAdding);
//
//         if (iDeleting > 0) straStatus.append_format("%d deleted", iDeleting);
//
//         printf(" %s", straStatus.implode(" ").c_str());
//
//      }

   }


} // namespace application_build_helper



