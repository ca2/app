//
// Created by camilo on 12/12/21  05:21 PM <3ThomasBorregaardSorensen!!
//

#include "framework.h"

#include <sys/stat.h>
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"

namespace linux
{


   build::build()
   {

   }


   build::~build()
   {

   }


   void build::prepare_build()
   {

      auto pini = file()->get_ini("/etc/os-release");

      m_strDistro = (*pini)["ID"];
      m_strDesktopEnvironment = (*pini)["VARIANT_ID"];
      m_strVersion = (*pini)["VERSION_ID"];

      //return ::success;

   }


   void build::do_build()
   {

      bool bTimeout = false;

      ::file::path pathBaseDir = directory_system()->home();

      ::file::path pathBuildDir = pathBaseDir / "build" / m_strDistro / m_strDesktopEnvironment;

      directory_system()->create(pathBuildDir);

      chdir(pathBuildDir);

      {

         string strConfigure = "cmake configure " + pathBaseDir + "/solution/basis";

         file_system()->put_contents("/home/camilo/configure_build.sh", strConfigure);

         chmod("/home/camilo/configure_build.sh", 0777);

         run_command("/usr/bin/bash -c /home/camilo/configure_build.sh");

      }

      {

         string strCmakeBuild = "cmake --build " + pathBuildDir + " -- -j 8";

         file_system()->put_contents("/home/camilo/cmake_build.sh", strCmakeBuild);

         chmod("/home/camilo/cmake_build.sh", 0777);

         run_command("/usr/bin/bash -c /home/camilo/cmake_build.sh");

      }

      //return ::success;

   }


} // namespace app_build



