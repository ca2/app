//
// Created by camilo on 12/12/21  05:21 PM <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "build_windows.h"
#include <sys/stat.h>
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/node.h"


namespace windows
{


   build::build()
   {

   }


   build::~build()
   {

   }


   void build::prepare_build()
   {

      //auto pini = file()->get_ini("/etc/os-release");

      //m_strDistro = (*pini)["ID"];
      //m_strDesktopEnvironment = (*pini)["VARIANT_ID"];
      //m_strVersion = (*pini)["VERSION_ID"];

      ////return ::success;

   }


   void build::do_build()
   {

      ::string strPlatform = "x64";

      ::string strConfiguration = "Release";

      ::string strDevEnv = "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\IDE\\devenv.exe";

      ::string strSolution = "C:\\stage\\operating-system\\operating-system-windows\\_solution\\all.sln";

      ::string strOperationSwitch = "/Build";

      ::string strCommand;

      strCommand.format("\"%s\" \"%s\" %s %s|%s",
         strDevEnv.c_str(),
         strSolution.c_str(),
         strOperationSwitch.c_str(),
         strConfiguration.c_str(),
         strPlatform.c_str());

      ::i32 iExitCode = 0;

      acmenode()->command_system(m_straLine, iExitCode, strCommand, e_command_system_inline_log);

      //bool bTimeout = false;

      //::file::path pathBaseDir = acmedirectory()->home();

      //::file::path pathBuildDir = pathBaseDir / "build" / m_strDistro / m_strDesktopEnvironment;

      //acmedirectory()->create(pathBuildDir);

      //chdir(pathBuildDir);

      //{

      //   string strConfigure = "cmake configure " + pathBaseDir + "/solution/basis";

      //   acmefile()->put_contents("/home/camilo/configure_build.sh", strConfigure);

      //   chmod("/home/camilo/configure_build.sh", 0777);

      //   run_command("/usr/bin/bash -c /home/camilo/configure_build.sh");

      //}

      //{

      //   string strCmakeBuild = "cmake --build " + pathBuildDir + " -- -j 8";

      //   acmefile()->put_contents("/home/camilo/cmake_build.sh", strCmakeBuild);

      //   chmod("/home/camilo/cmake_build.sh", 0777);

      //   run_command("/usr/bin/bash -c /home/camilo/cmake_build.sh");

      //}

      //return ::success;

   }


} // namespace windows



