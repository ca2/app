// Created by camilo on 2021-12-17 21:01 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "application_build_helper.h"
#include "acme/platform/scoped_restore.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/operating_system/process.h"
#include "acme/platform/node.h"


void get_root_and_item(string& strRoot, string& strItem, const char* pszFolder);


namespace application_build_helper
{


   void application_build_helper::package()
   {

      auto pathFolder = m_pathFolder;

      ::file::path pathApplicationTxt;

      pathApplicationTxt = pathFolder / "application.txt";

      if (!file_system()->exists(pathApplicationTxt))
      {

         throw ::exception(error_failed, "application.txt doesn't exist");

      }

      //      if (m_strProjectName.has_character())
      //      {
      //
      //         if (m_strProjectName.case_insensitive_begins("shared_") || m_strProjectName.case_insensitive_begins("static_"))
      //         {
      //
      //            throw ::exception(error_failed, "application.txt at shared_* or static_* folder");
      //
      //         }
      //
      //      }

      //      if(m_strProjectId.contains("just_message_box"))
      //      {
      //
      //         ::output_debug_string("just_message_box");
      //
      //      }

      ::file::path pathZip;

      ::file::path pathBinaries;

      ::string strZip;

#ifdef WINDOWS

      //pathZip = "C:/store/windows/" + m_strUnderscoreAppId + ".zip";

      pathZip = "C:/store/windows/" + m_strApplication + ".zip";

      pathBinaries = m_pathBaseDir / "time-windows/x64/Release";

      strZip = pathZip.windows_path();

#else

      //pathZip = "/store/" + m_strSlashedOperatingSystem + "/" + m_strUnderscoreAppId + ".zip";

      pathZip = directory_system()->home() / "store" / m_strSlashedOperatingSystem / (m_strApplication + ".zip");

      pathBinaries = m_pathBaseDir + "/cmake-build-release/output";

      strZip = pathZip;

#endif

      auto pathZipFolder = pathZip.folder();

      directory_system()->create(pathZipFolder);

      ::file::path pathPackageList;

      pathPackageList = m_pathFolder / "operating_system" / m_strSlashedOperatingSystem / "_packages.txt";

      string strInput = file_system()->as_string(pathPackageList);

      string_array stra;

      stra.add_lines(strInput, false);

      directory_system()->change_current(pathBinaries);

      int iAdding = 0;

      int iDeleting = 0;

      int iArchiveIsCurrent = 0;

      auto functionTrace = [&](enum_trace_level etracelevel, const ::scoped_string& str)
      {

         auto trimmed = str().trim();

         if (trimmed.case_insensitive_begins("adding:"))
         {

            iAdding++;

         }
         else if (trimmed.case_insensitive_begins("deleting:"))
         {

            iDeleting++;

         }
         else if (trimmed.case_insensitive_begins("archive is current"))
         {

            iArchiveIsCurrent++;

         }

      };

      ::file::path pathZipExe;

      ::string strExecutable;

#ifdef WINDOWS

      pathZipExe = "\"C:/operating_system/tool-windows/bin/zip.exe\"";

      strExecutable = pathZipExe.windows_path();

#else

      pathZipExe = "zip";

      strExecutable = pathZipExe;

#endif

      bool bFirst = true;

      string strCmd = strExecutable + " -FS \"" + strZip + "\"";

      for (auto& strLine : stra)
      {

         strLine.trim();

         if (strLine.has_character())
         {

            string_array straMatter;

            straMatter.explode("/", strLine);

            if (straMatter.get_size() == 2 || straMatter.get_size() == 3)
            {

               string strItem = straMatter.last();

               if (bFirst)
               {

                  {

#ifdef WINDOWS

                     string strName = "shared_" + strItem + ".exe";

#else

                     string strName = "_" + strItem;

#endif

                     ::file::path pathItem = pathBinaries / strName;

                     if (!file_system()->exists(pathItem))
                     {

                        ::string strMessage;

                        strMessage.format("File doesn't exist: %s", strName.c_str());

                        throw ::exception(error_failed, strMessage);

//
//                        //::string strMessage;
//
//                        //strMessage.format("File doesn't exist: %s", strName.c_str());
//
//                        //throw ::exception(error_file_not_found, strMessage);
//                        fprintf(stderr, "%s", strMessage.c_str());
//
//                        m_estatus = error_failed;
//

                     }

                     strCmd += " \"" + strName + "\"";

                  }

                  bFirst = false;

               }

               if (!strItem.case_insensitive_equals("none"))
               {

#ifdef WINDOWS

                  string strName = strItem + ".dll";

#else

                  string strName = "lib" + strItem + ".so";

#endif

                  ::file::path pathItem = pathBinaries / strName;

                  if (!file_system()->exists(pathItem))
                  {

                     ::string strMessage;

                     strMessage.format("File doesn't exist: %s", strName.c_str());

                     fprintf(stderr, "%s", strMessage.c_str());

                     throw ::exception(error_failed, strMessage);

                     //throw ::exception(error_file_not_found, strMessage);
                     //fprintf(stderr, "%s", strMessage.c_str());

                     //m_estatus = error_failed;

               }

                  strCmd += " \"" + strName + "\"";

            }

         }

      }

   }

      ::string_array straOutput;

      int iExitCode = acmenode()->command_system(strCmd, functionTrace);

      if (iExitCode != 0)
      {

         throw ::exception(error_file_not_found, "failed to zip");

      }
      else if (iAdding > 0 || iDeleting > 0)
      {

         ::string_array straStatus;

         if (iAdding > 0) straStatus.append_format("%d added", iAdding);

         if (iDeleting > 0) straStatus.append_format("%d deleted", iDeleting);

         m_strLog.format(" %s", straStatus.implode(" ").c_str());

      }
      else if (iArchiveIsCurrent)
      {

         //printf(" OK!!");

      }

}


} // namespace application_build_helper



