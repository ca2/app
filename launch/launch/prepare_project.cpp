// Created by camilo on 2021-12-17 21:01 BRT <3ThomasBorregaardS�rensen!!
#include "framework.h"
#include "application_build_helper.h"
#include "application.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/operating_system/process.h"
#include "acme/platform/node.h"
#include "acme/primitive/string/str.h"
//#include "aura/_defer.h"


namespace application_build_helper
{


   void application_build_helper::prepare_project()
   {

      auto pathBaseDeployIgnore = m_pathGroup / ".deployignore";

      auto straIgnoreRoot = acmefile()->lines(pathBaseDeployIgnore);

      if (straIgnoreRoot.case_insensitive_contains(m_strRoot))
      {

         return;

      }

      auto pathRootDeployIgnore = m_pathGroup / m_strRoot / ".deployignore";

      auto straIgnoreItem = acmefile()->lines(pathRootDeployIgnore);

      if (straIgnoreItem.case_insensitive_contains(m_strItem))
      {

         return;

      }

      if (m_strItem.case_insensitive_order("include") == 0)
      {

         return;

      }

      if (m_strItem.begins("_"))
      {

         return;

      }

#ifdef WINDOWS_DESKTOP

      if (m_strRoot == "app" && m_strItem == "acme")
      {

         string_array straOutput;

         int iExitCode = 0;

         string_array straCommand;

         auto pathBeforeBase = m_pathBaseDir - 1;

         auto pathStorage = pathBeforeBase / "operating_system/storage-windows";

         auto pathPlatformConfiguration = pathStorage / m_strBuildPlatform / m_strBuildConfiguration;

         string strPlatformConfiguration = pathPlatformConfiguration;

         strPlatformConfiguration.find_replace("/", "\\");

         auto pathOutDir = m_pathBaseDir / "time-windows";

         pathOutDir = pathOutDir / m_strBuildPlatform / m_strBuildConfiguration;

         string strOutDir = pathOutDir;

         strOutDir.find_replace("/", "\\");

         if (!m_strBuildConfiguration.case_insensitive_contains("static"))
         {

            m_papplication->folder_copy_if_newer(pathOutDir, pathPlatformConfiguration / "binary", { "*.*" }, e_depth_none, [&](auto, auto& str) { straOutput.add(str); printf("%s\n", str.c_str()); });

            m_papplication->folder_copy_if_newer(pathOutDir, pathPlatformConfiguration / "third/binary", { "*.*"}, e_depth_none, [&](auto, auto& str) { straOutput.add(str); printf("%s\n", str.c_str()); });

            //m_papplication->folder_copy_if_newer(pathOutDir, pathPlatformConfiguration / "*.pdb", {"*.pdb"}, e_depth_none, [&](auto, auto& str) { straOutput.add(str); printf("%s\n", str.c_str()); });

            //straCommand.add("cmd.exe /c xcopy /Y \"" + strPlatformConfiguration + "\\binary\\*.*\" \"" + strOutDir + "\"");
            //straCommand.add("cmd.exe /c xcopy /Y \"" + strPlatformConfiguration + "\\third\\binary\\*.*\" \"" + strOutDir + "\"");
            //straCommand.add("cmd.exe /c xcopy /Y \"" + strPlatformConfiguration + "\\library\\*.pdb\" \"" + strOutDir + "\"");

         }

         //for (auto & strCommand : straCommand)
         //{

         //   acmenode()->command_system(strCommand, [&](auto, auto& str) { straOutput.add(str); printf("%s\n", str.c_str()); });

         //}

      }

#endif

      generate_deployment_rc();

      if (m_strItem.case_insensitive_order("deployment") != 0)
      {

#ifdef WINDOWS_DESKTOP

         ::file::path pathResource = m_pathFolder / "resource.h";

         if (!file_exists(pathResource))
         {

            ::file::path pathResourceTemplate = m_pathOperatingSystem / ("operating_system-" PLATFORM_STRING) / "deployment/resource1.h";

            acmefile()->copy(pathResource, pathResourceTemplate, false);

         }

#endif

         ::file::path pathApplicationBuildHelperInput = m_pathFolder / "application_build_helper_input.txt";

         if (!file_exists(pathApplicationBuildHelperInput))
         {

            acmefile()->ensure_exists(pathApplicationBuildHelperInput);

         }

         ::file::path pathApplicationBuildHelperOutput = m_pathFolder / "application_build_helper_output.txt";

         if (!file_exists(pathApplicationBuildHelperOutput))
         {

            acmefile()->ensure_exists(pathApplicationBuildHelperOutput);

         }

      }

   }


   void application_build_helper::generate_deployment_rc()
   {

      if (m_strItem.case_insensitive_order("deployment") != 0)
      {

         ::file::path pathDeploymentRcTemplate = m_pathOperatingSystem / ("operating_system-" PLATFORM_STRING) / "deployment/deployment_rc.txt";

         string strDeploymentRcTemplate = acmefile()->as_string(pathDeploymentRcTemplate);

         string strDeploymentRc = ::str::find_replace("%ROOTNAME%", m_strRoot, strDeploymentRcTemplate);

         strDeploymentRc.find_replace("%PROJECTNAME%", m_strItem);

         ::file::path pathDeploymentRc = m_pathFolder / "deployment.rc";

         acmefile()->put_contents(pathDeploymentRc, strDeploymentRc);

      }

   } 


} // namespace application_build_helper



