//
// Created by camilo on 12/12/21  05:21 PM <3ThomasBorregaardSorensen!!
//

#include "framework.h"

#include <sys/stat.h>


namespace app_core_build
{


   app_build::app_build()
   {

   }


   app_build::~app_build()
   {

   }


   ::e_status app_build::prepare_build()
   {

      auto pini = m_pcontext->m_papexcontext->file().get_ini("/etc/os-release");

      m_strDistro = (*pini)["ID"];
      m_strDesktopEnvironment = (*pini)["VARIANT_ID"];
      m_strVersion = (*pini)["VERSION_ID"];

      return ::success;

   }


   ::e_status app_build::do_build()
   {

      bool bTimeout = false;

      //::parallelization::set_priority(::e_priority_highest);

      //process->prop("inherit") = false;

      ::file::path pathBaseDir = m_psystem->m_pacmedir->home();

      ::file::path pathBuildDir = pathBaseDir / "build" / m_strDistro / m_strDesktopEnvironment;

      m_psystem->m_pacmedir->create(pathBuildDir);

      chdir(pathBuildDir);

      {

         string strConfigure = "cmake configure " + pathBaseDir + "/solution/basis";


         m_psystem->m_pacmefile->put_contents("/home/camilo/configure_build.sh", strConfigure);

         chmod("/home/camilo/configure_build.sh", 0777);

         run_command("/usr/bin/bash -c /home/camilo/configure_build.sh");

      }

      {

         string strCmakeBuild = "cmake --build " + pathBuildDir + " -- -j 8";

         m_psystem->m_pacmefile->put_contents("/home/camilo/cmake_build.sh", strCmakeBuild);

         chmod("/home/camilo/cmake_build.sh", 0777);

         run_command("/usr/bin/bash -c /home/camilo/cmake_build.sh");

      }
      //m_straLine.add(strCompiler);


      return ::success;

   }



} // namespace app_core_build



